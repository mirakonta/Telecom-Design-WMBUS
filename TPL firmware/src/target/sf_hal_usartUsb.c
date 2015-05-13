#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_usartUsb.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for USART USB implementations.

  @addtogroup WMBUS_HAL_UART
  
  Recently added against the background of EZR devices is a driver for using the
  USART-USB interface: `/src/target/`sf_hal_usartUsb.c

*/
/**@{*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\hal\wmbus_hal_uart.h"
#include "descriptors.h"

/*! EFM32LIB includes */
#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_usb.h"

/*==============================================================================
                            CONFIGURATION
==============================================================================*/
/*! Setup UART interface */
#define USB_RX_BUF_SIZ               USB_FS_BULK_EP_MAXSIZE
#define USB_TX_BUF_SIZ               USB_BUFFER_TX_LEN

/*! Sets the length of the Rx ringbuffer. */
#define UART_BUFFER_RX_LEN           300U
/*! Sets the length of the Tx ringbuffer. */
#define USB_BUFFER_TX_LEN            300U


/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/
static int  loc_LineCodingReceived(USB_Status_TypeDef status,
                               uint32_t xferred,
                               uint32_t remaining);
static int  loc_SetupCmd(const USB_Setup_TypeDef *setup);
static void loc_StateChange(USBD_State_TypeDef oldState,
                        USBD_State_TypeDef newState);
static int  loc_UsbDataReceived(USB_Status_TypeDef status, uint32_t xferred,
                            uint32_t remaining);

/*==============================================================================
                          TYPEDEFS
==============================================================================*/

/* The serial port LINE CODING data structure, used to carry information  */
/* about serial port baudrate, parity etc. between host and device.       */
EFM32_PACK_START(1)
typedef struct
{
  uint32_t dwDTERate;               /** Baudrate                            */
  uint8_t  bCharFormat;             /** Stop bits, 0=1 1=1.5 2=2            */
  uint8_t  bParityType;             /** 0=None 1=Odd 2=Even 3=Mark 4=Space  */
  uint8_t  bDataBits;               /** 5, 6, 7, 8 or 16                    */
  uint8_t  dummy;                   /** To ensure size is a multiple of 4 bytes */
} __attribute__ ((packed)) cdcLineCoding_TypeDef;
EFM32_PACK_END()
/*==============================================================================
                            VARIABLES
==============================================================================*/
/*! Input ring buffer. */
volatile uint8_t gc_uart_bufferRx[UART_BUFFER_RX_LEN];
/*! Pointer to the Rx ring buffer's current write position */
volatile uint8_t *gpc_uart_bufferRxWrite;
/*! Pointer to the Rx ring buffer's current read position */
volatile uint8_t *gpc_uart_bufferRxRead;
/*! Number of bytes in the input buffer. */
volatile uint16_t gi_uart_bufferRxLen;

/*! Input ring buffer. */
volatile uint8_t gc_uart_bufferTx[USB_BUFFER_TX_LEN];
/*! Pointer to the Tx ring buffer's current write position */
volatile uint8_t *gpc_uart_bufferTxWrite;
/*! Pointer to the Tx ring buffer's current read position */
volatile uint8_t *gpc_uart_bufferTxRead;
/*! Number of bytes in the input buffer. */
volatile uint16_t gi_uart_bufferTxLen;


/*! USB Rx buffers */
STATIC_UBUF(usbRxBuffer, USB_RX_BUF_SIZ);    /* USB receive buffers.   */
/*! USB Tx buffers */
STATIC_UBUF(gc_usb_Txbuffer, USB_TX_BUF_SIZ);    /* USB transmit buffers.   */


/*
 * The LineCoding variable must be 4-byte aligned as it is used as USB
 * transmit and receive buffer.
 */
EFM32_ALIGN(4)
EFM32_PACK_START(1)
static cdcLineCoding_TypeDef __attribute__ ((aligned(4))) cdcLineCoding =
{
  115200, 0, 0, 8, 0
};
EFM32_PACK_END()

static const USBD_Callbacks_TypeDef callbacks =
{
  .usbReset        = NULL,
  .usbStateChange  = loc_StateChange,
  .setupCmd        = loc_SetupCmd,
  .isSelfPowered   = NULL,
  .sofInt          = NULL
};

static const USBD_Init_TypeDef InitStruct =
{
  .deviceDescriptor    = &USBDESC_deviceDesc,
  .configDescriptor    = USBDESC_configDesc,
  .stringDescriptors   = USBDESC_strings,
  .numberOfStrings     = sizeof(USBDESC_strings)/sizeof(void*),
  .callbacks           = &callbacks,
  .bufferingMultiplier = USBDESC_bufferingMultiplier,
  .reserved            = 0
};

/*==============================================================================
                      LOCAL FUNCTIONS
==============================================================================*/
/*******************************************************************************
 * @brief
 *   Callback function called when the data stage of a CDC_SET_LINECODING
 *   setup command has completed.
 *
 * @param[in] status    Transfer status code.
 * @param[in] xferred   Number of bytes transferred.
 * @param[in] remaining Number of bytes not transferred.
 *
 * @return USB_STATUS_OK if data accepted.
 *         USB_STATUS_REQ_ERR if data calls for modes we can not support.
 *****************************************************************************/
static int loc_LineCodingReceived(USB_Status_TypeDef status,
                              uint32_t xferred,
                              uint32_t remaining)
{
  uint32_t frame = 0;
  (void) remaining;

  /* We have received new serial port communication settings from USB host */
  if ((status == USB_STATUS_OK) && (xferred == 7))
  {
    /* Check bDataBits, valid values are: 5, 6, 7, 8 or 16 bits */
    if (cdcLineCoding.bDataBits == 5)
      frame |= USART_FRAME_DATABITS_FIVE;

    else if (cdcLineCoding.bDataBits == 6)
      frame |= USART_FRAME_DATABITS_SIX;

    else if (cdcLineCoding.bDataBits == 7)
      frame |= USART_FRAME_DATABITS_SEVEN;

    else if (cdcLineCoding.bDataBits == 8)
      frame |= USART_FRAME_DATABITS_EIGHT;

    else if (cdcLineCoding.bDataBits == 16)
      frame |= USART_FRAME_DATABITS_SIXTEEN;

    else
      return USB_STATUS_REQ_ERR;

    /* Check bParityType, valid values are: 0=None 1=Odd 2=Even 3=Mark 4=Space  */
    if (cdcLineCoding.bParityType == 0)
      frame |= USART_FRAME_PARITY_NONE;

    else if (cdcLineCoding.bParityType == 1)
      frame |= USART_FRAME_PARITY_ODD;

    else if (cdcLineCoding.bParityType == 2)
      frame |= USART_FRAME_PARITY_EVEN;

    else if (cdcLineCoding.bParityType == 3)
      return USB_STATUS_REQ_ERR;

    else if (cdcLineCoding.bParityType == 4)
      return USB_STATUS_REQ_ERR;

    else
      return USB_STATUS_REQ_ERR;

    /* Check bCharFormat, valid values are: 0=1 1=1.5 2=2 stop bits */
    if (cdcLineCoding.bCharFormat == 0)
      frame |= USART_FRAME_STOPBITS_ONE;

    else if (cdcLineCoding.bCharFormat == 1)
      frame |= USART_FRAME_STOPBITS_ONEANDAHALF;

    else if (cdcLineCoding.bCharFormat == 2)
      frame |= USART_FRAME_STOPBITS_TWO;

    else
      return USB_STATUS_REQ_ERR;

    /* Program new UART baudrate etc. */
    USART1->FRAME = frame;
    USART_BaudrateAsyncSet(USART1, 0, cdcLineCoding.dwDTERate, usartOVS16);
    return USB_STATUS_OK;
  }
  return USB_STATUS_REQ_ERR;
}
/*******************************************************************************
 * @brief
 *   Handle USB setup commands. Implements CDC class specific commands.
 *
 * @param[in] setup Pointer to the setup packet received.
 *
 * @return USB_STATUS_OK if command accepted.
 *         USB_STATUS_REQ_UNHANDLED when command is unknown, the USB device
 *         stack will handle the request.
 *****************************************************************************/
static int loc_SetupCmd(const USB_Setup_TypeDef *setup)
{
  int retVal = USB_STATUS_REQ_UNHANDLED;

  if ((setup->Type == USB_SETUP_TYPE_CLASS) &&
      (setup->Recipient == USB_SETUP_RECIPIENT_INTERFACE))
  {
    switch (setup->bRequest)
    {
    case USB_CDC_GETLINECODING:
      /********************/
      if ((setup->wValue == 0) &&
          (setup->wIndex == 0) &&               /* Interface no.            */
          (setup->wLength == 7) &&              /* Length of cdcLineCoding  */
          (setup->Direction == USB_SETUP_DIR_IN))
      {
        /* Send current settings to USB host. */
        USBD_Write(0, (void*) &cdcLineCoding, 7, NULL);
        retVal = USB_STATUS_OK;
      }
      break;

    case USB_CDC_SETLINECODING:
      /********************/
      if ((setup->wValue == 0) &&
          (setup->wIndex == 0) &&               /* Interface no.            */
          (setup->wLength == 7) &&              /* Length of cdcLineCoding  */
          (setup->Direction != USB_SETUP_DIR_IN))
      {
        /* Get new settings from USB host. */
        USBD_Read(0, (void*) &cdcLineCoding, 7, loc_LineCodingReceived);
        retVal = USB_STATUS_OK;
      }
      break;

    case USB_CDC_SETCTRLLINESTATE:
      /********************/
      if ((setup->wIndex == 0) &&               /* Interface no.  */
          (setup->wLength == 0))                /* No data        */
      {
        /* Do nothing ( Non compliant behaviour !! ) */
        retVal = USB_STATUS_OK;
      }
      break;
    }
  }
  return retVal;
}

/*******************************************************************************
 * @brief
 *   Callback function called each time the USB device state is changed.
 *   Starts CDC operation when device has been configured by USB host.
 *
 * @param[in] oldState The device state the device has just left.
 * @param[in] newState The new device state.
 *****************************************************************************/
static void loc_StateChange(USBD_State_TypeDef oldState,
                        USBD_State_TypeDef newState)
{
  if (newState == USBD_STATE_CONFIGURED)
  {
    /* We have been configured, start CDC functionality ! */

    if (oldState == USBD_STATE_SUSPENDED)   /* Resume ?   */
    {
    }

    /* Start receiving data from USB host. */
    USBD_Read(CDC_EP_DATA_OUT, (void*) usbRxBuffer,
              USB_RX_BUF_SIZ, loc_UsbDataReceived);
  }

  else if ((oldState == USBD_STATE_CONFIGURED) &&
           (newState != USBD_STATE_SUSPENDED))
  {
    /* We have been de-configured, stop CDC functionality */
    USBTIMER_Stop(0);
  }

  else if (newState == USBD_STATE_SUSPENDED)
  {
    /* We have been suspended, stop CDC functionality */
    /* Reduce current consumption to below 2.5 mA.    */
    USBTIMER_Stop(0);
  }
}

/*******************************************************************************
 * @brief Callback function called whenever a new packet with data is received
 *        on USB.
 *
 * @param[in] status    Transfer status code.
 * @param[in] xferred   Number of bytes transferred.
 * @param[in] remaining Number of bytes not transferred.
 *
 * @return USB_STATUS_OK.
 *****************************************************************************/
static int loc_UsbDataReceived(USB_Status_TypeDef status,
                           uint32_t xferred,
                           uint32_t remaining)
{
  (void) remaining;            /* Unused parameter */
  uint8_t i = 0;

  if ((status == USB_STATUS_OK) && (xferred > 0))
  {
    /* We received data successfully */
    for(i=0; i < xferred; ++i)
    {
      /* Read data from aligned USB buffer to local buffer */
      *gpc_uart_bufferRxWrite++ = usbRxBuffer[i];

      /*! Check for an overflow of the read pointer and adjust if required. */
      if(gpc_uart_bufferRxWrite == &gc_uart_bufferRx[UART_BUFFER_RX_LEN])
      {
        gpc_uart_bufferRxWrite = gc_uart_bufferRx;
      } /* if */
    }/* for() */

    /* Toogle to next aligned Rx buffer */
    USBD_Read(CDC_EP_DATA_OUT, (void*) usbRxBuffer,
              USB_RX_BUF_SIZ, loc_UsbDataReceived);
  }
  return USB_STATUS_OK;
}


/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* wmbus_hal_uart_init() */
/*============================================================================*/
bool_t wmbus_hal_uart_init(void)
{
  /*! Init the Tx-buffer variables. */
  gpc_uart_bufferTxWrite = gc_uart_bufferTx;
  gpc_uart_bufferTxRead = gc_uart_bufferTx;

  gpc_uart_bufferRxRead = gc_uart_bufferRx;
  gpc_uart_bufferRxWrite = gc_uart_bufferRx;

  USBD_Init(&InitStruct);

  return TRUE;
} /* sf_hal_uart_init() */


/*============================================================================*/
/* wmbus_hal_uart_write() */
/*============================================================================*/
uint16_t wmbus_hal_uart_write(uint8_t *pc_data, uint16_t i_len)
{
  uint16_t i;

  /*! Write to Tx-ringbuffer until i_len or USB_BUFFER_TX_LEN is reached. */
  for(i = 0U; (i < i_len) && (USB_BUFFER_TX_LEN > gi_uart_bufferTxLen); i++)
  {
    /*! Write current byte to the write pointers address within the ringbuffer
        and increase the pointer. */
    *gpc_uart_bufferTxWrite++ = pc_data[i];
    /*! Increase the number of bytes in ringbuffer. */
    gi_uart_bufferTxLen++;

    /*! Check for an overflow of the write pointer and adjust if required. */
    if(gpc_uart_bufferTxWrite == &gc_uart_bufferTx[USB_BUFFER_TX_LEN])
    {
      gpc_uart_bufferTxWrite = gc_uart_bufferTx;
    } /* if */

  } /* for */

  return i;
} /* sf_hal_uart_write() */

/*============================================================================*/
/* wmbus_hal_uart_read() */
/*============================================================================*/
uint16_t wmbus_hal_uart_read(uint8_t *pc_data, uint16_t i_len)
{
  uint16_t i = 0x00;

  if (i_len < UART_BUFFER_RX_LEN)
  {
    if (i_len <= wmbus_hal_uart_cntRxBytes())
    {
      /*! Read from Rx-ringbuffer until i_len or UART_BUFFER_RX_LEN is reached. */
      for(i = 0U; (i < i_len) ; i++)
      {
        /*! Write to the specified data pointer and increase the read pointer. */
        pc_data[i] = *gpc_uart_bufferRxRead;
        *gpc_uart_bufferRxRead = 0xff;
        gpc_uart_bufferRxRead++;

        /*! Check for an overflow of the read pointer and adjust if required. */
        if(gpc_uart_bufferRxRead == &gc_uart_bufferRx[UART_BUFFER_RX_LEN])
        {
          gpc_uart_bufferRxRead = gc_uart_bufferRx;
        } /* if(gpc_uart_bufferRxRead == &gc_uart_bufferRx[UART_BUFFER_RX_LEN])*/
      } /* for() */
    } /* if (i_len <= (stzedn_uart_cntRxBytes()) */
    else
    {
      i = 0x00;
    }
  } /* if (i_len < UART_BUFFER_RX_LEN) */
  return i;
} /* sf_hal_uart_read() */

/*============================================================================*/
/* wmbus_hal_uart_cntRxBytes() */
/*============================================================================*/
uint16_t wmbus_hal_uart_cntRxBytes(void)
{
  uint16_t i_cnt;

  if (gpc_uart_bufferRxWrite > gpc_uart_bufferRxRead)
    i_cnt = gpc_uart_bufferRxWrite - gpc_uart_bufferRxRead;
  else if(gpc_uart_bufferRxWrite < gpc_uart_bufferRxRead)
  {
    i_cnt = &gc_uart_bufferRx[UART_BUFFER_RX_LEN] - gpc_uart_bufferRxRead;
    i_cnt +=  gpc_uart_bufferRxWrite - gc_uart_bufferRx;
  }
  else
  {
    i_cnt = 0x00;
  }

  return i_cnt;
} /* sf_hal_uart_cntRxBytes() */

/*============================================================================*/
/* wmbus_hal_uart_cntTxBytes() */
/*============================================================================*/
uint16_t wmbus_hal_uart_cntTxBytes(void)
{
  /* Not needed for the usb interface */
  return 0x00;
} /* wmbus_hal_uart_cntTxBytes() */

/*============================================================================*/
/* wmbus_hal_uart_isRxOverflow() */
/*============================================================================*/
bool_t wmbus_hal_uart_isRxOverflow(void)
{
  bool_t b_return = FALSE;
  /* Not needed for the usb interface */
  return b_return;
} /* wmbus_hal_uart_isRxOverflow() */

/*============================================================================*/
/* wmbus_hal_uart_com_TxFinish() */
/*============================================================================*/
void wmbus_hal_uart_com_TxFinish(void)
{
  uint16_t i = 0x00U;

  for(i=0; gi_uart_bufferTxLen > 0; ++i)
  {
    /* Write Tx data to an aligned buffer to send it out via USB */
    gc_usb_Txbuffer[i] = *gpc_uart_bufferTxRead;
    gpc_uart_bufferTxRead++;
    /*! Decrease the number of bytes in ringbuffer. */
    gi_uart_bufferTxLen--;

    /*! Check for an overflow of the write pointer and adjust if required. */
    if(gpc_uart_bufferTxRead == &gc_uart_bufferTx[USB_BUFFER_TX_LEN])
    {
      gpc_uart_bufferTxRead = gc_uart_bufferTx;
    } /* if */
  }/* for() */

  /* Send out all pending data */
  USBD_Write(CDC_EP_DATA_IN, (void*) gc_usb_Txbuffer, i, NULL);
} /* sf_hal_uart_com_TxFinish() */

/*============================================================================*/
/* wmbus_hal_uart_com_run() */
/*============================================================================*/
void wmbus_hal_uart_com_run(void)
{
  return;
} /* sf_hal_uart_com_run() */

/**@}*/
#ifdef __cplusplus
}
#endif

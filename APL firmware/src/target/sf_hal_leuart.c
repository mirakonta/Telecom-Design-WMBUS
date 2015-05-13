#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_leuart.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for LEUART implementations.

  @addtogroup WMBUS_HAL_UART
  
  For using an EFM32ZG device, a LEUART driver for serial communication with the
  stack has been prepared: `/src/target/`sf_hal_leuart.c

*/
/**@{*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\hal\wmbus_hal_uart.h"

/*! EFM32LIB includes */
#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_leuart.h"

/*==============================================================================
                                CHECKS
==============================================================================*/
#ifndef UART_USART_INTERFACE
#error: define UART_USART_INTERFACE as LEUART ex. LEUART0, LEUART1
#endif 

#ifndef UART_USART_RX_PIN
#error: define a valid UART_USART_RX_PIN for your board
#endif 

#ifndef UART_USART_PORT
#error: define a valid UART_USART_PORT for your board
#endif 

#ifndef UART_USART_TX_PIN
#error: define a valid UART_USART_TX_PIN for your board
#endif 

/*==============================================================================
                            CONFIGURATION
==============================================================================*/

/*! Sets the length of the Rx ringbuffer. */
#define UART_BUFFER_RX_LEN            20U
/*! Sets the length of the Tx ringbuffer. */
#define UART_BUFFER_TX_LEN            50U

#ifndef UART_USE_TX_IRQ
/*! Enable UART Tx interrupts. */
#define UART_USE_TX_IRQ               TRUE
#endif /* UART_USE_TX_IRQ */

LEUART_TypeDef *usart_interface          = UART_USART_INTERFACE;

LEUART_Init_TypeDef usart_settings       =   
{   leuartEnable,      /* Enable RX/TX when init completed. */                                
    0,                 /* Use current configured reference clock for configuring baudrate. */
    9600,            /* 9600 bits/s. */
    leuartDatabits8,   /* 8 databits. */                                                      
    leuartNoParity,    /* No parity. */                                                       
    leuartStopbits1    /* 1 stopbit. */                                                      
};
                                
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
/*! Set if there was a Rx buffer overflow. */
volatile bool_t gb_uart_bufferRxOverflow;

/*! Input ring buffer. */
volatile uint8_t gc_uart_bufferTx[UART_BUFFER_TX_LEN];
/*! Pointer to the Tx ring buffer's current write position */
volatile uint8_t *gpc_uart_bufferTxWrite;
/*! Pointer to the Tx ring buffer's current read position */
volatile uint8_t *gpc_uart_bufferTxRead;
/*! Number of bytes in the input buffer. */
volatile uint16_t gi_uart_bufferTxLen;

/*==============================================================================
                         LOCAL   FUNCTIONS
==============================================================================*/

/*========================= UART Input ISR ===================================*/
/*============================================================================*/
/* loc_sf_uart_rx_isr() */
/*============================================================================*/
void loc_sf_uart_rx_isr(void)
{
  /*! If the Rx-ringbuffer is full, disable the Rx-interrupt. */
  if(UART_BUFFER_RX_LEN <= gi_uart_bufferRxLen)
  {
    usart_interface->IEN &= ~LEUART_IEN_RXDATAV;
    gb_uart_bufferRxOverflow = TRUE;
    return;
  }
  /*! Otherwise read the next byte into the Rx-ringbuffer. */
  *gpc_uart_bufferRxWrite++ = LEUART_Rx(usart_interface);  
  /*! Increase the number of bytes in Rx-ringbuffer. */
  gi_uart_bufferRxLen++;
  /*! Check for an overflow of the read pointer and adjust if required. */
  if(gpc_uart_bufferRxWrite == &gc_uart_bufferRx[UART_BUFFER_RX_LEN])
  {
    gpc_uart_bufferRxWrite = gc_uart_bufferRx;
  } /* if */

  /*! Reset the Rx-interrupt. */
  LEUART_IntClear(usart_interface, LEUART_IF_RXDATAV);
  return;
} /* stzedn_uart_rx_isr() */

/*========================= UART Output ISR ==================================*/
/*============================================================================*/
/* loc_sf_uart_tx_isr() */
/*============================================================================*/
void loc_sf_uart_tx_isr(void)
{
 /*! Reset the Tx-interrupt. */
  LEUART_IntClear(usart_interface, LEUART_IF_TXC);;

  /*! Decrease the number of bytes in Tx-ringbuffer. */
  gi_uart_bufferTxLen--;

  /*! If the Tx-ringbuffer is empty, disable the Tx-interrupt. */
  if(gi_uart_bufferTxLen == 0U)
  {
    return;
  }
  /*! Otherwise write the next byte from Tx-ringbuffer. */
  LEUART_Tx(usart_interface, *gpc_uart_bufferTxRead++); 

  /*! Check for an overflow of the write pointer and adjust if required. */
  if(gpc_uart_bufferTxRead == &gc_uart_bufferTx[UART_BUFFER_TX_LEN])
  {
    gpc_uart_bufferTxRead = gc_uart_bufferTx;
  } /* if */

  return;
} /* stzedn_uart_tx_isr() */

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* wmbus_hal_uart_init() */
/*============================================================================*/
bool_t wmbus_hal_uart_init(void)
{
/*! Init the Rx-buffer variables. */
  gpc_uart_bufferRxWrite = gc_uart_bufferRx;
  gpc_uart_bufferRxRead = gc_uart_bufferRx;
  gi_uart_bufferRxLen = 0U;
  gb_uart_bufferRxOverflow = FALSE;

  /*! Init the Tx-buffer variables. */
  gpc_uart_bufferTxWrite = gc_uart_bufferTx;
  gpc_uart_bufferTxRead = gc_uart_bufferTx;
  gi_uart_bufferTxLen = 0U;

  /* enable clock system */
  CMU_ClockEnable(cmuClock_HFPER, true);
  /* Enable clock for core */
  CMU->HFCORECLKEN0 = CMU_HFCORECLKEN0_LE;
  /* Enable clock for Peripherals */
  CMU->HFPERCLKEN0 = CMU_HFPERCLKEN0_GPIO;
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
  CMU_ClockDivSet(cmuClock_LEUART0 , cmuClkDiv_1);
  CMU_ClockEnable(cmuClock_LEUART0, true);  


  /* configure pins */
  GPIO_PinModeSet(UART_USART_PORT, UART_USART_TX_PIN, gpioModePushPull, 1); 
  GPIO_PinModeSet(UART_USART_PORT, UART_USART_RX_PIN, gpioModeInput, 0);

  /* Configure USART for basic async operation --> use LEUART */

  usart_settings.enable = leuartDisable;
  LEUART_Init(usart_interface, &usart_settings);

  /* setup location */
   usart_interface->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN;

  /* Clear previous RX interrupts */
  LEUART_IntClear(usart_interface, LEUART_IF_RXDATAV);
  NVIC_ClearPendingIRQ(LEUART0_IRQn);

  /* Enable RX interrupts */
  LEUART_IntEnable(usart_interface, LEUART_IF_RXDATAV);
  /* Enable TX interrupts */
  LEUART_IntEnable(usart_interface, LEUART_IF_TXC);

  NVIC_EnableIRQ(LEUART0_IRQn);

  /* Finally enable LEUART */
  LEUART_Enable(usart_interface, leuartEnable);

  return TRUE;
} /* wmbus_hal_uart_init() */


/*============================================================================*/
/* sf_hal_uart_write() */
/*============================================================================*/
uint16_t wmbus_hal_uart_write(uint8_t *pc_data, uint16_t i_len)
{
  uint16_t i;
  bool_t   b_first_write;

  #if UART_USE_TX_IRQ
  /*! Verify length-value. */
  if((0U == i_len) || (UART_BUFFER_TX_LEN <= gi_uart_bufferTxLen))
  {
    return 0U;
  } /* if */

   usart_interface->IEN &= ~LEUART_IEN_TXC;

  if( gi_uart_bufferTxLen == 0U )
  {
    /* This is the first write */
    b_first_write = TRUE;
  }
  else
  {
    /* This is not the first write */
    b_first_write = FALSE;
  }

  /*! Write to Tx-ringbuffer until i_len or UART_BUFFER_TX_LEN is reached. */
  for(i = 0U; (i < i_len) && (UART_BUFFER_TX_LEN > gi_uart_bufferTxLen); i++)
  {
    /*! Write current byte to the write pointers address within the ringbuffer
        and increase the pointer. */
    *gpc_uart_bufferTxWrite++ = pc_data[i];
    /*! Increase the number of bytes in ringbuffer. */
    gi_uart_bufferTxLen++;
    /*! Check for an overflow of the write pointer and adjust if required. */
    if(gpc_uart_bufferTxWrite == &gc_uart_bufferTx[UART_BUFFER_TX_LEN])
    {
      gpc_uart_bufferTxWrite = gc_uart_bufferTx;
    } /* if */

  } /* for */
  /*! Return the number of bytes written until the loop was left. */

  /*! If it is the first byte, write it. */
  if( (gi_uart_bufferTxLen > 0U) && (b_first_write == TRUE) )
  {
    /* write data */
   LEUART_Tx(usart_interface, *gpc_uart_bufferTxRead++);

    /*! Check for an overflow of the write pointer and adjust if required. */
    if(gpc_uart_bufferTxRead == &gc_uart_bufferTx[UART_BUFFER_TX_LEN])
    {
      /* reset buffer */
      gpc_uart_bufferTxRead = gc_uart_bufferTx;
    } /* if */
  } /* if */

  usart_interface->IEN |= LEUART_IEN_TXC;
  return i;

  #else
  for(i = 0U; i < i_len; i++)
  {
    UART_WRITE(pc_data[i]);
  } /* for */
  return i_len;
  #endif /* UART_USE_TX_IRQ */
} /* wmbus_hal_uart_write() */

/*============================================================================*/
/* wmbus_hal_uart_read() */
/*============================================================================*/
uint16_t wmbus_hal_uart_read(uint8_t *pc_data, uint16_t i_len)
{
  uint16_t i;

  /*! Read from Rx-ringbuffer until i_len or UART_BUFFER_RX_LEN is reached. */
  for(i = 0U; (i < i_len) && (0U < gi_uart_bufferRxLen); i++)
  {
    /*! Write to the specified data pointer and increase the read pointer. */
    pc_data[i] = *gpc_uart_bufferRxRead++;
    /*! Decrease the number of bytes in ringbuffer. */
    gi_uart_bufferRxLen--;
    /*! Check for an overflow of the read pointer and adjust if required. */
    if(gpc_uart_bufferRxRead == &gc_uart_bufferRx[UART_BUFFER_RX_LEN])
    {
      gpc_uart_bufferRxRead = gc_uart_bufferRx;
    } /* if */
    /*! (Re-)Enable the Rx-interrupt. */
    usart_interface->IEN |= LEUART_IEN_RXDATAV;
  }
  return i;
} /* wmbus_hal_uart_read() */

/*============================================================================*/
/* wmbus_hal_uart_cntRxBytes() */
/*============================================================================*/
uint16_t wmbus_hal_uart_cntRxBytes(void)
{
  return gi_uart_bufferRxLen;
} /* wmbus_hal_uart_cntRxBytes() */

/*============================================================================*/
/* wmbus_hal_uart_cntTxBytes() */
/*============================================================================*/
uint16_t wmbus_hal_uart_cntTxBytes(void)
{
  return (UART_BUFFER_TX_LEN - gi_uart_bufferTxLen);
} /* wmbus_hal_uart_cntTxBytes() */

/*============================================================================*/
/* wmbus_hal_uart_isRxOverflow() */
/*============================================================================*/
bool_t wmbus_hal_uart_isRxOverflow(void)
{
  bool_t b_return;
  b_return = gb_uart_bufferRxOverflow;
  gb_uart_bufferRxOverflow = FALSE;
  return b_return;
} /* wmbus_hal_uart_isRxOverflow() */

/*============================================================================*/
/* wmbus_hal_uart_com_TxFinish() */
/*============================================================================*/
void wmbus_hal_uart_com_TxFinish(void)
{
#if (SERIAL_USB_TO_HOST_ENABLED)
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
#else
  return;
#endif
} /* sf_hal_uart_com_TxFinish() */


/*============================================================================*/
/* wmbus_hal_uart_com_run() */
/*============================================================================*/
void wmbus_hal_uart_com_run(void)
{
  return;
} /* sf_hal_uart_com_run() */

/*==============================================================================
                            INTERRUPTHANDLER
==============================================================================*/

/*========================= LEUART0 RX/TX ISR ================================*/
void LEUART0_IRQHandler(void)
{
    LEUART_TypeDef *leuart_interface = UART_USART_INTERFACE;
    uint32_t flags;

    flags = LEUART_IntGet(leuart_interface);
    if(flags & LEUART_IF_TXC)
    {
      loc_sf_uart_tx_isr();
    }
    else if(flags & LEUART_IF_RXDATAV)
    {
      loc_sf_uart_rx_isr();
    }
}

/**@}*/
#ifdef __cplusplus
}
#endif

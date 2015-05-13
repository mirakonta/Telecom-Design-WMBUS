#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_spi.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for SPI implementations.
  @addtogroup SF_HAL_SPI

  The SPI access is implemented in `/src/target/`sf_hal_spi.c.

*/
/**@{*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
/*! Stack includes */
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\hal\wmbus_hal_mcu.h"

#include "sf_hal_spi.h"
#include "sf_rf_hal_mcu.h"

/*! EFM32LIB includes */
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_usart.h"

  
   
/*==============================================================================
                            CHECKS
==============================================================================*/
#ifndef SPI_MOSI_PORT
#error: define SPI_MOSI_PORT   
#endif

#ifndef SPI_MOSI_PIN
#error: define SPI_MOSI_PIN   
#endif
#ifndef SPI_MISO_PORT
#error: define SPI_MISO_PORT   
#endif

#ifndef SPI_MISO_PIN
#error: define SPI_MISO_PIN   
#endif

#ifndef SPI_CLK_PORT
#error: define SPI_CLK_PORT   
#endif

#ifndef SPI_CLK_PIN
#error: define SPI_CLK_PIN   
#endif

#ifndef SPI_CS_PORT
#error: define SPI_CS_PORT   
#endif

#ifndef SPI_CS_PIN
#error: define SPI_CS_PIN   
#endif

#ifndef SPI_BAUDRATE
#error: define SPI_BAUDRATE   
#endif                               

#ifndef SPI_USART_LOCATION
#error: define SPI_USART_LOCATION   
#endif 

/*==============================================================================
                            DEFINES
==============================================================================*/
/* Watchdog for the ISR */
/*! Timeout to prevent blocking errors in retries. */
#define SPI_ISR_TIMEOUT                        1000U
                                          
/*==============================================================================
                            TYPEDEF STRUCTS
==============================================================================*/
/*! Structure to save rx or tx parameters. */
typedef struct S_SPI_RXTX_T
{
  /*! Temporary data storage. */
  uint8_t *pc_data;
  /*! End address of writing or reading. */
  uint8_t *pc_end;
  /*! Number of bytes to send or receive. */
  uint16_t i_len;

} s_spi_txTx_t;

/*==============================================================================
                            LOCAL VARIABLES
==============================================================================*/
/*! Structure to save rx or tx parameters. */
volatile s_spi_txTx_t gs_spi_rx_tx;

/*! Watchdog ISR timer. */
volatile uint16_t gi_spi_isr_wtd;

/*! SPI instance */
USART_TypeDef *gps_spi;

/* pointer to the callback functions, set by rf-module on call sf_hal_spi_init */
static fp_hal_spi_event gfp_rx = NULL;
static fp_hal_spi_event gfp_tx = NULL;


/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/*! sf_hal_spi_init() */
/*============================================================================*/
void sf_hal_spi_init(fp_hal_spi_event fp_rx, fp_hal_spi_event fp_tx)
{
 
  /* store the callback pointers for usage within the ISR. */
  gfp_rx = fp_rx;
  gfp_tx = fp_tx;
  /* set the USART instance */
  gps_spi = SPI_USART_INST;

  /* enable clock for the SPI core and GPIO */
  SPI_CLK_ENABLE();
  CMU_ClockEnable(cmuClock_GPIO, true);

  /** Configure the SPI interface of the MCU */
  /**@{*/
  {
    /* Set frame options */
    gps_spi->FRAME = 0x1005;
    gps_spi->TRIGCTRL = 0;

    /* Calculate the correct divider for the spi clock */

    gps_spi->CLKDIV = 128 *(CMU_ClockFreqGet(cmuClock_HFPER) / SPI_BAUDRATE - 2);

    /* Using synchronous (SPI) mode with inverted Rx and Tx*/
    gps_spi->CTRL = USART_CTRL_SYNC | USART_CTRL_MSBF;

    /* Clear old transfers/receptions, and disable interrupts */
    gps_spi->CMD = (USART_CMD_CLEARRX | USART_CMD_CLEARTX);
    gps_spi->IEN = 0;

    /* Enable pins and set location */
    gps_spi->ROUTE = (USART_ROUTE_TXPEN | USART_ROUTE_RXPEN |
                      USART_ROUTE_CLKPEN |
                      (SPI_USART_LOCATION << _USART_ROUTE_LOCATION_SHIFT));
    gps_spi->IRCTRL = 0;
    #if defined (_EFM32_GIANT_FAMILY)
    gps_spi->INPUT = 0;
    gps_spi->I2SCTRL = 0;
    #endif

    /* Enable Master, TX and RX and disable auto CS*/
    gps_spi->CMD  = USART_CMD_MASTEREN;
    gps_spi->CMD  |= (USART_CMD_TXEN | USART_CMD_RXEN);
    gps_spi->CTRL &= ~USART_CTRL_AUTOCS;

    /* Clear previous interrupts */
    gps_spi->IFC = _USART_IFC_MASK;

    /* initialize the GPIO pins for the USART */
    GPIO_PinModeSet(SPI_MOSI_PORT, SPI_MOSI_PIN, gpioModePushPull, 0);
    GPIO_PinModeSet(SPI_MISO_PORT, SPI_MISO_PIN, gpioModeInput,    0);
    GPIO_PinModeSet(SPI_CLK_PORT, SPI_CLK_PIN, gpioModePushPull,  0);
    GPIO_PinModeSet(SPI_CS_PORT, SPI_CS_PIN, gpioModePushPull, 1);

  }
  /**@}*/

  /* disable interrupts and clear pending */
  NVIC_ClearPendingIRQ(SPI_USART_RX_IEN); /*Clear Pending interrupts*/
  NVIC_DisableIRQ(SPI_USART_RX_IEN);      /*Disable Rx IRQ*/
  gps_spi->IEN &= ~USART_IEN_RXDATAV;      /* Clear Rx buffer interrupt */

  NVIC_ClearPendingIRQ(SPI_USART_TX_IEN); /* Clear Pending interrupts*/
  NVIC_DisableIRQ(SPI_USART_TX_IEN);      /* Disable Tx IRQ*/
  gps_spi->IEN &= ~USART_IEN_TXBL;         /* Clear Tx buffer interrupt */
  
  return;
} /* sf_hal_spi_init() */

/*============================================================================*/
/* sf_hal_spi_chipSelect() */
/*============================================================================*/
void sf_hal_spi_chipSelect(void)
{
  GPIO_PinModeSet(SPI_CS_PORT, SPI_CS_PIN, gpioModePushPull, 0);
} /* sf_hal_spi_chipSelect() */

/*============================================================================*/
/* sf_hal_spi_chipDeselect() */
/*============================================================================*/
void sf_hal_spi_chipDeselect(void)
{
  GPIO_PinModeSet(SPI_CS_PORT, SPI_CS_PIN, gpioModePushPull, 1);
} /* sf_hal_spi_chipDeselect() */

/*============================================================================*/
/* sf_spi_xfer() */
/*============================================================================*/
void sf_hal_spi_xfer(uint8_t* pc_dataWrite, uint8_t* pc_dataRead, uint16_t i_len)
{
  sf_hal_spi_chipSelect();

  if(pc_dataWrite != NULL)
  {
    /* Write data. */
    gs_spi_rx_tx.pc_data = (uint8_t*) pc_dataWrite;
    gs_spi_rx_tx.pc_end = ((uint8_t*) pc_dataWrite) + i_len;
    gs_spi_rx_tx.i_len = i_len;

    /* Writes the first byte. */
    while( (gps_spi->STATUS & USART_STATUS_TXBL) == 0 );
    gps_spi->TXDATA = (*(gs_spi_rx_tx.pc_data));

    gs_spi_rx_tx.pc_data++;

    /* Enable Tx interrupt */
    NVIC_ClearPendingIRQ(SPI_USART_TX_IEN); /* Clear Pending interrupts*/
    NVIC_EnableIRQ(SPI_USART_TX_IEN);       /* Enable Tx IRQ*/
    gps_spi->IEN |= USART_IEN_TXBL;          /* Set Tx buffer interrupt */
  }
  else if(pc_dataRead != NULL)
  {
    /* Enable Rx interrupt */
    NVIC_ClearPendingIRQ(SPI_USART_RX_IEN); /*Clear Pending interrupts*/
    NVIC_EnableIRQ(SPI_USART_RX_IEN);       /*Enable Rx IRQ*/
    gps_spi->IEN |= USART_IEN_RXDATAV;       /*Set Rx buffer interrupt*/

    /* Read data. */
    gs_spi_rx_tx.pc_data = pc_dataRead;
    gs_spi_rx_tx.pc_end = pc_dataRead + i_len;
    gs_spi_rx_tx.i_len = i_len;

    /* Dummy write. */
    while( (gps_spi->STATUS & USART_STATUS_TXBL) == 0 );
    gps_spi->TXDATA =  0U ;
  } /* if */

} /* sf_spi_xfer() */


/*============================================================================*/
/* sf_spi_xferBlock() */
/*============================================================================*/
uint8_t sf_hal_spi_xferBlock(uint8_t *pc_dataWrite, uint8_t *pc_dataRead,
                      uint16_t i_len)
{
  uint16_t i;
  uint8_t c_status;

  /* Disable Interrupts from SPI */
  NVIC_ClearPendingIRQ(SPI_USART_TX_IEN); /* Clear Pending interrupts*/
  NVIC_DisableIRQ(SPI_USART_TX_IEN);      /* Disable Tx IRQ*/
  gps_spi->IEN &= ~USART_IEN_TXBL;         /* Clear Tx buffer interrupt */

  NVIC_ClearPendingIRQ(SPI_USART_RX_IEN); /*Clear Pending interrupts*/
  NVIC_DisableIRQ(SPI_USART_RX_IEN);      /*Disable Rx IRQ*/
  gps_spi->IEN &= ~USART_IEN_RXDATAV;      /* Clear Rx buffer interrupt */

  /* start watchdog */
  gi_spi_isr_wtd = 0x00;

  c_status = 0;

  if((pc_dataWrite != NULL) && (pc_dataRead == NULL))
  {
    for(i = 0U;i < i_len;i++)
    {
      /* wait until SPI is ready to transmit */
      while( (gps_spi->STATUS & USART_STATUS_TXBL) == 0 );

      /* Writes the next byte. */
      gps_spi->TXDATA = *pc_dataWrite++;
      while( (gps_spi->STATUS & USART_STATUS_TXC) == 0 );

      /* Read data. */
      while( (gps_spi->STATUS & USART_STATUS_TXBL) == 0 );
      c_status = gps_spi->RXDATA;
    } /* for */
  }
  else if((pc_dataRead != NULL))
  {
    /* fist check if data is available, if so clear it */
    while((gps_spi->STATUS & USART_STATUS_RXDATAV) == USART_STATUS_RXDATAV)
    {
      c_status = gps_spi->RXDATA;
    } /* if */

    for(i = 0U;i < i_len;i++)
    {
      /* wait until SPI is ready to transmit */
    	while( (gps_spi->STATUS & USART_STATUS_TXBL) == 0 );

      /* Dummy write. */
      if(pc_dataWrite != 0)
      {
        gps_spi->TXDATA = *pc_dataWrite++;
      }
      else
      {
    	  gps_spi->TXDATA = 0x00;
      }
      while( (gps_spi->STATUS & USART_STATUS_TXC) == 0 );

      /* Reads the value from RX buffer. */
      while( (gps_spi->STATUS & USART_STATUS_RXDATAV) == 0) 
      { 
        gi_spi_isr_wtd += 0x01U;
        if(gi_spi_isr_wtd == SPI_ISR_TIMEOUT){  return (FALSE); }
      }
      *pc_dataRead++ = gps_spi->RXDATA;
    } /* for */
  }
  else
  {
    /* Do nothing */
  } /* if ... else if ... else */

  /* Clear all Interrupts */
   gps_spi->IFC  = 0xFFFFFFFF;

  return c_status;
} /* sf_spi_xferBlock() */

/*==============================================================================
                            INTERRUPTS
==============================================================================*/

/*============================================================================*/
/* Rx SPI_USART_RXIRQ_HANDLER_FNC handler() */
/*============================================================================*/
void SPI_USART_RXIRQ_HANDLER_FNC( void )
{
  /* Temporary variable. */
  uint8_t c_buf;
  uint8_t *pc_end;

  /* start watchdog */
  gi_spi_isr_wtd = 0x00;

  /* clear IRQ */
  gps_spi->IFC  = 0xFFFFFFFF;

  /* Reads the value from RX buffer. */
  c_buf = gps_spi->RXDATA;
  (*(gs_spi_rx_tx.pc_data)) = c_buf;
  gs_spi_rx_tx.pc_data++;

  pc_end = gs_spi_rx_tx.pc_end;
  if(gs_spi_rx_tx.pc_data < pc_end)
  {
    /* Dummy write. */
    gps_spi->TXDATA = 0U;
  }
  else
  {
    gs_spi_rx_tx.pc_data = NULL;
    if( gfp_rx )
    {
      gfp_rx(gs_spi_rx_tx.i_len);
    }
  } /* if ... else */

  return;

}/* SPI_USART_RXIRQ_HANDLER_FNC() */


/*============================================================================*/
/* Tx IRQ SPI_USART_TXIRQ_HANDLER_FNC() */
/*============================================================================*/
void SPI_USART_TXIRQ_HANDLER_FNC( void )
{
  /* Temporary variable. */
  uint8_t *pc_end;
  uint8_t c_dummy;

  /* clear IRQ */
  gps_spi->IFC  = 0xFFFFFFFF;

  /* take a dummy read */
  c_dummy = gps_spi->RXDATA;

  pc_end = gs_spi_rx_tx.pc_end;

  if(gs_spi_rx_tx.pc_data < pc_end)
  {
    /* write to TX data buffer */
    gps_spi->TXDATA =  *(gs_spi_rx_tx.pc_data);
    gs_spi_rx_tx.pc_data++;
  }
  else
  {
    uint16_t i_len; /* used to overcome volatile access to gs_spi_rx_tx.i_len*/

    /*! disable Tx interrupts */
    NVIC_ClearPendingIRQ(SPI_USART_TX_IEN); /* Clear Pending interrupts*/ 
    NVIC_DisableIRQ(SPI_USART_TX_IEN);      /* Disable Tx IRQ*/ \
    gps_spi->IEN &= ~USART_IEN_TXBL;         /* Clear Tx buffer interrupt */
   
    gs_spi_rx_tx.pc_data = NULL;
    i_len = gs_spi_rx_tx.i_len;
    if(gfp_tx)
    {
      gfp_tx(i_len);
    }
  } /* if ... else */

  (void) c_dummy;

  return;
}/* SPI_USART_TXIRQ_HANDLER_FNC() */


/**@}*/
#ifdef __cplusplus
}
#endif

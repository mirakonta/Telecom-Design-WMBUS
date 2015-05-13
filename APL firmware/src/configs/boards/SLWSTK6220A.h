/*============================================================================*/
/**
 * @file       SLWSTK6220A.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @brief      configurations for the SLWSTK6220A development kit
 *
 */
/*============================================================================*/
/* this define is needed by the EFM library */


#define EZR32WG330F256R60


/* MCU */
#define MCU_SPEED                        (5U)        /* E_MCU_SPEED_28_MHZ  according to HFRCO band returned from em lib */

/* SPI */
#define SPI_MOSI_PORT                     gpioPortE
#define SPI_MOSI_PIN                      10
#define SPI_MISO_PORT                     gpioPortE
#define SPI_MISO_PIN                      11
#define SPI_CLK_PORT                      gpioPortE
#define SPI_CLK_PIN                       12
#define SPI_CS_PORT                       gpioPortE
#define SPI_CS_PIN                        9
#define SPI_BAUDRATE                      4500000U
#define SPI_USART_LOCATION                (0U)
#define SPI_USART_INST                    USARTRF0
#define SPI_USART_TXIRQ_HANDLER_FNC       USART0_TX_IRQHandler
#define SPI_USART_RXIRQ_HANDLER_FNC       USART0_RX_IRQHandler
#define SPI_USART_TX_IEN                  USARTRF0_TX_IRQn
#define SPI_USART_RX_IEN                  USARTRF0_RX_IRQn
#define SPI_CLK_ENABLE()                  CMU_ClockEnable(cmuClock_USARTRF0, true)
#define SPI_CLK_DISABLE()                 CMU_ClockEnable(cmuClock_USARTRF0, false)
                                          
/** Because the wmbus_typedefs.h collides with definitions by EFM32 library,
    wmbus_typedefs.h should prefer using stdint.h. */
#ifndef USE_STDINT
#define USE_STDINT                         (1U)
#endif     


/* USE USB exept for APL application, disable UART */
#if ((defined WMBUS_APP_SERIAL)||(defined WMBUS_APP_SNIFFER))
  #define SERIAL_USB_TO_HOST_ENABLED       (1U)
  #define UART_ENABLED                     (0U)
#else
  #define SERIAL_USB_TO_HOST_ENABLED       (0U)
  #define UART_ENABLED                     (0U)
#endif  

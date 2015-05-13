/*============================================================================*/
/**
 * @file       EFM32WG_STK3800.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @brief      Pre-include configurations for the EFM32WG_STK3800 demo kit
 *
 */
/*============================================================================*/
/* makro for EFM library */
#define EFM32WG990F256

#define RF_GPIO0_PORT                     gpioPortC 
#define RF_GPIO0_PIN                      (4U) 
#define RF_GPIO1_PORT                     gpioPortC 
#define RF_GPIO1_PIN                      (5U) 
#define RF_SDN_PORT                       gpioPortC 
#define RF_SDN_PIN                        (3U) 

/* MCU */
#define MCU_SPEED                         (5U)        /* E_MCU_SPEED_28_MHZ */

/* SPI */
#define SPI_MOSI_PORT                     gpioPortD
#define SPI_MOSI_PIN                      (0U)
#define SPI_MISO_PORT                     gpioPortD
#define SPI_MISO_PIN                      (1U)
#define SPI_CLK_PORT                      gpioPortD
#define SPI_CLK_PIN                       (2U)
#define SPI_CS_PORT                       gpioPortD
#define SPI_CS_PIN                        (3U)
#define SPI_BAUDRATE                      8000000U
#define SPI_USART_LOCATION                (1U)
#define SPI_USART_INST                    USART1
#define SPI_USART_TXIRQ_HANDLER_FNC       USART1_TX_IRQHandler
#define SPI_USART_RXIRQ_HANDLER_FNC       USART1_RX_IRQHandler
#define SPI_USART_TX_IEN                  USART1_TX_IRQn
#define SPI_USART_RX_IEN                  USART1_RX_IRQn
#define SPI_CLK_ENABLE()                  CMU_ClockEnable(cmuClock_USART1, true)
#define SPI_CLK_DISABLE()                 CMU_ClockEnable(cmuClock_USART1, false)    


/** Because the wmbus_typedefs.h collides with definitions by EFM32 library,
    wmbus_typedefs.h should prefer using stdint.h. */
#ifndef USE_STDINT
#define USE_STDINT                        (1U)
#endif


/*! USE USB exept for APL application, disable UART */
#if ((defined WMBUS_APP_SERIAL)||(defined WMBUS_APP_SNIFFER))
  #define SERIAL_USB_TO_HOST_ENABLED      (1U)
  #define UART_ENABLED                    (0U)
#else /* if defined WMBUS_APP_APL */
  #define SERIAL_USB_TO_HOST_ENABLED      (0U)
  #define UART_ENABLED                    (0U)
#endif 


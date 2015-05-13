/*============================================================================*/
/**
 * @file        STK3200.h
 * @copyright   STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author      STACKFORCE
 * @brief       configurations for the EFM32ZG-STK3200 development kit
 *
 */
/*============================================================================*/
/* makro for EFM library */
#define EFM32G210F128

#define RF_GPIO0_PORT                     gpioPortA	//not sure
#define RF_GPIO0_PIN                      (2U) 		//not sure
#define RF_GPIO1_PORT                     gpioPortB	//not sure
#define RF_GPIO1_PIN                      (14U)		//not sure
#define RF_SDN_PORT                       gpioPortC 
#define RF_SDN_PIN                        (13U) 
                                         
/* MCU */                                
#define MCU_SPEED                            (4U) /* MCU_SPEED_21_MHZ */
                                         
/* SPI */                                
#define SPI_MOSI_PORT                     gpioPortE
#define SPI_MOSI_PIN                      (10U)
#define SPI_MISO_PORT                     gpioPortE
#define SPI_MISO_PIN                      (11U)
#define SPI_CLK_PORT                      gpioPortE
#define SPI_CLK_PIN                       (12U)
#define SPI_CS_PORT                       gpioPortE
#define SPI_CS_PIN                        (13U)
#define SPI_BAUDRATE                      4500000U
#define SPI_USART_LOCATION                (0U)
#define SPI_USART_INST                    USART0
#define SPI_USART_TXIRQ_HANDLER_FNC       USART0_TX_IRQHandler
#define SPI_USART_RXIRQ_HANDLER_FNC       USART0_RX_IRQHandler
#define SPI_USART_TX_IEN                  USART0_TX_IRQn
#define SPI_USART_RX_IEN                  USART0_RX_IRQn
#define SPI_CLK_ENABLE()                  CMU_ClockEnable(cmuClock_USART0, true)
#define SPI_CLK_DISABLE()                 CMU_ClockEnable(cmuClock_USART0, false)    

      
/* UART */
#define UART_USART_INTERFACE                 LEUART0
#define UART_USART_PORT                      gpioPortD
#define UART_USART_RX_PIN                    5
#define UART_USART_TX_PIN                    4
                                            

/** Because the wmbus_typedefs.h collides with definitions by EFM32 library,
    wmbus_typedefs.h should prefer using stdint.h. */
#ifndef USE_STDINT
#define USE_STDINT                           (1U)
#endif


/*! Use UART except for APL mode */
#if ((defined WMBUS_APP_SERIAL)||(defined WMBUS_APP_SNIFFER))
   #define SERIAL_USB_TO_HOST_ENABLED        (0U)
   #define UART_ENABLED                      (1U)
#else /* if defined WMBUS_APP_APL */
     #define SERIAL_USB_TO_HOST_ENABLED      (0U)
     #define UART_ENABLED                    (0U)
#endif /* #ifdef (WMBUS_APP_SERIAL|WMBUS_APP_SNIFFER) */

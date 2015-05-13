#ifndef __WMBUS_HAL_UART_H__
#define __WMBUS_HAL_UART_H__

/**
  @file       wmbus_hal_uart.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Hardware Abstraction Layer Application Programming Interface
              for UART implementations.

  @defgroup WMBUS_HAL_UART WMBUS-HAL - Serial interface

  This module defines the Hardware Abstraction Layer for the serial interface
  enabling M2M communication, as required if the stack shall be accessed
  _remotely_ via the serial layer.

  This module is commonly implemented by a driver for the Universal Asynchronous
  Receiver Transmitter (UART) provided by almost every MCU.
  
*/
/**@{*/

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/

/** Enumeration of all selectable parity bits.  */
typedef enum
{
  /*! No parity */
  E_HAL_UART_PARITY_NONE,
  /*! Even parity */
  E_HAL_UART_PARITY_EVEN,
  /*! Odd parity */
  E_HAL_UART_PARITY_ODD
} E_HAL_UART_PARITY_t;

/*! Enumeration of all selectable data bits. */
typedef enum
{
  /*! 8 databits */
  E_HAL_UART_DATABITS_8,
  /*! 7 databits */
  E_HAL_UART_DATABITS_7
} E_HAL_UART_DATABITS_t;

/*! Enumeration of all selectable stop bits. */
typedef enum
{
  /*! 0 stopbits */
  E_HAL_UART_STOPBITS_0,
  /*! 1 stopbits */
  E_HAL_UART_STOPBITS_1,
  /*! 1,5 stopbits */
  E_HAL_UART_STOPBITS_15,
  /*! 2 stopbits */
  E_HAL_UART_STOPBITS_2
} E_HAL_UART_STOPBITS_t;

/*!@} end of WMBUS_HAL_UART_ENUMS */
/******************************************************************************/

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Initializes the UART.
          Within this function commonly the underlying UART interface will be
          configured accordingly.
  @note   In case of projects around the Wireless M-Bus stack by STACKFORCE,
          usually the settings are:
            115200 baud, 8 databits, no parity, 1 stopbit.
  @return Returns @c TRUE if initialization has been successful.
*/
bool_t wmbus_hal_uart_init(void);

/**
  @brief  Writes data to the UART.
          This function will be called by the serial layer of the stack when
          stack requests to send data to the connected host.
  @param  pc_data   Pointer to the data to be sent.
  @param  i_len     Number of bytes to be sent.
  @return Returns the number of bytes successfully sent.
*/
uint16_t wmbus_hal_uart_write(uint8_t *pc_data, uint16_t i_len);

/**
  @brief  Reads data from the UART.
          This function retrieves the requested amount of data from the UART
          driver.
  @param  pc_data   Pointer to the location where to store received data.
  @param  i_len     Number of bytes to be read.
  @return Number of successfully read bytes.
*/
uint16_t wmbus_hal_uart_read(uint8_t *pc_data, uint16_t i_len);

/*!
  @brief  Returns the number of ready-to-be-fetched bytes.
          This function is called by the stack in preparation to a receive
          operation and is for reading the number of received bytes, that
          are buffered by the stack.
  @return Number of received bytes.
*/
uint16_t wmbus_hal_uart_cntRxBytes(void);

/**
  @brief  Returns the current capability of transmitting bytes.
          In preparation to a transmit operation, the stack may request the
          number of bytes that could be transmitted. The UART driver shall
          return the number of bytes that possibly could be buffered until real
          transmission.
  @return Number of bytes that could possibly be transmitted.
*/
uint16_t wmbus_hal_uart_cntTxBytes(void);

/**
  @brief  Checks if there was a RX buffer overflow.
          This function will be called by the stack to double check if bytes
          have been lost, e.g. in case the stack has been receiving not
          plausible data.
          The UART driver should use this function to also reset its RX
          overflow error.
  @return Returns @c TRUE if there was an overflow.
*/
bool_t wmbus_hal_uart_isRxOverflow(void);

/**
  @brief  Signals that a serial telegram is complete.
          This function will be called by the serial layer, as soon as a
          complete serial telegram has been sent using the wmbus_hal_uart_write
          function.
*/
void wmbus_hal_uart_com_TxFinish(void);

/**
  @brief  Run the serial protocol state machine.
          In case the UART driver needs to maintain a state machine, the stack
          will provide main loop computing time by calling this function.
*/
void wmbus_hal_uart_com_run(void);

/**@}*/
#endif /* __WMBUS_HAL_UART_H__ */

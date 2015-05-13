#ifndef __SF_HAL_SPI_H__
#define __SF_HAL_SPI_H__

/**
  @file       sf_hal_spi.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL module implementing the SPI interface for the RF driver.

  @defgroup   SF_HAL_SPI Si446x driver SPI HAL
  
  The SPI HAL module provides access to the SPI which is needed to configure and
  exchange data with Si446x transceivers.
  
  Furthermore, the RF driver also requires to have the chip select handling
  implemented. This is chip select might be part of the MCU SPI periphery or
  might be independently configured GPIO. This is very dependent on the
  interconnection betweeen MCU and transceiver.

*/
/**@{*/


/*==============================================================================
                         CALLBACKS
==============================================================================*/

/**
  @brief Callback function on transmission and reception to notify RF module.
         Will be called each time the transmission of previously delivered data
         has finished.
 
  @param i_len       Length of the transmitted data.
*/
typedef void (*fp_hal_spi_event)(uint16_t i_len);

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Initialization of the SPI interface.
          This function will be called by the RF driver for initializing the
          SPI interface of the MCU as well as registering the callback
          pointers for signalling SPI Tx and Rx interrupts to the RF driver.
  @param  fp_rx   Callback pointer for signalling _Rx_ interrupts at the SPI.
  @param  fp_tx   Callback pointer for signalling _Tx_ interrupts at the SPI.
*/
void sf_hal_spi_init(fp_hal_spi_event fp_rx, fp_hal_spi_event fp_tx);

/** Will be called by the RF driver in order to _enable_ the chip select pin. */
void sf_hal_spi_chipSelect(void);

/** Will be called by the RF driver for _disabling_ the chip select pin. */
void sf_hal_spi_chipDeselect(void);

/**
  @brief  Exchanges multiple bytes interrupt driven via SPI .
          This functions handles a data exchange operation at the SPI. It'll
          transmit _i_len_ bytes located at address _pc_dataWrite_ and
          simultaneously stores _i_len_ bytes received at address location
          _pc_dataRead_. This function is non-blocking, uses ISRs for
          handling the exchange and is meant to handle many data bytes.
  @param  pc_dataWrite  Pointer to the data to be transmitted by writing to SPI.
  @param  pc_dataRead   Pointer where to store received data.
  @param  i_len         Number of bytes to be transmitted or received.
*/
void sf_hal_spi_xfer(uint8_t *pc_dataWrite, uint8_t* pc_dataRead,
                         uint16_t i_len);

/**
  @brief  Exchanges multiple data bytes via SPI.
          Compared to @ref sf_hal_spi_xfer this function does the very same,
          except of it is blocking during transmission. This type of SPI data
          exchange is meant for exchanging just a few bytes when ISR handling
          would cause too much overhead, e.g. when reading a single register
          from the transceiver.
  @param  pc_dataWrite  Pointer to the data to be transmitted by writing to SPI.
  @param  pc_dataRead   Pointer where to store received data.
  @param  i_len         Number of bytes to be transmitted or received.
  @return               TX: Status byte.
                        RX: Always 0.
*/
uint8_t sf_hal_spi_xferBlock(uint8_t *pc_dataWrite, uint8_t *pc_dataRead,
                                 uint16_t i_len);



/**@}*/
#endif /* __SF_HAL_SPI_H__ */

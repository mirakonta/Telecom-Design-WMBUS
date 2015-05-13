#ifndef __WMBUS_HAL_RF_H__
#define __WMBUS_HAL_RF_H__

/**
  @file       wmbus_hal_rf.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Hardware Abstraction Layer Application Programming Interface
              for radio implementations.

  @defgroup WMBUS_HAL_RF WMBUS-HAL - RF driver interface

  This module defines the Hardware Abstraction Layer for a radio driver.
  Please note, that the radio driver itself is responsible to define
  hardware requirements as communication interfaces respectively pins and
  ports of the MCU for control.
*/
/**@{*/

/*==============================================================================
                            MACROS
==============================================================================*/
/** These are macros required for usage within RX callback function
    fp_hal_rf_evt_rx which reports receptions to the PHY layer. They must not
    be changed. */
/**@{*/

/** Number of link quality bytes. Used within wmbus_hal_rf_rxInit. */
#define HAL_RF_QUALITY_LEN                    2U
/** This value indicates the beginning of the reception of a brand new
    telegram. */
#define HAL_RF_NEW_TLG                        0xFFFFU

/*========================= C-Mode ==================================*/
/** First byte of mode C preamble */
#define HAL_RF_MODE_C_PREAMBLE_FIRST          0x54U

/** Mode C preamble for frame type A */
#define HAL_RF_MODE_C_FRAMETYPE_A             0xCDU

/** Mode C preamble for frame type B */
#define HAL_RF_MODE_C_FRAMETYPE_B             0x3DU

/*========================= N-Mode ==================================*/
/** First byte of mode N sync word */
#define HAL_RF_MODE_N_SYNC1                   0xF6U

/*! Mode C preamble Frame type A.
    Second sync byte for A. */
#define HAL_RF_MODE_N_SYNC2_FRAME_A           0x8DU

/*! Mode C preamble Frame type B.
    Second sync byte for B. */
#define HAL_RF_MODE_N_SYNC2_FRAME_B           0x72U

/**@}*/

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/

/*! Enumeration of low power modi for the RF driver that are maintained by the
    stack. */
typedef enum
{
  /*! Shutdown mode */
  E_HAL_RF_POWERMODE_OFF,
  /*! Low power, register settings kept */
  E_HAL_RF_POWERMODE_IDLE,
  /*! Active power mode for Rx and Tx */
  E_HAL_RF_POWERMODE_RX,
  /*! Active power mode */
  E_HAL_RF_POWERMODE_MAX
} E_HAL_RF_POWERMODE_t;

/*! Enumeration for the wmbus_hal_rf_rxFinish function, specifying on how to
    proceed after finishing RX procedure. */
typedef enum
{
  /*! Running mode */
  E_HAL_RF_MODE_RUN,
  /*! Waiting */
  E_HAL_RF_MODE_WAIT
}E_HAL_RF_MODE_t;

/*! Enumeration required for wmbus_hal_rf_reset function specifying if the
    RF driver shall calibrate the transceiver after reset or not. */
typedef enum
{
  /*! Calibrate and store register values. */
  E_HAL_RF_CALIB_CALIBRATE_STORE,
  /*! Load stored values to registers. */
  E_HAL_RF_CALIB_LOAD,
  /*! No calibration as powering down. */
  E_HAL_RF_CALIB_OFF
} E_HAL_RF_CALIBRATE_t;

/*! Possible value for postamble that may be used by the RF driver after
    transmission. */
typedef enum
{
  /*! No postamble to send. */
  E_HAL_RF_POSTAMBLE_NONE = 0x00,
  /*! 0101 postamble to send. */
  E_HAL_RF_POSTAMBLE_ODD = 0x55,
  /*! 1010 postamble to send. */
  E_HAL_RF_POSTAMBLE_EVEN = 0xAA
} E_HAL_RF_POSTAMBLE_t;

/*! Enumeration of the status of a carrier sense. */
typedef enum
{
  /*! The transmission medium is free, no carrier detected. */
  E_HAL_RF_CS_STATUS_NO_CARRIER_DETECTED,
  /*! The transmission medium is occupied, carrier detected. */
  E_HAL_RF_CS_STATUS_CARRIER_DETECTED,
  /*! The chip is in an invalid state to perform carrier sense.  */
  E_HAL_RF_CS_STATUS_INVALID_STATE,
  /*! An error occured. CS could not be performed. */
  E_HAL_RF_CS_STATUS_ERROR
} E_HAL_RF_CS_STATUS_t;


/*==============================================================================
                         CALLBACKS
==============================================================================*/

/**
  @brief  Callback which indicates a finished transmission.
  @param  i_len         Length of the transmitted data.
*/
typedef void (*fp_hal_rf_evt_tx)(uint16_t i_len);

/**
  @brief  Callback which indicates a new reception.
  @param  i_len         Length of the received data.
  @param  e_frameType   Specifying the type of Wireless M-Bus frame.
*/
typedef void (*fp_hal_rf_evt_rx)(uint16_t i_len, E_WMBUS_FRAME_t e_frameType);


/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Initializes the RF module.
          This function simply initializes the RF driver itself. Before any
          communication starts, the stack will call wmbus_hal_rf_start.
  @return Returns @c TRUE if initialisation was successful.
*/
bool_t wmbus_hal_rf_init(void);

/**
  @brief  Sets the callback pointer for TX and RX events.
  @param  fp_tx Function pointer to the tx handle function.
  @param  fp_rx Function pointer to the rx handle function.
  @return Returns @c TRUE if initialisation has been succesful.
*/
bool_t wmbus_hal_rf_setCallback(fp_hal_rf_evt_tx fp_tx, fp_hal_rf_evt_rx fp_rx);

/**
  @brief  Turns off the supply voltage of the RF module.
*/
void wmbus_hal_rf_powerOff(void);

/**
  @brief  Turns on the supply voltage of the RF module.
*/
void wmbus_hal_rf_powerOn(void);

/**
  @brief  This function will be called once after the initialisation to start
          operation of the RF driver.
*/
void wmbus_hal_rf_start(void);

/**
  @brief  Initiates the transmission of data.
          This function will be called for initialising the transmission
          procedure.
  @param i_len        Total number of bytes to be sent.
  @param e_frameType  Specifies the Wireless M-Bus frame type to be used for
                      this transmission.
  @param   e_mode     Specifies the Wireless M-Bus mode to be used. In S and
                      T-Mode this parameter will not be observed from the lower
                      layers. In C-mode this parameter informs the lower layers
                      which RF configuration shall be used to communicate.
  @return             Returns whether TX initialisation was successful or failed.
*/
bool_t wmbus_hal_rf_txInit(uint16_t i_len, E_WMBUS_FRAME_t e_frameType,
                            E_WMBUS_MODE_t e_mode);

/**
  @brief  Transmits a chunk of data.
          For Wireless M-Bus the data will be sent chunk wise. Therefore all data
          to be transmitted will be delivered to the RF driver by sequentially
          calling this function.
  @warning  Prior to calling this function, wmbus_hal_rf_txInit must be
            called
  @param  pc_data     Pointer to data to be transmitted.
  @param  i_len       Number of bytes to be transmitted.
  @return             Returns whether transmission was successful or failed.
*/
bool_t wmbus_hal_rf_txData(uint8_t *pc_data, uint16_t i_len);

/**
  @brief  Finalises the transmission of data.
          This function will be called by the stack to finalise a transmission,
          independently if transmission succeeded of failed. At least
          wmbus_rf_txInit should be called before first.
  @return Returns whether finalisation was successful or failed.
*/
bool_t wmbus_hal_rf_txFinish(void);

/**
  @brief  Initiates the reception of data.
          As soon as the stack has been informed about the detection of a 
          telegram, the stack will initialise the reception procedure by calling
          this function.
  @param  pc_quality    Pointer to the memory where to store the link quality.
                        The number of quality values may differ between the RF
                        modules. The maximum number of bytes for the quality
                        field is specified by @c RF_QUALITY_LEN.
                        The parameter will be NULL if link quality is not
                        provided by the RF driver. Otherwise, the first byte is
                        always the RSSI value:
                          0xFF  no link quality available
                          FE  -254 dBm
                          ...
                          00  0 dBm
  @param c_len          Number of quality bytes to read.
  @return Returns @c FALSE if the receiving parameters could not be set
          successfully.
*/
bool_t wmbus_hal_rf_rxInit(uint8_t *pc_quality, uint8_t c_len);

/**
  @brief  Retrieves a chunk of data from the RF driver.
          Just like the transmission, reception of data is done chunk-wise. For
          this, the function will be called as fast as possible to retrieve all
          data received by the transceiver.
  @param  pc_data       Buffer to write the received data into.
  @param  i_len         Number of bytes to receive.
  @return Returns @c TRUE if the data could be received successfully.
*/
bool_t wmbus_hal_rf_rxData(uint8_t *pc_data, uint16_t i_len);

/**
  @brief  Finalises the reception of data.
          At least wmbus_rf_rxInit should be called before.
  @param  e_mode        Indicates the status the transceiver shall enter:
                          E_HAL_RF_MODE_WAIT: cleans the buffers and set the
                                              transceiver to IDLE state.
                          E_HAL_RF_MODE_RUN: re-enter RX state for further
                                             receptions.
  @return Returns @c TRUE if the finalisation was successful.
*/
bool_t wmbus_hal_rf_rxFinish(E_HAL_RF_MODE_t e_mode);

/**
  @brief  Resets the RF module.
          The stack will request the RF driver to reset any time the stack
          assumes the RF driver needs to re-enter a defined state.
  @param  e_calibrate     Specifies if the RF driver shall calibrate (and store
                          values), simply load existing values or omit
                          calibration.
  @return Returns @c TRUE when reset has been performed successfully.
*/
bool_t wmbus_hal_rf_reset(E_HAL_RF_CALIBRATE_t e_calibrate);

/**
  @brief  Sets the channel to use for RF communication.
  @param  i_channel       Channel to set.
  @return Returns @c TRUE if successful.
*/
bool_t wmbus_hal_rf_setRfChannel(uint16_t i_channel);

/**
  @brief  Sets the postamble to be used for transmissions.
  @param  e_postamble     Specifies the specific value of postamble to be used.
*/
void wmbus_hal_rf_txSetPostamble(E_HAL_RF_POSTAMBLE_t e_postamble);

/**
  @brief Returns the currently channel of the RF communication.
  @return          Current channel.
*/
uint16_t wmbus_hal_rf_getRfChannel(void);

/**
  @brief  Sets the power mode of the RF driver.
  @param  e_powermode     An enumerated value for the wanted mode.
  @return Returns @c TRUE if successful.
*/
bool_t wmbus_hal_rf_setPowerMode(E_HAL_RF_POWERMODE_t e_powermode);

/**
  @brief  Sets the signal strength for transmission.
          Requests the RF driver to set the output power for the transceiver
          to the appropriate value.
  @param  c_signal      Signal strength from -130dBm (0x0) to 125dBm (0xFE).
                        0xFF is reserved. If c_signal exceeds the minimum or
                        maximum TX power settings the output power will be set
                        to the lowest respective highest supported value.
*/
bool_t wmbus_hal_rf_setSignalStrength(uint8_t c_signal);

/**
  @brief  Sets the frequency offset of the carrier.
  @param  si_freqOffset Frequency offset in kHz.
  @return Returns @c TRUE if successful.
*/
bool_t wmbus_hal_rf_setFrequencyOffset(sint16_t si_freqOffset);

/**
  @brief  Get the signal strength of the transceiver.
          Requests the RF driver to read the currently configured output power.
  @return Current signal strength from -130dBm (0x0) to 125dBm (0xFE).
  @retval 0xFF  The value is invalid, maybe because this isn't supported by the
                transceiver or an invalid value has been read.
*/
uint8_t wmbus_hal_rf_getSignalStrength(void);

/**
  @brief  Requests the RF driver to enter sleep mode.
*/
void wmbus_hal_rf_sleep(void);

/**
  @brief  Requests the RF driver to wake up.
*/
void wmbus_hal_rf_wake(void);

/**
  @brief  Main loop computing time for the RF driver.
          The stack calls this function to forward computing time earned by the
          main loop to the RF driver.
          Commonly RF driver do not need generic computing time, but in case
          they need, this would be the entry point.
*/
void wmbus_hal_rf_run(void);

/**
  @brief  Retrieves the delay of receiving a telegram.
          Will be called for retrieving the delay in 500us steps the transceiver
          needs for receiving and forcing the data into the stack.
  @note   This function is required for some RF drivers only.
  @return Timeout in 500us steps Example: 1 = 500us, 3 = 1,5ms
*/
uint16_t wmbus_hal_rf_getTelegramDelay(void);

/*!
  @brief    Listens to the medium and reports whether its free or not.
            The functions uses the chip internal features to perform carrier
            sense. Before calling this function, the chip itself and the
            SPI communication interface must be initialized. The function sets
            the chip in the correct state to perform carrier sense.
  @param    sint8_t   The RSSI threshold in two's complement. After the RSSI
                      is valid, the value is compared with this threshold. When
                      the RSSI is bigger as the threshold, the chip detects a
                      carrier.
  @retval   E_HAL_RF_CS_STATUS_NO_CARRIER_DETECTED      No carrier detected.
  @retval   E_HAL_RF_CS_STATUS_CARRIER_DETECTED         Carrier detected.
  @retval   E_HAL_RF_CS_STATUS_INVALID_STATE            The chip is in an
                                                        invalid state.
  @retval   E_HAL_RF_CS_STATUS_ERROR                    An error occured and CS
                                                        could not be performed.
*/
E_HAL_RF_CS_STATUS_t wmbus_hal_rf_carrierSense(sint8_t c_rssiThres);

/**
  @brief  Sets the data rate of the transceiver.
          Requests the RF driver to configure the transceiver for the requested
          data rate on transmission and receptions.
  @param  e_dataRate    Data rate to set.
  @return bool_t        Returns @c TRUE if the data rate was set successfully.
*/
bool_t wmbus_hal_rf_setDataRate(E_WMBUS_DATA_RATE_t e_dataRate);

/**
  @brief  Enables mode C collector RX configuration for receiving mode T and C.
          Please note that this feature is optional as it is limited to be used
          for mode C collectors only. Additionally, this feature must be
          supported by the underlying RF driver. You may ask your support
          contact for further information on this feature.
          The current tuning configuration can be requested by using
          wmbus_hal_rf_getRxSenseTuning.
  @param  e_mode        This can be either E_WMBUS_MODE_T or E_WMBUS_MODE_C to
                        tune for for mode T or mode C meters.
  @return Returns @c TRUE if tuning was successful.
*/
bool_t wmbus_hal_rf_setRxSenseTuning(E_WMBUS_MODE_t e_mode);

/**
  @brief  Returns the current transceiver RX configuration.
          Returns the current transceiver RX configuration whether it is tuned
          for reception of either mode T or mode C meters.
          Please note that this feature is optional as it is limited to be used
          for mode C collectors only. Additionally, this feature must be
          supported by the underlying RF driver. You may ask your support
          contact for further information on this feature.
          The tuning configuration can be set by using
          wmbus_hal_rf_setRxSenseTuning.
  @return This can be either E_WMBUS_MODE_T or E_WMBUS_MODE_C.
*/
E_WMBUS_MODE_t wmbus_hal_rf_getRxSenseTuning(void);

/**@}*/
#endif /* __WMBUS_HAL_RF_H__ */

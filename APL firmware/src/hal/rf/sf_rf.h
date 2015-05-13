/*============================================================================*/
/*!
 * @file    sf_rf.h
 * @author  © by STACKFORCE, Heitersheim, Germany, http://www.stackforce.de
 * @brief   Internal defines, structures, enums and constants for the transceiver
 *
 *
 * $Revision$
 *   $Author$
 *     $Date$
 */
/*============================================================================*/

#ifndef __RF_H__
#define __RF_H__

#ifndef __DECL_RF_H__
#define __DECL_RF_H__ extern
#else
#define __RF_INIT_VAR__
#endif /* __DECL_RF_H__ */

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/

#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\utils\wmbus_api.h"
#include "inc\prv\cfg\wmbus_config.h"

/*==============================================================================
                            TYPEDEF STRUCTS
==============================================================================*/
/*! Register configuration. */
PACKED_STRUCT( typedef struct S_RF_REGISTER_T
{
  /*! Nameaddress of a register. */
  uint16_t i_name;
  /*! Value of the register. */
  uint8_t c_value;
}, s_rf_register_t);

/*==============================================================================
                            DEFINES
==============================================================================*/
/*! Number of link quality bytes. */
#define RF_QUALITY_LEN                    2U
/*! New telegram available. */
#define RF_NEW_TLG                        0xFFFFU

/*========================= C-Mode ==================================*/
/*! Mode C first byte of Sync Word */
#define RF_MODE_C_PREAMBLE_FIRST          0x54U

/*! Mode C preamble Frame type A */
#define RF_MODE_C_FRAMETYPE_A             0xCDU

/*! Mode C preamble Frame type B */
#define RF_MODE_C_FRAMETYPE_B             0x3DU

/*========================= N-Mode ==================================*/
/*! Mode N first byte of Sync Word */
#define RF_MODE_N_SYNC1                   0xF6U

/*! Mode C preamble Frame type A.
    Second sync byte for A. */
#define RF_MODE_N_SYNC2_FRAME_A           0x8DU

/*! Mode C preamble Frame type B.
    Second sync byte for B. */
#define RF_MODE_N_SYNC2_FRAME_B           0x72U

/*==============================================================================
                            ENUMS
==============================================================================*/
/*!
 * Enumeration of channels avaible in N mode.
 * 6 channels, 12.5kHz spacing, one overlapping channel
 */
typedef enum
{

#if WMBUS_CHECK_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_N | WMBUS_RF_TX_CHIPRATE_N)
  /*! 169.40625 MHz, mode N1/2a, 12.5kHz channel */
  E_RF_CHANNR_N_1A,
  /*! 169.41875 MHz, mode N1/2b, 12.5kHz channel */
  E_RF_CHANNR_N_1B,
  /*! 169.43125 MHz, mode N1/2c, 12.5kHz channel */
  E_RF_CHANNR_N_2A,
  /*! 169.44375 MHz, mode N1/2d, 12.5kHz channel */
  E_RF_CHANNR_N_2B,
  /*! 169.45625 MHz, mode N1/2e, 12.5kHz channel */
  E_RF_CHANNR_N_3A,
  /*! 169.46875 MHz, mode N1/2f, 12.5kHz channel */
  E_RF_CHANNR_N_3B,
  /*! 169.43750 MHz, mode N2g, 50kHz channel */
  E_RF_CHANNR_N_0,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_N | WMBUS_RF_RX_CHIPRATE_N) */

#if WMBUS_CHECK_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_4800baud | WMBUS_RF_TX_CHIPRATE_4800baud)
  /*! 868.03 MHz */
  E_RF_CHANNR_R2_METER_0,
  /*! 868.09 MHz */
  E_RF_CHANNR_R2_METER_1,
  /*! 868.15 MHz  */
  E_RF_CHANNR_R2_METER_2,
  /*! 868.21 MHz  */
  E_RF_CHANNR_R2_METER_3,
  /*! 868.27 MHz  */
  E_RF_CHANNR_R2_METER_4,
  /*! 868.33 MHz: data collector  */
  E_RF_CHANNR_R2_COLLECTOR,
  /*! 868.39 MHz  */
  E_RF_CHANNR_R2_METER_5,
  /*! 868.45 MHz  */
  E_RF_CHANNR_R2_METER_6,
  /*! 868.51 MHz  */
  E_RF_CHANNR_R2_METER_7,
  /*! 868.57 MHz  */
  E_RF_CHANNR_R2_METER_8,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_4800baud | WMBUS_RF_TX_CHIPRATE_4800baud) */

#if WMBUS_CHECK_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_32768baud | WMBUS_RF_TX_CHIPRATE_32768baud)
  /*! 868.30 MHz, mode S1/S2 and T2 meter(rx), T2 collector(tx), 47kHz channel */
  E_RF_CHANNR_868_30,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_32768baud | WMBUS_RF_TX_CHIPRATE_32768baud) */

#if WMBUS_CHECK_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_100000baud | WMBUS_RF_TX_CHIPRATE_100000baud)
  /*! 868.95 MHz, mode C1/C2/T1/T2 Meter(tx),
      C1/C2/T1/T2 collector(rx) 50kHz channel */
  E_RF_CHANNR_868_95,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_100000baud | WMBUS_RF_TX_CHIPRATE_100000baud) */

#if WMBUS_CHECK_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_50000baud | WMBUS_RF_TX_CHIPRATE_50000baud)
  /*! 869.52 MHz, mode C2 meter(rx), C2 collector(tx) */
  E_RF_CHANNR_869_52,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_50000baud | WMBUS_RF_TX_CHIPRATE_50000baud) */

  /*! Maximal number of channels */
  E_RF_CHANNR_N_MAX
  /* channels 1, 2, 3 currently not supported */
} E_RF_CHANNR_N_t;

typedef enum
{
  /* Dummy entry to support further #if */
  E_RF_DUMMY = (E_RF_CHANNR_N_MAX - 1U),
#if WMBUS_CHECK_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_N | WMBUS_RF_TX_CHIPRATE_N)
  /*! register accesses to switch to receive mode */
  E_RF_N_SETTINGS_RX,
  /*! register accesses to switch to transmit mode */
  E_RF_N_SETTINGS_TX,
  /*! 169.43125 MHz, mode N1/2c, 12.5kHz channel */
  E_RF_N_BASIC_WIDE_INDEX,
  /*! 169.44375 MHz, mode N1/2d, 12.5kHz channel */
  E_RF_N_BASIC_NARROW_INDEX,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_N | WMBUS_RF_TX_CHIPRATE_N) */

#if WMBUS_CHECK_RX_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_32768baud)
  /*! register accesses to switch to receive mode. S1/S2 collector S2/T2 meter*/
  E_RF_868_30_SETTINGS_RX,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_32768baud ) */

#if WMBUS_CHECK_TX_CHIPRATE_or(WMBUS_RF_TX_CHIPRATE_32768baud)
  /*! register accesses to switch to transmit mode. S1/S2 meter S2/T2 collector*/
  E_RF_868_30_SETTINGS_TX,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_TX_CHIPRATE_32768baud) */

#if WMBUS_CHECK_RX_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_100000baud)
 /*! register accesses to switch to receive mode. C1/C2/T1/T2 collector */
  E_RF_868_95_SETTINGS_WIDE_RX,
  /*! register accesses to switch to receive mode. C1/C2 collector */
  E_RF_868_95_SETTINGS_NARROW_RX,
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_100000baud) */

#if WMBUS_CHECK_TX_CHIPRATE_or(WMBUS_RF_TX_CHIPRATE_100000baud)
  /*! register accesses to switch to transmit mode. C1/C2/T1/T2 meter*/
  E_RF_868_95_SETTINGS_TX,
 #endif /* _IF_CHIPRATE_or(WMBUS_RF_TX_CHIPRATE_100000baud) */
 /*! register accesses to switch to receive mode. C2 meter */

#if WMBUS_CHECK_RX_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_50000baud)
  E_RF_869_52_SETTINGS_RX,
  /*! register accesses to switch to transmit mode. C2 collector */
#endif /* _IF_CHIPRATE_or(WMBUS_RF_RX_CHIPRATE_50000baud) */

#if WMBUS_CHECK_TX_CHIPRATE_or(WMBUS_RF_TX_CHIPRATE_50000baud)
  E_RF_869_52_SETTINGS_TX,
  /*! Maximal number of settings */
#endif /* _IF_CHIPRATE_or(WMBUS_RF_TX_CHIPRATE_50000baud) */
  E_RF_NOF_SETTINGS
  /* channels 1, 2, 3 currently not supported as not defined yet */
} E_RF_SETTINGS_t;

/*! Possible errors */
typedef enum
{
  /* Indicates that the cts flag was polled over 10 ms without getting a
     positive response */
  E_RF_ERROR_CTS = 0x01,
} E_RF_ERROR_t;

/*! RF GPIO's */
typedef enum
{
  /*! No GPIO, functionality disabled. */
  E_RF_GPIO_NONE  = (0U),
  /*! RF GPIO 0 */
  E_RF_GPIO_0     = (1U),
  /*! RF GPIO 1 */
  E_RF_GPIO_1     = (2U),
  /*! RF GPIO 2 */
  E_RF_GPIO_2     = (3U),
  /*! RF GPIO 3 */
  E_RF_GPIO_3     = (4U)
} E_RF_GPIO_t;

/*! Enumeration of possible low power modi. */
typedef enum
{
  /*! Shutdown mode */
  E_RF_POWERMODE_OFF,
  /*! Low power, register settings kept */
  E_RF_POWERMODE_IDLE,
  /*! Active power mode for Rx and Tx */
  E_RF_POWERMODE_RX,
  /*! Active power mode */
  E_RF_POWERMODE_MAX
} E_RF_POWERMODE_t;

/* Enumeration for the sf_rf_reset() function. */
typedef enum
{
  /*! Running mode */
  E_RF_MODE_RUN,
  /*! Waiting */
  E_RF_MODE_WAIT
}E_RF_MODE_t;

/*! RF calibration: selection during reset. */
typedef enum
{
  /*! Calibrate and store register values. */
  E_RF_CALIB_CALIBRATE_STORE,
  /*! Load stored values to registers. */
  E_RF_CALIB_LOAD,
  /*! No calibration as powering down. */
  E_RF_CALIB_OFF
} E_RF_CALIBRATE_t;

/*! Possible postambles */
typedef enum
{
  /*! No postamble to send. */
  E_RF_POSTAMBLE_NONE = 0x00,
  /*! 0101 postamble to send. */
  E_RF_POSTAMBLE_ODD = 0x55,
  /*! 1010 postamble to send. */
  E_RF_POSTAMBLE_EVEN = 0xAA
} E_RF_POSTAMBLE_t;

/*==============================================================================
                         CALLBACKS
==============================================================================*/
/*============================================================================*/
/*!
 * \brief Callback which indicates a finished transmission.
 *
 * \param i_len       Length of the transmitted data.
 */
/*============================================================================*/
typedef void (*fp_rf_evt_tx)(uint16_t i_len);

/*============================================================================*/
/*!
 * \brief Callback which indicates a new reception.
 *
 * \param i_len       Length of the received data.
 * \param e_frameType Wireless M-Bus frame type.
 */
/*============================================================================*/
typedef void (*fp_rf_evt_rx)(uint16_t i_len, E_WMBUS_FRAME_t e_frameType);

/*==============================================================================
                            VARIABLES
==============================================================================*/

/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/
/*============================================================================*/
/*!
 * @brief  Sets the GPIO's of the radio the stack shall use.
 *
 * @param  e_gdo0 - Radio gpio connected to gdo0.
 * @param  e_gdo2 - Radio gpio connected to gdo2.
 *
 * @return TRUE, if operation successful.
 */
/*============================================================================*/
bool_t sf_rf_setInternalGpio(E_RF_GPIO_t e_gdo0, E_RF_GPIO_t e_gdo2);

/*============================================================================*/
/*!
 * @brief  Sets the functionality of a GPIO of the radio.
 *
 * @param  e_gpio - Radio gpio to configure.
 * @param  c_registerValueRx - The register value to set in RX mode.
 * @param  c_registerValueTx - The register value to set in TX mode.
 *
 * @return TRUE, if operation successful.
 * @return FALSE, if the GPIO is in use by another module.
 */
/*============================================================================*/
bool_t sf_rf_setGpioFunc(E_RF_GPIO_t e_gpio,
                             uint8_t c_registerValueRx,
                             uint8_t c_registerValueTx);


/*============================================================================*/
/*!
 * \brief Initializes the RF module.
 *        To start the RF module the function sf_rf_reset() has to be called.
 *
 * \param  fp_tx Function pointer to the tx handle function.
 * \param  fp_rx Function pointer to the rx handle function.
 *
 * \return    \ref TRUE if successful.
 */
/*============================================================================*/
bool_t sf_rf_init();

/*============================================================================*/
/*!
 * \brief  Sets the callbacks for TX and RX events.
 *
 * \param  fp_tx Function pointer to the tx handle function.
 * \param  fp_rx Function pointer to the rx handle function.
 *
 * \return TRUE, if successfully, FALSE otherwise.
 */
/*============================================================================*/
bool_t sf_rf_setCallback(fp_rf_evt_tx fp_tx, fp_rf_evt_rx fp_rx);

/*============================================================================*/
/*!
 * \brief   Turns off the supply voltage of the RF module.
 */
/*============================================================================*/
void sf_rf_powerOff(void);

/*============================================================================*/
/*!
 * \brief   Turns on the supply voltage of the RF module.
 */
/*============================================================================*/
void sf_rf_powerOn(void);

/*============================================================================*/
/*!
 * \brief   Starts the rf module.
 */
/*============================================================================*/
void sf_rf_start(void);

/*============================================================================*/
/*!
 * \brief Initiates the transmission of data.
 *
 * \param i_len         Total number of bytes to send.
 * \param e_frameType   Wireless M-Bus frame type.
 * \param   e_mode      Wireless Mbus-mode of the meter. In S and T-Mode this
 *                      parameter will not be observed from the lower layers.
 *                      In C-mode this parameter inform the lower layers which
 *                      rf configuration is used to comunicate with the meter.
 *
 * \return              Returns @ref FALSE if tx-initialisation was not
 *                      successful.
 */
/*============================================================================*/
bool_t sf_rf_txInit(uint16_t i_len, E_WMBUS_FRAME_t e_frameType,
                            E_WMBUS_MODE_t e_mode);

/*============================================================================*/
/*!
 * \brief Sends data. @ref sf_rf_txInit() has to be called before first sending
 *        data (for each telegram).
 *        Sending is finished if the number of really sent bytes reaches the
 *        number of total bytes to send (c.f. sf_rf_txInit).
 *
 * \param pc_data       Pointer to the data to transmit.
 * \param i_len         Number of bytes to transmit.
 *
 * \return              Returns \ref TRUE if the transmission was successful.
 */
/*============================================================================*/
bool_t sf_rf_txData(uint8_t *pc_data, uint16_t i_len);

/*============================================================================*/
/*!
 * \brief Finalizes the transmission of data. At least @ref sf_rf_txInit()
 *        should be called before first.
 *
 * \return Returns \ref TRUE if the finalisation was successful.
 */
/*============================================================================*/
bool_t sf_rf_txFinish(void);

/*============================================================================*/
/*!
 * \brief Initiates the reception of data.
 *
 * \param pc_quality    Pointer to the memory where to store the link quality.
 *                      The number of quality values may differ between the RF
 *                      modules. The max number of bytes for the quality field
 *                      is specified by \ref RF_QUALITY_LEN.
 *                      NULL if link quality has not to be read.
 *                      The first byte is always the RSSI value:
 *                        0xFF  no link quality available
 *                        FE  -254 dBm
 *                        ...
 *                        00  0 dBm
 * \param c_len         Number of quality bytes to read.
 *
 * \return              Returns \ref FALSE if the receiving parameters could not be
 *                      set successfully.
 */
/*============================================================================*/
bool_t sf_rf_rxInit(uint8_t *pc_quality, uint8_t c_len);

/*============================================================================*/
/*!
 * \brief Retrieves the Rx-data. \ref sf_rf_rxInit() must have been called
 *        before!
 *
 * \param pc_data       Buffer to write the received data into.
 * \param i_len         Number of bytes to receive.
 *
 * \return              \ref TRUE if the data could be received successfully.
 */
/*============================================================================*/
bool_t sf_rf_rxData(uint8_t *pc_data, uint16_t i_len);

/*============================================================================*/
/*!
 * \brief Finalizes the reception of data. At least @ref sf_rf_rxInit() should
 *        be called before first.
 *
 * \param e_mode      Indicates if the tranceiver will intermeaditly go in receive mode.
 *                    E_HAL_RF_MODE_WAIT: cleans the buffers and set the trx in IDLE mode
 *                    E_HAL_RF_MODE_RUN: resets the trx and go in rx mode
 *
 * \return              Returns \ref TRUE if the finalization was successful.
 */
/*============================================================================*/
bool_t sf_rf_rxFinish(E_RF_MODE_t e_mode);

/*============================================================================*/
/*!
 * \brief Resets the RF module.
 *
 * \param e_calibrate   Run calibration and store values, load values or neglect.
 *
 * \return    \ref TRUE if successful.
 */
/*============================================================================*/
bool_t sf_rf_reset(E_RF_CALIBRATE_t e_calibrate);

/*============================================================================*/
/*!
 * \brief Sets the channel to use for RF communication.
 *
 * \param i_channel      Channel to set.
 *
 * \return    \ref TRUE if successful.
 */
/*============================================================================*/
bool_t sf_rf_setRfChannel(uint16_t i_channel);

/*============================================================================*/
/*!
 * \brief   Sets the postamble to use for the packet that is currently being sent
 *
 * \param   e_postamble   Postamble to use.
 *
 * \return   void.
 */
/*============================================================================*/
void sf_rf_txSetPostamble(E_RF_POSTAMBLE_t e_postamble);

/*============================================================================*/
/*!
 * \brief Returns the currently channel of the RF communication.
 *
 * \return          Current channel.
 */
/*============================================================================*/
uint16_t sf_rf_getRfChannel(void);

/*============================================================================*/
/*!
 * \brief Sets the power mode of the rf-module.
 *
 * \param e_powermode       An enumerated value for the wanted mode.
 *
 * \return    \ref TRUE if successful.
 */
/*============================================================================*/
bool_t sf_rf_setPowerMode(E_RF_POWERMODE_t e_powermode);

/*============================================================================*/
/*!
 * \brief Sets the signal strength of the rf-module.
 *
 * \param c_signal       Signal strength from -130dBm (0x0) to 125dBm (0xFE).
 *                       0xFF is reserved. If c_signal exceeds the minimum ore
 *                       maximum tx power settings the outputpower will be set
 *                       to the next supported value.
 */
/*============================================================================*/
bool_t sf_rf_setSignalStrength(uint8_t c_signal);

/*============================================================================*/
/*!
 * \brief Get the signal strength of the rf-module.
 *
 * \return               Current signal strength from -130dBm (0x0) to 125dBm (0xFE).
 *                       If 0xFF is returned the value of in the PATABLE is
 *                       not known.
 */
/*============================================================================*/
uint8_t sf_rf_getSignalStrength(void);

/*============================================================================*/
/*!
 * \brief  Sets the RF module to sleep mode.
 */
/*============================================================================*/
void sf_rf_sleep(void);

/*============================================================================*/
/*!
 * @brief  TRUE if the routine is handled.
 */
/*============================================================================*/
bool_t sf_rf_isr(void);

/*============================================================================*/
/*!
 * \brief  Wakes the RF module up.
 */
/*============================================================================*/
void sf_rf_wake(void);

/*============================================================================*/
/*!
 * \brief  Control function for the rf module. This function will check if the
           tranceiver is in the right state.
 */
/*============================================================================*/
void sf_rf_run(void);

/*============================================================================*/
/*!
 * \brief Get the delay in 500us steps which the transceiver needs to receive and
 *        force the data to the stack.
 * \return timeout in 500us steps Example: 1 = 500us, 3 = 1,5ms
 */
/*============================================================================*/
uint16_t sf_rf_getTelegramDelay(void);

/*============================================================================*/
/*!
 * @brief  Enable rf interrupt service routine.
 */
/*============================================================================*/
void sf_rf_isrEnable(void);

/*============================================================================*/
/*!
 * @brief  Disable rf interrupt service routine.
 */
/*============================================================================*/
void sf_rf_isrDisable(void);

/*============================================================================*/
/*!
 * @brief  Test function to generate only a modulated carrier wave.
 *         Should be called in a while(true) loop.
 * @return TRUE, if test mode could be activated, ohterwise FALSE
 */
/*============================================================================*/
bool_t sf_rf_test_generate_carrier_modulated(void);

/*============================================================================*/
/*!
 * @brief  Test function to generate only a carrier wave. Should be called
 *         in a while(true) loop.
 * @return TRUE, if test mode could be activated, ohterwise FALSE
 */
/*============================================================================*/
bool_t sf_rf_test_generate_carrier(void);

/*============================================================================*/
/*!
 * @brief  Resets the deviation of the radio module
 *
 * @return TRUE, if deviation was resetted successfully, otherwise FALSE
 */
/*============================================================================*/
bool_t sf_rf_test_reset_deviation(void);

#if WMBUS_RX_ENABLED
/*============================================================================*/
/*!
 * @brief  Test function to set the radio modul in RX mode. Should be called
 *         in a while(true) loop.
 * @return TRUE, if test mode could be activated, ohterwise FALSE
 */
/*============================================================================*/
bool_t sf_rf_test_set_to_rx(void);
#endif /* WMBUS_RX_ENABLED */

/*============================================================================*/
/*!
 * @brief  Sets the radio module to idle mode.
 *
 * @return TRUE, if radio module could be set to idle mode, otherwiese FLASE.
 */
/*============================================================================*/
bool_t sf_rf_test_set_to_idle(void);

/*============================================================================*/
/*!
 * @brief Callback which indicates that an critical error occured.
          This event must be handled in the file target.c
 * @param E_RF_ERROR_t      Occured error.
 */
/*============================================================================*/
void sf_rf_evt_criticalError(E_RF_ERROR_t e_err);



#endif /* __RF_H__ */

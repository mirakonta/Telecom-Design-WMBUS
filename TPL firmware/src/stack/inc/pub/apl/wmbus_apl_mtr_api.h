#ifndef __APPLICATIONLAYER_MTR_API_H__
#define __APPLICATIONLAYER_MTR_API_H__
#ifndef __DECL_APPLICATIONLAYER_MTR_API_H__
#define __DECL_APPLICATIONLAYER_MTR_API_H__ extern
#else
#define __DECL_APPLICATIONLAYER_MTR_API_H__
#endif /* __APPLICATIONLAYER_MTR_API_H__ */

/**
  @file       wmbus_apl_mtr_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Application Layer API of Wireless M-Bus Meter Device.

              Include before:
              - wmbus_typedefs.h
              - wmbus_api.h
              - stezdn_clock.h
              - wmbus_global.h
              - wmbus_apl_api.h
*/

/** @example main_meter.c
 * Meter application layer example. */

/*! @defgroup WMBUS_APL_MTR Application Layer Interface Description for a Meter Device.
 *  This section describes the API for the STACKFORCE application layer.
 *  @{
 */

/*! \defgroup WMBUS_APL_MTR_COMPILE_TIME_SET Meter compile time settings
 *  Device specific compile time settings for a meter device.
 *  @{
 */
/*==============================================================================
                            DEFINES
==============================================================================*/

#ifndef APL_IGNORE_UNENCRYPTED_COLLECTOR_COMMANDS
  /*! Disables the reception of unencrypted commands
      (sent from collector to meter)*/
  #define APL_IGNORE_UNENCRYPTED_COLLECTOR_COMMANDS           TRUE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning APL_IGNORE_UNENCRYPTED_COLLECTOR_COMMANDS set to default value: TRUE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* APL_IGNORE_UNENCRYPTED_COLLECTOR_COMMANDS */

/*========================= INSTALLATION MODE ================================*/
#ifndef APL_INSTALL_RETRIES
  /*! If the device is in installation mode, run installation maximal 3 times.
      Set this defined to 0 to repeat the telegram endless. */
  #define APL_INSTALL_RETRIES           6U

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning APL_INSTALL_RETRIES set to default value: 3
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* APL_INSTALL_RETRIES */

/*========================= DEBUGGING ========================================*/
#ifndef APL_METER_SPONTANEOUS_CONF
  /*! Enables sending spontaneous telegrams from meter device without reply. */
  #define APL_METER_SPONTANEOUS_CONF  FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning APL_METER_SPONTANEOUS_CONF set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* APL_METER_SPONTANEOUS_CONF */

/*!@} end of WMBUS_APL_MTR_COMPILE_TIME_SET */
/******************************************************************************/

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/

/*! \defgroup WMBUS_APL_MTR_STRUCTS Meter structures
 *  Device specific structures for a meter device.
 *  @{
 */
/*==============================================================================
                             TYPEDEF STRUCTS
==============================================================================*/

/*! Start structure to start a meter device */
PACKED_STRUCT(typedef struct S_APL_STARTMETERATTR_T
{
  /*! Common start attributes for all WMBus device types */
  s_apl_startCommonAttr_t s_apl_startCommonAttr;
  /*! Key of the device */
  uint8_t* pc_ownKey;
  /*! The address of the collector. If the collector is not known, set it to
      zero. */
  s_wmbus_addr_t* s_collectorAddr;
  /*! Tell the device to bind to a data collector. Only possible, if the
      collector address is valid. */
  bool_t b_connected;
  /*! The interval for periodical user data in ms. */
  uint32_t l_interval;
}, s_apl_startMeterAttr_t);

/*!@} end of WMBUS_APL_MTR_STRUCTS */
/******************************************************************************/

/*! \defgroup WMBUS_APL_MTR_CALLBACKS Meter event callbacks
 *  Device specific callbacks for a meter device.
 *  @{
 */
/*==============================================================================
                            CALLBACK FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  This function is called if user data class 1 (alarm) is requested.
 *         An alarm telegram (CI=74) is created. The content of
 *         the telegram has to be written with function
 *         wmbus_apl_writeApplicationError().
 *
 *         Be careful: To signal, that there is an alarm available, before
 *                     wmbus_apl_setErrorAvailable () should be used. This method
 *                     sets a flag which is deleted if a user data class 1
 *                     request is received.
 *
 * @return  Alarm code to transmit.
 */
/*============================================================================*/
uint8_t wmbus_apl_evt_alarmRequested(void);

/*============================================================================*/
/*!
 * @brief  This function is called if user data class 2 is requested.
 *         Now meter device data is requested. The respond telegram is created
 *         automatically, the data has to be added to the telegram by
 *         function wmbus_apl_writeData().
 *
 * @param c_tlgId       Id of the respond telegram.
 * @param b_periodical  @ref TRUE if periodical user data is requested.
 * @return  Set if a respond has to be sent.
 *          Not set if the request has to be ignored.
 */
/*============================================================================*/
bool_t wmbus_apl_evt_userDataRequested(uint8_t c_tlgId, bool_t b_periodical);

/*!@} end of WMBUS_APL_MTR_CALLBACKS */
/******************************************************************************/

/*! \defgroup WMBUS_APL_MTR_API Meter public API functions
 *  Device specific public APIs for a meter device.
 *  @{
 */
/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  Initializes the application layer for the device type meter.
 */
/*============================================================================*/
void wmbus_apl_mtr_init(void);

/*============================================================================*/
/*!
 * @brief  Starts the application layer for the device type meter.
 *
 * @param  s_startAttr Start attributes for the meter device.
 *
 * @return Status of the operation @ref E_APL_STATUS_t
 */
/*============================================================================*/
E_APL_STATUS_t wmbus_apl_mtr_start(s_apl_startMeterAttr_t* s_startAttr);

/*============================================================================*/
/*!
 * @brief  Default running method of meter device application layer.
 *
 *         This method has to be called as often as possible in order to let the
 *         stack process its tasks in time.
 */
/*============================================================================*/
void wmbus_apl_mtr_run(void);

#if !(DSMR_V405_ENABLED)
/*============================================================================*/
/*!
 * @brief  Gets the alarm code from APL.
 *
 * @return  Alarm code.
 */
/*============================================================================*/
uint8_t wmbus_apl_mtr_getAlarmCode(void);
#endif /* !(DSMR_V405_ENABLED) */

#if !(DSMR_V405_ENABLED)
/*============================================================================*/
/*!
 * @brief  Sets the alarm code in APL.
 *
 * @param c_alarmCode       Alarm Code to be set.
 */
/*============================================================================*/
void wmbus_apl_mtr_setAlarmCode(uint8_t c_alarmCode);
#endif /* !(DSMR_V405_ENABLED) */

#if !(DSMR_V405_ENABLED)
/*============================================================================*/
/*!
 * @brief  Clears the given alarm code in APL.
 * @param c_alarmCode       Alarm Code to be cleared.
 */
/*============================================================================*/
void wmbus_apl_mtr_clrAlarmCode(uint8_t c_alarmCode);
#endif /* !(DSMR_V405_ENABLED) */

/*============================================================================*/
/*!
 * @brief  Creates an installation request.
 *
 * @return Id of the request telegram.
 *         @ref APL_ERR_TLG_NOT_AVAILABLE if the request could not be sent.
 */
/*============================================================================*/
uint8_t wmbus_apl_mtr_sendInstallationRequest(void);

/*============================================================================*/
/*!
 * @brief  Sets the long header address for the application layer of an outgoing
 *         telegram. By default, this is identical to the own address, but this
 *         function call permits to enter the address of e.g. a connected meter
 *         Before using this function, create the telegram, and pass the ID here.
 *
 * @param c_tlgId       ID of the outgoing telegram.
 * @param ps_addr       Address to use for this telegram.
 *
 * @return  Success: FALSE if the telegram does not exist or has no long header
 */
/*============================================================================*/
bool_t wmbus_apl_mtr_setLongHeaderAddr(uint8_t c_tlgId, s_wmbus_addr_t *ps_addr);

/*============================================================================*/
/*!
 * @brief  Sets the error flag (aka. status byte) of the APL header of the meter
 *         telegram. The meter will afterwards send its telegram with the Status
 *         field according to value that has been set from this function.
 *         To clear status byte, call function @ref wmbus_apl_mtr_clrErrorFlag().
 * @param c_error   This parameters is to signalize a temporary or
 *                  permanent error (cf. EN 13757-3 Table 5).
 * @return          TRUE if successful (when the function is called in meter device)
 *                  FALSE if not successful
 */
/*============================================================================*/
bool_t wmbus_apl_mtr_setErrorFlag(uint8_t c_error);

/*============================================================================*/
/*!
 * @brief  Allowes to clear application error flags. The application error
 *         flags are never cleared automatically by the application layer.
 * @param c_error   Allowes to select one or more error to clear
 *                  (cf. EN 13757-3 Table 5).
 */
/*============================================================================*/
void wmbus_apl_mtr_clrErrorFlag(uint8_t c_error);

/*============================================================================*/
/*!
 * @brief  Reads if there is a set application error.
 * @return          Set error.
 */
/*============================================================================*/
uint8_t wmbus_apl_mtr_getErrorFlag(void);

/*============================================================================*/
/*!
 * @brief  Writes the encryption key.
 *
 * @param pc_key  Storage to load the key from.
 * @param c_len   Size of @ref pc_key.
 * @return  @ref TRUE if the key is written successfully. FALSE otherwise.
 */
/*============================================================================*/
bool_t wmbus_apl_mtr_setKey(uint8_t* pc_key, uint8_t c_len);

/*============================================================================*/
/*!
 * @brief  Reads the encryption key.
 *
 * @param pc_key  Storage to save the key into.
 * @param c_len   Size of @ref pc_key.
 * @return  @ref TRUE if the key is read successfully. FALSE otherwise.
 */
/*============================================================================*/
bool_t wmbus_apl_mtr_getKey(uint8_t* pc_key, uint8_t c_len);

/*============================================================================*/
/*!
 * @brief  Sets the address of the connected collector.
 *
 * @param ps_collectorAddr  Address of the collector.
 */
/*============================================================================*/
void wmbus_apl_mtr_setCollectorAddress(s_wmbus_addr_t *ps_collectorAddr);

/*============================================================================*/
/*!
 * @brief  Gets the address of the connected collector.
 *
 * @param ps_collectorAddr  Address of the collector.
 */
/*============================================================================*/
void wmbus_apl_mtr_getCollectorAddress(s_wmbus_addr_t *ps_collectorAddr);

/*============================================================================*/
/*!
 * @brief  Sets the periodical interval of the meter device.
 *
 * @param l_interval  Periodical interval in milliseconds.
 */
/*============================================================================*/
void wmbus_apl_mtr_setInterval(uint32_t l_interval);

/*============================================================================*/
/*!
 * @brief  Returns the periodical interval of a meter device. If the device is
 *         a collector always 0 is returned.
 *
 * @return  Periodical interval in milliseconds.
 */
/*============================================================================*/
uint32_t wmbus_apl_mtr_getInterval(void);

/*============================================================================*/
/*!
 * @brief  Sets the meter as connected or disconnect.
 *
 * @param b_connect  Set to connect the meter device.
 */
/*============================================================================*/
void wmbus_apl_mtr_setConnected(bool_t b_connect);

#if WMBUS_CHECK_BIDIRECTIONAL()
/*============================================================================*/
/*!
 * @brief Returns the global accessibility setting of the meter device.
 *        Default = E_WMBUS_ACCESSIBILITY_BIDIRECTIONAL_ACCESS
 * @return  Displayed mode in the configuration word
 */
/*============================================================================*/
E_WMBUS_ACCESSIBILITY_t wmbus_apl_mtr_getAccessibility(void);

/*============================================================================*/
/*!
 * @brief This function is only for meter devices. Set the acessibiolity type
 *        of the meter to save energy.
 * @param e_access  Displayed mode in the configuration word
 */
/*============================================================================*/
void wmbus_apl_mtr_setAccessibility(E_WMBUS_ACCESSIBILITY_t e_access);

/*============================================================================*/
/*!
 * @brief Enables the FAC mode if disabled. By default FAC mode is activated.
 */
/*============================================================================*/
void wmbus_apl_mtr_enableFAC(void);

/*============================================================================*/
/*!
 * @brief Disables using the FAC mode for bidirectional communication.
 */
/*============================================================================*/
void wmbus_apl_mtr_disableFAC(void);

#endif /* WMBUS_CHECK_BIDIRECTIONAL */

/*============================================================================*/
/*!
 * @brief   Sets the response delay to be used by the bidirectional meter device
 *          of WMBus mode C or WMBus mode N.
 *          The user given input may be overwritten by the collector the meter
 *          is connected to.
 *
 * @details According to the EN13757-4 (2013) meter devices of mode C and mode
 *          N respect the response delay as forced by the collector.
 *          This WMBus behaviour may lead to the effect that the user given
 *          input is overwritten (by the collector) once the meter is connected
 *          to a collector.
 *          Therefore this function must be used carefully.
 *          In order to verify the response delay that is currently used one
 *          can call @ref wmbus_ell_mtr_getResponseDelay() .
 *
 * @param   e_respDelay Response delay to be used.
 * @return  TRUE if set successfully. FALSE otherwise e.g. if not supported
 *          for the current device type.
 */
/*============================================================================*/
bool_t wmbus_apl_mtr_setResponseDelay(E_WMBUS_RESPONSE_DELAY_t e_respDelay);

/*============================================================================*/
/*!
 * @brief   Returns the response delay currently used by the meter device.
 *
 * @param   None.
 * @return  E_WMBUS_RESPONSE_DELAY_SLOW - indicating slow response delay.
 *          E_WMBUS_RESPONSE_DELAY_FAST - indicating fast response delay.
 */
/*============================================================================*/
E_WMBUS_RESPONSE_DELAY_t wmbus_apl_mtr_getResponseDelay(void);

/*============================================================================*/
/*!
 * @brief  Creates a telegram. On meter device.
 * @param c_ci        CI field to use.
 * @param i_meterId   Id of the meter device to send the telegram to. If the
 *                    device is a meter this value is ignored.
 * @param b_encrypt  Set @TRUE to enable telegram encryption.
 * @param b_synchronous Set @TRUE to set the synchronous bit in the configuration
                        word. Please only set the parameter @TRUE if you know
                        the rules for sending synchronous telegrams (EN13757-3&4)
                        A collector will ignore this value.
 * @return  Telegram id, @ref APL_ERR_TLG_NOT_AVAILABLE if no telegram could be
 *          created.
 */
/*============================================================================*/
uint8_t wmbus_apl_mtr_createTlg(uint8_t c_ci, uint16_t i_meterId,
                                  bool_t b_encrypt, bool_t b_synchronous);

/*============================================================================*/
/*!
 * @brief  Sends a telegram. Meter device.
 *         Before the telegram has to be created with function
 *         @ref wmbus_apl_mtr_createTlg().
 *
 * @param c_tlgId   Id of the telegram.
 * @return          TRUE if the telegram could be sent.
 */
/*============================================================================*/
bool_t wmbus_apl_mtr_sendTlg(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Wake up the target. Meter device.
 *
 * @param e_sleepMode  Current power-mode
 */
/*============================================================================*/
void wmbus_apl_mtr_wakeUp(E_WMBUS_SLEEP_MODE_t e_sleepMode);

/*============================================================================*/
/*!
 * @brief Set the content of message bits that are stored in the configuration
 *        word defined in the EN13757-3 2013.
 *
 *        This function should only be called for telegrams created by
 *        the meter device.
 *
 * @param e_content   Content of the message to set. Must be of type
 *                    @ref E_APL_COM_t.
 * @param c_tlgId     ID of the telegram.
 *
 * @return     TRUE if content of message was set. FALSE otherwise.
 */
/*============================================================================*/
bool_t wmbus_apl_mtr_setContentOfMessage(E_APL_COM_t e_content, uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief Get the content of message bits which are stored in the configuration
 *        word. This function should only be called for received telegrams.
 *
 *        Please note that this function is called by meter device, it returns
 *        the content of message of a received telegram from a collector.
 *
 * @param c_tlgId     ID of the telegram.
 *
 * @return  Content of the message. @ref E_APL_COM_t .
 */
/*============================================================================*/
E_APL_COM_t wmbus_apl_mtr_getContentOfMessage(uint8_t c_tlgId);

/*!@} end of WMBUS_APL_MTR_API */
/******************************************************************************/

/*!@} end of WMBUS_APL_MTR */
/******************************************************************************/
#endif /* __APPLICATIONLAYER_MTR_API_H__ */

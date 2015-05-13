#ifndef __APPLICATIONLAYER_COL_API_H__
#define __APPLICATIONLAYER_COL_API_H__
#ifndef __DECL_APPLICATIONLAYER_COL_API_H__
#define __DECL_APPLICATIONLAYER_COL_API_H__ extern
#else
#define __DECL_APPLICATIONLAYER_COL_API_H__
#endif /* __APPLICATIONLAYER_COL_API_H__ */

/**
  @file       wmbus_apl_col_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Application Layer API of Wireless M-Bus Collector Device.

              Include before:
             - wmbus_typedefs.h
              - wmbus_api.h
              - stezdn_clock.h
              - wmbus_global.h
              - wmbus_apl_api.h
*/

/** @example main_collector.c
 * Collector application layer example. */

/*! @defgroup WMBUS_APL_COL Application Layer Interface Description for a Collector Device.
 *  This section describes the API for the STACKFORCE application layer.
 *  @{
 */

/*! \defgroup WMBUS_APL_COL_COMPILE_TIME_SET Collector compile time settings
 *  Device specific compile time settings for a collector device.
 *  @{
 */
/*==============================================================================
                            DEFINES
==============================================================================*/

/*========================= ERRORS ===========================================*/
/*! The data could not be read because the meter index is out of range.
    This define has to have the same value as DLL_ERR_METER_OUT_OF_RANGE */
#define APL_ERR_METER_OUT_OF_RANGE              0xFFFFU
/*! The device is not available. */
#define APL_ERR_DEVICE_NOT_ADDED                0xFFFF

/*========================= CONFIGURATION WORD ===========================*/
/*! Macro to mask the synchronous bit of configuration word */
#define APL_CONFIGURATION_WORD_SYNC             0x20U

/*=============================== ENCRYPTION =================================*/
/*! AES key length */
#define APL_AES_SIZE_OF_KEY                     0x10U

/*==============================================================================
                            INCLUDES 2
==============================================================================*/
#if APL_CLOCK_ENABLED
/*! Needed for clock return values. */
#include "inc\pub\utils\wmbus_clock_api.h"
#endif /* APL_CLOCK_ENABLED */

/*!@} end of WMBUS_APL_COL_COMPILE_TIME_SET */
/******************************************************************************/

/*! \defgroup WMBUS_APL_COL_STRUCTS Collector structures
 *  Device specific structures for a collector device.
 *  @{
 */

/*==============================================================================
                             TYPEDEF STRUCTS
==============================================================================*/
/*! Structure of one meter entry in the list. */
PACKED_STRUCT(typedef struct S_APL_METERENTRY_T
{
  /*! Address of the meter device */
  s_wmbus_addr_t s_meterAddr;
  /*! Wmbus mode */
  E_WMBUS_MODE_t e_wmbusMode;
  /*! RF adapter */
  s_wmbus_addr_t s_rfAdapter;
  /*! Key of the meter device */
  uint8_t pc_meterKey[APL_AES_SIZE_OF_KEY];
}, s_apl_meterEntry_t);

/*! Structure of the meter list. Please note, that the meter entry array must
    be a packed list!. */
PACKED_STRUCT(typedef struct S_APL_METERLIST_T
{
  /*! Number of meter devices in the list. */
  uint16_t i_numberOfMeters;
  /*! Pointer to the first meter entry. */
  s_apl_meterEntry_t* ps_meterEntry;
}, s_apl_meterList_t);

/*! Structure of the return value of the function wmbus_mem_mgmt_mlMeterAdd. */
PACKED_STRUCT(typedef struct S_APL_ADD_METER_RET_T
{
  /*! Return status of the function. */
  E_APL_RET_t e_ret;
  /*! Meter index. */
  uint16_t i_meterId;
}, s_apl_addMeterRet_t);


/*! Start structure to start a collector device */
PACKED_STRUCT(typedef struct S_APL_STARTCOLLECTORATTR_T
{
  /*! Common start attributes for all WMBus device types */
  s_apl_startCommonAttr_t s_apl_startCommonAttr;

  /*! Static meters to install at startup. If no static meters are available,
    set the parameter to NULL. */
  s_apl_meterList_t* ps_meterList;
}, s_apl_startCollectorAttr_t);

/*!@} end of WMBUS_APL_COL_STRUCTS */
/******************************************************************************/

/*! \defgroup WMBUS_APL_COL_CALLBACKS Collector event callbacks
 *  Device specific callbacks for a collector device.
 *  @{
 */

/*==============================================================================
                            CALLBACK FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  This function is called if the receives ACC-DMD telegram from the meter.
 *
 * @param c_tlgId     Id of the received telegram.
 */
/*============================================================================*/
void wmbus_apl_evt_ACCDMDReceived(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  This function is called if the ACD bit of a meter telegram is set.
 *         Triggered by the ACD-bit the MUC should request alarm data (class 1)
 *         with the next unsolicited trans-mission of the Meter.
 *
 * @param c_tlgId     Id of the received telegram.
 */
/*============================================================================*/
void wmbus_apl_evt_ACDBitSet(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  A new meter device is requesting for connection.
 *
 * @param ps_meter    Data of the meter.
 * @param ps_tlgAttr  Telegram attributes from the installation request of the
 *                    meter device.
 *
 * @return            TRUE if the meter device has to be added to the meter
 *                    list.
 */
/*============================================================================*/
bool_t wmbus_apl_evt_newMeter(s_wmbus_addr_t *ps_meter,
                                s_apl_tlgAttr_t *ps_tlgAttr);

/*!@} end of WMBUS_APL_COL_CALLBACKS */
/******************************************************************************/

/*! \defgroup WMBUS_APL_COL_API Collector public API functions
 *  Device specific public APIs for a collector device.
 *  @{
 */

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/*!
 * @brief  Initializes the application layer for the device type collector.
 */
/*============================================================================*/
void wmbus_apl_col_init(void);

/*============================================================================*/
/*!
 * @brief  Starts the application layer for the device type collector.
 *
 * @param  s_startAttr  Start attributes of the collector device.
 *
 * @return Status of the operation @ref E_APL_STATUS_t
 */
/*============================================================================*/
E_APL_STATUS_t wmbus_apl_col_start(s_apl_startCollectorAttr_t* s_startAttr);

/*============================================================================*/
/*!
 * @brief  Default running method of collector device application layer.
 *
 *         This method has to be called as often as possible in order to let the
 *         stack process its tasks in time.
 */
/*============================================================================*/
void wmbus_apl_col_run(void);

/*============================================================================*/
/*!
 * @brief  Creates a clock synchronization command for a meter device.
 *         Be careful: If @ref APL_CLOCK_ENABLED is set to @ref FALSE the
 *         command can not be created. Then always @ref APL_ERR_TLG_NOT_AVAILABLE
 *         is returned.
 *
 * @param i_meterId    Id of the meter device to create the telegram.
 * @return             Id of the command telegram.
 *                     @ref APL_ERR_TLG_NOT_AVAILABLE if the request could not
 *                     be created.
 */
/*============================================================================*/
uint8_t wmbus_apl_col_createCmdClkSync(uint16_t i_meterId);

/*============================================================================*/
/*!
 * @brief  Create an alarm request for a meter device.
 *
 * @param i_meterId  Id of the meter device to create the telegram.
 * @return           Id of the request telegram.
 *                   @ref APL_ERR_TLG_NOT_AVAILABLE if the request could not
 *                   be created.
 */
/*============================================================================*/
uint8_t wmbus_apl_col_createAlarmRequest(uint16_t i_meterId);

/*============================================================================*/
/*!
 * @brief  Creates a user data request.
 *
 * @param i_meterId  Id of the meter device to create the telegram.
 * @param ps_record  Data of the request. @ref NULL if no data has to be sent.
 * @return           Id of the request telegram.
 *                   @ref APL_ERR_TLG_NOT_AVAILABLE if the request could not
 *                   be created.
 */
/*============================================================================*/
uint8_t wmbus_apl_col_createUserDataRequest(uint16_t i_meterId);

/*============================================================================*/
/*!
 * @brief  Reads the optional error code of a telegram.
 *
 * @param c_tlgId  Id of the telegram to read from.
 * @return         Reset code of the telegram.
 *                 If no error code is available, @ref APL_ERROR_UNSPECIFIED
 *                 is returned (cf. EN 13757-3).
 */
/*============================================================================*/
uint8_t wmbus_apl_col_readError(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Start a bidirectional communication the next time as possible.
 *
 * @return TRUE if opperation was successful.
 */
/*============================================================================*/
bool_t wmbus_apl_col_open(void);

/*============================================================================*/
/*!
 * @brief  Adds a telegram to the collector queue.
 *
 * @param c_tlgId    Id of the request.
 * @param b_append   If TRUE the telegram will be appended to the device specific
 *                   queue. If FALSE the telegram will set as first telegram
 *                   of the queue. Append should be set to FALSE to add a
 *                   request at the start of the queue if there was an problem
 *                   while sending the request.
 * @return           TRUE if the preparation was successful.
 */
/*============================================================================*/
bool_t wmbus_apl_col_sendQueued(uint8_t c_tlgId, bool_t b_append);

/*============================================================================*/
/*!
 * @brief  Resets the flag to start a bidirectional communication.
 *
 * @param i_meterId  Id of the meter device.
 * @param b_sendNke     TRUE if the collector should send an NKE message to the
 *                      meter to terminate the fac window of the meter device.
 *                      FALSE if the collector does not expect an answer. For
 *                      example: After the collector sends the confimation of an
 *                      Installation request dll_close() must be called with
 *                      b_sendNKE = FALSE because the collector should not send an
 *                      NKE message to end the communication.
 * @return           Returns the telegram ID of the close telegram.
 */
/*============================================================================*/
uint8_t wmbus_apl_col_close(uint16_t i_meterId, bool_t b_sendNke);

/*============================================================================*/
/*!
 * @brief  Adds a meter device to the meter list.
 *
 * @param ps_meterEntry Entry of a meter.
 * @return            Returns the id of the meter device.
 *                    Returns @ref APL_ERR_DEVICE_NOT_ADDED in case of failure.
 */
/*============================================================================*/
s_apl_addMeterRet_t wmbus_apl_col_meterAdd(s_apl_meterEntry_t* ps_meterEntry);

/*============================================================================*/
/*!
 * @brief  Removes a meter device from the meter list.
 *
 * @param i_meterId  Id of the meter to remove.
 * @return           E_APL_RET_OK if deleting was successful.
 */
/*============================================================================*/
E_APL_RET_t wmbus_apl_col_meterRemove(uint16_t i_meterId);

/*============================================================================*/
/*!
 * @brief  Updates the RF adapter address of a meter device.
 *
 * @param i_meterId   Id of the meter device.
 * @param ps_rf       Address of the RF adapter the meter device is connected
 *                    to.
 * @return            @ref E_APL_RET_OK if the adapter address could be changed.
 */
/*============================================================================*/
E_APL_RET_t wmbus_apl_col_meterSetRfAdapter(uint16_t i_meterId,
                                               s_wmbus_addr_t *ps_rf);

/*============================================================================*/
/*!
 * @brief  Reads the RF adapter address of a meter device.
 *
 * @param i_meterId   Id of the meter device.
 * @param ps_rf       Destination storage to write the address of the RF
 *                    adapter to.
 * @return            @ref TRUE if the adapter address could be read.
 */
/*============================================================================*/
bool_t wmbus_apl_col_meterGetRfAdapter(uint16_t i_meterId,
                                          s_wmbus_addr_t *ps_rf);

/*============================================================================*/
/*!
 * @brief   Updates the meter specific key.
 * @param i_meterId   Id of the meter device.
 *                    APL_ERR_METER_OUT_OF_RANGE to set the same key for all
 *                    devices.
 * @param pc_key      Key to set.
 * @param c_len       Size of the key.
 * @return            @ref E_APL_RET_OK if the key could be changed.
 */
/*============================================================================*/
E_APL_RET_t wmbus_apl_col_meterSetKey(uint16_t i_meterId, uint8_t* pc_key,
                                         uint8_t c_len);

/*============================================================================*/
/*!
 * @brief   Reads the key of the meter.
 * @param i_meterId   Id of the meter device.
 * @param pc_key      memory to write the key data to.
 * @param c_len       Size of pc_key.
 * @return            @ref TRUE if a key is available.
 */
/*============================================================================*/
bool_t wmbus_apl_col_meterGetKey(uint16_t i_meterId, uint8_t* pc_key,
                                    uint8_t c_len);

/*============================================================================*/
/*!
 * @brief  Gets the number of connected meter devices.
 *
 * @return  Number of connected meter devices.
 */
/*============================================================================*/
uint16_t wmbus_apl_col_meterGetNum(void);

/*============================================================================*/
/*!
 * @brief  Reads the attributes of a meter device.
 *
 * @param i_meterId    Id of the meter device.
 * @param ps_meterAddr Memory to write the meter address into.
 * @return             @ref FALSE if the index is out of range.
 */
/*============================================================================*/
bool_t wmbus_apl_col_meterGetAddr(uint16_t i_meterId,
                                     s_wmbus_addr_t *ps_meterAddr);

/*============================================================================*/
/*!
 * @brief  Reads the id of a meter device.
 *
 * @param ps_meterAddr Address of the meter device.
 * @return             @ref id of the meter, @ref APL_ERR_METER_OUT_OF_RANGE
 *                     if there is no meter in the list with the address
 *                     ps_meterAddr.
 */
/*============================================================================*/
uint16_t wmbus_apl_col_meterGetId(s_wmbus_addr_t *ps_meterAddr);

/*============================================================================*/
/*!
 * @brief   This function resets the complete queue.
 *
 * @details This function only clears the telegram references in the queue.
 *          The telegrams itself are not destroyed automatically!
 *
 * @param   None.
 * @return  None.
 */
/*============================================================================*/
void wmbus_apl_col_clearTlgQueue(void);

/*============================================================================*/
/*!
 * @brief   Removes all telegrams from the queue for a specific meter.
 *
 * @details This function only clears telegram references of a specific meter
 *          queue. The telegrams itself are not destroyed automatically!
 *
 * @param   i_meterId   ID of the selected meter.
 *
 * @return E_WMBUS_COL_QUEUE_RET_OK if all works fine.
 */
/*============================================================================*/
E_WMBUS_COL_QUEUE_RET_t wmbus_apl_col_clearMtrTlgQueue(uint16_t i_meterId);

/*============================================================================*/
/*!
 * @brief  Creates a telegram. On collector device.
 * @param c_ci        CI field to use.
 * @param i_meterId   Id of the meter device to send the telegram to. If the
 *                    device is a meter this value is ignored.
 * @param b_encrypt  Set @TRUE to enable telegram encryption.
 * @return  Telegram id, @ref APL_ERR_TLG_NOT_AVAILABLE if no telegram could be
 *          created.
 */
/*============================================================================*/
uint8_t wmbus_apl_col_createTlg(uint8_t c_ci, uint16_t i_meterId,
                                   bool_t b_encrypt);

/*============================================================================*/
/*!
 * @brief  Sends a telegram. Collector device.
 *         Before the telegram has to be created with function
 *         @ref wmbus_apl_col_createTlg().
 *
 * @param c_tlgId   Id of the telegram.
 * @return          TRUE if the telegram could be sent.
 */
/*============================================================================*/
bool_t wmbus_apl_col_sendTlg(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Wake up the target. Collector device.
 *
 * @param e_sleepMode  Current power-mode
 */
/*============================================================================*/
void wmbus_apl_col_wakeUp(E_WMBUS_SLEEP_MODE_t e_sleepMode);

/*============================================================================*/
/*!
 * @brief Set the content of message bits that are stored in the configuration
 *        word defined in the EN13757-3 2013.
 *
 *        This function should only be called for telegrams created by
 *        the collector device.
 *
 * @param e_content   Content of the message to set. Must be of type
 *                    @ref E_APL_COM_t.
 * @param c_tlgId     ID of the telegram.
 *
 * @return     TRUE if content of message was set. FALSE otherwise.
 */
/*============================================================================*/
bool_t wmbus_apl_col_setContentOfMessage(E_APL_COM_t e_content,
                                            uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief Get the content of message bits which are stored in the configuration
 *        word. This function should only be called for received telegrams.
 *
 *        Please note that this function is called by collector device, it returns
 *        the content of message of a received telegram from a meter.
 *
 * @param c_tlgId     ID of the telegram.
 *
 * @return  Content of the message. @ref E_APL_COM_t .
 */
/*============================================================================*/
E_APL_COM_t wmbus_apl_col_getContentOfMessage(uint8_t c_tlgId);

/*!@} end of WMBUS_APL_COL_API */
/******************************************************************************/

/*!@} end of WMBUS_APL_COL */
/******************************************************************************/

#endif /* __APPLICATIONLAYER_COL_API_H__ */

#ifndef __DATALINKLAYER_API_H__
#define __DATALINKLAYER_API_H__
#ifndef __DECL_DATALINKLAYER_API_H__
#define __DECL_DATALINKLAYER_API_H__ extern
#else
#define __DATALINKLAYER_API_INIT_VAR__
#endif /* __DECL_DATALINKLAYER_API_H__ */

/**
  @file       wmbus_dll_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Data Link Layer Application Programming Interface of
              Wireless M-Bus.

              Include before:
              - stezdn_typedefs.h
              - stezdn_wmbus_api.h
              - stezdn_wmbus_config.h
              - wmbus_dll_defines.h
*/

/******************************************************************************/
/*! @defgroup WMBUS_DLL STACKFORCE Data Link Layer
  This section describes the STACKFORCE Data Link Layer implementation.
  @{  */

/******************************************************************************/
/*! @defgroup WMBUS_DLL_COMPILE_TIME_SET Compile time settings
   This section describes the compile time settings for the STACKFORCE Data Link
   Layer implementation.
   @{  */
/*!@} end of WMBUS_DLL_COMPILE_TIME_SET */
/******************************************************************************/


/******************************************************************************/
/*! @defgroup WMBUS_DLL_ENUMS Enumerations
   This section describes the enumerations used by the STACKFORCE Data Link Layer
   implementation.
   @{  */
/*!@} end of WMBUS_DLL_ENUMS */
/******************************************************************************/

/******************************************************************************/
/*! @defgroup WMBUS_DLL_STRUCTS Structures
   This section describes the structures used by the STACKFORCE Data Link Layer
   implementation.
   @{  */
/*!@} end of WMBUS_DLL_STRUCTS */
/******************************************************************************/

/******************************************************************************/
/*! @defgroup WMBUS_DLL_API STACKFORCE Public API functions
   This section describes the public API functions for the STACKFORCE Data Link
   Layer implementation.
   @{  */

   /***************************************************************************/
   /*! @defgroup WMBUS_DLL_API_CALLBACKS Callbacks
   This section describes callback functions of the STACKFORCE Data Link Layer
   implementation. The functions listed within this section must be implemented
   by the upper layer in order to compile the project. These event functions
   are called by the Data Link Layer.
   @{  */
   /*!@} end of WMBUS_DLL_API_CALLBACKS */
   /***************************************************************************/

   /***************************************************************************/
   /*! @defgroup WMBUS_DLL_API_TLG_HANDLE Telegram handling
   This section describes functions of the STACKFORCE Data Link Layer
   implementation that deal with the reception and transmission of Wireless M-Bus
   telegrams.
   @{  */
   /*!@} end of WMBUS_DLL_API_TLG_HANDLE */
   /***************************************************************************/

   /***************************************************************************/
   /*! @defgroup WMBUS_DLL_API_COMMON Common device functions
   This section describes functions of the STACKFORCE Data Link Layer
   implementation that can be used by Wireless M-Bus meters as well as
   collectors.
   @{  */
   /*!@} end of WMBUS_DLL_API_COMMON */
   /***************************************************************************/

   /***************************************************************************/
   /*! @defgroup WMBUS_DLL_API_WRAPPER Wrapper functions
   This section describes functions of the STACKFORCE Data Link Layer
   implementation that serve as wrapper functions only, meaning that they
   provide access to public APIs of lower layers and just pass-through the
   function calls.
   @{  */
   /*!@} end of WMBUS_DLL_API_WRAPPER */
   /***************************************************************************/

/*!@} end of WMBUS_DLL_API */
/******************************************************************************/


/*==============================================================================
                            INCLUDES
==============================================================================*/

/* Stack specific includes */
#include "wmbus_global.h"
#include "wmbus_dll_defines.h"

/*==============================================================================
                            DEFINES
==============================================================================*/
/******************************************************************************/
/*! \addtogroup WMBUS_DLL_COMPILE_TIME_SET
   @{ */

/*! Check macro RF_HW_3OUTOF6_ENABLED  */
#ifndef RF_HW_CRC_ENABLED
#error check if the tranceiver supports crc calculation in hardware.
#endif /* RF_HW_CRC_ENABLED */

#if RF_HW_CRC_ENABLED
  #define DLL_CRC_HARDWARE                   TRUE
#else
  #define DLL_CRC_HARDWARE                   FALSE
#endif /* RF_HW_CRC_ENABLED */

#ifndef DLL_RX_ALL
  /*! Set @ref TRUE if receiving of data from all devices is allowed.
      This option only works if the device is a data collector. */
  #define DLL_RX_ALL                    FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DLL_RX_ALL set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* DLL_RX_ALL */

#ifndef DLL_RX_INVALID
  /*! Set @ref TRUE if receiving of data with invalid checksums is allowed.
      This option only works if the device is a data collector. */
  #define DLL_RX_INVALID                FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DLL_RX_INVALID set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* DLL_RX_INVALID */

#ifndef DLL_OPTIMIZE_SIZE
  /*! Disables size optimization. */
  #define DLL_OPTIMIZE_SIZE             FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DLL_OPTIMIZE_SIZE set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* DLL_OPTIMIZE_SIZE */

#ifndef DLL_INSTALL_ALLOW_ALL
  /*! Disables forwarding all telegrams in installation mode. */
  #define DLL_INSTALL_ALLOW_ALL       FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DLL_INSTALL_ALLOW_ALL set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* DLL_INSTALL_ALLOW_ALL */

/*========================= METERLIST  =======================================*/
/*! Defines the length or size of the struct S_DLL_METERENTRY_T */
#ifndef DLL_METERLIST_ENTRY_LEN
  #define DLL_METERLIST_ENTRY_LEN      (WMBUS_ADDR_LEN + 1U)
#endif /* DLL_METERLIST_ENTRY_LEN */

/*!@} end of WMBUS_DLL_COMPILE_TIME_SET */
/******************************************************************************/

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/

/*==============================================================================
                             TYPEDEFS
==============================================================================*/

/*==============================================================================
                            CALLBACK FUNCTIONS
==============================================================================*/
/*! \addtogroup WMBUS_DLL_API_CALLBACKS
 *  @{
 */

/*============================================================================*/
/*!
 * @brief  Meter device only.
 *         This function is called if periodical user data has to be sent.
 *         For this a new telegram has to be created and filled with user
 *         data.
 *         Be careful: In mode T2 a telegram with C-field
 *         @ref DLL_FIELD_C_PRM_AD should be sent, in other modes
 *         @ref DLL_FIELD_C_PRM_UD_NOREPL. This telegram has to be sent from
 *         higher layers because of the different M-Bus specifications as
 *         OMS or DSMR.
 */
/*============================================================================*/
void wmbus_dll_evt_sendUserData(void);

/*============================================================================*/
/*!
 * @brief  This function is called if a telegram is available. If the parameter
 *         c_tlgReqId is not equal to @ref BUFFER_INVALID_ID the upper layer must
 *         check if the received telegram is an respond to a sent request.
 *         If the received telegram is the response for the sent request the
 *         c_tlgReqId must be destroyed by the upper layer using
 *         @ref wmbus_dll_destroyTlg() !
 *         If the received telegram is not the respond the c_tlgReqId should not
 *         be destroyed and the DLL will continue with receiving until the next
 *         telegram arrives or a timeout occurred.
 *
 * @param e_status    Status of the telegram.
 * @param c_tlgReqId  Id of the request telegram. @ref NULL if there is no
 *                    request telegram available.
 * @param c_tlgId     Id of the telegram.
 */
/*============================================================================*/
void wmbus_dll_evt_tlgAvailable(E_WMBUS_RX_t e_status, uint8_t c_tlgReqId,
                          uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  This function is called if a bidirectional communication with a
 *         meter device is started.
 *         It is the acknowledgment to @ref wmbus_dll_open().
 *
 * @param c_tlgId Id of the request.
 */
/*============================================================================*/
void wmbus_dll_evt_opened(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  This function is called if a rf telegram is sent successfully
 *
 * @param c_tlgId     Id of the sent telegram.
 */
/*============================================================================*/
void wmbus_dll_evt_tx(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  This function is only needed for the C and the italic N mode.
 *         This modes allows different delays for an meter respond. The used
 *         delay depends on the "RD" field of the extended link layer header
 *         (CI = 0x8C || CI = 0x8D). This functions returns the timeout in
 *         milliseconds which has to be used for the given telegram.
 *
 * @param c_tlgId   Id of the telegram.
 * @return          TRUE if the telegram specifies the slow mode.
 */
/*============================================================================*/
bool_t wmbus_dll_evt_checkTelegramDelay(uint8_t c_tlgId);

/*!@} end of WMBUS_DLL_API_CALLBACKS */
/******************************************************************************/

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*! \addtogroup WMBUS_DLL_API_COMMON
 *  @{
 */

/*============================================================================*/
/*!
 * @brief  Returns the current status of the data link layer.
 *
 * @return  Status of the data link layer.
 */
/*============================================================================*/
uint8_t wmbus_dll_getStatus(void);

/*============================================================================*/
/*!
 * @brief Returns the address of the device.
 *
 * @param ps_addr  Pointer to the memory to write the address into.
 */
/*============================================================================*/
void wmbus_dll_getAddrOwn(s_wmbus_addr_t *ps_meterAddr);

/*============================================================================*/
/*!
 * @brief Sets the address of the device.
 *
 * @param ps_addr  Pointer to the memory to get the address from.
 */
/*============================================================================*/
void wmbus_dll_setAddrOwn(s_wmbus_addr_t *ps_meterAddr);

/*============================================================================*/
/*!
 * @brief  Checks if the dll is able to go in low power-mode
 * @param e_sleepMode  Power mode for the target
 * @return Returns the status of the request as @ref  E_PHY_SLEEP_RESULT_t.
 */
/*============================================================================*/
E_WMBUS_SLEEP_RESULT_t wmbus_dll_sleep(E_WMBUS_SLEEP_MODE_t e_sleepMode);

/*============================================================================*/
/*!
 * @brief  Wake up the target
 *
 * @param e_apl_sleep_mode  Current power-mode
 */
/*============================================================================*/
void wmbus_dll_wakeUp(E_WMBUS_SLEEP_MODE_t e_sleepMode);

/*============================================================================*/
/*!
 * @brief  Counts the number of telegram data bytes.
 *
 * @param c_tlgId   Id of the telegram.
 * @return          Number of data bytes.
 */
/*============================================================================*/
uint16_t wmbus_dll_cntDataBytes(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Sets a timeout to wait before sending the next telegram.
 * @param l_timeout   Time to wait in milliseconds.
 */
/*============================================================================*/
void wmbus_dll_setTxWait(uint32_t l_timeout);

/*============================================================================*/
/*!
 * @brief  Cleans up all buffers.
 */
/*============================================================================*/
void wmbus_dll_bufCleanUp(void);

/*!@} end of WMBUS_DLL_API_COMMON */
/******************************************************************************/

/*! \addtogroup WMBUS_DLL_API_TLG_HANDLE
 *  @{
 */
/*============================================================================*/
/*!
 * @brief  Creates a new telegram.
 *
 * @param c_type       Telegram type.
 * @param i_len        Number of data bytes to send.
 * @return             Id of the telegram.
 *                     @ref DLL_ERR_TLG_NOT_AVAILABLE if there is not enough
 *                     memory to create the telegram.
 */
/*============================================================================*/
uint8_t wmbus_dll_createTlg(uint8_t c_type, uint16_t i_len);

/*============================================================================*/
/*!
 * @brief  Writes data to a telegram.
 *
 * @param c_tlgId   Id of the telegram to write the data into.
 * @param pc_data   Data to write.
 * @param c_len     Number of bytes to write.
 * @param c_offset  Offset to start writing into the telegram.
 *                  @ref DLL_TLG_WRITE_APPEND if the data has to be appended.
 * @param b_reverse @ref TRUE if the data has to be written reverse.
 * @return          @ref TRUE if writing was successful.
 */
/*============================================================================*/
bool_t wmbus_dll_writeTlg(uint8_t c_tlgId, uint8_t *pc_data, uint8_t c_len,
                    uint8_t c_offset, bool_t b_reverse);

/*============================================================================*/
/*!
 * @brief  Sends a telegram.
 *         If the telegram is sent successfully, it is destroyed by the data
 *         link layer automatically.
 *
 * @param c_tlgId  Id of the telegram to send.
 * @return         @ref TRUE if sending was successful.
 */
/*============================================================================*/
bool_t wmbus_dll_sendTlg(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Destroys a telegram.
 *
 * @param c_tlgId  Id of the telegram to destroy.
 * @return         TRUE if the telegram exists, FALSE if c_tlgId is out of
 *                 range.
 */
/*============================================================================*/
bool_t wmbus_dll_destroyTlg(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Receives data from a telegram.
 *
 * @param c_tlgId   Id of the telegram to read from.
 * @param pc_data   Memory to write the data into.
 * @param c_len     Number of bytes to read.
 * @param c_offset  Index to read the data from.
 * @param b_reverse The data has to be received in reverse order.
 * @return          Number of read bytes.
 *                  @ref DLL_ERR_PARAM_OUT_OF_RANGE if data could not be read.
 */
/*============================================================================*/
uint8_t wmbus_dll_receiveTlg(uint8_t c_tlgId, uint8_t *pc_data, uint8_t c_len,
                        uint8_t c_offset, bool_t b_reverse);

/*============================================================================*/
/*!
 * @brief  Reads the attributes of a received telegram.
 *
 * @param c_tlgId         ID of the telegram.
 * @param ps_tlgAttrRecv  Memory to save the telegram information into.
 * @return                @ref TRUE if attributes are read successfully.
 *                        @ref FALSE otherwise.
 */
/*============================================================================*/
bool_t wmbus_dll_getTlgAttr(uint8_t c_tlgId, s_dll_tlgAttr_t *ps_tlgAttrRecv);

/*============================================================================*/
/*!
 * @brief  Sets the frame type of the telegram. This function should only be
           used in C-mode. Only the C-mode supports packets in format A and B.
 * @param c_tlgId       Telegram Id
 * @param e_frameType   Frame type.
 */
/*============================================================================*/
void wmbus_dll_setTlgFormat(uint8_t c_tlgId, E_WMBUS_FRAME_t e_frameType);

/*============================================================================*/
/*!
 * @brief  Sets the mode of the telegram
 * @param c_tlgId       Telegram Id
 * @param e_mode        Mode of the received telegram (S, T, C or N).
 */
/*============================================================================*/
void wmbus_dll_setTlgMode(uint8_t c_tlgId, E_WMBUS_MODE_t e_mode);

/*============================================================================*/
/*!
 * @brief  Set the format and other parameters of the new telegram.
 *          Function used by collector device only.
 *
 * @param c_tlgId   Id of the telegram to write the data into.
 * @param ps_meterAddr Address of the meter device.
 */
/*============================================================================*/
void wmbus_dll_set_tlgParam(uint8_t c_tlgId, s_wmbus_addr_t *ps_meterAddr);

/*!@} end of WMBUS_DLL_API_TLG_HANDLE */
/******************************************************************************/

/*============================= WRAPPER FUNCTIONS ============================*/
/*! \addtogroup WMBUS_DLL_API_WRAPPER
 *  @{
 */

/*============================================================================*/
/*!
 * @brief Sets the transmission power of the rf-module. Please have a look in
 *        the corresponding data sheet of the selected transceiver to choose a
 *        supported transmission power.
 * @param c_txPower      Tx power from -130dBm (0x0) to 125dBm (0xFE).
 *                       0xFF is reserved.
 */
/*============================================================================*/
void wmbus_dll_setTxPower(uint8_t c_txPower);

/*============================================================================*/
/*!
 * @brief Reads the transmission power.
 * @return  Tx power from -130dBm (0x0) to 125dBm (0xFE).
 *          0xFF is reserved.
 */
/*============================================================================*/
uint8_t wmbus_dll_getTxPower(void);

/*============================================================================*/
/*!
 * @brief Sets the radio channel of the rf-module. This function should only be
 *        used in mode N to set the correct channel for the device.
 * @param i_channel      Radio channel or channel mask.
 *                       0xFFFF is reserved.
 * @return               TRUE if the channel was set.
 */
/*============================================================================*/
bool_t wmbus_dll_setRfChannel(E_RADIO_CHANNEL_INDEX_t e_channel);

/*============================================================================*/
/*!
 * @brief Reads the radio channel of the rf-module.
 * @return  Current radio channel
 */
/*============================================================================*/
E_RADIO_CHANNEL_INDEX_t wmbus_dll_getRfChannel(void);

/*!@} end of WMBUS_DLL_API_COL */
/******************************************************************************/
/*!@} end of WMBUS_DLL */
/******************************************************************************/
#endif /* __DATALINKLAYER_API_H__ */

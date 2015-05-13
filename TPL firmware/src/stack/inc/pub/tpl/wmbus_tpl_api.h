#ifndef __TRANSPORTLAYER_H__
#define __TRANSPORTLAYER_H__
#ifndef __DECL_TRANSPORTLAYER_H__
#define __DECL_TRANSPORTLAYER_H__ extern
#else
#define __TRANSPORTLAYER_INIT_VAR__
#endif /* __DECL_TRANSPORTLAYER_H__ */

/**
  @file       wmbus_tpl_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Transport Layer Application Programming Interface of
              Wireless M-Bus.
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/

/* Stack specific includes */
#include "wmbus_global.h"

/*==============================================================================
                            DEFINES
==============================================================================*/

/*========================= DUTCH'S DEFINES ==================================*/
#if DSMR_V405_ENABLED
#define TPL_DSMR_FRAME_CTR_LEN                  4U
#endif /* DSMR_V405_ENABLED */

/*========================= AES128 + CBC =====================================*/
#ifndef AES128_DYNAMIC_IV_DECRYPT_ENABLED
  /*! AES128 + CBC decryption with dynamic IV disabled. */
  #define AES128_DYNAMIC_IV_DECRYPT_ENABLED   FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning AES128_DYNAMIC_IV_DECRYPT_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* AES128_DYNAMIC_IV_DECRYPT_ENABLED */

#ifndef AES128_DYNAMIC_IV_ENCRYPT_ENABLED
  /*! AES128 + CBC encryption with dynamic IV disabled. */
  #define AES128_DYNAMIC_IV_ENCRYPT_ENABLED   FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning AES128_DYNAMIC_IV_ENCRYPT_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* AES128_DYNAMIC_IV_ENCRYPT_ENABLED */

#ifndef AES128_STATIC_IV_DECRYPT_ENABLED
  /*! AES128 + CBC decryption with static IV disabled. */
  #define AES128_STATIC_IV_DECRYPT_ENABLED   FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning AES128_STATIC_IV_DECRYPT_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* AES128_STATIC_IV_DECRYPT_ENABLED */

#ifndef AES128_STATIC_IV_ENCRYPT_ENABLED
  /*! AES128 + CBC encryption with static IV disabled. */
  #define AES128_STATIC_IV_ENCRYPT_ENABLED   FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning AES128_STATIC_IV_ENCRYPT_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* AES128_STATIC_IV_ENCRYPT_ENABLED */

#ifndef AES_INITIALIZATION_VECOR_ADDRESS
  #error please specifie  the AES_INITIALIZATION_VECOR_ADDRESS
#endif /* AES_INITIALIZATION_VECOR_ADDRESS */

#ifndef AES_SIZE_OF_KEY
  #define AES_SIZE_OF_KEY                     0x10U
#endif /* AES_SIZE_OF_KEY */

#ifndef AES_DEFAULT_NETWORK_KEY
  #define AES_DEFAULT_NETWORK_KEY             {0xFF, 0xFF, 0xFF, 0xFF,\
                                               0xFF, 0xFF, 0xFF, 0xFF,\
                                               0xFF, 0xFF, 0xFF, 0xFF,\
                                               0xFF, 0xFF, 0xFF, 0xFF}
#endif /* AES_DEFAULT_NETWORK_KEY */

/*========================= DES + CBC ========================================*/
#ifndef DES_DYNAMIC_IV_DECRYPT_ENABLED
  /*! DES + CBC decryption with dynamic IV disabled. */
  #define DES_DYNAMIC_IV_DECRYPT_ENABLED      FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DES_DYNAMIC_IV_DECRYPT_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#elif DES_DYNAMIC_IV_DECRYPT_ENABLED
  #error Decryption with DES + CBC with dynamic IV is not implemented yet.
#endif /* DES_DYNAMIC_IV_DECRYPT_ENABLED */

#ifndef DES_DYNAMIC_IV_ENCRYPT_ENABLED
  /*! DES + CBC encryption with dynamic IV disabled. */
  #define DES_DYNAMIC_IV_ENCRYPT_ENABLED      FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DES_DYNAMIC_IV_ENCRYPT_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#elif DES_DYNAMIC_IV_ENCRYPT_ENABLED
  #error Encryption with DES + CBC with dynamic IV is not implemented yet.
#endif /* DES_DYNAMIC_IV_ENCRYPT_ENABLED */

#ifndef DES_STATIC_IV_DECRYPT_ENABLED
  /*! DES + CBC decryption with static IV disabled. */
  #define DES_STATIC_IV_DECRYPT_ENABLED       FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DES_STATIC_IV_DECRYPT_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#elif DES_STATIC_IV_DECRYPT_ENABLED
  #error Decryption with DES + CBC with static IV is not implemented yet.
#endif /* DES_STATIC_IV_DECRYPT_ENABLED */

#ifndef DES_STATIC_IV_ENCRYPT_ENABLED
  /*! DES + CBC encryption with static IV disabled. */
  #define DES_STATIC_IV_ENCRYPT_ENABLED       FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DES_STATIC_IV_ENCRYPT_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#elif DES_STATIC_IV_ENCRYPT_ENABLED
  #error Encryption with DES + CBC with static IV is not implemented yet.
#endif /* DES_STATIC_IV_ENCRYPT_ENABLED */

/*========================= CONTROL INFORMATION FIELD (CI-field) =============*/
/*! Reset(EN 13757-3) */
#define TPL_FIELD_CI_RESET                          0x50U
/*! Data send (EN 13757-3) */
/*! @todo according to EN13757-3:2013 this CI field is not allowed for Wireless
 * M-Bus anymore! */
#define TPL_FIELD_CI_DATA_SEND                      0x51U
/*! Slave select (EN 13757-3) */
#define TPL_FIELD_CI_SLAVE_SELECT                   0x52U
/*! CMD to device with short header (OMS Vol.2 Issue 2.0.0/2009-07-20)
                                    (DSMR 2.3.1) */
#define TPL_FIELD_CI_CMD_TO_DEVICE_SHORT            0x5AU
/*! CMD to device with long header (OMS Vol.2 Issue 2.0.0/2009-07-20)
                                   (DSMR 2.3.1) */
#define TPL_FIELD_CI_CMD_TO_DEVICE_LONG             0x5BU
/*! Time synchronization (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define TPL_FIELD_CI_TIME_SYNC_1                    0x6CU
/*! Time synchronization (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define TPL_FIELD_CI_TIME_SYNC_2                    0x6DU
/*! Error from device with short header (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define TPL_FIELD_CI_APL_ERROR_SHORT                0x6EU
/*! Error from device with long header (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define TPL_FIELD_CI_APL_ERROR_LONG                 0x6FU
/*! Report of application errors (EN 13757-3) */
#define TPL_FIELD_CI_APL_ERROR                      0x70U
/*! report of alarms (EN 13757-3) */
#define TPL_FIELD_CI_ALARM                          0x71U
/*! 12 byte header followed by variable format data (EN 13757-3) */
#define TPL_FIELD_CI_HEADER_LONG                    0x72U
/*! Alarm from device with short header (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define TPL_FIELD_CI_APL_ALARM_SHORT                0x74U
/*! Alarm from device with long header (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define TPL_FIELD_CI_APL_ALARM_LONG                 0x75U
/*! Variable data format respond without header (EN 13757-3) */
#define TPL_FIELD_CI_HEADER_NO                      0x78U
/*! 4 byte header followed by variable data format respond (EN 13757-3) */
#define TPL_FIELD_CI_HEADER_SHORT                   0x7AU
/*! Link extension to device with long header (OMS Vol.2 Issue 2.0.02009-07-20) */
#define TPL_FIELD_CI_LINK_TO_DEVICE_LONG            0x80U
/*! Link extension from device with short header
    (OMS Vol.2 Issue 2.0.0/2009-07-20) */
#define TPL_FIELD_CI_LINK_FROM_DEVICE_SHORT         0x8AU
/*! Link extension from device with long header
    (OMS Vol.2 Issue 2.0.0/2009-07-20) */
#define TPL_FIELD_CI_LINK_FROM_DEVICE_LONG          0x8BU

#if !OMS_V402_ENABLED
/*! Additional Link Layer may be applied for Radio messages with or without
    Application Layer.   */
#define TPL_FIELD_CI_EXT_DLL_I                      0x8CU
/*! Additional Link Layer may be applied for Radio messages with or without
    Application Layer.   */
#define TPL_FIELD_CI_EXT_DLL_II                     0x8DU
#endif /* !OMS_V402_ENABLED */

/*! Manufacture specific CI-Field with no header*/
#define TPL_FIELD_CI_MANU_NO                        0xA1U
/*! Manufacture specific CI-Field with short header*/
#define TPL_FIELD_CI_MANU_SHORT                     0xA2U
/*! Manufacture specific CI-Field with long header*/
#define TPL_FIELD_CI_MANU_LONG                      0xA3U
/*! Manufacture specific CI-Field with short header (for RF-Test)*/
#define TPL_FIELD_CI_MANU_SHORT_RF                  0xA4U
/*! No CI-field transmitted. */
#define TPL_FIELD_CI_NULL                           0xFFU
/*! Length of the control information field. */
#define TPL_FIELD_CI_LEN                            0x01U

/* Encryption Mode */
/*! Use no encryption.  */
#define TPL_ENCRYPTION_MODE_0                       0x00U
/*! AES + CBC */
#define TPL_ENCRYPTION_MODE_4                       0x04U
/*! AES + CBC with dynamic IV */
#define TPL_ENCRYPTION_MODE_5                       0x05U
/*! AES + CBC with dynamic Key */
#define TPL_ENCRYPTION_MODE_7                       0x07U
/*! AES + CBC with dynamic IV for DSMR*/
#define TPL_ENCRYPTION_MODE_15                      0x0FU

#define TPL_MAX_HEADER_LENGTH                       12U

/*! Signals that stack is busy. Must be in sync with lower layer macros! */
#define TPL_STATUS_BUSY                             0x01U
/*! Signals that the meter device is connected to a data collector.
    Must be in sync with lower layer macros! */
#define TPL_STATUS_CONNECTED                        0x08U

/*========================= TELEGRAM FLAG REGISTER ===========================*/
/*! Clears all flags. */
#define TPL_TLG_FLAG_CLR                        0x0000U
/*! Mask for signature field. */
#define TPL_TLG_FLAG_SIGNATURE                  0x000CU
/*! Data collector only: Set if the data could not be encrpyted. */
#define TPL_TLG_FLAG_SIGNATURE_UNKNOWN          0x0004U
/*! @deprecated: Data collector only: There was an encryption error. */
#define TPL_TLG_FLAG_SIGNATURE_ERROR            0x0008U
/*! Data collector only: The data is unencrypted. */
#define TPL_TLG_FLAG_SIGNATURE_NO               0x000CU

/*! Hop counter of the telegram */
#define TPL_TLG_FLAG_HOP_COUNTER                0x0010U
/*! Hop counter of the telegram */
#define TPL_TLG_FLAG_REPEATER_ACCESS            0x0020U
/* First bit of the content of message field */
#define TPL_TLG_FLAG_CONTENT_OF_MESSAGE_0       0x0040U
/* Second bit of the content of message field */
#define TPL_TLG_FLAG_CONTENT_OF_MESSAGE_1       0x0080U
/* Mask for mode field */
#define TPL_TLG_FLAG_ENCRYPTION_MODE_MASK       0x1F00U
/* The telegram is encypted using mode 5 defined in EN13757 (2013) */
#define TPL_TLG_FLAG_ENCRYPTION_MODE_5          0x0500U
/* The telegram is encypted using mode 7 defined in OMS_VOL2_Primary_v401 */
#define TPL_TLG_FLAG_ENCRYPTION_MODE_7          0x0700U
/* The telegram is encypted using mode 13 defined in OMS_VOL2_Primary_v401 */
#define TPL_TLG_FLAG_ENCRYPTION_MODE_13         0x0D00U
/*! Bidirectional communication. */
#define TPL_TLG_FLAG_SYNC                       0x2000U
/*! Receiver accessibility. */
#define TPL_TLG_FLAG_ACCESSIBILITY              0x4000U
/*! Bidirectional communication. */
#define TPL_TLG_FLAG_BIDIRECTIONAL              0x8000U

/*============================ CONFIGURATION WORD ============================*/
/*! Hop counter of the telegram. */
#define TPL_FIELD_CONF_WORD_HOP_COUNTER                          0x0001U
/*! Repeater access. */
#define TPL_FIELD_CONF_WORD_REPEATER_ACCESS                      0x0002U
/*! Content of message mask. */
#define TPL_FIELD_CONF_WORD_CONTENT_OF_MESSAGE_MASK              0x000CU
/*! Content of message bit 0. */
#define TPL_FIELD_CONF_WORD_CONTENT_OF_MESSAGE_0                 0x0004U
/*! Content of message bit 1. */
#define TPL_FIELD_CONF_WORD_CONTENT_OF_MESSAGE_1                 0x0008U
/*! Content of message bit 0
    of Encryption Mode 7 Configuration Word (OMS v4.0.2) */
#define TPL_FIELD_CONF_WORD_MODE_7_CONTENT_OF_MESSAGE_0          0x4000U
/*! Content of message bit 1
    of Encryption Mode 7 Configuration Word (OMS v4.0.2) */
#define TPL_FIELD_CONF_WORD_MODE_7_CONTENT_OF_MESSAGE_1          0x8000U
/*! Number of encryption blocks mask. */
#define TPL_FIELD_CONF_WORD_ENCRYPTION_BLOCK_MASK                0x00F0U
/*! Encryption mode mask. (5 Bits according to OMS v4.0.2)*/
#define TPL_FIELD_CONF_WORD_ENCRYPTION_MODE_MASK                 0x1F00U
/*! Use no encryption.  */
#define TPL_FIELD_CONF_WORD_NO_ENCRYPTION                        0x0000U
/*! DES + CBC */
#define TPL_FIELD_CONF_WORD_ENCRYPTION_MODE_2                    0x0200U
/*! DES + CBC with dynamic IV */
#define TPL_FIELD_CONF_WORD_ENCRYPTION_MODE_3                    0x0300U
/*! AES + CBC */
#define TPL_FIELD_CONF_WORD_ENCRYPTION_MODE_4                    0x0400U
/*! AES + CBC with dynamic IV */
#define TPL_FIELD_CONF_WORD_ENCRYPTION_MODE_5                    0x0500U
/*! AES + CBC mode 7 */
#define TPL_FIELD_CONF_WORD_ENCRYPTION_MODE_7                    0x0700U
/*! AES + CBC mode 13 */
#define TPL_FIELD_CONF_WORD_ENCRYPTION_MODE_13                   0x0D00U
/*! AES + CBC with dynamic IV (DSMR Mode 15)*/
#define TPL_FIELD_CONF_WORD_ENCRYPTION_MODE_15                   0x0F00U
/*! Bidirectional and accessibility mask. */
#define TPL_FIELD_CONF_WORD_BI_ACCESSIBILITY_MASK                0xC000U
/*! Bidirectional communication. */
#define TPL_FIELD_CONF_WORD_BIDIRECTIONAL                        0x8000U
/*! Receiver always on. */
#define TPL_FIELD_CONF_WORD_ACCESSIBILITY                        0x4000U
/*! Synchronous message. */
#define TPL_FIELD_CONF_WORD_SYNC                                 0x2000U

/*========================= METERLIST  =======================================*/
/* Defines the length or size of the struct S_TPL_METER_ENTRY_T */
#ifndef TPL_METERLIST_ENTRY_LEN
  #define TPL_METERLIST_ENTRY_LEN                (WMBUS_ADDR_LEN + \
                                                  1U + \
                                                  WMBUS_ADDR_LEN + \
                                                  AES_SIZE_OF_KEY)
#endif /* TPL_METERLIST_ENTRY_LEN */

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/
/*! Enumeration of return values. */
typedef enum
{
  /*! The telegram is decrypted. */
  E_TPL_CRYPT_RET_OK,
  /*! There was an error at telegram decryption. */
  E_TPL_CRYPT_RET_ERR,
  /*! Unknown encryption algorithm. */
  E_TPL_CRYPT_RET_UNKNOWN,
  /*! Too few data bytes. */
  E_TPL_CRYPT_RET_TOO_FEW_BYTES,
  /*! The encrypted data is invalid. */
  E_TPL_CRYPT_RET_INVALID
} E_TPL_CRYPT_RET_t;

/*! Enumeration of return values. */
typedef enum
{
  /*! All OK */
  E_TPL_RET_OK = 0U,
  /*! Error. */
  E_TPL_RET_ERR,
  /*! Stack is not ready */
  E_TPL_RET_NOT_READY,
  /*! Only used for the MeterAdd command. Indicates that the meter ist already in the list */
  E_TPL_RET_DUPLICATED
} E_TPL_RET_t;

/*! Enumeration of header types. */
typedef enum
{
  /*! No application header (0 bytes). */
  E_TPL_HEADER_TYPE_NO,
  /*! Short application header (4 bytes). */
  E_TPL_HEADER_TYPE_SHORT,
  /*! Long application header (12 bytes). */
  E_TPL_HEADER_TYPE_LONG,
  /*! Extended link layer     (2  bytes).  (CI = 0x8C) */
  E_TPL_HEADER_TYPE_EXT_I,
  /*! Extended link layer     (8  bytes).  (CI = 0x8D) */
  E_TPL_HEADER_TYPE_EXT_II,
  /*! Invalid header. */
  E_TPL_HEADER_TYPE_INVALID
} E_TPL_HEADER_TYPE_t;

/*! Enumeration of the status of the dll+ functions. */
typedef enum
{
  /*! Error occured for unknown reasons. */
  E_TPL_STATUS_ERROR,
  /*! Invalid input parameter error */
  E_TPL_STATUS_INVALID_PARAM_ERROR,
  /*! Stack not initialized error.  */
  E_TPL_STATUS_NOT_INIT_ERROR,
  /*! Operation success.*/
  E_TPL_STATUS_SUCCESS
} E_TPL_STATUS_t;

/*! Result of authentication/verification of a message. Used by
 *  @ref s_tpl_tlgAttr_t only in function @ref wmbus_tpl_getTlgAttr .
 *  This information is gained by underlying Authentication and Fragmentation
 *  Layer (AFL) if present. If not present, @ref s_tpl_tlgAttr_t will always
 *  signal @ref E_AFL_AUTH_RESULT_NONE . */
typedef enum
{
  /*! Authentication of received message was successfully verified. */
  E_TPL_AUTH_RESULT_OK,
  /*! Received message is not authenticated. */
  E_TPL_AUTH_RESULT_NONE,
  /*! An error occurred during verification of authentication of received
   *  message */
  E_TPL_AUTH_RESULT_ERROR
} E_TPL_AUTH_RESULT_t;

/*==============================================================================
                            TYPEDEF STRUCTS
==============================================================================*/
/*! Structure of an application header. */
typedef struct
{
  /*! Header type. */
  E_TPL_HEADER_TYPE_t e_type;
  /*! Default length */
  uint8_t pc_data[TPL_MAX_HEADER_LENGTH];
} s_tpl_header_t;

/*! Structure of an long application header. */
PACKED_STRUCT(typedef struct
{
  /*! Header type. */
  E_TPL_HEADER_TYPE_t e_type;
  /*! Access number. */
  uint8_t c_accNo;
  /*! Status byte. */
  uint8_t c_status;
  /*! Signature word. */
  uint16_t i_signature;
  /*! Application address. */
  s_wmbus_addr_t s_addr;
} , s_tpl_headerLong_t);

/*! Structure of an short application header. */
PACKED_STRUCT(typedef struct
{
  /*! Header type. */
  E_TPL_HEADER_TYPE_t e_type;
  /*! Access number. */
  uint8_t c_accNo;
  /*! Status byte. */
  uint8_t c_status;
  /*! Signature word. */
  uint16_t i_signature;
} , s_tpl_headerShort_t);

/*! Structure of an extended link layer header version I. */
typedef struct
{
  /*! Header type. */
  E_TPL_HEADER_TYPE_t e_type;
  /*! Communication control field */
  uint8_t c_commControl;
  /*! Access number. */
  uint8_t c_accNo;
} s_tpl_headerExtI_t;

/*! Structure of an extended link layer header version II. */
typedef struct
{
  /*! Header type. */
  E_TPL_HEADER_TYPE_t e_type;
  /*! Communication control field */
  uint8_t c_commControl;
  /*! Access number. */
  uint8_t c_accNo;
  /*! Session number. */
  uint32_t l_sessionNr;
  /*! Payload CRC  */
  uint16_t i_payloadCrc;
} s_tpl_headerExtII_t;

/*! Structure of one meter entry in the list. */
PACKED_STRUCT(typedef struct S_TPL_METERENTRY_T
{
  /*! Address of the meter device */
  s_wmbus_addr_t s_meterAddr;
  /*! Wmbus mode */
  E_WMBUS_MODE_t e_wmbusMode;
  /*! RF adapter */
  s_wmbus_addr_t s_rfAdapter;
  /*! Key of the meter device */
  uint8_t pc_meterKey[AES_SIZE_OF_KEY];
}, s_tpl_meterEntry_t);

/*! Structure of the meter list. Please note, that the meter entry array must
    be a packed list!. */
PACKED_STRUCT(typedef struct S_TPL_METERLIST_T
{
  /*! Number of meter devices in the list. */
  uint16_t i_numberOfMeters;
  /*! Pointer to the first meter entry. */
  s_tpl_meterEntry_t* ps_meterEntry;
}, s_tpl_meterList_t);

/*! Start structure to start a meter device */
PACKED_STRUCT(typedef struct S_TPL_STARTATTR_T
{
  /*! Frequency offset of the carrier. If the parameter is not known,
      set it to 0. */
  sint16_t si_freqOffset;
  /*! Address of the device */
  s_wmbus_addr_t* s_deviceAddr;

#if WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_METER)

  /*! The address of the collector. If the collector is not known, set it to
      zero. */
  s_wmbus_addr_t* s_collectorAddr;
  /*! Tell the device to bind to a data collector. Only possible, if the
      collector address is valid. */
  bool_t b_connected;
  /*! The interval for periodical user data in ms. */
  uint32_t l_interval;
  /*! Key of the device */
  uint8_t* pc_ownKey;
#endif /* WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_METER) */

#if WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_COLLECTOR)

  /*! Static meters to install at startup. If no static meters are available,
      set the parameter to NULL. */
  s_tpl_meterList_t* ps_meterList;
#endif /* WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_COLLECTOR) */
}, s_tpl_startAttr_t);

/*! Structure of the return value of the function wmbus_mem_mgmt_mlMeterAdd. */
PACKED_STRUCT(typedef struct S_TPL_ADDMETERRET_T
{
  /* Return status of the function. */
  E_TPL_RET_t e_ret;
  /* Meter index. */
  uint16_t i_meterId;
}, s_tpl_addMeterRet_t);

typedef struct
{
  /*
   * Attributes provided by Data Link Layer (DLL)
   */
  /*! Id of the telegram. */
  uint8_t c_tlgId;
  /*! Address of the meter device the telegram was received from.
      If the target is a meter device, this field includes invalid data. */
  s_wmbus_addr_t s_meterAddr;
  /*! Type of the telegram (C-field). */
  uint8_t c_controlField;
  /*! Data Collector only:
      TRUE if further requests may be sent.
      FALSE if further requests could cause an overflow. */
  bool_t b_flowControl;
  /*! TRUE if user data class 1 is available. */
  bool_t b_accessDemand;
  /*! Type of the data (CI-field). If no CI field is received, this value is
      @ref APL_FIELD_CI_NULL. */
  uint8_t c_controlInfo;
  /*! Number of received data bytes. 0 if no data is available. */
  uint16_t i_len;
  /*! Quality of a received telegram.
   * FF  no link quality available
   * FE  -254 dBm
   * ...
   * 00  0 dBm */
  uint8_t c_quality;
  /*! Mode in which the telegram was received.
   * [S, T, C] In C mode also T packets would be received*/
  E_WMBUS_MODE_t e_mode;
  /*! Defines the type of frame format. */
  E_WMBUS_FRAME_t e_frameType;

  /*! Access number of the received telegram. */
  uint8_t c_accNo;

  /*! Status bytes, read from status byte of the telegram. */
  uint8_t c_status;

  /*! Address information used for the long telegram header */
  s_wmbus_addr_t s_longHeaderAddr;

  /*! Telegram communication flag register.
   *  Bit 0,1   Reserved
   *  Bit 2,3   Signature
   *            00 No signature error
   *            01 Signature unknown
   *            10 Encryption error
   *            11 No encryption
   *  Bit 4     Hop counter
   *  Bit 5     Repeater access
   *  Bit 6,7   Content of message
   *  Bit 8-12  Encryption mode
   *  Bit 13    Synchronous comminication
   *  Bit 14    Accessibility
   *  Bit 15    Bidirectional communication
   */
  uint16_t i_flag;

  /*
   * Attributes provided by Authentication and Fragmentation Layer (AFL)
   */
   E_TPL_AUTH_RESULT_t e_aflAuthenticationResult;
} s_tpl_tlgAttr_t ;

/*==============================================================================
                            CALLBACK FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  Transmits a CI field and requires the type of headers.
 * @param c_ci    User specific control information field.
 * @return        Header type.
 */
/*============================================================================*/
E_TPL_HEADER_TYPE_t wmbus_tpl_evt_getCiHeader(uint8_t c_ci);

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
void wmbus_tpl_evt_mtr_sendUserData(void);

#if WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_COLLECTOR)
/*============================================================================*/
/*!
 * @brief  This function is called if a telegram is available. Collector device.
 *
 * @param e_status    Status of the telegram.
 * @param c_tlgReqId  Id of the request telegram. @ref NULL if there is no
 *                    request telegram available.
 * @param c_tlgId     Id of the telegram.
 */
/*============================================================================*/
void wmbus_tpl_evt_col_tlgAvailable(E_WMBUS_RX_t e_status, uint8_t c_tlgReqId,
                          uint8_t c_tlgId);
#endif /* WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_COLLECTOR) */

#if WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_METER)
/*============================================================================*/
/*!
 * @brief  This function is called if a telegram is available. Meter device.
 *
 * @param e_status    Status of the telegram.
 * @param c_tlgReqId  Id of the request telegram. @ref NULL if there is no
 *                    request telegram available.
 * @param c_tlgId     Id of the telegram.
 */
/*============================================================================*/
void wmbus_tpl_evt_mtr_tlgAvailable(E_WMBUS_RX_t e_status, uint8_t c_tlgReqId,
                          uint8_t c_tlgId);
#endif /* WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_METER) */

/*============================================================================*/
/*!
 * @brief  This function is called if a bidirectional communication with a
 *         meter device is started.
 *         It is the acknowledgement to wmbus_dll_open().
 *
 * @param c_tlgId   Id of the request.
 */
/*============================================================================*/
void wmbus_tpl_evt_col_opened(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  This function is called if a telegram is sent successfully. Meter deivce.
 *
 * @param c_tlgId     Id of the sent telegram.
 */
/*============================================================================*/
void wmbus_tpl_evt_mtr_tx(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  This function is called if a telegram is sent successfully. Collector device.
 *
 * @param c_tlgId     Id of the sent telegram.
 */
/*============================================================================*/
void wmbus_tpl_evt_col_tx(uint8_t c_tlgId);

/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  Initializes the transport layer.
 */
/*============================================================================*/
void wmbus_tpl_init(void);

/*============================================================================*/
/*!
 * @brief  Starts the transport layer.
 */
/*============================================================================*/
E_TPL_STATUS_t wmbus_tpl_start(s_tpl_startAttr_t* s_startAttr);

/*============================================================================*/
/*!
 * @brief  Default running function of the transport layer.
 *         This function has to be called as often as possible.
 */
/*============================================================================*/
void wmbus_tpl_run(void);

/*============================================================================*/
/*!
 * @brief  Returns the current status of the transport layer.
 *
 * @return  Status of the transport layer.
 */
/*============================================================================*/
uint8_t wmbus_tpl_getStatus(void);

/*============================================================================*/
/*!
 * @brief   Reads the header type of the CI field.
 * @param c_ci  Control information field.
 * @return      Type of the header.
 */
/*============================================================================*/
E_TPL_HEADER_TYPE_t wmbus_tpl_getHeaderType(uint8_t c_ci);

/*============================================================================*/
/*!
 * @brief  Writes the local encryption key.
 * @param pc_key  Storage to load the key from.
 * @param c_len   Size of @ref pc_key.
 * @return        @ref TRUE if the key is written.
 */
/*============================================================================*/
bool_t wmbus_tpl_setKey(uint8_t* pc_key, uint8_t c_len);

/*============================================================================*/
/*!
 * @brief  Reads the local encryption key.
 * @param pc_key  Storage to save the key into.
 * @param c_len   Size of @ref pc_key.
 * @return        @ref TRUE if the key is read.
 */
/*============================================================================*/
bool_t wmbus_tpl_getKey(uint8_t* pc_key, uint8_t c_len);

/*============================================================================*/
/*!
 * @brief  Prepares data encryption.
 * @param c_tlgId     Id of the telegram.
 * @return            @ref TRUE if the telegram is prepared for encryption.
 */
/*============================================================================*/
bool_t wmbus_tpl_encryptPrepare(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Encrypts a complete telegrams.
 * @param c_tlgId     Id of the telegram.
 * @return            Status of telegram encryption.
 */
/*============================================================================*/
E_TPL_CRYPT_RET_t wmbus_tpl_encrypt(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Decrypts a complete telegrams.
 * @param c_tlgId     Id of the telegram.
 * @return            Status of telegram decryption.
 */
/*============================================================================*/
E_TPL_CRYPT_RET_t wmbus_tpl_decrypt(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Creates a new telegram.
 *
 * @param c_type       Telegram type.
 * @param ps_meterAddr Address of the meter device.
 * @param c_ci         The value for the control information field.
 * @return             Id of the telegram.
 *                     @ref DLL_ERR_TLG_NOT_AVAILABLE if there is not enough
 *                     memory to create the telegram.
 */
/*============================================================================*/
uint8_t wmbus_tpl_createTlg(uint8_t c_type, s_wmbus_addr_t *ps_meterAddr,
                          uint8_t c_ci);

/*============================================================================*/
/*!
 * @brief  Writes data to a telegram.
 *
 * @param c_tlgId   Id of the telegram to write the data into.
 * @param pc_data   Data to write.
 * @param i_len     Number of bytes to write.
 * @param i_offset  Offset to start writing into the telegram.
 *                  @ref DLL_TLG_WRITE_APPEND if the data has to be appended.
 * @param b_reverse @ref TRUE if the data has to be written reverse.
 * @return          @ref TRUE if writing was successful.
 */
/*============================================================================*/
bool_t wmbus_tpl_writeTlg(uint8_t c_tlgId, uint8_t *pc_data, uint16_t i_len,
                    uint16_t i_offset, bool_t b_reverse);

/*============================================================================*/
/*!
 * @brief  Counts the number of telegram data bytes.
 *
 * @param c_tlgId   Id of the telegram.
 * @return          Number of data bytes.
 */
/*============================================================================*/
uint16_t wmbus_tpl_cntDataBytes(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Sets a timeout to wait before sending the next telegram.
 * @param l_timeout   Time to wait in milliseconds.
 */
/*============================================================================*/
void wmbus_tpl_setTxWait(uint32_t l_timeout);

/*============================================================================*/
/*!
 * @brief  Sends a telegram.
 *         If the telegram is sent successfully, it is destroyed by the
 *         data link layer automatically.
 *
 * @param c_tlgId  Id of the telegram to send.
 * @return         @ref TRUE if sending was successful.
 */
/*============================================================================*/
bool_t wmbus_tpl_sendTlg(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Destroys a telegram.
 *
 * @param c_tlgId  Id of the telegram to destroy.
 * @return         TRUE if the telegram exists, FALSE if c_tlgId is out of
 *                 range.
 */
/*============================================================================*/
bool_t wmbus_tpl_destroyTlg(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Receives data from a telegram.
 *
 * @param c_tlgId   Id of the telegram to read from.
 * @param pc_data   Memory to write the data into.
 * @param i_len     Number of bytes to read.
 * @param i_offset  Index to read the data from.
 * @param b_reverse The data has to be received in reverse order.
 * @return          Number of read bytes.
 *                  @ref DLL_ERR_INDEX_OUT_OF_RANGE if data could not be read.
 */
/*============================================================================*/
uint16_t wmbus_tpl_receiveTlg(uint8_t c_tlgId, uint8_t *pc_data, uint16_t i_len,
                        uint16_t i_offset, bool_t b_reverse);

/*============================================================================*/
/*!
 * @brief  Reads the attributes of a received telegram.
 *
 * @param c_tlgId         ID of the telegram.
 * @param ps_tlgAttrRecv  Memory to save the telegram information into.
 * @return                Always @ref TRUE.
 */
/*============================================================================*/
bool_t wmbus_tpl_getTlgAttr(uint8_t c_tlgId, s_tpl_tlgAttr_t *ps_tlgAttrRecv);

/*============================================================================*/
/*!
 * @brief  Sets the header values of a telegram.
 * @param c_tlgId     Id of the telegram.
 * @param ps_header   Destination structure to write the header information to.
 * @return            @ref TRUE if the header is added successfully.
 */
/*============================================================================*/
bool_t wmbus_tpl_setHeader(uint8_t c_tlgId, s_tpl_header_t* ps_header);

/*============================================================================*/
/*!
 * @brief  Reads the header of a telegram.
 * @param c_tlgId   Id of the telegram to read the header from.
 * @param ps_header Destination structure to write the header information to.
 * @return  @ref TRUE if the header could be read. Use ps_header->e_type to
 *          get the length of the header.
 */
/*============================================================================*/
bool_t wmbus_tpl_getHeader(uint8_t c_tlgId, s_tpl_header_t* ps_header);

/*========================= METER DEVICE FUNCTIONS ===========================*/
/*============================================================================*/
/*!
 * @brief  Signalizes that user data class 1 is available.
 *         This flag is reset if there is an incoming user data class 1
 *         request.
 */
/*============================================================================*/
void wmbus_tpl_setAccessDemandFlag(void);

/*========================= DATA COLLECTOR FUNCTIONS =========================*/

/*============================================================================*/
/*!
 * @brief  Start a bidirectional communication the next time as possible.
 *         Function used by collector device only.
 *
 * @return TRUE if opperation was successful.
 */
/*============================================================================*/
bool_t wmbus_tpl_open(void);

/*============================================================================*/
/*!
 * @brief  Adds a telegram to the collector queue.
 *         Function used by collector device only.
 *
 * @param c_tlgId       Id of the request.
 * @param i_meterId     Id of the meter.
 * @param b_append      If TRUE the telegram will be appended to the device specific
 *                      queue. If FALSE the telegram will set as first telegram
 *                      of the queue. Append should be set to FALSE to add a
 *                      request at the start of the queue if there was an problem
 *                      while sending the request.
 * @return              TRUE if the preparation was successful.
 */
/*============================================================================*/
bool_t wmbus_tpl_sendQueued(uint8_t c_tlgId, uint16_t i_meterId, bool_t b_append);

/*============================================================================*/
/*!
 * @brief  Resets the flag to start a bidirectional communication.
 *         Function used by collector device only.
 *
 * @param i_meterId     Id of the meter device.
 * @param b_sendNke     TRUE if the collector should send an NKE message to the
 *                      meter to terminate the fac window of the meter device.
 *                      FALSE if the collector does not expect an answer. For
 *                      example: After the collector sends the confimation of an
 *                      Installation request dll_close() must be called with
 *                      b_sendNKE = FALSE because the collector should not send an
 *                      NKE message to end the communication.
 * @return              Returns the telegram ID of the closing telegram.
 *                      If sending of NKE fails or no telegram can be created
 *                      @ref DLL_ERR_TLG_NOT_AVAILABLE is returned.
 */
/*============================================================================*/
uint8_t wmbus_tpl_close(uint16_t i_meterId, bool_t b_sendNke);

/*============================================================================*/
/*!
 * @brief   Adds a meter device to the meter list.
 *          Function used by collector device only.
 * @param   ps_meter_entry Entry of a meter.
 * @return              Id of the added meter device.
 *                      @ref DLL_ERR_METER_OUT_OF_RANGE if there is no free
 *                      space to add the meter device. If a device with the same
 *                      address is already in the list, its id is returned.
 */
/*============================================================================*/
s_tpl_addMeterRet_t wmbus_tpl_meterAdd(s_tpl_meterEntry_t*
                                                   ps_meterEntry);

/*============================================================================*/
/*!
 * @brief   Removes a meter device from the meter list.
 *          Function used by collector device only.
 * @param ps_meter  Address of the meter device.
 *                  Set to @ref NULL to clear the complete meter list.
 * @return  @ref E_TPL_RET_OK if the meter is removed successfully.
 */
/*============================================================================*/
E_TPL_RET_t wmbus_tpl_meterRemove(s_wmbus_addr_t *ps_meter);

/*============================================================================*/
/*!
 * @brief   Updates the RF adapter address of the meter device.
 *          Function used by collector device only.
 * @param ps_meter      Address of the meter device.
 * @param ps_rfadapter  Address of the RF adapter.
 * @return              @ref E_TPL_RET_OK if the adapter address could be changed.
 */
/*============================================================================*/
E_TPL_RET_t wmbus_tpl_meterSetRfAdapter(s_wmbus_addr_t *ps_meter,
                                 s_wmbus_addr_t *ps_rfadapter);

/*============================================================================*/
/*!
 * @brief   Reads the rf adapter address of the meter.
 *          Function used by collector device only.
 * @param ps_meter      Address of the meter device.
 * @param ps_rfadapter  Destination memory to write the adapter address to.
 * @return  @ref TRUE if a rf adapter address is available.
 */
/*============================================================================*/
bool_t wmbus_tpl_meterGetRfAdapter(s_wmbus_addr_t *ps_meter,
                                 s_wmbus_addr_t *ps_rfadapter);

/*============================================================================*/
/*!
 * @brief   Updates the meter specific key.
 *          Function used by collector device only.
 * @param ps_meter      Address of the meter device.
 * @param pc_key        Key to set.
 * @param c_len         Size of the key.
 * @return              @ref E_TPL_RET_OK if the key could be changed.
 */
/*============================================================================*/
E_TPL_RET_t wmbus_tpl_meterSetKey(s_wmbus_addr_t *ps_meter, uint8_t* pc_key,
                           uint8_t c_len);

/*============================================================================*/
/*!
 * @brief   Reads the key of the meter.
 *          Function used by collector device only.
 * @param ps_meter      Address of the meter device.
 * @param pc_key        memory to write the key data to.
 * @param c_len         Size of pc_key.
 * @return  @ref TRUE if a key is available.
 */
/*============================================================================*/
bool_t wmbus_tpl_meterGetKey(s_wmbus_addr_t *ps_meter, uint8_t* pc_key,
                           uint8_t c_len);

/*============================================================================*/
/*!
 * @brief  Gets the number of connected meter devices.
 *          Function used by collector device only.
 *
 * @return  Number of connected meter devices.
 */
/*============================================================================*/
uint16_t wmbus_tpl_meterGetNum(void);

/*============================================================================*/
/*!
 * @brief  Reads the address of a meter device.
 *          Function used by collector device only.
 *
 * @param i_index      Index of the meter device to get the address from.
 * @param ps_meterAddr Pointer to save the meter address into.
 * @return             @ref TRUE if the meter address could be read.
 */
/*============================================================================*/
bool_t wmbus_tpl_meterGetAddr(uint16_t i_index, s_wmbus_addr_t *ps_meterAddr);

/*============================================================================*/
/*!
 * @brief  Reads the index of a meter device.
 *          Function used by collector device only.
 *
 * @param ps_meterAddr Pointer to save the meter address into.
 * @return             Index of the meter device.
 *                     @ref DLL_ERR_METER_OUT_OF_RANGE if the meter device is
 *                     not in the list.
 */
/*============================================================================*/
uint16_t wmbus_tpl_meterGetIndex(s_wmbus_addr_t *ps_meterAddr);

/*============================================================================*/
/*!
 * @brief  Returns the address of the device.
 *
 * @param ps_meterAddr  Address of the storage to write the meter address into.
 */
/*============================================================================*/
void wmbus_tpl_getAddrOwn(s_wmbus_addr_t *ps_meterAddr);

/*============================================================================*/
/*!
 * @brief  Sets the address of the meter device.
 *
 * @param ps_meterAddr  Address of the storage to get the meter address from.
 */
/*============================================================================*/
void wmbus_tpl_setAddrOwn(s_wmbus_addr_t *ps_meterAddr);

/*============================================================================*/
/*!
 * @brief  Returns the periodical interval of a meter device. If the device is
 *         a collector always 0 is returned.
 *
 * @return  Periodical interval in milliseconds.
 */
/*============================================================================*/
uint32_t wmbus_tpl_getInterval(void);

/*============================================================================*/
/*!
 * @brief  Sets the periodical interval of a meter device.
 *
 * @param l_interval  Interval to set in milliseconds.
 */
/*============================================================================*/
void wmbus_tpl_setInterval(uint32_t l_interval);

/*============================================================================*/
/*!
 * @brief  Sets the device connected or disconnected.
 *
 * @param b_connected  @ref TRUE if the device is connected.
 */
/*============================================================================*/
void wmbus_tpl_setConnected(bool_t b_connected);

/*============================================================================*/
/*!
 * @brief  Sets the address of the data collector.
 *         (needed for OMS)
 * @param ps_collectorAddr  Collector address
 */
/*============================================================================*/
void wmbus_tpl_setCollectorAddr(s_wmbus_addr_t *ps_collectorAddr);

/*============================================================================*/
/*!
 * @brief  Reads the address of the data collector.
 *         (needed for OMS)
 * @param ps_collectorAddr  Collector address
 */
/*============================================================================*/
void wmbus_tpl_getCollectorAddr(s_wmbus_addr_t *ps_collectorAddr);

/*============================================================================*/
/*!
 * @brief  Checks if the dll is able to go in low power-mode
 * @param e_sleepMode  Power mode for the target
 * @return Returns the status of the request as @ref  E_PHY_SLEEP_RESULT_t.
 */
/*============================================================================*/
E_WMBUS_SLEEP_RESULT_t wmbus_tpl_sleep(E_WMBUS_SLEEP_MODE_t e_sleepMode);

/*============================================================================*/
/*!
 * @brief  Wake up the target
 *
 * @param e_apl_sleep_mode  Current power-mode
 */
/*============================================================================*/
void wmbus_tpl_wakeUp(E_WMBUS_SLEEP_MODE_t e_sleepMode);

/*============================================================================*/
/*!
 * @brief  Sets the frame type of the telegram. This function should only be
           used in C-mode. Only the C-mode supports packets in format A and B.
 * @param c_tlgId       Telegram Id
 * @param e_frameType   Frame type.
 */
/*============================================================================*/
void wmbus_tpl_setTlgFormat(uint8_t c_tlgId, E_WMBUS_FRAME_t e_frameType);

/*============================================================================*/
/*!
 * @brief  Sets the mode of the telegram
 * @param c_tlgId       Telegram Id
 * @param e_mode        Mode of the received telegram (S, S sync, T, C or N).
 */
/*============================================================================*/
void wmbus_tpl_setTlgMode(uint8_t c_tlgId, E_WMBUS_MODE_t e_mode);

/*============================================================================*/
/*!
 * @brief Sets the transmission power of the rf-module. Please have a look in
 *        the corresponding data sheet of the selected transceiver to choose a
 *        supported transmission power.
 * @param c_txPower      Tx power from -130dBm (0x0) to 125dBm (0xFE).
 *                       0xFF is reserved.
 */
/*============================================================================*/
void wmbus_tpl_setTxPower(uint8_t c_txPower);

/*============================================================================*/
/*!
 * @brief Reads the transmission power.
 * @return  Tx power from -130dBm (0x0) to 125dBm (0xFE).
 *          0xFF is reserved.
 */
/*============================================================================*/
uint8_t wmbus_tpl_getTxPower(void);

/*============================================================================*/
/*!
 * @brief  This function is called if the ACD bit of a meter telegram is set.
 *          Function used by collector device only.
 *
 * @param c_tlgId     Id of the received telegram.
 */
/*============================================================================*/
void wmbus_tpl_evt_col_ACDBitSet(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief Sets the radio channel of the rf-module. This function should only be
 *        used in mode N to set the correct channel for the device.
 * @param i_channel      Radio channel or channel mask.
 *                       0xFFFF is reserved.
 * @return               TRUE if the channel was set.
 */
/*============================================================================*/
bool_t wmbus_tpl_setRfChannel(E_RADIO_CHANNEL_INDEX_t e_channel);

/*============================================================================*/
/*!
 * @brief Reads the radio channel of the rf-module.
 * @return  Current radio channel
 */
/*============================================================================*/
E_RADIO_CHANNEL_INDEX_t wmbus_tpl_getRfChannel(void);

/*============================================================================*/
/*!
 * @brief Increments the access number which is used from the tpl and the apl.
 *
 * @param c_numberOfIncrements  Number of incrementations.
 *
 * @return                      Incremented access number
 */
/*============================================================================*/
uint8_t wmbus_tpl_accessNoIncrementBy(uint8_t c_numberOfIncrements);

/*============================================================================*/
/*!
 * @brief Returns the current access number which is used from the tpl and the apl.
 *
 * @return                      Current access number
 */
/*============================================================================*/
uint8_t  wmbus_tpl_getAccessNo(void);

/*============================================================================*/
/*!
 * @brief Sets the current access number which is used from the tpl and the apl.
 *
 * @param c_accessNo  Access number to be set.
 */
/*============================================================================*/
void wmbus_tpl_setAccessNo(uint8_t c_accessNo);

/*============================================================================*/
/*!
 * @brief Returns the current status byte which is used from the tpl and the apl.
 *
 * @return                      Current access number
 */
/*============================================================================*/
uint8_t  wmbus_tpl_getHeaderStatus(void);

/*============================================================================*/
/*!
 * @brief Sets a flag in the current status byte which is used from the tpl and
 *        the apl.
 *
 * @param c_flag  Flag to be set.
 */
/*============================================================================*/
void  wmbus_tpl_setHeaderStatusFlag(uint8_t c_flag);

/*============================================================================*/
/*!
 * @brief Clears a flag in the current status byte which is used from the tpl and
 *        the apl.
 *
 * @param c_flag  Flag to be cleared.
 */
/*============================================================================*/
void  wmbus_tpl_clrHeaderStatusFlag(uint8_t c_flag);

#if DSMR_V405_ENABLED
/*============================================================================*/
/*!
 * @brief   Gets the DSMR meter frame counter from DLL
 * @param   i_meterId   Meter Id (for device collector only)
 * @return  Returns frame counter in DLL
 */
/*============================================================================*/
uint32_t wmbus_tpl_dsmr_getFrameCounter(uint16_t i_meterId);
#endif /* DSMR_V405_ENABLED */

#if DSMR_V405_ENABLED
/*============================================================================*/
/*!
 * @brief   Validates the received frame counter and update the current frame
 *          counter if it is validated
 * @param   pc_frameCtrData      Frame counter data from the received telegram
 * @param   i_meterId            Meter Id (for device collector only)
 * @return  TRUE                 if frame counter is validated
 *          FALSE                if frame counter is not validated
 */
/*============================================================================*/
bool_t wmbus_tpl_dsmr_validateFrameCounter(uint8_t *pc_frameCtrData, uint16_t i_meterId);
#endif /* DSMR_V405_ENABLED */

#if DSMR_V405_ENABLED
/*============================================================================*/
/*!
 * @brief   Sets the frame counter to the memory manually
 * @param   l_frameCounter       Frame counter to be set
 * @param   i_meterId            Meter Id (for device collector only)
 * @return  TRUE                 if frame counter is set
 *          FALSE                if frame counter is not set
 */
/*============================================================================*/
bool_t wmbus_tpl_dsmr_setFrameCounter(uint32_t l_frameCounter, uint16_t i_meterId);
#endif /* DSMR_V405_ENABLED */

/*============================================================================*/
/*!
 * @brief Returns the global accessibility setting of the meter device.
 *        Default = E_WMBUS_ACCESSIBILITY_BIDIRECTIONAL_ACCESS
 *          Function used by bidirectional meter device only.
 * @return  Displayed mode in the configuration word
 */
/*============================================================================*/
E_WMBUS_ACCESSIBILITY_t wmbus_tpl_getAccessibility(void);

/*============================================================================*/
/*!
 * @brief This function is only for meter devices. Set the acessibiolity type
 *        of the meter to save energy.
 *          Function used by bidirectional meter device only.
 * @param e_access  Displayed mode in the configuration word
 */
/*============================================================================*/
void wmbus_tpl_setAccessibility(E_WMBUS_ACCESSIBILITY_t e_access);

#if WMBUS_RX_ENABLED
/*============================================================================*/
/*!
 * @brief  Activate the FAC cycle. The next telegram will be repeated in the
 *         FAC cycle.
 *         Function used by meter device only.
 *
 */
/*============================================================================*/
void wmbus_tpl_enableFAC(void);
#endif /* WMBUS_RX_ENABLED */

#if WMBUS_RX_ENABLED
/*============================================================================*/
/*!
 * @brief  Stops the FAC cycle.
 *          Function used by meter device only.
 *
 */
/*============================================================================*/
void wmbus_tpl_disableFAC(void);
#endif /* WMBUS_RX_ENABLED */

/*============================================================================*/
/*!
 * @brief  Cleans up all buffers.
 */
/*============================================================================*/
void wmbus_tpl_bufCleanUp(void);

/*============================================================================*/
/*!
 * @brief  Sends an Ack message.
 *
 * @param c_accNo   Access number to transmit.
 * @param i_meterId  Id of the connected meter. If the device is a meter this
 *                   parameter will be ignored
 * @return           Id of the sent telegram,
 *                   @ref DLL_ERR_TLG_NOT_AVAILABLE if no free buffer is
 *                   available of the telegram could not be sent.
 */
/*============================================================================*/
uint8_t wmbus_tpl_sendAck(uint8_t c_accNo, uint16_t i_meterId);

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
void wmbus_tpl_col_clearTlgQueue(void);

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
E_WMBUS_COL_QUEUE_RET_t wmbus_tpl_col_clearMtrTlgQueue(uint16_t i_meterId);

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
bool_t wmbus_tpl_mtr_setResponseDelay(E_WMBUS_RESPONSE_DELAY_t e_respDelay);
#endif /* __TRANSPORTLAYER_H__ */

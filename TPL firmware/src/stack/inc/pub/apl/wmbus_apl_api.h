#ifndef __APPLICATIONLAYER_API_H__
#define __APPLICATIONLAYER_API_H__
#ifndef __DECL_APPLICATIONLAYER_API_H__
#define __DECL_APPLICATIONLAYER_API_H__ extern
#else
#define __DECL_APPLICATIONLAYER_API_H__
#endif /* __APPLICATIONLAYER_API_H__ */

/**
  @file       wmbus_apl_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Application Layer API of Wireless M-Bus.

              Include before:
              - wmbus_typedefs.h
              - wmbus_api.h
              - stezdn_clock.h

              This application layer provides the following control information
              values:
              - 0x50:  Application reset.
              - 0x70:  Slave to master: Report of application errors.
              - 0x72:  Slave to master: 12 byte header followed by variable
                       format data.
                       Telegrams with long headers may be received, but not
                       sent.
              - 0x71:  Report of alarms.
              - 0x78:  Slave to master: Variable data format respond without
                       header.
                       Telegrams whithout header may be received but not sent.
              - 0x7A:  Slave to master: 4 byte header follwoed by variable data
                       format respond.
                       Each outgoing data telegram uses a short header.
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/

/* Stack specific includes */
#include "wmbus_global.h"

/*! @defgroup WMBUS_APL Application Layer Interface Description
 *  This section describes the API for the STACKFORCE application layer.
 *  @{
 */

/*! @defgroup WMBUS_APL_COMPILE_TIME_SET Compile time settings
 *  This section lists compile time settings for the STACKFORCE application layer.
 *  @{
 */
/*==============================================================================
                            DEFINES
==============================================================================*/
/*! Enable/disable APL clock module. Defined in wmbus_global.h by default */
#ifndef APL_CLOCK_ENABLED
  /*! Disables the clock module by default. */
  #define APL_CLOCK_ENABLED           FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning APL_CLOCK_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* APL_CLOCK_ENABLED */

/*========================= APPLICATION EVENTS ===============================*/
/*! Enable/disable APL RX event. Defined in wmbus_global.h by default */
#ifndef APL_EVT_RX_ENABLED
  /*! Enable to call the function wmbus_apl_evt_rx() if a telegram is received. */
  #define APL_EVT_RX_ENABLED            FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning APL_EVT_RX_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* APL_EVT_RX_ENABLED */

/*! Enable/disable APL TX event. Defined in wmbus_global.h by default */
#ifndef APL_EVT_TX_ENABLED
  /*! Enable to call the function wmbus_apl_evt_tx() if a telegram is sent. */
  #define APL_EVT_TX_ENABLED            FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning APL_EVT_TX_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* APL_EVT_TX_ENABLED */

/*!@} end of WMBUS_APL_COMPILE_TIME_SET */
/******************************************************************************/

/*! @defgroup WMBUS_APL_MACROS Define macros
 *  This describes general define macros for the APL.
 *  @{
 */
/*========================= STATUS BYTE ======================================*/
/*! The application layer is busy. */
#define APL_STATUS_BUSY               0x80U
/*! The application layer is inactive. */
#define APL_STATUS_INACTIVE           0x01U
/*! The application layer is in installation mode. */
#define APL_STATUS_INSTALL            0x02U
/*! The meter device is connected to a data collector. */
#define APL_STATUS_CONNECTED          0x04U
/*! The device is ready to sleep */
#define APL_STATUS_SLEEP              0x08U

/*========================= ERRORS ===========================================*/
/*! The telegram is not available.
    This define has to have the same value as DLL_ERR_TLG_NOT_AVAILABLE */
#define APL_ERR_TLG_NOT_AVAILABLE               0xFFU

/*========================= CONTROL INFORMATION FIELD (CI-field) =============*/
/*! CMD to device with none header (DSMR v2.2) */
#define APL_FIELD_CI_CMD_TO_DEVICE_NONE         0x51U
/*! CMD to device with short header (DSMR 2.2) */
#define APL_FIELD_CI_CMD_TO_DEVICE_SHORT        0x5AU
/*! CMD to device with long header (OMS Vol.2 Issue 2.0.0/2009-07-20)
                                   (DSMR 2.3.1) */
#define APL_FIELD_CI_CMD_TO_DEVICE_LONG         0x5BU

/*! Time synchronization (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define APL_FIELD_CI_TIME_SYNC_1                0x6CU
/*! Time synchronization (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define APL_FIELD_CI_TIME_SYNC_2                0x6DU
/*! Error from device with short header (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define APL_FIELD_CI_APL_ERROR_SHORT            0x6EU
/*! Error from device with long header (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define APL_FIELD_CI_APL_ERROR_LONG             0x6FU
/*! 12 byte header followed by variable format data (EN 13757-3) */
#define APL_FIELD_CI_HEADER_LONG                0x72U
/*! Alarm from device with short header (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define APL_FIELD_CI_APL_ALARM_SHORT            0x74U
/*! Alarm from device with long header (OMS Vol.2 Issue 3.0.0xxxx-xx-xx) */
#define APL_FIELD_CI_APL_ALARM_LONG             0x75U
/*! no header followed by variable data format respond (EN 13757-3) */
#define APL_FIELD_CI_HEADER_NONE                0x78U
/*! 4 byte header followed by variable data format respond (EN 13757-3) */
#define APL_FIELD_CI_HEADER_SHORT               0x7AU
/*! Link extension to device with long header (OMS Vol.2 Issue 2.0.02009-07-20) */
#define APL_FIELD_CI_LINK_TO_DEVICE_LONG        0x80U
/*! radio relaying and application layer (CEN-TC294) */
#define APL_FIELD_CI_RELAY                      0x81U
/*! networkapplication Layer (CENELEC-TC205) */
#define APL_FIELD_CI_NETWORK                    0x82U
/*! Link extension from device with short header
    (OMS Vol.2 Issue 2.0.0/2009-07-20) */
#define APL_FIELD_CI_LINK_FROM_DEVICE_SHORT     0x8AU
/*! Link extension from device with long header
    (OMS Vol.2 Issue 2.0.0/2009-07-20) */
#define APL_FIELD_CI_LINK_FROM_DEVICE_LONG      0x8BU
/*! set baud rate to 300 baud */
#define APL_FIELD_CI_BAUD_300                   0xB8U
/*! set baud rate to 600 baud */
#define APL_FIELD_CI_BAUD_600                   0xB9U
/*! set baud rate to 1200 baud */
#define APL_FIELD_CI_BAUD_1200                  0xBAU
/*! set baud rate to 2400 baud */
#define APL_FIELD_CI_BAUD_2400                  0xBBU
/*! set baud rate to 4800 baud */
#define APL_FIELD_CI_BAUD_4800                  0xBCU
/*! set baud rate to 9600 baud */
#define APL_FIELD_CI_BAUD_9600                  0xBDU
/*! set baud rate to 19200 baud */
#define APL_FIELD_CI_BAUD_19200                 0xBEU
/*! set baud rate to 38400 baud */
#define APL_FIELD_CI_BAUD_38400                 0xBFU

/*! No CI-field transmitted.
    This define has to have the same value as TPL_FIELD_CI_NULL */
#define APL_FIELD_CI_NULL                       0xFFU

/*========================= STATUS FIELD =====================================*/
/*! No error */
#define APL_FIELD_STATUS_NO_ERROR               0x00U
/*! Application busy */
#define APL_FIELD_STATUS_APPLICATION_BUSY       0x01U
/*! Any application error */
#define APL_FIELD_STATUS_ANY_APPLICATION_ERROR  0x02U
/*! Abnormal condition / alarm */
#define APL_FIELD_STATUS_ALARM                  0x03U
/*! Power low */
#define APL_FIELD_STATUS_POWER_LOW              0x04U
/*! Permanent error */
#define APL_FIELD_STATUS_PERMANENT_ERROR        0x08U
/*! Temporary error */
#define APL_FIELD_STATUS_TEMPORARY_ERROR        0x10U

#if (DSMR_V405_ENABLED || DSMR_V300_ENABLED || DSMR_V22_PLUS_ENABLED)
/*! Clock synchronisation more than 60 seconds deviation.
    DSMR v4.0.5 final P2 */
#define APL_FIELD_STATUS_CLOCK_ERROR            0x20U
/*! Fraud attempt registred.
    DSMR v4.0.5 final P2 */
#define APL_FIELD_STATUS_FRAUD_ERROR            0x40U
/*! Valve alarm.
    DSMR v4.0.5 final P2 */
#define APL_FIELD_STATUS_VALVE_ALARM            0x80U
#endif /* DSMR_V405_ENABLED || DSMR_V300_ENABLED || DSMR_V22_PLUS_ENABLED */

/*========================= METER CONFIGURATION FIELD ========================*/
#if DSMR_V405_ENABLED
/*! Meter Configuration Data Field for DSMR specification
 *     Bit              Meaning
 *     0                Clock device implemented
 *     1                Valve device implemented
 *     2                Meter type Gas only: Converted volume.
 *                              This bit is set when temperature converted value
 *                              is indicated on the display and transmitted
 *                              via M-Bus.
 *     3                Valve release command is suppored
 *     4                Valave open direct command is supported
 */

/*! Mask for clock device implemented. */
#define APL_FIELD_METER_CONF_CLOCK_IMPL                 1U
/*! Mask for valve device implemented. */
#define APL_FIELD_METER_CONF_VALVE_IMPL                 2U
/*! Mask for converted volume (meter type gas only). */
#define APL_FIELD_METER_CONF_CONV_VAL                   4U
/*! Mask for valve release command supported. */
#define APL_FIELD_METER_CONF_VALVE_REL_SUPP             8U
/*! Mask for valve open direct command supported. */
#define APL_FIELD_METER_CONF_VALVE_OPN_SUPP             16U

#endif /* DSMR_V405_ENABLED */


/*=================== CONFIGURATION WORD ENCRYPTION TYPES ====================*/
/*! Content of message mask. */
#define APL_FIELD_CONF_WORD_CONTENT_OF_MESSAGE_MASK            0x000CU
/*! Content of message bit 0. */
#define APL_FIELD_CONF_WORD_CONTENT_OF_MESSAGE_0               0x0004U
/*! Content of message bit 1. */
#define APL_FIELD_CONF_WORD_CONTENT_OF_MESSAGE_1               0x0008U
/*! Content of message bit 0
    of Encryption Mode 7 Configuration Word (OMS v4.0.2) */
#define APL_FIELD_CONF_WORD_MODE_7_CONTENT_OF_MESSAGE_0        0x4000U
/*! Content of message bit 1
    of Encryption Mode 7 Configuration Word (OMS v4.0.2) */
#define APL_FIELD_CONF_WORD_MODE_7_CONTENT_OF_MESSAGE_1        0x8000U
/*! Encryption mode mask. (5 Bits according to OMS v4.0.2)*/
#define APL_FIELD_CONF_WORD_ENCRYPT_MODE_MASK                  0x1F00U
/*! Use no encryption.  */
#define APL_FIELD_CONF_WORD_NO_ENCRYPTION                      0x0000U
/*! DES + CBC */
#define APL_FIELD_CONF_WORD_DES_CBC                            0x0200U
/*! DES + CBC with dynamic IV */
#define APL_FIELD_CONF_WORD_DES_CBC_IV                         0x0300U
/*! AES + CBC */
#define APL_FIELD_CONF_WORD_AES_CBC                            0x0400U
/*! AES + CBC with dynamic IV */
#define APL_FIELD_CONF_WORD_AES_CBC_IV                         0x0500U
/*! AES + CBC with dynamic key */
#define APL_FIELD_CONF_WORD_AES_CBC_MODE_7                     0x0700U
/*! AES + CBC with dynamic IV (DSMR Mode 15)*/
#define APL_FIELD_CONF_WORD_AES_CBC_IV_DSMR                    0x0F00U

/*========================= DATA INFORMATION FIELD ===========================*/
/*! No data */
#define APL_DIF_DATA_FIELD_NO_DATA              0x00U
/*! 8 Bit IntegerBinary */
#define APL_DIF_DATA_FIELD_8_INT                0x01U
/*! 16 Bit IntegerBinary */
#define APL_DIF_DATA_FIELD_16_INT               0x02U
/*! 24 Bit IntegerBinary */
#define APL_DIF_DATA_FIELD_24_INT               0x03U
/*! 32 Bit IntegerBinary */
#define APL_DIF_DATA_FIELD_32_INT               0x04U
/*! 32 Bit Real */
#define APL_DIF_DATA_FIELD_32_REAL              0x05U
/*! 48 Bit IntegerBinary */
#define APL_DIF_DATA_FIELD_48_INT               0x06U
/*! 64 Bit IntegerBinary */
#define APL_DIF_DATA_FIELD_64_INT               0x07U
/*! Selection for Readout */
#define APL_DIF_DATA_FIELD_SELECTION            0x08U
/*! 2 digit BCD */
#define APL_DIF_DATA_FIELD_2_BCD                0x09U
/*! 4 digit BCD */
#define APL_DIF_DATA_FIELD_4_BCD                0x0AU
/*! 6 digit BCD */
#define APL_DIF_DATA_FIELD_6_BCD                0x0BU
/*! 8 digit BCD */
#define APL_DIF_DATA_FIELD_8_BCD                0x0CU
/*! variable length */
#define APL_DIF_DATA_FIELD_VARIABLE             0x0DU
/*! 12 digit BCD */
#define APL_DIF_DATA_FIELD_12_BCD               0x0EU
/*! Special Functions */
#define APL_DIF_DATA_FIELD_SPECIAL_FUNC         0x0FU
/*! Special function: Idle Filler, following byte = DIF of next record. */
#define APL_DIF_DATA_FIELD_SPECIAL_FILLER       0x2FU

/*! Instantaneous value */
#define APL_DIF_FUNC_INSTANTANEOUS              0x00U
/*! Maximum value */
#define APL_DIF_FUNC_MAXIMUM                    0x10U
/*! Minimum value */
#define APL_DIF_FUNC_MINIMUM                    0x20U
/*! Value during error state */
#define APL_DIF_FUNC_ERROR                      0x30U
/*! LSB of storage number */
#define APL_DIF_LSB_STORAGE_NUMBER              0x40U

/*! DIF(E) extension bit. */
#define APL_DIF_EXTENSION_BIT                   0x80U

/*========================= VALUE INFORMATION FIELD ==========================*/
/*! E000 0nnn -> 10^(nnn-3) Wh */
#define APL_VIF_ENERGY_WH                       0x00U
/*! E000 1nnn -> 10^(nnn) J */
#define APL_VIF_ENERGY_J                        0x08U
/*! E001 0nnn -> 10^(nnn-6) m^3 */
#define APL_VIF_VOLUME_M3                       0x10U
/*! E001 1nnn -> 10^(nnn-3) kg */
#define APL_VIF_MASS_KG                         0x18U
/*! E010 00nn -> nn see APL_VIF_TIME_x */
#define APL_VIF_ON_TIME                         0x20U
/*! E010 01nn -> nn see APL_VIF_TIME_x */
#define APL_VIF_OPERATING_TIME                  0x24U
/*! E010 1nnn -> 10^(nnn-3) W */
#define APL_VIF_POWER_W                         0x28U
/*! E011 0nnn -> 10^(nnn) Jh */
#define APL_VIF_POWER_JH                        0x30U
/*! E011 1nnn -> 10^(nnn-6) m^3h */
#define APL_VIF_VOLUME_FLOW_M3H                 0x38U
/*! E100 0nnn -> 10^(nnn-7) m^3m */
#define APL_VIF_VOLUME_FLOW_EXT_M3M             0x40U
/*! E100 1nnn -> 10^(nnn-9) m^3s */
#define APL_VIF_VOLUME_FLOW_EXT_M3S             0x48U
/*! E101 0nnn -> 10^(nnn-3) kgh */
#define APL_VIF_MASS_FLOW_KGH                   0x50U
/*! E101 10nn -> 10^(nn-3) °C */
#define APL_VIF_FLOW_TEMPERATURE_C              0x58U
/*! E101 11nn -> 10^(nn-3) °C */
#define APL_VIF_RETURN_TEMPERATURE_C            0x5CU
/*! E110 00nn -> 10^(nn-3) K */
#define APL_VIF_TEMPERATURE_DIF_K               0x60U
/*! E110 01nn -> 10^(nn-3) °C */
#define APL_VIF_EXT_TEMPERATURE_C               0x64U
/*! E110 10nn -> 10(nn-3) bar */
#define APL_VIF_PRESSURE_BAR                    0x68U
/*! E110 1100 -> data field 0010b, type G */
#define APL_VIF_DATE                            0x6CU
/*! E110 1101 -> data field 0100b, type F
    E110 1101 -> data field 0011b, type J
    E110 1101 -> data field 0110b, type I */
#define APL_VIF_DATE_TIME                       0x6DU
/*! E110 1110 */
#define APL_VIF_UNITS_FOR_HCA                   0x6EU
/*! E111 00nn -> nn see APL_VIF_TIME_x */
#define APL_VIF_AVERAGING_DURATION              0x70U
/*! E111 01nn -> nn see APL_VIF_TIME_x */
#define APL_VIF_ACTUALITY_DURATION              0x74U
/*! E111 1000 */
#define APL_VIF_FABRICATION_NO                  0x78U
/*! E111 1001 */
#define APL_VIF_ENHANCED_ID                     0x79U
/*! E111 1010 */
#define APL_VIF_ADDRESS                         0x7AU
/*! 1111 1011 */
#define APL_VIF_FIRST_EXTENSION                 0x7BU
/*! 1111 1101 */
#define APL_VIF_SECOND_EXTENSION                0xFDU
/*! E111 1111 */
#define APL_VIF_MANUFACTURER                    0x7FU

/*! VIF(E) extension bit. */
#define APL_VIF_EXTENSION_BIT                   0x80U

/*========================= EXTENDED VALUE INFORMATION FIELD =================*/
/*! E001 1001: By default this value is reserved. */
#define APL_VIFE_SEC_KEY                        0x19U
/*! E000 1000: Unique telegram identification (transmission counter) */
#define APL_VIFE_TRANS_CTR                      0x08U
/*! E001 0111: Error flags (binary) (device type specific) */
#define APL_VIFE_ERR_FLAG                       0x17U
/*! E110 0111: Specfial supplier information */
#define APL_VIFE_SPEC_SUPP_INFO                 0x67U
#if DSMR_V405_ENABLED || DSMR_V300_ENABLED || DSMR_V22_PLUS_ENABLED
/*! E001 1001: Reserved (!DSMR uses for AES128 KEY exchange!) */
#define APL_VIFE_KEY_EXCHANGE                   0x19U
/*! E001 1001: Reserved (!DSMR uses for valve command!) */
#define APL_VIFE_REMOTE_CONTROL                 0x1FU
#endif /* DSMR_V405_ENABLED || DSMR_V300_ENABLED || DSMR_V22_PLUS_ENABLED */

/*========================= SIZEDN VIFES =====================================*/
/*! Data from an acceleration sensor
 *  [0] X
 *  [1] Y
 *  [2] Z */
#define APL_VIFE_MANUFR_ACCELERATION            0x01U
/*! Activity: boolean */
#define APL_VIFE_MANUFR_ACTIVITY                0x02U
/*! Fall: boolean */
#define APL_VIFE_MANUFR_FALL                    0x03U

/*========================= ALARMS (CI=0x74) =================================*/
/*! STACKFORCE Manufacturer Specific Alarms */
/*! Unspecified alarm: also if data field is missing */
#define APL_ALARM_UNSPECIFIED_BIT               1U
/*! No alarm: All alarm bits are 0 */
#define APL_ALARM_NONE                          0x00U
/*! All alarms */
#define APL_ALARM_ALL                           0xFFU

/*========================= APPLICATION ERRORS (CI=0x70) =====================*/
/*! Unspecified error: also if data field is missing */
#define APL_ERROR_UNSPECIFIED                   0x00U
/*! Unimplemented CI-Field */
#define APL_ERROR_CI_UNIMPLEMENTED              0x01U
/*! Buffer too long, truncated */
#define APL_ERROR_BUFFER_TOO_LONG               0x02U
/*! Too many records */
#define APL_ERROR_TOO_MANY_RECORDS              0x03U
/*! Premature end of record */
#define APL_ERROR_PREMATURE_END_OF_RECORD       0x04U
/*! More than 10 DIFE's */
#define APL_ERROR_TOO_MANY_DIFES                0x05U
/*! More than 10 VIFE's */
#define APL_ERROR_TOO_MANY_VIFES                0x06U
/*! Application too busy for handling readout request */
#define APL_ERROR_APPLICATION_BUSY              0x08U
/*! Too many readouts (for slaves with limited readouts per time) */
#define APL_ERROR_TOO_MANY_READOUTS             0x09U
/*! Access denied (Login, Password or Authorisation level is wrong)
    (OMS Vol.2 Issue 2.0.0/2009-07-20) */
#define APL_ERROR_ACCESS_DENIED                 0x10U
/*! Application/Command unknown or not supported
    (OMS Vol.2 Issue 2.0.0/2009-07-20) */
#define APL_ERROR_CMD_UNKNOWN                   0x11U
/*! Parameter is missing or wrong (OMS Vol.2 Issue 2.0.02009-07-20) */
#define APL_ERROR_PARAMETER                     0x12U
/*! Unknown Receiver address (OMS Vol.2 Issue 2.0.02009-07-20) */
#define APL_ERROR_UNKNOWN_RECEIVER              0x13U
/*! Decryption key fails (OMS Vol.2 Issue 2.0.02009-07-20) */
#define APL_ERROR_DECRYPTION_FAILS              0x14U
/*! Encryption method is not supported (OMS Vol.2 Issue 2.0.02009-07-20) */
#define APL_ERROR_ENCRYPTION_NOT_SUPPORTED      0x15U
/*! Signature method is not supported (OMS Vol.2 Issue 2.0.02009-07-20) */
#define APL_ERROR_SIGNATURE_NOT_SUPPORTED       0x16U
/*! Dynamic Application Error (OMS Vol.2 Issue 2.0.02009-07-20) */
#define APL_ERROR_DYNAMIC_APPLICATION_ERROR     0xF0U
/*! Invalid error code. */
#define APL_ERROR_INVALID                       0xFFU

/*========================= TELEGRAM FLAG REGISTER ===========================*/
/*!
 * \brief The following flags are used within the stack to signal telegram status
 *        information to the user.
 *
 * [@
 * Bit 0                Flow control
 *                        DFC bit of the C-field. Defined in EN 60870-5-2
 * Bit 1                Access demand
 *                        ACD bit of the C-field. Defined in EN 60870-5-2
 * Bit 2,3              Signature
 *                        00  No signature error
 *                        01  Signature unknown
 *                        10  Encryption error
 *                        11  No data encryption
 * Bit 4                Hop-Counter
 *                        Bit00 of the configuration word of Mode 5 EN13757-3 2013
 * Bit 5                Repeater Access
 *                        Bit01 of the configuration word of Mode 5 EN13757-3 2013
 * Bit 6,7              Content of Message
 *                        Bit02,03 of the configuration word of Mode 5 EN13757-3 2013
 * Bit 8,9,10,11,12     Encryption Mode
 *                        Bit08,09,10,11,12 of the configuration word OMS_VOL2_Primary_v401
 * Bit 13               Sync
 *                        Bit13 of the configuration word of Mode 5 EN13757-3 2013
 * Bit 14               Accessibllity
 *                        Bit14 of the configuration word of Mode 5 EN13757-3 2013
 * Bit 15               Bidirectional
 *                        Bit15 of the configuration word of Mode 5 EN13757-3 2013
 */
/*! Clears all flags. */
#define APL_TLG_FLAG_CLR                        0x0000U

/*! Data collector only: Set if further requests may be sent.  */
#define APL_TLG_FLAG_FLOW_CONTROL               0x0001U

/*! Set if user data class 1 is available. */
#define APL_TLG_FLAG_ACCESS_DEMAND              0x0002U

/*! Mask for signature field. */
#define APL_TLG_FLAG_SIGNATURE                  0x000CU
/*! Data collector only: Set if the data could not be encrpyted. */
#define APL_TLG_FLAG_SIGNATURE_UNKNOWN          0x0004U
/*! @deprecated: Data collector only: There was an encryption error. */
#define APL_TLG_FLAG_SIGNATURE_ERROR            0x0008U
/*! Data collector only: The data is unencrypted. */
#define APL_TLG_FLAG_SIGNATURE_NO               0x000CU

/*! Hop counter of the telegram */
#define APL_TLG_FLAG_HOP_COUNTER                0x0010U

/*! Hop counter of the telegram */
#define APL_TLG_FLAG_REPEATER_ACCESS            0x0020U

/* First bit of the content of message field */
#define APL_TLG_FLAG_COM_0                      0x0040U
/* Second bit of the content of message field */
#define APL_TLG_FLAG_COM_1                      0x0080U

/* Mask for mode field */
#define APL_TLG_FLAG_ENCRYPTION_MODE            0x1F00U
/* The telegram is encypted using mode 5 defined in EN13757 (2013) */
#define APL_TLG_FLAG_ENCRYPTION_MODE_5          0x0500U
/* The telegram is encypted using mode 7 defined in OMS_VOL2_Primary_v401 */
#define APL_TLG_FLAG_ENCRYPTION_MODE_7          0x0700U
/* The telegram is encypted using mode 13 defined in OMS_VOL2_Primary_v401 */
#define APL_TLG_FLAG_ENCRYPTION_MODE_13         0x0D00U

/*! Bidirectional communication. */
#define APL_TLG_FLAG_SYNC                       0x2000U

/*! Receiver always on. */
#define APL_TLG_FLAG_RX_ALWAYS_ON               0x4000U

/*! Bidirectional communication. */
#define APL_TLG_FLAG_BIDIRECTIONAL              0x8000U

/*!@} end of WMBUS_APL_MACROS */
/******************************************************************************/

/*! @defgroup WMBUS_APL_ENUMS Enumerations
 *  This section describes enumerations of the Stackforce application layer.
 *  @{
 */
/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/

/*! Enumeration of the status of the apl functions.
 *  Enumeration is used by @ref wmbus_apl_mtr_start() and wmbus_apl_col_start().
 */
typedef enum
{
  /*! Error occured for unknown reasons. */
  E_APL_STATUS_ERROR,
  /*! Invalid input parameter error */
  E_APL_STATUS_INVALID_PARAM_ERROR,
  /*! Stack not initialized error.  */
  E_APL_STATUS_NOT_INIT_ERROR,
  /*! Operation success.*/
  E_APL_STATUS_SUCCESS
} E_APL_STATUS_t;

/*! Enumeration of return values.
 *  Enumeration is used by @ref wmbus_apl_col_meterRemove(),
 *  @ref wmbus_apl_col_meterSetRfAdapter() and @ref wmbus_apl_col_meterSetKey().
 */
typedef enum
{
  /*! All OK */
  E_APL_RET_OK = 0U,
  /*! Error. */
  E_APL_RET_ERR,
  /*! Stack is not ready */
  E_APL_RET_NOT_READY,
  /*! Only used for the MeterAdd command. Indicates that
   *         the meter ist already in the list */
  E_APL_RET_DUPLICATED
} E_APL_RET_t;

/*! Enumeration for the "CC"-bit in the configuration word.
 *  Defined in the EN13757-3 2013.
 *  Enumeration is used by:
 *  - @ref wmbus_apl_col_setContentOfMessage()
 *  - @ref wmbus_apl_mtr_setContentOfMessage()
 *  - @ref wmbus_apl_col_getContentOfMessage()
 *  - @ref wmbus_apl_mtr_getContentOfMessage()
 */
typedef enum
{                                    /* |Bit3 (C)| Bit2 (C)| */
  E_APL_COM_UNKNOWN,                 /* |   x    |    x    | */
  E_APL_COM_METER_DEFAULT_DATA,      /* |   0    |    0    | */
  E_APL_COM_METER_RESERVED_SIGNED,   /* |   0    |    1    | */
  E_APL_COM_METER_STATIC,            /* |   1    |    0    | */
  E_APL_COM_METER_RESERVED,          /* |   1    |    1    | */
  E_APL_COM_OTHER_DEFAULT_COMMAND,   /* |   0    |    0    | */
  E_APL_COM_OTHER_RESERVED_AUTH,     /* |   0    |    1    | */
  E_APL_COM_OTHER_RESERVED,          /* |   1    |    0    | */
  E_APL_COM_OTHER_RESERVED_FUTURE    /* |   1    |    1    | */
}E_APL_COM_t;
/*! @} end of WMBUS_APL_ENUMS */
/******************************************************************************/

/*! @defgroup WMBUS_APL_STRUCTS Structures
 *  This section describes structures of the Stackforce application layer.
 *  @{
 */
/*==============================================================================
                             TYPEDEF STRUCTS
==============================================================================*/
/*! Structure of a data record. */
typedef struct S_APL_RECORDINFO_T
{
  /*! Coding of the value. This field specifies the data length (number of
      bytes) and the coding (Binary/Real/BCD) */
  uint8_t c_coding;
  /*! Type of the value (InstaneousMaximumMinimum) */
  uint8_t c_type;
  /*! Unit of the value (EnergyVolumeMass...) */
  uint8_t c_unit;
  /*! Extended value information. */
  uint8_t c_extended;
  /*! Exponent value.
      The number of bits is dependent of the chosen value coding. */
  uint8_t c_exponent;
  /*! Pointer to attached data. */
  uint8_t *pc_data;
  /*! Lenght of the attached data. */
  uint16_t i_dataLen;
} s_apl_recordInfo_t;

/*! Structure of telegram attributes.
 *  Structure is used by @ref wmbus_apl_getTlgAttr() and
 *  @ref wmbus_apl_evt_newMeter().
 */
typedef struct S_APL_TLGATTR_T
{
  /*! Id of the meter device the telegram was received from. If the target is
   *  in meter device mode, this field is always NULL. */
  uint16_t i_meterId;
  /*! Address of the sending device. If the target is
   * in meter device mode, this field is has to be ignored */
  s_wmbus_addr_t s_addr;
  /*! Address information used for the long telegram header */
  s_wmbus_addr_t s_longHeaderAddr;
  /*! Id of the telegram. */
  uint8_t c_tlgId;
  /*! Type of the data (CI-field). If no CI field is received, this value is
      @ref APL_FIELD_CI_NULL. */
  uint8_t c_controlInfo;
  /*! Includes the number of data bytes (with filler bytes!) */
  uint16_t i_dataLen;
  /*! Access number of the request telegram. */
  uint8_t c_accNo;
  /*! Flag register.
      See APL_TLG_FLAG_x for getting information about available flags. */
  uint16_t i_flag;
  /*! Status bytes, read from status byte of the telegram. */
  uint8_t c_status;
  /*! Link quality (RSSI).
   *  FF  no link quality available
   *  FE  -254 dBm
   *  ...
   *  00  0 dBm */
  uint8_t c_quality;
} s_apl_tlgAttr_t;

/*! Start structure holding common attributes for any WMBus device
 *  Structure is referenced by device specific start structures
 *  @ref s_apl_start_collector_attr_t and @ref s_apl_start_meter_attr_t */
PACKED_STRUCT(typedef struct S_APL_STARTCOMMONATTR_T
{
  /*! Frequency offset of the carrier. If the parameter is not known,
      set it to 0. */
  sint16_t si_freqOffset;
  /*! Address of the device */
  s_wmbus_addr_t* s_deviceAddr;
}, s_apl_startCommonAttr_t);

/*! @} end of WMBUS_APL_STRUCTS */
/******************************************************************************/

/*! @defgroup WMBUS_APL_CALLBACKS Event Callbacks
 *  This section describes callback functions that must be implemented by the
 *  application that uses the Stackforce application layer.
 *  @{
 */
/*==============================================================================
                            CALLBACK FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  This function is called if a rf telegram is received to display a
 *         LED or a symbol on the display.
 */
/*============================================================================*/
void wmbus_apl_evt_rx(void);

/*============================================================================*/
/*!
 * @brief  This function is called if a rf telegram is sent to display a
 *         LED or a symbol on the display.
 *
 * @param c_tlgId       Id of the sent telegram.
 */
/*============================================================================*/
void wmbus_apl_evt_tx(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  This function is called if a new telegram is available.
 *
 * @param e_status    Status of the received telegram. Type of @ref E_WMBUS_RX_t.
 * @param c_tlgReqId  Id of the request telegram.
 *                    If the recevied telegram is a response to a previously sent
 *                    request, this parameter holds the ID of the request
 *                    telegram. It is set to @ref APL_ERR_TLG_NOT_AVAILABLE
 *                    if there is no request telegram available.
 * @param ps_tlgAttr  Pointer to structure @ref s_apl_tlgAttr_t containing
                      attributes of the received telegram.
 *                    In case of an error this value is @ref NULL.
 */
/*============================================================================*/
void wmbus_apl_evt_tlgAvailable(E_WMBUS_RX_t e_status, uint8_t c_tlgReqId,
                          s_apl_tlgAttr_t *ps_tlgAttr);

/*============================================================================*/
/*!
 * @brief  Requests the type of header by the customer application.
 *
 *         To handle manufacturer specific CI fields this event functions has to
 *         be implemented by the customer application.
 *         If the stack has to send or receive a manufacturer specific or any
 *         unknown CI field this event is called. The application has to return
 *         the type of header that applies for this CI field in order to let the
 *         stack parse the header properly.
 *
 * @param c_ci    User specific control information field.
 * @return        Header type that applies for the given CI field. Return value
 *                must be of type @ref E_APL_HEADER_TYPE_t.
 */
/*============================================================================*/
E_APL_HEADER_TYPE_t wmbus_apl_evt_getCiHeader(uint8_t c_ci);

/*!@} end of WMBUS_APL_CALLBACKS */
/******************************************************************************/

/*! @defgroup WMBUS_APL_API Public API functions
 *  This section describes callback public API functions of the STACKFORCE
 *  application layer.
 *  @{
 */
/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/*!
 * @brief  Returns the current status of the application layer.
 *
 * @return  Current status of the application layer. Returns
 *          @ref APL_STATUS_BUSY if stack is currently processing some task.
 *          If device is a meter @ref APL_STATUS_CONNECTED is returned if
 *          the meter device is connected to a data collector.
 */
/*============================================================================*/
uint8_t wmbus_apl_getStatus(void);

/*============================================================================*/
/*!
 * @brief  Destroys a telegram.
 *         This function may only be used in events which provide user data.
 *
 * @param c_tlgId  Id of the telegram to destroy.
 * @return         TRUE if the telegram is deleted successfully,
                   FALSE if the given telegram ID is out of range.
 */
/*============================================================================*/
bool_t wmbus_apl_destroyTlg(uint8_t c_tlgId);

/*============================================================================*/
/*!
 * @brief  Adds data bytes to the telegram.
 *
 * @param c_tlgId       Id of the telegram to add the data to.
 * @param pc_data       Pointer to the data to add to the telegram.
 * @param i_len         Number of bytes to add.
 * @param b_reverse     Set @ref TRUE to add the data in reverse order.
 * @return              @ref TRUE if the data could be written.
 */
/*============================================================================*/
bool_t wmbus_apl_writeData(uint8_t c_tlgId, uint8_t *pc_data, uint16_t i_len,
                     bool_t b_reverse);

/*============================================================================*/
/*!
 * @brief  Reads data bytes from a telegram.
 *
 * @param c_tlgId       Id of the telegram to read the datam from.
 * @param pc_data       Memory to store the read data into.
 * @param i_len         Number of bytes to read.
 * @param i_offset      Offset to start reading at.
 * @return              Number of read bytes.
 */
/*============================================================================*/
uint16_t wmbus_apl_readData(uint8_t c_tlgId, uint8_t *pc_data, uint16_t i_len,
                      uint16_t i_offset);

/*============================================================================*/
/*!
 * @brief  Sets the own address of the device.
 *
 * @param ps_addr       Address of the device. Parameter must be of type
 *                      @ref s_wmbus_addr_t.
 */
/*============================================================================*/
void wmbus_apl_setDeviceAddr(s_wmbus_addr_t *ps_addr);

/*============================================================================*/
/*!
 * @brief  Returns the address of the device.
 *
 * @param ps_addr  Address of the storage to write the meter address into.
 *                 Parameter must be of type @ref s_wmbus_addr_t.
 */
/*============================================================================*/
void wmbus_apl_getDeviceAddr(s_wmbus_addr_t *ps_addr);

/*============================================================================*/
/*!
 * @brief  Copies the long header address for the application layer of a received
 *         telegram to the specified memory.
 *
 * @param c_tlgId       ID of the incoming telegram.
 * @param ps_addr       Pointer to array for storing the address.
 *                      Parameter must be of type @ref s_wmbus_addr_t.
 *
 * @return  TRUE if address is copied successfully. FALSE otherwise, e.g. if
 *          the telegram does not exist or has no long header.
 */
/*============================================================================*/
bool_t wmbus_apl_getLongHeaderAddr(uint8_t c_tlgId, s_wmbus_addr_t *ps_addr);

/*============================================================================*/
/*!
 * @brief  Sets the ACC counter of the device.
 *
 *         The acc counter will be incremented by every synchronous transmission.
 *         With this function the user is able to set a defined acc. This is
 *         needed for example if the stack wakes up from mode
 *         @ref E_WMBUS_SLEEP_MODE_DEEPSLEEP.
 *         In this case the user has to set the correct value for the acc
 *         counter using this function.
 *
 * @param c_accessNo      Value for the internal access number
 */
/*============================================================================*/
void wmbus_apl_setAccessNo(uint8_t c_accessNo);

/*============================================================================*/
/*!
 * @brief  Get the current ACC counter of the meter device.
 *
 *         This function serves as counter part to @ref wmbus_apl_setAccessNo().
 *
 * @return Value of the internal access counter
 */
/*============================================================================*/
uint8_t wmbus_apl_getAccessNo(void);

#if APL_CLOCK_ENABLED
/*============================================================================*/
/*!
 * @brief  Sets the clock of the device.
 *
 *         The clock will be insert in synchronous telegrams to add a variable
 *         value for the aes encryption. With this function the user is able
 *         to set the global clock. This is needed for example if the whole
 *         stack woke up from mode @ref E_WMBUS_SLEEP_MODE_DEEPSLEEP.
 *         In this case the user has to set the correct value for the clock
 *         with the help of this function. Please be sure to set the correct
 *         values if you use this function!
 *
 * @param ps_clock      Pointer to the clock structure.
 */
/*============================================================================*/
void wmbus_apl_setClock(s_clock_t* ps_clock);
#endif /* APL_CLOCK_ENABLED */

#if APL_CLOCK_ENABLED
/*============================================================================*/
/*!
 * @brief  Get the clock of the device.
 *
 * @param ps_clock      Pointer to the clock structure.
 */
/*============================================================================*/
void wmbus_apl_getClock(s_clock_t* ps_clock);
#endif /* APL_CLOCK_ENABLED */

/*============================================================================*/
/*!
 * @brief Sets the transmission power of the rf-module. Please have a look in
 *        the corresponding data sheet of the selected transceiver to choose a
 *        supported transmission power.
 * @param c_txPower      Tx power from -130dBm (0x0) to 125dBm (0xFE).
 *                       0xFF is reserved.
 */
/*============================================================================*/
void wmbus_apl_setTxPower(uint8_t c_txPower);

/*============================================================================*/
/*!
 * @brief Reads the transmission power.
 * @return  Tx power from -130dBm (0x0) to 125dBm (0xFE).
 *          0xFF is reserved.
 */
/*============================================================================*/
uint8_t wmbus_apl_getTxPower(void);

/*============================================================================*/
/*!
 * @brief  Sets the target in low power-mode
 *
 * @param e_sleepMode  Power mode for the target @ref E_WMBUS_SLEEP_MODE_t.
 * @return Returns the status of the request as @ref E_WMBUS_SLEEP_RESULT_t.
 */
/*============================================================================*/
E_WMBUS_SLEEP_RESULT_t wmbus_apl_sleep(E_WMBUS_SLEEP_MODE_t e_sleepMode);

/*============================================================================*/
/*!
 * @brief  Cleans up all buffers.
 */
/*============================================================================*/
void wmbus_apl_bufCleanUp(void);

/*============================================================================*/
/*!
 * @brief  Reads the APL attributes of a received telegram.
 *
 * @param c_tlgId         ID of the telegram.
 * @param ps_tlgAttrRecv  Memory to save the telegram information into.
 *                        Must be of type @ref s_apl_tlgAttr_t.
 * @return                TRUE if attributes were read successfully.
 *                        FALSE otherwise.
 */
/*============================================================================*/
bool_t wmbus_apl_getTlgAttr(uint8_t c_tlgId, s_apl_tlgAttr_t *ps_tlgAttrRecv);

/*============================================================================*/
/*!
 * @brief Sets the radio channel of the rf-module. This function should only be
 *        used in mode N to set the correct channel for the device.
 * @param e_channel      Radio channel or channel mask.
 *                       0xFFFF is reserved. @ref E_RADIO_CHANNEL_INDEX_t .
 * @return               TRUE if the channel was set. FALSE otherwise.
 */
/*============================================================================*/
bool_t wmbus_apl_setRfChannel(E_RADIO_CHANNEL_INDEX_t e_channel);

/*============================================================================*/
/*!
 * @brief Reads the radio channel of the rf-module.
 * @return  Current radio channel
 */
/*============================================================================*/
E_RADIO_CHANNEL_INDEX_t wmbus_apl_getRfChannel(void);

/*!@} end of WMBUS_APL_API_GENERAL */
/******************************************************************************/

/*!@} end of WMBUS_APL_API */
/******************************************************************************/

/*!@} end of WMBUS_APL */
/******************************************************************************/

#endif /* __APPLICATIONLAYER_API_H__ */

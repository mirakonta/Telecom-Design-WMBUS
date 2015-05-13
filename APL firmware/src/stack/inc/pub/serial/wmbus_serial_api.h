#ifndef __APP_SERIAL_H__
#define __APP_SERIAL_H__
#ifndef __DECL_APP_SERIAL_H__
#define __DECL_APP_SERIAL_H__ extern
#else
#define __APP_SERIAL_INIT_VAR__
#endif /* __DECL_APP_SERIAL_H__ */

/**
  @file       wmbus_serial_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Serial Application Programming Interface.

              Include before:
              - wmbus_typedefs.h
              - wmbus_dll_api.h
              - wmbus_apl_api.h
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/
/* Stack specific includes */
#include "wmbus_global.h"

/*==============================================================================
                            DEFINES
==============================================================================*/
/*============================ CONFIGURATIONS ================================*/
#ifndef SERIAL_EVT_RX_ENABLED
  /*! Enable to call the function wmbus_serial_evt_rx() if a telegram is received. */
  #define SERIAL_EVT_RX_ENABLED         FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_EVT_RX_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_EVT_RX_ENABLED */

#ifndef SERIAL_EVT_TX_ENABLED
  /*! Enable to call the function wmbus_serial_evt_tx() if a telegram is sent. */
  #define SERIAL_EVT_TX_ENABLED         FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_EVT_TX_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_EVT_TX_ENABLED */

#ifndef SERIAL_DLL_ENABLED
  /*! By default serial data link layer commands are disabled. */
  #define SERIAL_DLL_ENABLED            FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_DLL_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_DLL_ENABLED */

#ifndef SERIAL_APL_ENABLED
  /*! By default serial application layer commands are disabled. */
  #define SERIAL_APL_ENABLED            FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_APL_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_APL_ENABLED */

#if SERIAL_DLL_ENABLED && SERIAL_APL_ENABLED
#error Only one of these options may be set: SERIAL_DLL_ENABLED or \
  SERIAL_APL_ENABLED
#endif /* SERIAL_DLL_ENABLED && SERIAL_APL_ENABLED */

#ifndef SERIAL_CFG_APL_ENABLED
  /*! By default configuration settings are not allowed. */
  #define SERIAL_CFG_APL_ENABLED        FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_CFG_APL_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_CFG_APL_ENABLED */

#if SERIAL_APL_ENABLED
  #ifdef SERIAL_CFG_APL_ENABLED
    #if SERIAL_CFG_APL_ENABLED == FALSE
      #error Set SERIAL_CFG_APL_ENABLED to TRUE.
    #endif /* SERIAL_CFG_APL_ENABLED */
  #endif /* SERIAL_CFG_APL_ENABLED */
#endif /* SERIAL_CFG_APL_ENABLED */

#if SERIAL_DLL_ENABLED || SERIAL_CFG_APL_ENABLED
  #ifdef SERIAL_CFG_DLL_ENABLED
    #if SERIAL_CFG_DLL_ENABLED == FALSE
      #error Set SERIAL_CFG_DLL_ENABLED to TRUE.
    #endif /* SERIAL_CFG_DLL_ENABLED */
  #endif /* SERIAL_CFG_DLL_ENABLED */
#endif /* SERIAL_DLL_ENABLED || SERIAL_APL_ENABLED */

#ifndef SERIAL_CFG_DLL_ENABLED
  /*! By default configuration settings are not allowed. */
  #define SERIAL_CFG_DLL_ENABLED        FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_CFG_DLL_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_CFG_DLL_ENABLED */

#ifndef SERIAL_BAUD
  /*! Default baud rate of the serial protocol. */
  #define SERIAL_BAUD                   E_UART_BAUDRATE_115200

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_BAUD set to default value: 115200
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_BAUD */

#ifndef SERIAL_DLL_TLG_DATA
  /*! By default no data is added to the default DLL telegram available telegrams. */
  #define SERIAL_DLL_TLG_DATA           FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_DLL_TLG_DATA set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_DLL_TLG_DATA */

#ifndef SERIAL_OPEN_ENABLED
  /*! By default connection open telegrams are allowed.
      If the meter list handling does not provide open flags, this makro has
      to be set FALSE. */
  #define SERIAL_OPEN_ENABLED           TRUE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning SERIAL_OPEN_ENABLED set to default value: TRUE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* SERIAL_OPEN_ENABLED */

/*========================== SERIAL FRAME TYPES ==============================*/
/*! Confirm command type */
#define SERIAL_CMD_TYPE_CONFIRM                (uint8_t)0x00U
/*! RF data command type */
#define SERIAL_CMD_TYPE_RF_DATA                (uint8_t)0x01U
/*! Local data command type */
#define SERIAL_CMD_TYPE_LOCAL_DATA             (uint8_t)0x02U
/*! Set config command type */
#define SERIAL_CMD_TYPE_SET_CONFIG             (uint8_t)0x05U
/*! Get config command type */
#define SERIAL_CMD_TYPE_GET_CONFIG             (uint8_t)0x06U
/*! Ping command type */
#define SERIAL_CMD_TYPE_PING                   (uint8_t)0x0AU
/*! Power down on idle command type */
#define SERIAL_CMD_TYPE_POWER_DOWN_ON_IDLE     (uint8_t)0x0BU
/*! Status command type */
#define SERIAL_CMD_TYPE_STATUS                 (uint8_t)0x20U
/*! Synchronize RAM with NVM, if available. */
#define SERIAL_CMD_TYPE_SYNCHRONIZE            (uint8_t)0x21U
/*! Buffer clean up command type */
#define SERIAL_CMD_TYPE_BUFFER_CLEAN_UP        (uint8_t)0xFAU
/*! Manufacturer command type */
#define SERIAL_CMD_TYPE_MANUFR                 (uint8_t)0xFBU
/*! Internal event command type */
#define SERIAL_CMD_TYPE_INTERNAL_EVENT         (uint8_t)0xFCU
/*! Update command type */
#define SERIAL_CMD_TYPE_UPDATE                 (uint8_t)0xFDU
/*! Sizedn command type */
#define SERIAL_CMD_TYPE_SIZEDN                 (uint8_t)0xFEU
/*! Reset command type */
#define SERIAL_CMD_TYPE_RESET                  (uint8_t)0xFFU

/*============================ APL FRAME TYPES ===============================*/
/*! APL SETERR command type */
#define SERIAL_CMD_TYPE_APL_SETERR             (uint8_t)0x30U
/*! APL SETALARM command type */
#define SERIAL_CMD_TYPE_APL_SETALARM           (uint8_t)0x31U
/*! APL event telegram available command type */
#define SERIAL_CMD_TYPE_APL_EVT_TLG_AVAILABLE  (uint8_t)0x33U
/*! APL event new meter command type */
#define SERIAL_CMD_TYPE_APL_EVT_NEWMETER       (uint8_t)0x34U
/*! APL event ACD bit from the telegram is set */
#define SERIAL_CMD_TYPE_APL_EVT_ACDBIT_SET     (uint8_t)0x35U
/*! APL event UD request command type */
#define SERIAL_CMD_TYPE_APL_EVT_UD_REQ         (uint8_t)0x36U
/*! APL set UD byte command type */
#define SERIAL_CMD_TYPE_APL_SETUD_BYTE         (uint8_t)0x37U
/*! APL event tx finished type */
#define SERIAL_CMD_TYPE_APL_EVT_TX_FINISH      (uint8_t)0x38U
/*! APL event alarm telegram transmitted */
#define SERIAL_CMD_TYPE_APL_EVT_ALARM_TX       (uint8_t)0x39U
/*! APL event ACC_DMD received */
#define SERIAL_CMD_TYPE_APL_EVT_ACCDMD         (uint8_t)0x3AU
/*! APL command to set the current FAC mode */
#define SERIAL_CMD_TYPE_APL_SET_FAC            (uint8_t)0x3BU
/*! APL destroy telegram command type */
#define SERIAL_CMD_TYPE_APL_DESTROY_TLG        (uint8_t)0x40U
/*! APL TX IR command type */
#define SERIAL_CMD_TYPE_APL_TX_IR              (uint8_t)0x41U
/*! APL event ACK (after DSMR key exchange) received. */
#define SERIAL_CMD_TYPE_APL_EVT_ACKED          (uint8_t)0x42U
/*! This function is only for meter devices. Set the accessibility type of the
    meter to save energy. Function used by bidirectional meter device only. */
#define SERIAL_CMD_TYPE_APL_SET_ACCESSIBILITY  (uint8_t)0x44U
/*! Returns the global accessibility setting of the meter device.
    Default = E_WMBUS_ACCESSIBILITY_BIDIRECTIONAL_LIMITED_ACCESS function used
    by bidirectional meter device only.*/
#define SERIAL_CMD_TYPE_APL_GET_ACCESSIBILITY  (uint8_t)0x45U
/*! APL TX CMD clk command type */
#define SERIAL_CMD_TYPE_APL_TX_CMD_CLK         (uint8_t)0x46U
/*! APL TX error request command type */
#define SERIAL_CMD_TYPE_APL_TX_ERR_REQ         (uint8_t)0x47U
/*! APL TX UD request command type */
#define SERIAL_CMD_TYPE_APL_TX_UD_REQ          (uint8_t)0x48U
/*! APL RX APL error command type */
#define SERIAL_CMD_TYPE_APL_RX_APL_ERR         (uint8_t)0x4AU
/*! APL set APL error command type */
#define SERIAL_CMD_TYPE_APL_SET_APL_ERR        (uint8_t)0x4CU
/*! APL clear APL error command type */
#define SERIAL_CMD_TYPE_APL_CLR_APL_ERR        (uint8_t)0x4DU
/*! APL open command type */
#define SERIAL_CMD_TYPE_APL_OPEN               (uint8_t)0x4EU
/*! APL close command type */
#define SERIAL_CMD_TYPE_APL_CLOSE              (uint8_t)0x4FU
/*! APL meter add command type */
#define SERIAL_CMD_TYPE_APL_METER_ADD          (uint8_t)0x50U
/*! APL meter remove command type */
#define SERIAL_CMD_TYPE_APL_METER_REMOVE       (uint8_t)0x51U
/*! APL meter num command type */
#define SERIAL_CMD_TYPE_APL_METER_NUM          (uint8_t)0x52U
/*! APL meter address command type */
#define SERIAL_CMD_TYPE_APL_METER_ADDRESS      (uint8_t)0x53U
/*! APL create spontaneous telegram command type */
#define SERIAL_CMD_TYPE_APL_CREATE_SPONTANEOUS (uint8_t)0x54U
/*! APL TX spontaneous telegram command type */
#define SERIAL_CMD_TYPE_APL_TX_SPONTANEOUS     (uint8_t)0x55U
/*! APL RX data command type */
#define SERIAL_CMD_TYPE_APL_RX_DATA            (uint8_t)0x56U
/*! APL meter get RF command type */
#define SERIAL_CMD_TYPE_APL_METER_GET_RF       (uint8_t)0x57U
/*! APL meter set RF command type */
#define SERIAL_CMD_TYPE_APL_METER_SET_RF       (uint8_t)0x58U
/*! APL meter get key command type */
#define SERIAL_CMD_TYPE_APL_METER_GET_KEY      (uint8_t)0x59U
/*! APL meter set key command type */
#define SERIAL_CMD_TYPE_APL_METER_SET_KEY      (uint8_t)0x5AU
/*! APL meter ID command type */
#define SERIAL_CMD_TYPE_APL_METER_ID           (uint8_t)0x5BU
/*! APL meter set long header */
#define SERIAL_CMD_TYPE_APL_SET_LONG_HEADER    (uint8_t)0x5CU
/*! APL get long header address */
#define SERIAL_CMD_TYPE_APL_GET_LONG_HEADER    (uint8_t)0x5DU
/*! Reads out a complete telegram and destroy the telegram afterwards */
#define SERIAL_CMD_TYPE_APL_RX_WHOLE_TLG       (uint8_t)0x5EU
/*! APL TX CMD DSMR key exchange command type */
#define SERIAL_CMD_TYPE_APL_TX_CMD_KEY_EX     (uint8_t)0x5FU

/*============================ LAYER IDENTIFIER ==============================*/
/*! Identifier byte for DLL-CIG-Layer commands. */
#define SERIAL_LAYER_DLL_CIG                   (uint8_t)0x60U
/*! Identifier byte for DLL-CIG-Layer commands. */
#define SERIAL_LAYER_ELL                       (uint8_t)0x80U

/*============================ DLL FRAME TYPES ===============================*/
/*! DLL telegram available command type */
#define SERIAL_CMD_TYPE_DLL_TLG_AVAILABLE      (uint8_t)0x61U
/*! DLL opened command type */
#define SERIAL_CMD_TYPE_DLL_OPENED             (uint8_t)0x62U

/*============================ ELL FRAME TYPES ===============================*/
/*! Serial command to create a telegram based on ELL API */
#define SERIAL_CMD_TYPE_ELL_CREATE_TLG           (uint8_t)0x80U
/*! Serial command to write to a telegram based on ELL API */
#define SERIAL_CMD_TYPE_ELL_WRITE_TLG            (uint8_t)0x81U
/*! Serial command to send a telegram based on ELL API */
#define SERIAL_CMD_TYPE_ELL_SEND_TLG             (uint8_t)0x82U
/*! Serial command to destroy a telegram based on ELL API */
#define SERIAL_CMD_TYPE_ELL_DESTROY_TLG          (uint8_t)0x83U
/*! Serial command to receive telegram data based on ELL API */
#define SERIAL_CMD_TYPE_ELL_RECEIVE_TLG          (uint8_t)0x84U
/*! Serial command to receive a complete telegram based on ELL API */
#define SERIAL_CMD_TYPE_ELL_RECEIVE_COMPLETE_TLG (uint8_t)0x85U

/*========================== CONFIGURATION TYPES ==============================*/
/*! Configuration types. @todo Modified! To be confirmed!!! */
/*! CFG mode type */
#define SERIAL_CMD_CFG_MODE                    (uint8_t)0x01U
/*! CFG device type */
#define SERIAL_CMD_CFG_DEVICE                  (uint8_t)0x02U
/*! CFG RF power type */
#define SERIAL_CMD_CFG_RF_POWER                (uint8_t)0x03U
#if WMBUS_MODE_COMBINED_T_C
/*! CFG rx sense tuning */
#define SERIAL_CMD_CFG_RX_SENSE_TUNE           (uint8_t)0x05U
#endif /* WMBUS_MODE_COMBINED_T_C */
/*! CFG address type */
#define SERIAL_CMD_CFG_ADDR                    (uint8_t)0x15U
/*! CFG interval type */
#define SERIAL_CMD_CFG_INTERVAL                (uint8_t)0x16U
/*! CFG key type */
#define SERIAL_CMD_CFG_KEY                     (uint8_t)0x17U
/*! CFG clock type */
#define SERIAL_CMD_CFG_CLOCK                   (uint8_t)0x18U
/*! CFG connected type */
#define SERIAL_CMD_CFG_CONNECTED               (uint8_t)0x1BU
/*! CFG collector type */
#define SERIAL_CMD_CFG_COLLECTOR               (uint8_t)0x1CU
/*! CFG channel type */
#define SERIAL_CMD_CFG_RF_CHANNEL              (uint8_t)0x1DU
/*! CFG transceiver frequency offset */
#define SERIAL_CMD_CFG_RF_FREQ_OFFSET          (uint8_t)0x1EU

#if APP_HARDWARE_TESTING
/*! CFG start hardware test mode */
#define SERIAL_CMD_CFG_START_TEST              (uint8_t)0x30U
/*! CFG test mode */
#define SERIAL_CMD_CFG_MODE_TEST               (uint8_t)0x31U
#endif /* APP_HARDWARE_TESTING */

/*! Sets the timer counter register */
#define SERIAL_CMD_CFG_SET_TIMER_COUNTER       (uint8_t)0x32U
/*! Adds a positive or negative offset to the timer counter */
#define SERIAL_CMD_CFG_ADD_TO_TIMER_COUNTER    (uint8_t)0x33U

/*! CFG firmware version type */
#define SERIAL_CMD_CFG_FIRMWARE_VERSION        (uint8_t)0xFCU
/*! CFG flash erase type */
#define SERIAL_CMD_CFG_FLASHERASE              (uint8_t)0xFDU
/*! CFG version type */
#define SERIAL_CMD_CFG_VERSION                 (uint8_t)0xFEU

/*============================== DEVICE MODES ================================*/
/*! Mode configuration. @todo Modified! To be confirmed!!! */
/* All commented modes are not implemented on the capt2web software. */
/*! CFG mode off type */
#define SERIAL_CMD_CFG_MODE_OFF        (uint8_t)0x00U
/*! CFG mode S1 type */
#define SERIAL_CMD_CFG_MODE_S1         (uint8_t)0x01U
/*! CFG mode S1M type */
#define SERIAL_CMD_CFG_MODE_S1M        (uint8_t)0x02U
/*! CFG mode S2 type */
#define SERIAL_CMD_CFG_MODE_S2         (uint8_t)0x03U
/*! CFG mode T1 type */
#define SERIAL_CMD_CFG_MODE_T1         (uint8_t)0x04U
/*! CFG mode T2 type */
#define SERIAL_CMD_CFG_MODE_T2         (uint8_t)0x05U
/*! CFG mode R2 type */
#define SERIAL_CMD_CFG_MODE_R2         (uint8_t)0x06U
/*! CFG mode C1 type */
#define SERIAL_CMD_CFG_MODE_C1         (uint8_t)0x07U
/*! CFG mode C2 type */
#define SERIAL_CMD_CFG_MODE_C2         (uint8_t)0x08U
/*! CFG mode N1 type */
#define SERIAL_CMD_CFG_MODE_N1         (uint8_t)0x09U
/*! CFG mode N2 type */
#define SERIAL_CMD_CFG_MODE_N2         (uint8_t)0x0AU
/*! CFG mode F type */
#define SERIAL_CMD_CFG_MODE_F          (uint8_t)0x0BU
#if WMBUS_MODE_COMBINED_T_C
/*! CFG mode C type - used for combined T and C collector only */
#define SERIAL_CMD_CFG_MODE_C          (uint8_t)0x0CU
/*! CFG mode T type - used for combined T and C collector only */
#define SERIAL_CMD_CFG_MODE_T          (uint8_t)0x0DU
#endif /* WMBUS_MODE_COMBINED_T_C */
/*! CFG mode unknown type */
#define SERIAL_CMD_CFG_MODE_UNKNOWN    (uint8_t)0xFFU


/*============================== DEVICE TYPES ================================*/
/*! CFG device type meter */
#define SERIAL_CMD_CFG_DEVICE_METER            (uint8_t)0x01U
/*! CFG device type collector */
#define SERIAL_CMD_CFG_DEVICE_COLLECTOR        (uint8_t)0x02U
/*! CFG device type collector */
#define SERIAL_CMD_CFG_DEVICE_SNIFFER          (uint8_t)0x04U
/*! CFG device type unknown */
#define SERIAL_CMD_CFG_DEVICE_UNKNOWN          (uint8_t)0xFFU

/*=========================== SERIAL ERROR TYPES ==============================*/
/*! Serial confirm ok */
#define SERIAL_CONFIRM_OK                       (uint8_t)0x00U
/*! Serial confirm busy */
#define SERIAL_CONFIRM_BUSY                     (uint8_t)0x01U
/*! Serial confirm failed */
#define SERIAL_CONFIRM_FAILED                   (uint8_t)0x02U
/*! Serial confirm no data */
#define SERIAL_CONFIRM_NODATA                   (uint8_t)0x03U
/*! Serial confirm unkown command */
#define SERIAL_CONFIRM_UNKNOWN_COMMAND          (uint8_t)0x13U
/*! Serial confirm too few bytes */
#define SERIAL_CONFIRM_TOO_FEW_BYTES            (uint8_t)0x14U
/*! Serial confirm buffer too small */
#define SERIAL_CONFIRM_BUFFER_TOO_SMALL         (uint8_t)0x15U
/*! Serial confirm crc invalid */
#define SERIAL_CONFIRM_CRC_INVALID              (uint8_t)0x16U
/*! Serial confirm not supported */
#define SERIAL_CONFIRM_CFG_NOT_SUPPORTED        (uint8_t)0x20U
/*! Serial confirm modus not supported */
#define SERIAL_CONFIRM_MODUS_NOT_SUPPORTED      (uint8_t)0x21U
/*! Serial confirm channel not supported */
#define SERIAL_CONFIRM_CHANNEL_NOT_SUPPORTED    (uint8_t)0x22U
/*! Serial confirm device not supported */
#define SERIAL_CONFIRM_DEVICE_NOT_SUPPORTED     (uint8_t)0x23U
/*! Serial confirm encryption not supported */
#define SERIAL_CONFIRM_ENCRYPTION_NOT_SUPPORTED (uint8_t)0x24U
/*! Serial confirm NVM not ready to write. */
#define SERIAL_CONFIRM_NVM_NOT_READY            (uint8_t)0x25U
/*! Confirmation for the meter add command. Indicates that the meter already exists. */
#define SERIAL_CONFIRM_METER_DUPLICATED         (uint8_t)0x26U

/* RF channels.
    All commented modes are not implemented on the capt2web software. */
/*! Serial CFG command channel none */
#define SERIAL_CMD_CFG_CHAN_NONE               (uint16_t)0x0000U
/*! Serial CFG command channel 868.3 MHz */
#define SERIAL_CMD_CFG_CHAN_868_3              (uint16_t)0x0001U
/*! Serial CFG command channel 868.95 MHz */
#define SERIAL_CMD_CFG_CHAN_868_95             (uint16_t)0x0002U
/*! Serial CFG command channel 868.52 MHz */
#define SERIAL_CMD_CFG_CHAN_869_52             (uint16_t)0x0004U
/*! Serial CFG command channel 169.406250 MHz */
#define SERIAL_CMD_CFG_CHAN_169_1A             (uint16_t)0x0008U
/*! Serial CFG command channel 169.418750 MHz */
#define SERIAL_CMD_CFG_CHAN_169_1B             (uint16_t)0x0010U
/*! Serial CFG command channel 169.431250 MHz */
#define SERIAL_CMD_CFG_CHAN_169_2A             (uint16_t)0x0020U
/*! Serial CFG command channel 169.443750 MHz */
#define SERIAL_CMD_CFG_CHAN_169_2B             (uint16_t)0x0040U
/*! Serial CFG command channel 169.456250 MHz */
#define SERIAL_CMD_CFG_CHAN_169_3A             (uint16_t)0x0080U
/*! Serial CFG command channel 169.468750 MHz */
#define SERIAL_CMD_CFG_CHAN_169_3B             (uint16_t)0x0100U
/*! Serial CFG command channel 169.437500 MHz */
#define SERIAL_CMD_CFG_CHAN_169_0              (uint16_t)0x0200U
/*! Serial CFG command channel 169.412500 MHz */
#define SERIAL_CMD_CFG_CHAN_169_1              (uint16_t)0x0400U
/*! Serial CFG command channel 169.437500 MHz */
#define SERIAL_CMD_CFG_CHAN_169_2              (uint16_t)0x0800U
/*! Serial CFG command channel 169.462500 MHz */
#define SERIAL_CMD_CFG_CHAN_169_3              (uint16_t)0x1000U
/*! Serial CFG command channel unknown */
#define SERIAL_CMD_CFG_CHAN_UNKNOWN            (uint16_t)0xFFFFU

/*=========================== SERIAL ALARM TYPES ==============================*/
/*! STACKFORCE Manufacturer Specific Alarms */
/*! Unspecified alarm: also if data field is missing (Bit 0) */
#define SERIAL_ALARM_UNSPECIFIED_BIT            1U
/*! Low Battery (Bit 1) */
#define SERIAL_ALARM_LOW_BATTERY_BIT            2U
/*! Device malfunctioning (Bit 2) */
#define SERIAL_ALARM_DEVICE_MAL_FUNC_BIT        4U
/*! Transmission Power (RSSI) too high (Bit 3) */
#define SERIAL_ALARM_RSSI_TOO_HIGH_BIT          8U
/*! Transmission Power (RSSI) too low (Bit 4) */
#define SERIAL_ALARM_RSSI_TOO_LOW_BIT           16U
/*! Meter configuration changed (Bit 5) */
#define SERIAL_ALARM_CONF_CHANGED_BIT           32U
/*! Temperature too high (Bit 6) */
#define SERIAL_ALARM_TEMPERATURE_TOO_HIGH_BIT   64U
/*! Temperature too low (Bit 7) */
#define SERIAL_ALARM_TEMPERATURE_TOO_LOW_BIT    128U

/*! No alarm: All alarm bits are 0 */
#define SERIAL_ALARM_NONE                       0x00U
/*! All alarms */
#define SERIAL_ALARM_ALL                        0xFFU

/*=========================== SERIAL FAC TYPES ==============================*/
/*! FAC invalid */
#define SERIAL_FAC_INVALID                      0xFFU
/*! FAC disable */
#define SERIAL_FAC_DISABLE                      0x00U
/*! FAC enable */
#define SERIAL_FAC_ENABLE                       0x01U

/*=========================== MEMORY MODES  ==================================*/
/*! Serial CFG command memory normal mode  */
#define SERIAL_CMD_CFG_MEM_MODE_NORMAL         0x01U
/*! Serial CFG command memory memory mode  */
#define SERIAL_CMD_CFG_MEM_MODE_NVM            0x02U

/*======================= TELEGRAM AVAILABLE STATES ==========================*/
/*! DLL state telegram available error */
#define SERIAL_DLL_TLG_AVAILABLE_ERROR         0x00U
/*! DLL state telegram available succeed */
#define SERIAL_DLL_TLG_AVAILABLE_SUCCEED       0x01U
/*! DLL state telegram available timeout */
#define SERIAL_DLL_TLG_AVAILABLE_TIMEOUT       0x02U
/*! DLL state telegram available overflow */
#define SERIAL_DLL_TLG_AVAILABLE_OVERFLOW      0x03U

/*============================ INTERNAL EVENTS ===============================*/
/*! Internal message state event timeout */
#define SERIAL_INTERNAL_EVENT_TIMEOUT          0x01U
/*! Internal message state event uart overflow */
#define SERIAL_INTERNAL_EVENT_UART_OVERFLOW    0x02U

/*==============================================================================
                            STRUCTs and TYPEDEFs
==============================================================================*/

PACKED_STRUCT(typedef struct S_SERIAL_STARTCOMMONATTR_T
{
  /*! Frequency offset of the carrier. If the parameter is not known,
      set it to 0. */
  sint16_t si_freqOffset;
  /*! Address of the device */
  s_wmbus_addr_t* s_deviceAddr;
}, s_serial_startCommonAttr_t);

/*! Structure of one meter entry in the list. */
PACKED_STRUCT(typedef struct S_SERIAL_METERENTRY_T
{
  /*! Address of the meter device */
  s_wmbus_addr_t s_meterAddr;
  /*! Wmbus mode */
  E_WMBUS_MODE_t e_wmbusMode;
  /*! RF adapter */
  s_wmbus_addr_t s_rfAdapter;
  /*! Key of the meter device */
  uint8_t pc_meterKey[16];
}, s_serial_meterEntry_t);

/*! Structure of the meter list. Please note, that the meter entry array must
    be a packed list!. */
PACKED_STRUCT(typedef struct S_SERIAL_METERLIST_T
{
  /*! Number of meter devices in the list. */
  uint16_t i_numberOfMeters;
  /*! Pointer to the first meter entry. */
  s_serial_meterEntry_t* ps_meterEntry;
}, s_serial_meterList_t);

/*! Start structure to start a collector device */
PACKED_STRUCT(typedef struct S_SERIAL_STARTCOLLECTORATTR_T
{
  /* Common start attributes for all WMBus device types */
  s_serial_startCommonAttr_t s_serial_startCommonAttr;

  /*! Static meters to install at startup. If no static meters are available,
    set the parameter to NULL. */
  s_serial_meterList_t* ps_meterList;
}, s_serial_startCollectorAttr_t);

/*! Start structure to start a meter device */
PACKED_STRUCT(typedef struct S_SERIAL_STARTMETERATTR_T
{
  /*! Common start attributes for all WMBus device types */
  s_serial_startCommonAttr_t s_serial_startCommonAttr;
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
}, s_serial_startMeterAttr_t);


/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  Manufacturer specific telegram.
 *
 * @param c_bufId   Id of the buffer.
 * @param i_len     Number of available bytes.
 * @return  Set @ref TRUE if the telegram is a known one and the event handler
 *          creates the response.
 *          Set @ref FALSE if the telegram is unknown and the stack has to
 *          create the response.
 */
/*============================================================================*/
bool_t wmbus_serial_evt_manufrRx(uint8_t c_bufId, uint16_t i_len);

#if SERIAL_APL_ENABLED
/*============================================================================*/
/*!
 * @brief  Transmits a CI field and requires the type of headers.
 * @param c_ci    User specific control information field.
 * @return        Header type.
 */
/*============================================================================*/
E_APL_HEADER_TYPE_t wmbus_serial_evt_getCiHeader(uint8_t c_ci);
#endif /* SERIAL_APL_ENABLED */

/*============================================================================*/
/*!
 * @brief  Initializes the serial interface.
 */
/*============================================================================*/
void wmbus_serial_init(void);

/*============================================================================*/
/*!
 * @brief  Initializes the serial interface for collector devices.
 */
/*============================================================================*/
void wmbus_serial_initCollector(void);

/*============================================================================*/
/*!
 * @brief  Initializes the serial interface for meter devices.
 */
/*============================================================================*/
void wmbus_serial_initMeter(void);

/*============================================================================*/
/*!
 * @brief  Starts the serial communication interface for collector devices.
 */
/*============================================================================*/
void wmbus_serial_startCollector(s_serial_startCollectorAttr_t *ps_startAttr);

/*============================================================================*/
/*!
 * @brief  Starts the serial communication interface for meter devices.
 */
/*============================================================================*/
void wmbus_serial_startMeter(s_serial_startMeterAttr_t *ps_startAttr);

/*============================================================================*/
/*!
 * @brief  Runs the serial protocol.
 *         This function has to be called as often as pssible.
 */
/*============================================================================*/
void wmbus_serial_run(void);

/*============================================================================*/
/*!
 * @brief  Writes into a byte array.
 * @param pc_data  Byte array to read into.
 * @param i_len    Number of bytes to read.
 * @return         Number of read bytes.
 */
/*============================================================================*/
uint16_t wmbus_serial_read(uint8_t *pc_data, uint16_t i_len);

/*============================================================================*/
/*!
 * @brief  Transmits RFDATA.
 * @param c_rssi  RSSI value.
 * @param c_lqi   LQI value.
 * @param i_len   Number of data bytes to transmit.
 */
/*============================================================================*/
void wmbus_serial_rfdata_init(uint8_t c_rssi, uint8_t c_lqi, uint16_t i_len);

/*============================================================================*/
/*!
 * @brief  Transmits data bytes of a RFDATA telegram. Before
 *         @ref wmbus_serial_rfdata_init has to be called.
 * @param pc_data  Data to transmit.
 * @param c_len    Number of data bytes.
 */
/*============================================================================*/
void wmbus_serial_rfdata(uint8_t *pc_data, uint8_t c_len);

/*============================================================================*/
/*!
 * @brief  Finishes writing rfdata.
 */
/*============================================================================*/
void wmbus_serial_rfdata_finish(void);

/*============================================================================*/
/*!
 * @brief  Transmits LOCAL DATA.
 * @param c_reqType   Request Type
 * @param i_len       Number of data bytes to transmit.
 */
/*============================================================================*/
void wmbus_serial_localdata_init(uint8_t c_reqType, uint16_t i_len);

/*============================================================================*/
/*!
 * @brief  Transmits data bytes of a LOCAL DATA telegram. Before
 *         @ref wmbus_serial_localdata_init has to be called.
 * @param pc_data  Data to transmit.
 * @param c_len    Number of data bytes.
 */
/*============================================================================*/
void wmbus_serial_localdata_write(uint8_t *pc_data, uint8_t c_len);

/*============================================================================*/
/*!
 * @brief  Writes the header of a telegram.
 * @param i_len   Length field.
 * @param c_type  Telegram type.
 */
/*============================================================================*/
void wmbus_serial_localdata_writeHeader(uint16_t i_len, uint8_t c_type);

/*============================================================================*/
/*!
 * @brief  Finishes writing LOCAL DATA.
 */
/*============================================================================*/
void wmbus_serial_localdata_finish(void);

/*============================================================================*/
/*!
 * @brief  Sends a serial confirmation.
 * @param c_confirm   Confirmation code.
 * @param c_reqType   Request Type
 * @param pc_data     Additional data to transmit.
 * @param i_len       Number of data bytes to transmit.
 */
/*============================================================================*/
void wmbus_serial_confirm(uint8_t c_confirm, uint8_t c_reqType, uint8_t *pc_data,
                    uint16_t i_len);

/*============================================================================*/
/*!
 * @brief  This event is called if a serial telegram is received to display a
 *         LED or a symbol on the display.
 */
/*============================================================================*/
void wmbus_serial_evt_rx(void);

/*============================================================================*/
/*!
 * @brief  This function is called if a serial telegram is sent to display a
 *         LED or a symbol on the display.
 */
/*============================================================================*/
void wmbus_serial_evt_tx(void);

/*============================================================================*/
/*!
 * @brief  This event is called if a rf telegram is received to display a
 *         LED or a symbol on the display.
 */
/*============================================================================*/
void wmbus_serial_evt_rf_rx(void);

/*============================================================================*/
/*!
 * @brief  This function is called if a rf telegram is sent to display a
 *         LED or a symbol on the display.
 */
/*============================================================================*/
void wmbus_serial_evt_rf_tx(void);

/*============================================================================*/
/*!
 * @brief  Reads data from a buffer.
 * @param c_bufId   Id of the buffer. If several buffers are linked, c_bufId
 *                  includes the first one.
 * @param pc_data   Memory to copy the data from buffer to.
 * @param i_len     Number of data bytes to read from the buffer.
 * @param i_offset  Offset to start reading from the buffer.
 * @return          Number of read bytes.
 */
/*============================================================================*/
uint16_t wmbus_serial_readBuf(uint8_t c_bufId, uint8_t *pc_data, uint16_t i_len,
                     uint16_t i_offset);


#endif /* __APP_SERIAL_H__ */

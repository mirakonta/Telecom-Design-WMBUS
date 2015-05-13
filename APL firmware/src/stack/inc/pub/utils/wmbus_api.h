#ifndef __WMBUS_API_H__
#define __WMBUS_API_H__
#ifndef __DECL_WMBUS_API_H__
#define __DECL_WMBUS_API_H__ extern
#else
#define __WMBUS_API_INIT_VAR__
#endif /* __DECL_WMBUS_API_H__ */

/**
  @file       wmbus_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Wireless M-Bus configuration Application Programming Interface.

              Include before:
              - wmbus_typedefs.h
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/
/* Stack specific includes */
#include "wmbus_global.h"

/*==============================================================================
                            DEFINES
==============================================================================*/
#ifndef OMS_ENABLED
  /*! Disables the additional functions of the Open Metering System. */
  #define OMS_ENABLED                   FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning OMS_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#else
  #if (OMS_ENABLED && STZ_INFO && __SUPPORT_WARNINGS__)
  #warning OMS functions enabled.
  #endif /* OMS_ENABLED && STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* OMS_ENABLED */

#ifndef OMS_V402_ENABLED
  /*! \brief Disables the additional functions of the Open Metering System v4.0.2.
   *
   *  \details For the time being the default OMS version compiled with the
   *           stack is OMS v3 configured by define macro @ref OMS_ENABLED.
   *           Major new features of OMSv4:
   *           - Authentication & Fragmentation Layer (AFL) that splits long
   *             messages (up to 16kByte) into several fragments (= common
   *             WMBus telegrams) and calculates/adds a CMAC for the message.
   *           - Encryption Mode 7 (TPL) that allows dynamic key usage for
   *             encryption/decryption of a message.
   */
  #define OMS_V402_ENABLED                   FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning OMS_V402_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* OMS_V402_ENABLED */

#ifndef DSMR_V300_ENABLED
  /*! Disables the additional functions of the Dutch Smart Meter Requirements. */
  #define DSMR_V300_ENABLED             FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DSMR_V300_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#else
  #if (STZ_INFO && __SUPPORT_WARNINGS__ && DSMR_V300_ENABLED)
  #warning DSMR functions enabled.
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ && DSMR_V300_ENABLED */
#endif /* DSMR_V300_ENABLED */

#ifndef DSMR_V405_ENABLED
  /*! Disables the additional functions of the Dutch Smart Meter Requirements v4.0.5 */
  #define DSMR_V405_ENABLED             FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DSMR_V405_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#else
  #if (STZ_INFO && __SUPPORT_WARNINGS__ && DSMR_V405_ENABLED)
  #warning DSMR functions enabled.
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ && DSMR_V405_ENABLED */
#endif /* DSMR_V405_ENABLED */

#ifndef DSMR_V22_PLUS_ENABLED
  /*! Disables the additional functions of the Dutch Smart Meter Requirements v2.2+
      (Landis+Gyr) */
  #define DSMR_V22_PLUS_ENABLED             FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning DSMR_V22_PLUS_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#else
  #if (STZ_INFO && __SUPPORT_WARNINGS__ && DSMR_V22_PLUS_ENABLED)
  #warning DSMR functions enabled.
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ && DSMR_V22_PLUS_ENABLED */
#endif /* DSMR_V22_PLUS_ENABLED */

#ifndef CIG_V2_ENABLED
  /*! Disables the additional functions of the Dutch Smart Meter Requirements v2.2+
      (Landis+Gyr) */
  #define CIG_V2_ENABLED             FALSE

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning CIG_V2_ENABLED set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#else
  #if (STZ_INFO && __SUPPORT_WARNINGS__ && CIG_V2_ENABLED)
  #warning CIG functions enabled according to version 2.0.
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ && CIG_V2_ENABLED */
#endif /* CIG_V2_ENABLED */

/* ========================================================================== */
/*                       check specification macros                           */
/* ========================================================================== */
#ifdef OMS_ENABLED
#ifdef DSMR_V405_ENABLED
  /* Checks if both OMS and DSMR v4.0.5 are enabled, an error has to be generated. */
  #if (OMS_ENABLED && DSMR_V405_ENABLED)
  #error Both OMS and DSMR specifications cannot be enabled at the same time.
  #endif /* (OMS_ENABLED && DSMR_V405_ENABLED) */
#endif /* DSMR_V405_ENABLED */

#ifdef DSMR_V300_ENABLED
  /* Checks if both OMS and DSMR v3.0.0 are enabled, an error has to be generated. */
  #if (OMS_ENABLED && DSMR_V300_ENABLED)
  #error Both OMS and DSMR specifications cannot be enabled at the same time.
  #endif /* (OMS_ENABLED && DSMR_V300_ENABLED) */
#endif /* DSMR_V300_ENABLED */

#ifdef DSMR_V22_PLUS_ENABLED
  /* Checks if both OMS and DSMR v2.2+ are enabled, an error has to be generated. */
  #if (OMS_ENABLED && DSMR_V22_PLUS_ENABLED)
  #error Both OMS and DSMR specifications cannot be enabled at the same time.
  #endif /* (OMS_ENABLED && DSMR_V22_PLUS_ENABLED) */
#endif /* DSMR_V22_PLUS_ENABLED */
#endif /* OMS_ENABLED */

#ifdef DSMR_V405_ENABLED
#ifdef DSMR_V300_ENABLED
  /* Checks if both DSMR v4.0.5 and v3.0.0 are enabled, an error has to be generated. */
  #if (DSMR_V405_ENABLED && DSMR_V300_ENABLED)
  #error Both DSMR v405 and v300 specifications cannot be enabled at the same time.
  #endif /* (DSMR_V405_ENABLED && DSMR_V300_ENABLED) */
#endif /* DSMR_V300_ENABLED */

#ifdef DSMR_V22_PLUS_ENABLED
  /* Checks if both DSMR v4.0.5 and v2.2+ are enabled, an error has to be generated. */
  #if (DSMR_V405_ENABLED && DSMR_V22_PLUS_ENABLED)
  #error Both DSMR v405 and v22+ specifications cannot be enabled at the same time.
  #endif /* (DSMR_V405_ENABLED && DSMR_V22_PLUS_ENABLED) */
#endif /* DSMR_V22_PLUS_ENABLED */
#endif /* DSMR_V405_ENABLED */

#ifdef DSMR_V405_ENABLED
  /* Checks if the DSMR v4.0.5 is enabled, the Alarm Access Demand must not be sent. */
  #ifdef APL_ALARM_ACC_DMD_ENABLED
    #if APL_ALARM_ACC_DMD_ENABLED
        #error When DSMR v405 is enabled Alarm Access Demand must not be sent.
    #endif /* APL_ALARM_ACC_DMD_ENABLED */
  #else
    #define APL_ALARM_ACC_DMD_ENABLED          FALSE
  #endif /* APL_ALARM_ACC_DMD_ENABLED */
#endif /* DSMR_V405_ENABLED */

#ifdef CIG_V2_ENABLED
  /* Checks if the DSMR v4.0.5 is enabled, the Alarm Access Demand must not be sent. */
  #if CIG_V2_ENABLED
    #if (DSMR_V405_ENABLED || DSMR_V22_PLUS_ENABLED || DSMR_V300_ENABLED ||\
         OMS_ENABLED)
        #error More than one specification is enabled
    #endif /* (DSMR_V405_ENABLED || DSMR_V22_PLUS_ENABLED || DSMR_V300_ENABLED |\
               OMS_ENABLED) */
  #endif /* #if CIG_V2_ENABLED */
#endif /* #ifdef CIG_V2_ENABLED */

/*! Initialisation vectors for the de- and encryption.
   Default: WMBUS_IV_METER_ADDR (As defined in EN13757) */
#define WMBUS_IV_METER_ADDR       1
/*! Initialisation vectors for the de- and encryption.
   Default: WMBUS_IV_METER_ADDR (As defined in EN13757) */
#define WMBUS_IV_COLLECTOR_ADDR   2

/* Defines of the highest layer with which the wmbus stack operates. */
/*! The stack operates at with the APL layer as highest layer. */
#define WMBUS_STACK_LAYER_APL                     0x00
/*! The stack operates at with the TPL layer as highest layer. */
#define WMBUS_STACK_LAYER_TPL                     0x01
/*! The stack operates at with the DLL layer as highest layer. */
#define WMBUS_STACK_LAYER_DLL                     0x02

/*! Other */
#define WMBUS_DEV_TYPE_OTHER                      0x00U
/*! Oil */
#define WMBUS_DEV_TYPE_OIL                        0x01U
/*! Electricity */
#define WMBUS_DEV_TYPE_ELECTRICITY                0x02U
/*! Gas */
#define WMBUS_DEV_TYPE_GAS                        0x03U
/*! Heat */
#define WMBUS_DEV_TYPE_HEAT                       0x04U
/*! Steam */
#define WMBUS_DEV_TYPE_STEAM                      0x05U
/*! Warm Water (30°C...90°C) */
#define WMBUS_DEV_TYPE_WARM_WATER                 0x06U
/*! Water */
#define WMBUS_DEV_TYPE_WATER                      0x07U
/*! Heat Cost Allocator */
#define WMBUS_DEV_TYPE_HEAT_COST_ALLOCATOR        0x08U
/*! Compressed Air */
#define WMBUS_DEV_TYPE_COMPRESSED_AIR             0x09U
/*! Cooling load meter (Volume measured at return temperature: outlet) */
#define WMBUS_DEV_TYPE_CLM_OUTLET                 0x0AU
/*! Cooling load meter (Volume measured at flow temperature: inlet) */
#define WMBUS_DEV_TYPE_CLM_INLET                  0x0BU
/*! Heat (Volume measured at flow temperature: inlet) */
#define WMBUS_DEV_TYPE_HEAT_INLET                 0x0CU
/*! Heat / Cooling load meter */
#define WMBUS_DEV_TYPE_HEAT_COOLING_LOAD_METER    0x0DU
/*! Bus / System component */
#define WMBUS_DEV_TYPE_BUS_SYSTEM_COMPONENT       0x0EU
/*! Unknwon medium */
#define WMBUS_DEV_TYPE_UNKNOWN_MEDIUM             0x0FU
/* 0x10 to 0x14 reserved */
/*! Hot water (>=90°C) */
#define WMBUS_DEV_TYPE_HOT_WATER                  0x15U
/*! Cold water */
#define WMBUS_DEV_TYPE_COLD_WATER                 0x16U
/*! Dual register (hot/cold) Water Meter */
#define WMBUS_DEV_TYPE_DUAL_REGISTER_WATER_METER  0x17U
/*! Pressure */
#define WMBUS_DEV_TYPE_PRESSURE                   0x18U
/*! A/D Converter */
#define WMBUS_DEV_TYPE_AD_CONVERTER               0x19U
/* 0x1A to 0x20 reserved */
/*! Reserved for valve */
#define WMBUS_DEV_TYPE_VALVE                      0x21U
/* 0x22 to 0xFF reserved */
/*! Display device (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_DISPLAY                    0x25U
/*! OMS MUC (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_MUC                        0x31U
/*! OMS unidirectional repeater (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_REPEATER_UNIDIRECTIONAL    0x32U
/*! OMS bidirectional repeater (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_REPEATER_BIDIRECTIONAL     0x33U
/*! Smart Metering Electricity Meter (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_SM_ELECTRICITY             0x42U
/*! Smart Metering Gas Meter (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_SM_GAS                     0x43U
/*! Smart Metering Heat Meter (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_SM_HEAT                    0x44U
/*! Smart Metering Water Meter (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_SM_WATER                   0x47U
/*! Smart Metering Heat Cost Allocator (OMS Vol.2 Issue 2.0.02009-07-20) */
#define WMBUS_DEV_TYPE_SM_HCALLOC                 0x48U
/*@}*/


/* ========================================================================== */

/*! Wireless M-Bus mode S1 */
#define WMBUS_CFG_MODE_S1                 0x0002U
/*! Wireless M-Bus mode S1-m */
#define WMBUS_CFG_MODE_S1M                0x0004U
/*! Wireless M-Bus mode S2 */
#define WMBUS_CFG_MODE_S2                 0x0008U
/*! Wireless M-Bus mode T1 */
#define WMBUS_CFG_MODE_T1                 0x0010U
/*! Wireless M-Bus mode T2 */
#define WMBUS_CFG_MODE_T2                 0x0020U
/*! Wireless M-Bus mode N1 */
#define WMBUS_CFG_MODE_N1                 0x0040U
/*! Wireless M-Bus mode N2 */
#define WMBUS_CFG_MODE_N2                 0x0080U
/*! Wireless M-Bus mode C1 */
#define WMBUS_CFG_MODE_C1                 0x0100U
/*! Wireless M-Bus mode C2 */
#define WMBUS_CFG_MODE_C2                 0x0200U
/*! Provide all Wireless M-Bus modes */
#define WMBUS_CFG_MODE_all                0xFFFFU


#if (WMBUS_CFG_MODE != WMBUS_CFG_MODE_all)
  #if (WMBUS_CFG_MODE == WMBUS_CFG_MODE_S2)
    #define WMBUS_MODE_S2                 TRUE
  #elif (WMBUS_CFG_MODE == WMBUS_CFG_MODE_S1)
    #define WMBUS_MODE_S1                 TRUE
  #elif (WMBUS_CFG_MODE == WMBUS_CFG_MODE_S1M)
    #define WMBUS_MODE_S1M                TRUE
  #elif (WMBUS_CFG_MODE == WMBUS_CFG_MODE_T1)
    #define WMBUS_MODE_T1                 TRUE
  #elif (WMBUS_CFG_MODE == WMBUS_CFG_MODE_T2)
    #define WMBUS_MODE_T2                 TRUE
  #elif (WMBUS_CFG_MODE == WMBUS_CFG_MODE_N1)
    #define WMBUS_MODE_N1                 TRUE
  #elif (WMBUS_CFG_MODE == WMBUS_CFG_MODE_N2)
    #define WMBUS_MODE_N2                 TRUE
  #elif (WMBUS_CFG_MODE == WMBUS_CFG_MODE_C1)
    #define WMBUS_MODE_C1                 TRUE
  #elif (WMBUS_CFG_MODE == WMBUS_CFG_MODE_C2)
    #define WMBUS_MODE_C2                 TRUE
  #else
    #error Please define a valid wireless m-bus mode
  #endif /* (WMBUS_CFG_MODE == WMBUS_CFG_MODE_S2)  */

  #define WMBUS_MODE                      TRUE

  #ifndef WMBUS_MODE_S2
    #define WMBUS_MODE_S2                 FALSE
  #endif /* WMBUS_MODE_S2 */
  #ifndef WMBUS_MODE_S1
    #define WMBUS_MODE_S1                 FALSE
  #endif /* WMBUS_MODE_S1 */
  #ifndef WMBUS_MODE_S1M
    #define WMBUS_MODE_S1M                FALSE
  #endif /* WMBUS_MODE_S1M */
  #ifndef WMBUS_MODE_T1
    #define WMBUS_MODE_T1                 FALSE
  #endif /* WMBUS_MODE_T1 */
  #ifndef WMBUS_MODE_T2
    #define WMBUS_MODE_T2                 FALSE
  #endif /* WMBUS_MODE_T2 */
  #ifndef WMBUS_MODE_N1
    #define WMBUS_MODE_N1                 FALSE
  #endif /* WMBUS_MODE_N1 */
  #ifndef WMBUS_MODE_N2
    #define WMBUS_MODE_N2                 FALSE
  #endif /* WMBUS_MODE_N2 */
  #ifndef WMBUS_MODE_C1
    #define WMBUS_MODE_C1                 FALSE
  #endif /* WMBUS_MODE_C1 */
  #ifndef WMBUS_MODE_C2
    #define WMBUS_MODE_C2                 FALSE
  #endif /* WMBUS_MODE_C2 */

  #define WMBUS_MODE_all                  FALSE

#else
  /*! Wireless M-Bus mode S1 */
  #define WMBUS_MODE_S1                 0x0002U
  /*! Wireless M-Bus mode S1-m */
  #define WMBUS_MODE_S1M                0x0004U
  /*! Wireless M-Bus mode S2 */
  #define WMBUS_MODE_S2                 0x0008U
  /*! Wireless M-Bus mode T1 */
  #define WMBUS_MODE_T1                 0x0010U
  /*! Wireless M-Bus mode T2 */
  #define WMBUS_MODE_T2                 0x0020U
  /*! Wireless M-Bus mode N1 */
  #define WMBUS_MODE_N1                 0x0040U
  /*! Wireless M-Bus mode N2 */
  #define WMBUS_MODE_N2                 0x0080U
  /*! Wireless M-Bus mode C1 */
  #define WMBUS_MODE_C1                 0x0100U
  /*! Wireless M-Bus mode C2 */
  #define WMBUS_MODE_C2                 0x0200U
  /*! Provide all Wireless M-Bus modes */
  #define WMBUS_MODE_all                0xFFFFU

  #define WMBUS_MODE                    WMBUS_MODE_all
#endif /* (WMBUS_CFG_MODE != WMBUS_CFG_MODE_all) */

/*@}*/
/*! Use configuration of data collector. */
#define WMBUS_CFG_DEVICE_COLLECTOR        0x01U
/*! Use configuration of meter device. */
#define WMBUS_CFG_DEVICE_METER            0x02U
/*! Use configuration of sniffer device. */
#define WMBUS_CFG_DEVICE_SNIFFER          0x04U
/*! Allow switching between meter and collector. */
#define WMBUS_CFG_DEVICE_all              0xFFU
/*@}*/

#if (WMBUS_CFG_DEVICE != WMBUS_CFG_DEVICE_all)
  #if (WMBUS_CFG_DEVICE == WMBUS_CFG_DEVICE_COLLECTOR)
    #define WMBUS_DEVICE_COLLECTOR      TRUE
  #elif (WMBUS_CFG_DEVICE == WMBUS_CFG_DEVICE_METER)
    #define WMBUS_DEVICE_METER          TRUE
  #elif (WMBUS_CFG_DEVICE == WMBUS_CFG_DEVICE_SNIFFER)
    #define WMBUS_DEVICE_SNIFFER        TRUE
  #else
    #error Please define a valid wireless m-bus device
  #endif /* (WMBUS_CFG_DEVICE != WMBUS_CFG_DEVICE_all) */

  #define WMBUS_DEVICE                  TRUE

  /*! Use configuration of data collector. */
  #ifndef  WMBUS_DEVICE_COLLECTOR
  #define WMBUS_DEVICE_COLLECTOR        FALSE
  #endif /* WMBUS_DEVICE_COLLECTOR */

  #ifndef  WMBUS_DEVICE_METER
  #define WMBUS_DEVICE_METER            FALSE
  #endif /* WMBUS_DEVICE_METER */

  #ifndef  WMBUS_DEVICE_SNIFFER
  #define WMBUS_DEVICE_SNIFFER          FALSE
  #endif /* WMBUS_DEVICE_SNIFFER */

  /*! Allow switching between meter and collector. */
  #define WMBUS_DEVICE_all              FALSE
  /*@}*/
#else
#error The device "WMBUS_CFG_DEVICE_all" is not supported
#endif /* (WMBUS_CFG_DEVICE != WMBUS_DEVICE_all) */


/*! Unidirectional modes. */
#define WMBUS_MODE_UNIDIRECTIONAL     ( WMBUS_MODE_S1 | WMBUS_MODE_S1M | \
                                        WMBUS_MODE_T1 | WMBUS_MODE_C1 | WMBUS_MODE_N1)
/*! Bidirectional modes. */
#define WMBUS_MODE_BIDIRECTIONAL      (  WMBUS_MODE_S2 | WMBUS_MODE_T2 \
                                       | WMBUS_MODE_C2 |WMBUS_MODE_N2 )

/* ========================================================================== */

/*! Converts an address before transmitting (tx) or after receiving (rx).
    M0M1 A0A1A2A3 V T => M1M0 A3A2A1A0 V T */
#define WMBUS_ADDR_FLIP(x, y)         wmbus_addrFlip((x), (y))

/*! Copies an address. */
#define WMBUS_ADDR_CPY(x, y)          wmbus_addrCopy((x), (y))

/*! Compares two addresses */
#define WMBUS_ADDR_CMP(x, y)          wmbus_addrCompare((x), (y))

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/

/*! Enumeration of return values. */
typedef enum
{
  /*! All OK */
  E_WMBUS_COL_QUEUE_RET_OK = 0U,
  /*! An Error occured. */
  E_WMBUS_COL_QUEUE_RET_ERR,
  /*! The telegram id already exists in the queue */
  E_WMBUS_COL_QUEUE_RET_DUPLICATED_ID,
 /*! The queue is full. The element can not be added now */
  E_WMBUS_COL_QUEUE_RET_QUEUE_FULL,
 /*! Something is wrong with the inserted function parameters */
  E_WMBUS_COL_QUEUE_RET_INVALID_PARAM
} E_WMBUS_COL_QUEUE_RET_t;

/*! Return values of sleep requests. */
typedef enum
{
  /*! The data link layer is ready to go to sleep mode. */
  E_WMBUS_SLEEP_RESULT_OK = 0U,
  /*! The data link layer is not able to go to sleep mode because it is busy. */
  E_WMBUS_SLEEP_RESULT_BUSY,
  /*! The sleep mode is not provided. */
  E_WMBUS_SLEEP_RESULT_FAILED
} E_WMBUS_SLEEP_RESULT_t;

/*! Different power modes of the stack */
typedef enum
{
  /*! The data in the RAM is stored and the
      transceiver is set in mode IDLE (This mode should only be used by the
      stack). */
  E_WMBUS_SLEEP_MODE_SILENCE,
  /*! It is assumed that the mcu will enter a lpm state in which the RAM content
      will be kept. The radio will be set to power down mode. The "tmr_tick"
      counter will not be called */
  E_WMBUS_SLEEP_MODE_SLEEP,
  /*! It is assumed that the mcu will enter a lpm state in which the RAM content
      will not be kept. The radio will be set to power down mode. The "tmr_tick"
      counter will not be called */
  E_WMBUS_SLEEP_MODE_DEEPSLEEP
} E_WMBUS_SLEEP_MODE_t;

/*! Enumeration of accessibility types displayed in the configuration field.
    This enum is only used for bidirectional meter devices */
typedef enum
{
  /* The last two bits of the configuration word will show that the
     telegram was send from an unidirectional device. (BIT15 = 0 Bit 14 = 0) */
  E_WMBUS_ACCESSIBILITY_UNIDIRECTIONAL = 0,
  /* The last two bits of the configuration word will show that the
     telegram was send from a bidirectional device. The meter supports
     bidirectional access in general, but there is no access window after this
     transmission  (BIT15 = 0 Bit 14 = 1) */
  E_WMBUS_ACCESSIBILITY_BIDIRECTIONAL_NO_ACCESS = 1,
  /* The last two bits of the configuration word will show that the
     telegram was send from a bidirectional device. The meter provides a short
     access window only immediately after this transmission   (BIT15 = 1 Bit 14 = 0) */
  E_WMBUS_ACCESSIBILITY_BIDIRECTIONAL_LIMITED_ACCESS = 2,
  /* The last two bits of the configuration word will show that the
     telegram was send from a bidirectional device. The meter provides unlimited
     access at least until next transmission  (BIT15 = 1 Bit 14 = 1) */
  E_WMBUS_ACCESSIBILITY_BIDIRECTIONAL_UNLIMITED_ACCESS = 3,
} E_WMBUS_ACCESSIBILITY_t;

/*! Enumeration of fac delay types as specified by EN13757-4 (2013). */
typedef enum
{
  /* FAC delay = 2 seconds. Applicable for mode S2,T2 and C2 */
  E_WMBUS_FAC_TX_DELAY_2,
  /* FAC delay = 3 seconds. Applicable for mode S2,T2 and C2 */
  E_WMBUS_FAC_TX_DELAY_3,
  /* FAC delay = 5 seconds. Applicable for mode S2,T2,C2 and N2 */
  E_WMBUS_FAC_TX_DELAY_5,
  /* FAC delay = 7 seconds. Applicable for mode N2 only */
  E_WMBUS_FAC_TX_DELAY_7,
  /* FAC delay = 13 seconds. Applicable for mode N2 only */
  E_WMBUS_FAC_TX_DELAY_13,
} E_WMBUS_FAC_TX_DELAY;

/*! Enumeration of response delay types as specified by EN13757-4 (2013). */
typedef enum
{
  /* The device should use the slow response delay */
  E_WMBUS_RESPONSE_DELAY_SLOW = 0x00U,
  /* The device should use the fast response delay */
  E_WMBUS_RESPONSE_DELAY_FAST = 0x01U
} E_WMBUS_RESPONSE_DELAY_t;

/*! Enumeration of data rates specified by EN13757-4 (2013) for the different
    n-modes. */
typedef enum
{
  /*! 2400 BPS. */
  E_WMBUS_DATA_RATE_2400 = 0x00U,
  /*! 4800 BPS. */
  E_WMBUS_DATA_RATE_4800 = 0x01U
} E_WMBUS_DATA_RATE_t;


/*! Definition of the radio channels (as array index).
    Make sure the definitions to match those of the serial module.
*/
typedef enum E_RADIO_CHANNEL_INDEX
{
  /*! Channel none */
  E_RF_CFG_CHAN_NONE = 0,

  /* 868 MHZ channels */
  /*! Channel 868.3 MHz */
  E_RF_CFG_CHAN_868_30,
  /*! Channel 868.95 MHz */
  E_RF_CFG_CHAN_868_95,
  /*! Channel 868.52 MHz */
  E_RF_CFG_CHAN_869_52,

  /* 169 MHZ channels */
  /*! Channel 169.406250 MHz */
  E_RF_CFG_CHAN_169_1A,
  /*! Channel 169.418750 MHz */
  E_RF_CFG_CHAN_169_1B,
  /*! Channel 169.431250 MHz */
  E_RF_CFG_CHAN_169_2A,
  /*! Channel 169.443750 MHz */
  E_RF_CFG_CHAN_169_2B,
  /*! Channel 169.456250 MHz */
  E_RF_CFG_CHAN_169_3A,
  /*! Channel 169.468750 MHz */
  E_RF_CFG_CHAN_169_3B,
  /*! Channel 169.437500 MHz */
  E_RF_CFG_CHAN_169_0,
  /*! Channel 169.412500 MHz */
  E_RF_CFG_CHAN_169_1,
  /*! Channel 169.437500 MHz */
  E_RF_CFG_CHAN_169_2,
  /*! Channel 169.462500 MHz */
  E_RF_CFG_CHAN_169_3,
  /*! Channel max */
  /* maximum for arrays */
  E_RF_CFG_CHAN_MAX,
  /*! Channel unknown - error case, should never occur  */
  E_RF_CFG_CHAN_UNKNOWN

}E_RADIO_CHANNEL_INDEX_t;
/*==============================================================================
                            TYPEDEF STRUCTS
==============================================================================*/
/*! Wireless M-Bus stack version */
typedef struct
{
  /*! Main version. */
  uint8_t c_mainVersion;
  /*! Subversion */
  uint8_t c_subVersion;
  /*! Release version */
  uint8_t c_releaseVersion;
} s_wmbus_version_t;

/* Includes related to telegram information. */
#include "wmbus_tlg_api.h"

/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/

/*============================================================================*/
/*!
 * @brief This function initializes all stack-global stuff.
 */
/*============================================================================*/
void wmbus_init(void);

/*============================================================================*/
/*!
 * @brief Sets the appropriate mode for the whole stack.
 *
 * @param l_mode      The wanted mode.
 * @return            Returns @ref TRUE if mode could be set.
 */
/*============================================================================*/
bool_t wmbus_setMode(uint32_t l_mode);

/*============================================================================*/
/*!
 * @brief Gets the current mode of the whole stack.
 *
 * @return            Returns the mode currently set.
 */
/*============================================================================*/
uint32_t wmbus_getMode(void);

/*============================================================================*/
/*!
 * @brief Sets the appropriate type of device for the whole stack.
 *
 * @param l_device    The wanted type of device.
 * @return            Returns @ref TRUE if type could be set.
 */
/*============================================================================*/
bool_t wmbus_setDevice(uint32_t l_device);

/*============================================================================*/
/*!
 * @brief Gets the current type of device of the whole stack.
 *
 * @return            Returns the type of device currently set.
 */
/*============================================================================*/
uint32_t wmbus_getDevice(void);

/*============================================================================*/
/*!
 * @brief Flips an address to destination memory.
 * @details Flipping in this context means that the Wireless M-Bus address fields
 *          "Manufacturer ID" and the "Identification Numder" (that are multiple
 *          byte fields) are returned in reverse byte order.
 *          The remaining two address fields "Version" and "Type" are not
 *          affected by the flipping as these are single byte fields.
 *          Result can be displayed as:
 *          M0M1 A0A1A2A3 V T => M1M0 A3A2A1A0 V T
 * @param ps_dst  Destination address memory to store the flipped address.
 * @param ps_src  Source address memory to read the address from.
 */
/*============================================================================*/
void wmbus_addrFlip(s_wmbus_addr_t* ps_dst, s_wmbus_addr_t* ps_src);

/*============================================================================*/
/*!
 * @brief Copies an address to destination memory.
 * @param ps_dst  Destination address memory to store the address to.
 * @param ps_src  Source address memory to read the address from.
 */
/*============================================================================*/
void wmbus_addrCopy(s_wmbus_addr_t* ps_dst, s_wmbus_addr_t* ps_src);

/*============================================================================*/
/*!
 * @brief Compares two addresses.
 * @param ps_addr1  One address to compare.
 * @param ps_addr2  The other address to compare.
 * @return          TRUE if the addresses are equal.
 * @return          FALSE if the addresses are different.
 */
/*============================================================================*/
bool_t wmbus_addrCompare(s_wmbus_addr_t* ps_addr1, s_wmbus_addr_t* ps_addr2);

/*============================================================================*/
/*!
 * @brief Gets the current version of the stack.
 *
 * @return            Returns the stack version.
 */
/*============================================================================*/
s_wmbus_version_t wmbus_getVersion(void);

#endif /* __WMBUS_API_H__ */

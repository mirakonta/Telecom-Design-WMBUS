/**
  @file       wmbus_config.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Configuration of Wireless M-Bus.

              Include before:
                - wmbus_typedefs.h
                - wmbus_api.h
*/


#ifndef __WMBUS_CONFIG_H__
#define __WMBUS_CONFIG_H__

#ifndef __DECL_WMBUS_CONFIG_H__
#define __DECL_WMBUS_CONFIG_H__ extern
#else
#define __WMBUS_CONFIG_INIT_VAR__
#endif /* __DECL_WMBUS_CONFIG_H__ */

/*==============================================================================
                            INCLUDES
==============================================================================*/
/* Stack specific includes */
#include "wmbus_global.h"

#if (WMBUS_DEVICE == WMBUS_DEVICE_METER)
#include "wmbus_meter_config.h"
#elif ((WMBUS_DEVICE == WMBUS_DEVICE_COLLECTOR) || (WMBUS_DEVICE == WMBUS_DEVICE_SNIFFER))
#include "wmbus_collector_config.h"
#else
#error Please choose a supported device
#endif /* (WMBUS_DEVICE == WMBUS_DEVICE_METER) */
/*==============================================================================
                            CHECK CONFIG
==============================================================================*/
#if !defined(WMBUS_MODE)
  #error WMBUS_MODE must be defined!
#endif
#if !defined(WMBUS_DEVICE)
  #error WMBUS_DEVICE must be defined!
#endif

/*==============================================================================
                            DEFINES
==============================================================================*/
/* definition of the radio channel mask.
   Make sure the definitions to match those of the serial module.
*/
/*! Serial CFG channel mask none */
#define RF_CFG_CHAN_MSK_NONE       (uint16_t)0x0000U
/*! Serial CFG channel mask 868.3 MHz */
#define RF_CFG_CHAN_MSK_868_30     (uint16_t)0x0001U
/*! Serial CFG channel mask 868.95 MHz */
#define RF_CFG_CHAN_MSK_868_95     (uint16_t)0x0002U
/*! Serial CFG channel mask 868.52 MHz */
#define RF_CFG_CHAN_MSK_869_52     (uint16_t)0x0004U
/*! Serial CFG channel mask 169.406250 MHz */
#define RF_CFG_CHAN_MSK_169_1A     (uint16_t)0x0008U
/*! Serial CFG channel mask 169.418750 MHz */
#define RF_CFG_CHAN_MSK_169_1B     (uint16_t)0x0010U
/*! Serial CFG channel mask 169.431250 MHz */
#define RF_CFG_CHAN_MSK_169_2A     (uint16_t)0x0020U
/*! Serial CFG channel mask 169.443750 MHz */
#define RF_CFG_CHAN_MSK_169_2B     (uint16_t)0x0040U
/*! Serial CFG channel mask 169.456250 MHz */
#define RF_CFG_CHAN_MSK_169_3A     (uint16_t)0x0080U
/*! Serial CFG channel mask 169.468750 MHz */
#define RF_CFG_CHAN_MSK_169_3B     (uint16_t)0x0100U
/*! Serial CFG channel mask 169.437500 MHz */
#define RF_CFG_CHAN_MSK_169_0      (uint16_t)0x0200U
/*! Serial CFG channel mask 169.412500 MHz */
#define RF_CFG_CHAN_MSK_169_1      (uint16_t)0x0400U
/*! Serial CFG channel mask 169.437500 MHz */
#define RF_CFG_CHAN_MSK_169_2      (uint16_t)0x0800U
/*! Serial CFG channel mask 169.462500 MHz */
#define RF_CFG_CHAN_MSK_169_3      (uint16_t)0x1000U
/*! Serial CFG channel mask unknown */
#define RF_CFG_CHAN_MSK_UNKNOWN    (uint16_t)0xFFFFU
/*! Serial CFG channel mask 868 MHz */
#define RF_CFG_CHAN_MSK_868_MHZ_CHANNELS (RF_CFG_CHAN_MSK_868_30 | RF_CFG_CHAN_MSK_868_95 | RF_CFG_CHAN_MSK_869_52)
/*! Serial CFG channel mask 169 MHz */
#define RF_CFG_CHAN_MSK_169_MHZ_CHANNELS (RF_CFG_CHAN_MSK_169_1A | RF_CFG_CHAN_MSK_169_1B \
                                        | RF_CFG_CHAN_MSK_169_2A | RF_CFG_CHAN_MSK_169_2B \
                                        | RF_CFG_CHAN_MSK_169_3A | RF_CFG_CHAN_MSK_169_3B \
                                        | RF_CFG_CHAN_MSK_169_0 | RF_CFG_CHAN_MSK_169_1 | RF_CFG_CHAN_MSK_169_2 | RF_CFG_CHAN_MSK_169_3)

#if (WMBUS_MODE == WMBUS_MODE_all)
  /* List of all codecs required by the PHY on reception. */
  /*! RX codec none */
  #define WMBUS_PHY_RX_CODEC_NONE       0x0001U
  /*! RX codec manchester */
  #define WMBUS_PHY_RX_CODEC_MANCHESTER 0x0002U
  /*! RX codec 3 out of6 */
  #define WMBUS_PHY_RX_CODEC_3OUTOF6    0x0004U
  /*! RX codec NRZ_C */
  #define WMBUS_PHY_RX_CODEC_NRZ_C      0x0008U
  /*! RX codec NRZ_N */
  #define WMBUS_PHY_RX_CODEC_NRZ_N      0x0010U
  /*! RX codec all */
  #define WMBUS_PHY_RX_CODEC_all        0x00FFU
  
  /* List of all codecs required by the PHY on transmission. */
  /*! TX codec none */
  #define WMBUS_PHY_TX_CODEC_NONE       0x0100U
  /*! TX codec manchester */
  #define WMBUS_PHY_TX_CODEC_MANCHESTER 0x0200U
  /*! TX codec 3 out of 6 */
  #define WMBUS_PHY_TX_CODEC_3OUTOF6    0x0400U
  /*! TX codec NRZ_C */
  #define WMBUS_PHY_TX_CODEC_NRZ_C      0x0800U
  /*! TX codec NRZ_N */
  #define WMBUS_PHY_TX_CODEC_NRZ_N      0x1000U
  /*! TX codec all */
  #define WMBUS_PHY_TX_CODEC_all        0xFF00U
  
  /* List of all chiprates required by the RF-module on reception. */
  /*! RF RX chiprate none */
  #define WMBUS_RF_RX_CHIPRATE_NONE       0x0001U
  /*! RF RX chiprate 4800 baud */
  #define WMBUS_RF_RX_CHIPRATE_4800baud   0x0002U
  /*! RF RX chiprate 32768 baud */
  #define WMBUS_RF_RX_CHIPRATE_32768baud  0x0004U
  /*! RF RX chiprate 100000 baud */
  #define WMBUS_RF_RX_CHIPRATE_100000baud 0x0008U
  /*! RF RX chiprate 2400 baud */
  #define WMBUS_RF_RX_CHIPRATE_2400baud   0x0010U
  /*! RF RX chiprate 50000 baud */
  #define WMBUS_RF_RX_CHIPRATE_50000baud  0x0020U
  /*! RF RX chiprate N */
  #define WMBUS_RF_RX_CHIPRATE_N          0x0040U
  /*! RF RX chiprate all */
  #define WMBUS_RF_RX_CHIPRATE_all        0x00FFU
  
  /* List of all chiprates required by the RF-module on transmission. */
  /*! RF TX chiprate none */
  #define WMBUS_RF_TX_CHIPRATE_NONE       0x0100U
  /*! RF TX chiprate 4800 baud */
  #define WMBUS_RF_TX_CHIPRATE_4800baud   0x0200U
  /*! RF TX chiprate 32768 baud */
  #define WMBUS_RF_TX_CHIPRATE_32768baud  0x0400U
  /*! RF TX chiprate 100000 baud */
  #define WMBUS_RF_TX_CHIPRATE_100000baud 0x0800U
  /*! RF TX chiprate 2400 baud */
  #define WMBUS_RF_TX_CHIPRATE_2400baud   0x1000U
  /*! RF TX chiprate 50000 baud */
  #define WMBUS_RF_TX_CHIPRATE_50000baud  0x2000U
  /*! RF TX chiprate N */
  #define WMBUS_RF_TX_CHIPRATE_N          0x4000U
  /*! RF TX chiprate all */
  #define WMBUS_RF_TX_CHIPRATE_all        0xFF00U

#else
  /* List of all codecs required by the PHY on reception. */
  /*! RX codec none */
  #ifndef WMBUS_PHY_RX_CODEC_NONE
    #define WMBUS_PHY_RX_CODEC_NONE               FALSE
  #endif /* WMBUS_PHY_RX_CODEC_NONE */
  
  /*! RX codec manchester */
  #ifndef WMBUS_PHY_RX_CODEC_MANCHESTER
    #define WMBUS_PHY_RX_CODEC_MANCHESTER         FALSE
  #endif /* WMBUS_PHY_RX_CODEC_MANCHESTER */
  
  /*! RX codec 3 out of6 */
  #ifndef WMBUS_PHY_RX_CODEC_3OUTOF6
    #define WMBUS_PHY_RX_CODEC_3OUTOF6            FALSE
  #endif /* WMBUS_PHY_RX_CODEC_3OUTOF6 */
  
  /*! RX codec NRZ_C  */
  #ifndef WMBUS_PHY_RX_CODEC_NRZ_C
    #define WMBUS_PHY_RX_CODEC_NRZ_C              FALSE
  #endif /* WMBUS_PHY_RX_CODEC_NRZ_C */
  
  /*! RX codec NRZ_N */
  #ifndef WMBUS_PHY_RX_CODEC_NRZ_N
    #define WMBUS_PHY_RX_CODEC_NRZ_N              FALSE
  #endif /* WMBUS_PHY_RX_CODEC_NRZ_N */
  
  /*! RX codec all */
  #ifndef WMBUS_PHY_RX_CODEC_all
    #define WMBUS_PHY_RX_CODEC_all                FALSE
  #endif /* WMBUS_PHY_RX_CODEC_all */
  
  /* List of all codecs required by the PHY on transmission. */
  /*! TX codec none */
  #ifndef WMBUS_PHY_TX_CODEC_NONE
    #define WMBUS_PHY_TX_CODEC_NONE               FALSE
  #endif /* WMBUS_PHY_TX_CODEC_NONE */
  
  /*! TX codec manchester */
  #ifndef WMBUS_PHY_TX_CODEC_MANCHESTER
    #define WMBUS_PHY_TX_CODEC_MANCHESTER         FALSE
  #endif /* WMBUS_PHY_TX_CODEC_MANCHESTER */
  
  /*! TX codec 3 out of 6 */
  #ifndef WMBUS_PHY_TX_CODEC_3OUTOF6
    #define WMBUS_PHY_TX_CODEC_3OUTOF6            FALSE
  #endif /* WMBUS_PHY_TX_CODEC_3OUTOF6 */
  
  /*! TX codec NRZ_C */
  #ifndef WMBUS_PHY_TX_CODEC_NRZ_C
    #define WMBUS_PHY_TX_CODEC_NRZ_C              FALSE
  #endif /* WMBUS_PHY_TX_CODEC_NRZ_C */
  
  /*! TX codec NRZ_N */
  #ifndef WMBUS_PHY_TX_CODEC_NRZ_N
    #define WMBUS_PHY_TX_CODEC_NRZ_N              FALSE
  #endif /* WMBUS_PHY_TX_CODEC_NRZ_N */
  
  /*! TX codec all */
  #ifndef WMBUS_PHY_TX_CODEC_all
    #define WMBUS_PHY_TX_CODEC_all                FALSE
  #endif /* WMBUS_PHY_TX_CODEC_all */
  
  
  /* List of all chiprates required by the RF-module on reception. */
  /*! RF RX chiprate none */
  #ifndef WMBUS_RF_RX_CHIPRATE_NONE
    #define WMBUS_RF_RX_CHIPRATE_NONE             FALSE
  #endif /* WMBUS_RF_RX_CHIPRATE_NONE */
  
  /*! RF RX chiprate 4800 baud */
  #ifndef WMBUS_RF_RX_CHIPRATE_4800baud
    #define WMBUS_RF_RX_CHIPRATE_4800baud         FALSE
  #endif /* WMBUS_RF_RX_CHIPRATE_4800baud */
  
  /*! RF RX chiprate 32768 baud */
  #ifndef WMBUS_RF_RX_CHIPRATE_32768baud
    #define WMBUS_RF_RX_CHIPRATE_32768baud        FALSE
  #endif /* WMBUS_RF_RX_CHIPRATE_32768baud */
  
  /*! RF RX chiprate 100000 baud */
  #ifndef WMBUS_RF_RX_CHIPRATE_100000baud
    #define WMBUS_RF_RX_CHIPRATE_100000baud       FALSE
  #endif /* WMBUS_RF_RX_CHIPRATE_100000baud */
  
  /*! RF RX chiprate 2400 baud */
  #ifndef WMBUS_RF_RX_CHIPRATE_2400baud
    #define WMBUS_RF_RX_CHIPRATE_2400baud         FALSE
  #endif /* WMBUS_RF_RX_CHIPRATE_2400baud */
  
  /*! RF RX chiprate 50000 baud */
  #ifndef WMBUS_RF_RX_CHIPRATE_50000baud
    #define WMBUS_RF_RX_CHIPRATE_50000baud        FALSE
  #endif /* WMBUS_RF_RX_CHIPRATE_50000baud */
  
  /*! RF RX chiprate N */
  #ifndef WMBUS_RF_RX_CHIPRATE_N
    #define WMBUS_RF_RX_CHIPRATE_N                FALSE
  #endif /* WMBUS_RF_RX_CHIPRATE_N */
  
  /*! RF RX chiprate all */
  #ifndef WMBUS_RF_RX_CHIPRATE_all
    #define WMBUS_RF_RX_CHIPRATE_all              FALSE
  #endif /* WMBUS_RF_RX_CHIPRATE_all */
  
  
  /* List of all chiprates required by the RF-module on transmission. */
  /*! RF TX chiprate none */
  #ifndef WMBUS_RF_TX_CHIPRATE_NONE
    #define WMBUS_RF_TX_CHIPRATE_NONE             FALSE
  #endif /* WMBUS_RF_TX_CHIPRATE_NONE */
  
  /*! RF TX chiprate 4800 baud */
  #ifndef WMBUS_RF_TX_CHIPRATE_4800baud
    #define WMBUS_RF_TX_CHIPRATE_4800baud         FALSE
  #endif /* WMBUS_RF_TX_CHIPRATE_4800baud */
  
  /*! RF TX chiprate 32768 baud */
  #ifndef WMBUS_RF_TX_CHIPRATE_32768baud
    #define WMBUS_RF_TX_CHIPRATE_32768baud        FALSE
  #endif /* WMBUS_RF_TX_CHIPRATE_32768baud */
  
  /*! RF TX chiprate 100000 baud */
  #ifndef WMBUS_RF_TX_CHIPRATE_100000baud
    #define WMBUS_RF_TX_CHIPRATE_100000baud       FALSE
  #endif /* WMBUS_RF_TX_CHIPRATE_100000baud */
  
  /*! RF TX chiprate 2400 baud */
  #ifndef WMBUS_RF_TX_CHIPRATE_2400baud
    #define WMBUS_RF_TX_CHIPRATE_2400baud         FALSE
  #endif /* WMBUS_RF_TX_CHIPRATE_2400baud */
  
  /*! RF TX chiprate 50000 baud */
  #ifndef WMBUS_RF_TX_CHIPRATE_50000baud
    #define WMBUS_RF_TX_CHIPRATE_50000baud        FALSE
  #endif /* WMBUS_RF_TX_CHIPRATE_50000baud */
  
  /*! RF TX chiprate N */
  #ifndef WMBUS_RF_TX_CHIPRATE_N
    #define WMBUS_RF_TX_CHIPRATE_N                FALSE
  #endif /* WMBUS_RF_TX_CHIPRATE_N */
  
  /*! RF TX chiprate all */
  #ifndef WMBUS_RF_TX_CHIPRATE_all
    #define WMBUS_RF_TX_CHIPRATE_all              FALSE
  #endif /* WMBUS_RF_TX_CHIPRATE_all */

  /*! RF TX chiprate */
  #ifndef WMBUS_RF_TX_CHIPRATE
    #define WMBUS_RF_TX_CHIPRATE                  TRUE
  #endif /* WMBUS_RF_TX_CHIPRATE */

  /*! RF RX chiprate */
  #ifndef WMBUS_RF_RX_CHIPRATE
    #define WMBUS_RF_RX_CHIPRATE                  TRUE
  #endif /* WMBUS_RF_RX_CHIPRATE */

  /*! RF RX codec */
  #ifndef WMBUS_PHY_RX_CODEC
    #define WMBUS_PHY_RX_CODEC                    TRUE
  #endif /* WMBUS_PHY_RX_CODEC */

  /*! RF TX codec */
  #ifndef WMBUS_PHY_TX_CODEC
    #define WMBUS_PHY_TX_CODEC                    TRUE
  #endif /* WMBUS_PHY_TX_CODEC */

#endif /* (WMBUS_MODE == WMBUS_MODE_all) */

/*==============================================================================
                            CONFIGURATION
==============================================================================*/
/* These macros will be replaced by the wmbus_parser */

#if ((WMBUS_MODE == WMBUS_MODE_all) && (WMBUS_DEVICE != WMBUS_DEVICE_all))

  /*! Checks if the chosen device type is compatible to A. */
  #define WMBUS_CHECK_DEVICE_or(A)          (A)
  /*! Checks if the chosen device type is compatible to A. */
  #define WMBUS_CHECK_DEVICE_and(A)         (A)

  /*! Checks if the chosen mode is compatible to A. */
  #define WMBUS_CHECK_MODE_or(A)            TRUE
  /*! Checks if the chosen mode is compatible to A. */
  #define WMBUS_CHECK_MODE_and(A)           TRUE
  /*! Checks if the chosen mode is compatible to A. */
  #define WMBUS_CHECK_UNIDIRECTIONAL()      TRUE
  /*! Checks if the chosen mode is compatible to A. */
  #define WMBUS_CHECK_BIDIRECTIONAL()       TRUE

  /*! Checks if the chosen chiprate is compatible to A. */
  #define WMBUS_CHECK_CHIPRATE_or(A)        TRUE

  /*! Rx codec */
  #define WMBUS_CHECK_RX_CODEC_or(A)         TRUE
  #define WMBUS_CHECK_RX_CODEC_and(A)        TRUE

  /*! Checks if Rx chiprate A is supported. */
  #define WMBUS_CHECK_RX_CHIPRATE_or(A)      TRUE
  /*! Checks if Rx chiprate A is exclusively supported. */
  #define WMBUS_CHECK_RX_CHIPRATE_and(A)     TRUE

  /*! Tx codec */
  #define WMBUS_CHECK_TX_CODEC_or(A)         TRUE
  #define WMBUS_CHECK_TX_CODEC_and(A)        TRUE

  /*! Checks if Rx chiprate A is supported. */
  #define WMBUS_CHECK_TX_CHIPRATE_or(A)      TRUE
  /*! Checks if Rx chiprate A is exclusively supported. */
  #define WMBUS_CHECK_TX_CHIPRATE_and(A)     TRUE


  /*! Checks if the chosen device and mode are compatible to A. */
  #define WMBUS_CHECK_DEVICE_MODE_or(A,B)   (A)
  /*! Checks if the chosen device and mode are compatible to A. */
  #define WMBUS_CHECK_DEVICE_MODE_and(A,B)  (A)

  /*! Specifies RF default channel mask for collector */
  #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_868_30
  /*! Specifies RF channel mask for collector */
  #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_868_MHZ_CHANNELS \
                                          | RF_CFG_CHAN_MSK_169_MHZ_CHANNELS

#elif (((WMBUS_MODE != WMBUS_MODE_all) && (WMBUS_DEVICE != WMBUS_DEVICE_all)))
  /*
   * Following config is common for all specific modes and only differs 
   * for MODE_all devices.
   */
  /*! Checks if the chosen device type is compatible to A. */
  #define WMBUS_CHECK_DEVICE_or(A)          (A)
  /*! Checks if the chosen device type is compatible to A. */
  #define WMBUS_CHECK_DEVICE_and(A)         (A)

  /*! Checks if the chosen mode is compatible to A. */
  #define WMBUS_CHECK_MODE_or(A)            (A)
  /*! Checks if the chosen mode is compatible to A. */
  #define WMBUS_CHECK_MODE_and(A)           (A)
  /*! Checks if the chosen mode is compatible to A. */
  #define WMBUS_CHECK_UNIDIRECTIONAL()      WMBUS_MODE_UNIDIRECTIONAL
  /*! Checks if the chosen mode is compatible to A. */
  #define WMBUS_CHECK_BIDIRECTIONAL()       WMBUS_MODE_BIDIRECTIONAL

  /*! Checks if the chosen chiprate is compatible to A. */
  #define WMBUS_CHECK_CHIPRATE_or(A)        (A)

  /*! Rx codec */
  #define WMBUS_CHECK_RX_CODEC_or(A)         (A)
  #define WMBUS_CHECK_RX_CODEC_and(A)        (WMBUS_PHY_RX_CODEC && A)

  /*! Checks if Rx chiprate A is supported. */
  #define WMBUS_CHECK_RX_CHIPRATE_or(A)      (A)
  /*! Checks if Rx chiprate A is exclusively supported. */
  #define WMBUS_CHECK_RX_CHIPRATE_and(A)     (WMBUS_RF_RX_CHIPRATE && A)

  /*! Tx codec */
  #define WMBUS_CHECK_TX_CODEC_or(A)         (A)
  #define WMBUS_CHECK_TX_CODEC_and(A)        (WMBUS_PHY_TX_CODEC && A)

  /*! Checks if Rx chiprate A is supported. */
  #define WMBUS_CHECK_TX_CHIPRATE_or(A)      (A)
  /*! Checks if Rx chiprate A is exclusively supported. */
  #define WMBUS_CHECK_TX_CHIPRATE_and(A)     (WMBUS_RF_TX_CHIPRATE && A)

  /*! Checks if the chosen device and mode are compatible to A. */
  #define WMBUS_CHECK_DEVICE_MODE_or(A,B)   (A || B)
  /*! Checks if the chosen device and mode are compatible to A. */
  #define WMBUS_CHECK_DEVICE_MODE_and(A,B)  (A && B)
#else
#error Please choose a supported configuration
#endif /* ((WMBUS_MODE == WMBUS_MODE_all) && (WMBUS_DEVICE == WMBUS_DEVICE_all)) */
                               
/*==============================================================================
                            SOFT-IFS
==============================================================================*/
#if ((WMBUS_MODE == WMBUS_MODE_all) && (WMBUS_DEVICE != WMBUS_DEVICE_all))
/* --- MODE --- */
#define _IF_MODE_and(A)                         if((gi_wmbus_mode & (A)) == (A)){
#define _ELSE_                                  }else{
#define _ENDIF_                                 }
#define _IF_MODE_BIDIRECTIONAL()                if(gi_wmbus_mode & (WMBUS_MODE_BIDIRECTIONAL)){
#define _IF_MODE_or(A)                          if(gi_wmbus_mode & (A)) {
#define _ELIF_MODE_or(A)                        } else if(gi_wmbus_mode & (A)) {
#define _ELIF_MODE_and(A)                       } else if((gi_wmbus_mode & (A)) == (A)) {
#define _IF_MODE_UNIDIRECTIONAL()               if(gi_wmbus_mode & (WMBUS_MODE_UNIDIRECTIONAL)) {
#define _ELIF_MODE_UNIDIRECTIONAL()             } else if(gi_wmbus_mode & (WMBUS_MODE_UNIDIRECTIONAL)) {
#define _ELIF_MODE_BIDIRECTIONAL()              } else if(gi_wmbus_mode & (WMBUS_MODE_BIDIRECTIONAL)) {
#define _IF_DEVICE_or(A)                        if(A) {
#define _IF_DEVICE_and(A)                       if(A){
#define _ELIF_DEVICE_or(A)                      } else if(A) {
#define _ELIF_DEVICE_and(A)                     } else if(A) {
#define _IF_DEVICE_MODE_and(A,B)                if(A){
#define _ELIF_DEVICE_MODE_and(A,B)              } else if(A){
/* --- Chiprate ---*/
#define _IF_CHIPRATE_or(A)                      if(gi_wmbus_chiprate & (A)) {
/* Chiprate TX */
#define _ELIF_TX_CHIPRATE_or(A)                 } else if(gi_wmbus_chiprate & (A)) {
#define _IF_TX_CHIPRATE_or(A)                   if(gi_wmbus_chiprate & (A)) {
#define _IF_TX_CHIPRATE_and(A)                  if((gi_wmbus_chiprate & WMBUS_RF_TX_CHIPRATE_all) == (A)) { /* all ???? */
#define _ELIF_TX_CHIPRATE_and(A)                } else if((gi_wmbus_chiprate & WMBUS_RF_TX_CHIPRATE_all) == (A)) { /* all ???? */
/* Chiprate RX */
#define _IF_RX_CHIPRATE_and(A)                  if((gi_wmbus_chiprate & WMBUS_RF_RX_CHIPRATE_all) == (A)) {
#define _ELIF_RX_CHIPRATE_and(A)                } else if((gi_wmbus_chiprate & WMBUS_RF_RX_CHIPRATE_all) == (A)) {
/* --- Codec TX --- */
#define _ELIF_CHECK_TX_CODEC_or(A)              } else if(gi_wmbus_codec & (A)) {
#define _IF_CHECK_TX_CODEC_and(A)               if((gi_wmbus_codec & WMBUS_PHY_TX_CODEC_all) == (A)) {
#define _ELIF_CHECK_TX_CODEC_and(A)             } else if((gi_wmbus_codec & WMBUS_PHY_TX_CODEC_all) == (A)) {
/* --- Codec RX --- */
#define _IF_CHECK_RX_CODEC_and(A)               if((gi_wmbus_codec & WMBUS_PHY_RX_CODEC_all) == (A)) {
#define _ELIF_CHECK_RX_CODEC_and(A)             } else if((gi_wmbus_codec & WMBUS_PHY_RX_CODEC_all) == (A)) {
#define _ELIF_CHECK_RX_CODEC_or(A)              } else if(gi_wmbus_codec & (A)) {                                            

#else
                                            
/* --- MODE --- */
#define _IF_MODE_and(A)                         if(A){
#define _ELSE_                                  }else{
#define _ENDIF_                                 }
#define _IF_MODE_BIDIRECTIONAL()                if(WMBUS_MODE_BIDIRECTIONAL){
#define _IF_MODE_or(A)                          if(A) {
#define _ELIF_MODE_or(A)                        } else if(A) {
#define _ELIF_MODE_and(A)                       } else if(A) {
#define _IF_MODE_UNIDIRECTIONAL()               if(WMBUS_MODE_UNIDIRECTIONAL) {
#define _ELIF_MODE_UNIDIRECTIONAL()             } else if(WMBUS_MODE_UNIDIRECTIONAL) {
#define _ELIF_MODE_BIDIRECTIONAL()              } else if(WMBUS_MODE_BIDIRECTIONAL) {
/* --- DEVICE --- */
#define _IF_DEVICE_or(A)                        if(A) {
#define _IF_DEVICE_and(A)                       if(A){
#define _ELIF_DEVICE_or(A)                      } else if(A) {
#define _ELIF_DEVICE_and(A)                     } else if(A) {
#define _IF_DEVICE_MODE_and(A,B)                if(A && B){
#define _ELIF_DEVICE_MODE_and(A,B)              } else if(A && B){
/* --- Chiprate ---*/
#define _IF_CHIPRATE_or(A)                      if(A) {
/* Chiprate TX */
#define _ELIF_TX_CHIPRATE_or(A)                 } else if(A) {
#define _IF_TX_CHIPRATE_or(A)                   if(A) { /* all ???? */
#define _IF_TX_CHIPRATE_and(A)                  if(WMBUS_RF_TX_CHIPRATE && A) { /* all ???? */
#define _ELIF_TX_CHIPRATE_and(A)                } else if(WMBUS_RF_TX_CHIPRATE && A) { /* all ???? */
/* Chiprate RX */
#define _IF_RX_CHIPRATE_and(A)                  if(WMBUS_RF_RX_CHIPRATE && A) {
#define _ELIF_RX_CHIPRATE_and(A)                } else if(WMBUS_RF_RX_CHIPRATE && A) {
/* --- Codec TX --- */
#define _ELIF_CHECK_TX_CODEC_or(A)              } else if(A) {
#define _IF_CHECK_TX_CODEC_and(A)               if(WMBUS_PHY_TX_CODEC && A) {
#define _ELIF_CHECK_TX_CODEC_and(A)             } else if(WMBUS_PHY_TX_CODEC && A) {
/* --- Codec RX --- */
#define _IF_CHECK_RX_CODEC_and(A)               if(WMBUS_PHY_RX_CODEC && A) {
#define _ELIF_CHECK_RX_CODEC_and(A)             } else if(WMBUS_PHY_RX_CODEC && A) {
#define _ELIF_CHECK_RX_CODEC_or(A)              } else if(A) {         
#endif /* ((WMBUS_MODE == WMBUS_MODE_all) || (WMBUS_DEVICE == WMBUS_DEVICE_all)) */

#ifdef OPNET

/*!Structure of global WMBUS configuration variables. */
typedef struct S_WMBUS_CFG_CTX_T
{
  /*! wmbus mode */
  uint16_t ui_wmbus_mode;
  /*! wmbus device type */
  uint16_t ui_wmbus_device;
  /*! wmbus codec */
  uint16_t ui_wmbus_codec;
  /*! wmbus chiprate */
  uint16_t ui_wmbus_chiprate;

} s_wmbus_cfg_ctx_t;
#endif /* OPNET */


/*==============================================================================
                            DEFINES
==============================================================================*/
/*! Specifies the power amplifier usage. */
#ifndef RF_USES_PA
  #define RF_USES_PA                   FALSE
#endif
#if RF_USES_PA == TRUE
  #if ((WMBUS_MODE == WMBUS_MODE_N1) || (WMBUS_MODE == WMBUS_MODE_N2))
    /* maximum transceiver output power: -5dBm -> +27dBm after PA */
    #define RF_USES_PA_SKYWORKS      TRUE
    #define RF_USES_PA_CC1190        FALSE
  #else
    /* maximum transceiver output power: +10dBm -> +27dBm after PA */
    #define RF_USES_PA_SKYWORKS      FALSE
    #define RF_USES_PA_CC1190        TRUE
  #endif
#endif

#ifndef WMBUS_FRAME_B_ENABLED
  #define WMBUS_FRAME_B_ENABLED        FALSE
#endif /* WMBUS_FRAME_B_ENABLED */

#ifndef WMBUS_FRAME_A_ENABLED
#define WMBUS_FRAME_A_ENABLED          TRUE
#endif /* WMBUS_FRAME_A_ENABLED */

#if WMBUS_FRAME_B_ENABLED
  #ifndef WMBUS_DEFAULT_FRAME_FORMAT
    #define WMBUS_DEFAULT_FRAME_FORMAT   WMBUS_FRAME_FORMAT_B
  #endif /* WMBUS_DEFAULT_FRAME_FORMAT */
#else
  #define WMBUS_DEFAULT_FRAME_FORMAT   WMBUS_FRAME_FORMAT_A
#endif /* WMBUS_FRAME_B_ENABLED */

/*==============================================================================
                            SUPER GLOBAL VARIABLES
==============================================================================*/

#if (WMBUS_MODE == WMBUS_MODE_all) || (WMBUS_DEVICE == WMBUS_DEVICE_all)
#ifndef OPNET

/*! Allowed Wireless M-Bus modes: WMBUS_MODE_x */
__DECL_WMBUS_CONFIG_H__ uint16_t gi_wmbus_mode
#ifdef __WMBUS_CONFIG_INIT_VAR__
 = WMBUS_MODE
#endif
;

/*! Allowed device types: WMBUS_DEVICE_x */
__DECL_WMBUS_CONFIG_H__ uint16_t gi_wmbus_device
#ifdef __WMBUS_CONFIG_INIT_VAR__
 = WMBUS_DEVICE
#endif
;

/*! Allowed codecs: WMBUS_PHY_x_CODEC_y */
__DECL_WMBUS_CONFIG_H__ uint16_t gi_wmbus_codec;

/*! Allowed chip rates: WMBUS_RF_x_CHIPRATE_y */
__DECL_WMBUS_CONFIG_H__ uint16_t gi_wmbus_chiprate;
#else

/*! Allowed Wireless M-Bus modes: WMBUS_MODE_x */
#define gi_wmbus_mode (*(wmbus_config_getMode()))
/*! Allowed device types: WMBUS_DEVICE_x */
#define gi_wmbus_device (*(wmbus_config_getDevice()))
/*! Allowed codecs: WMBUS_PHY_x_CODEC_y */
#define gi_wmbus_codec (*(wmbus_config_getCodec()))
/*! Allowed Wireless M-Bus modes: WMBUS_MODE_x */
#define gi_wmbus_chiprate (*(wmbus_config_getChiprate()))
#endif /* OPNET */
#endif /* (WMBUS_MODE != WMBUS_MODE_all) && (WMBUS_DEVICE != WMBUS_DEVICE_all)*/

/*==============================================================================
                                    OPNET
==============================================================================*/
#ifdef OPNET
/*! name of the config context in the OPNET simulator. */
#define WMBUS_CONFIG_OPNET_VAR   ("gui_wmbus_cfg")

/*============================================================================*/
/*!
* \brief    Get the current WMBUS mode.
*
* \return   Pointer to the current WMBUS mode.
*/
/*============================================================================*/
SF_INLINE uint16_t* wmbus_config_getMode( void )
{
  s_wmbus_cfg_ctx_t* pui_cfg = 0;

  #ifdef OPNET
  FIN( wmbus_config_getMode);
  #endif /* OPNET */

  /* get the pointer to the context structure */
  pui_cfg =
    (s_wmbus_cfg_ctx_t*)op_ima_obj_svar_get(op_id_self(), WMBUS_CONFIG_OPNET_VAR);

  /* return context pointer */
  #ifdef OPNET
  FRET( &(pui_cfg->ui_wmbus_mode) );
  #else
  return &(pui_cfg->ui_wmbus_mode);
  #endif /* OPNET */
} /* wmbus_config_getMode() */

/*============================================================================*/
/*!
* \brief    Get the current WMBUS device type.
*
* \return   Pointer to the current WMBUS device type.
*/
/*============================================================================*/
SF_INLINE uint16_t* wmbus_config_getDevice( void )
{
  s_wmbus_cfg_ctx_t* pui_cfg = 0;

  #ifdef OPNET
  FIN( wmbus_config_getDevice);
  #endif /* OPNET */

  /* get the pointer to the context structure */
  pui_cfg =
    (s_wmbus_cfg_ctx_t*)op_ima_obj_svar_get(op_id_self(), WMBUS_CONFIG_OPNET_VAR);

  /* return context pointer */
  #ifdef OPNET
  FRET( &(pui_cfg->ui_wmbus_device) );
  #else
  return &(pui_cfg->ui_wmbus_device);
  #endif /* OPNET */
} /* wmbus_config_getDevice() */

/*============================================================================*/
/*!
* \brief    Get the current WMBUS codec.
*
* \return   Pointer to the current WMBUS codec.
*/
/*============================================================================*/
SF_INLINE uint16_t* wmbus_config_getCodec( void )
{
  s_wmbus_cfg_ctx_t* pui_cfg = 0;

  #ifdef OPNET
  FIN( wmbus_config_getCodec);
  #endif /* OPNET */

  /* get the pointer to the context structure */
  pui_cfg =
    (s_wmbus_cfg_ctx_t*)op_ima_obj_svar_get(op_id_self(), WMBUS_CONFIG_OPNET_VAR);

  /* return context pointer */
  #ifdef OPNET
  FRET( &(pui_cfg->ui_wmbus_codec) );
  #else
  return &(pui_cfg->ui_wmbus_codec);
  #endif /* OPNET */
} /* wmbus_config_getCodec() */

/*============================================================================*/
/*!
* \brief    Get the current WMBUS chiprate.
*
* \return   Pointer to the current WMBUS chiprate.
*/
/*============================================================================*/
SF_INLINE uint16_t* wmbus_config_getChiprate( void )
{
  s_wmbus_cfg_ctx_t* pui_cfg = 0;

  #ifdef OPNET
  FIN( wmbus_config_getChiprate);
  #endif /* OPNET */

  /* get the pointer to the context structure */
  pui_cfg =
    (s_wmbus_cfg_ctx_t*)op_ima_obj_svar_get(op_id_self(), WMBUS_CONFIG_OPNET_VAR);

  /* return context pointer */
  #ifdef OPNET
  FRET( &(pui_cfg->ui_wmbus_chiprate) );
  #else
  return &(pui_cfg->ui_wmbus_chiprate);
  #endif /* OPNET */
} /* wmbus_config_getChiprate() */

#endif /* OPNET */

#endif /* __WMBUS_CONFIG_H__ */

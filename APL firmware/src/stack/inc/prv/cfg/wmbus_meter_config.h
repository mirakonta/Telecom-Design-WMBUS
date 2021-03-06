/**
  @file       wmbus_meter_config.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Configuration of Wireless M-Bus.

              Include before:
                - wmbus_typedefs.h
                - wmbus_api.h
*/

#ifndef __WMBUS_METER_CONFIG_H__
#define __WMBUS_METER_CONFIG_H__

#ifndef __DECL_WMBUS_METER_CONFIG_H__
#define __DECL_WMBUS_METER_CONFIG_H__ extern
#else
#define __WMBUS_METER_CONFIG_INIT_VAR__
#endif /* __DECL_WMBUS_CONFIG_H__ */

/*==============================================================================
                            INCLUDES
==============================================================================*/
/* Stack specific includes */
#include "wmbus_global.h"

/*==============================================================================
                            CHECK CONFIG
==============================================================================*/
#if !defined(WMBUS_MODE)
  #error WMBUS_MODE must be defined!
#endif
#if !defined(WMBUS_DEVICE)
  #error WMBUS_DEVICE must be defined!
#endif
#if (WMBUS_DEVICE != WMBUS_DEVICE_METER)
#error This file defines config for metere devices only! Please check your include paths.
#endif

/*==============================================================================
                            DEFINES
==============================================================================*/


#if (WMBUS_MODE != WMBUS_MODE_all)
/*==============================================================================
                            S1 CONFIG
==============================================================================*/
  #if(WMBUS_MODE == WMBUS_MODE_S1)
    /*! Enable Tx mode. */
    #define WMBUS_TX_ENABLED                  TRUE
    /*! Enable Rx mode. */
    #define WMBUS_RX_ENABLED                  FALSE

    /*! Specifies RF default channel mask for meter */
    #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_868_30
    /*! Specifies RF channel mask for meter */
    #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_868_MHZ_CHANNELS

    /*! TX codec */
    #define WMBUS_PHY_TX_CODEC_MANCHESTER     TRUE
    /*! RF TX chiprate */
    #define WMBUS_RF_TX_CHIPRATE_32768baud    TRUE

    /* No RX settings for unidirectional modes! */
    #define WMBUS_RF_RX_CHIPRATE_NONE         TRUE
    #define WMBUS_PHY_RX_CODEC_NONE           TRUE

    /*! Default TX power: -5dBm.
        Tx power from -130dBm (0x0) to 125dBm (0xFE).*/
    #define WMBUS_PHY_DEFAULT_TX_POWER        0x7D

    /*! Frame B enable/disable */
    #define WMBUS_FRAME_B_ENABLED             FALSE
  /* #elif(WMBUS_MODE == WMBUS_MODE_S1) */
/*==============================================================================
                            S2 CONFIG
==============================================================================*/
  #elif(WMBUS_MODE == WMBUS_MODE_S2)
    /*! Enable Tx mode. */
    #define WMBUS_TX_ENABLED                  TRUE
    /*! Enable Rx mode. */
    #define WMBUS_RX_ENABLED                  TRUE

    /*! Specifies RF default channel mask for meter */
    #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_868_30
    /*! Specifies RF channel mask for meter */
    #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_868_MHZ_CHANNELS

    /*! TX codec */
    #define WMBUS_PHY_TX_CODEC_MANCHESTER     TRUE
    /*! RF TX chiprate */
    #define WMBUS_RF_TX_CHIPRATE_32768baud    TRUE

    /*! RX codec */
    #define WMBUS_PHY_RX_CODEC_MANCHESTER     TRUE
    /*! RF RX chiprate */
    #define WMBUS_RF_RX_CHIPRATE_32768baud    TRUE

    /*! Default TX power: -5dBm.
        Tx power from -130dBm (0x0) to 125dBm (0xFE).*/
    #define WMBUS_PHY_DEFAULT_TX_POWER        0x7DU

    /*! Frame B enable/disable */
    #define WMBUS_FRAME_B_ENABLED             FALSE
  /* #elif(WMBUS_MODE == WMBUS_MODE_S2) */
/*==============================================================================
                            T1 CONFIG
==============================================================================*/
  #elif(WMBUS_MODE == WMBUS_MODE_T1)
    /*! Enable Tx mode. */
    #define WMBUS_TX_ENABLED                  TRUE
    /*! Enable Rx mode. */
    #define WMBUS_RX_ENABLED                  FALSE

    /*! Specifies RF default channel mask for meter */
    #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_868_95
    /*! Specifies RF channel mask for meter */
    #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_868_MHZ_CHANNELS

    /*! TX codec */
    #define WMBUS_PHY_TX_CODEC_3OUTOF6        TRUE
    /*! RF TX chiprate */
    #define WMBUS_RF_TX_CHIPRATE_100000baud   TRUE

    /*! No RX settings for unidirectional modes! */
    #define WMBUS_RF_RX_CHIPRATE_NONE         TRUE
    #define WMBUS_PHY_RX_CODEC_NONE           TRUE

    /*! Default TX power: -5dBm.
        Tx power from -130dBm (0x0) to 125dBm (0xFE).*/
    #define WMBUS_PHY_DEFAULT_TX_POWER        0x7D

    /*! Frame B enable/disable */
    #define WMBUS_FRAME_B_ENABLED             FALSE
  /* #elif(WMBUS_MODE == WMBUS_MODE_T1) */
/*==============================================================================
                            T2 CONFIG
==============================================================================*/
  #elif(WMBUS_MODE == WMBUS_MODE_T2)
    /*! Enable Tx mode. */
    #define WMBUS_TX_ENABLED                  TRUE
    /*! Enable Rx mode. */
    #define WMBUS_RX_ENABLED                  TRUE

    /*! Specifies RF default channel mask for meter */
    #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_868_95
    /*! Specifies RF channel mask for meter */
    #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_868_MHZ_CHANNELS

    /*! TX codec */
    #define WMBUS_PHY_TX_CODEC_3OUTOF6        TRUE
    /*! RF TX chiprate */
    #define WMBUS_RF_TX_CHIPRATE_100000baud   TRUE

    /*! RX codec */
    #define WMBUS_PHY_RX_CODEC_MANCHESTER     TRUE
    /*! RF RX chiprate */
    #define WMBUS_RF_RX_CHIPRATE_32768baud    TRUE

    /*! Default TX power: -5dBm.
        Tx power from -130dBm (0x0) to 125dBm (0xFE).*/
    #define WMBUS_PHY_DEFAULT_TX_POWER        0x7D

    /*! Frame B enable/disable */
    #define WMBUS_FRAME_B_ENABLED             FALSE
  /* #elif(WMBUS_MODE == WMBUS_MODE_T2) */
/*==============================================================================
                            N1 CONFIG
==============================================================================*/
  #elif(WMBUS_MODE == WMBUS_MODE_N1)
    /*! Enable Tx mode. */
    #define WMBUS_TX_ENABLED                  TRUE
    /*! Enable Rx mode. */
    #define WMBUS_RX_ENABLED                  FALSE

    /*! Specifies RF default channel mask for meter */
    #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_169_2B
    /*! Specifies RF channel mask for meter */
    #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_169_MHZ_CHANNELS

    /*! TX codec */
    #define WMBUS_PHY_TX_CODEC_NRZ_N          TRUE
    /*! RF TX chiprate */
    #define WMBUS_RF_TX_CHIPRATE_N            TRUE

    /* No RX settings for unidirectional modes! */
    #define WMBUS_RF_RX_CHIPRATE_NONE         TRUE
    #define WMBUS_PHY_RX_CODEC_NONE           TRUE

    /*! Default TX power: 0dBm.
        Tx power from -130dBm (0x0) to 125dBm (0xFE).*/
    #define WMBUS_PHY_DEFAULT_TX_POWER        0x82

  /* #elif(WMBUS_MODE == WMBUS_MODE_N1) */
/*==============================================================================
                            N2 CONFIG
==============================================================================*/
  #elif(WMBUS_MODE == WMBUS_MODE_N2)
    /*! Enable Tx mode. */
    #define WMBUS_TX_ENABLED                  TRUE
    /*! Enable Rx mode. */
    #define WMBUS_RX_ENABLED                  TRUE

    /*! Specifies RF default channel mask for meter */
    #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_169_2B
    /*! Specifies RF channel mask for meter */
    #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_169_MHZ_CHANNELS

    /*! TX codec */
    #define WMBUS_PHY_TX_CODEC_NRZ_N          TRUE
    /*! RF TX chiprate */
    #define WMBUS_RF_TX_CHIPRATE_N            TRUE

    /*! RX codec */
    #define WMBUS_PHY_RX_CODEC_NRZ_N          TRUE
    /*! RF RX chiprate */
    #define WMBUS_RF_RX_CHIPRATE_N            TRUE

    /*! Default TX power: 0dBm.
        Tx power from -130dBm (0x0) to 125dBm (0xFE).*/
    #define WMBUS_PHY_DEFAULT_TX_POWER        0x82

  /* #elif(WMBUS_MODE == WMBUS_MODE_N2) */
/*==============================================================================
                            C1 CONFIG
==============================================================================*/
  #elif(WMBUS_MODE == WMBUS_MODE_C1)
    /*! Enable Tx mode. */
    #define WMBUS_TX_ENABLED                  TRUE
    /*! Enable Rx mode. */
    #define WMBUS_RX_ENABLED                  FALSE

    /*! Specifies RF default channel mask for meter */
    #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_868_95
    /*! Specifies RF channel mask for meter */
    #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_868_MHZ_CHANNELS

    /*! TX codec */
    #define WMBUS_PHY_TX_CODEC_NRZ_C          TRUE
    /*! RF TX chiprate */
    #define WMBUS_RF_TX_CHIPRATE_100000baud   TRUE

    /* No RX settings for unidirectional modes! */
    #define WMBUS_RF_RX_CHIPRATE_NONE         TRUE
    #define WMBUS_PHY_RX_CODEC_NONE           TRUE

    /*! Default TX power: -5dBm.
        Tx power from -130dBm (0x0) to 125dBm (0xFE).*/
    #define WMBUS_PHY_DEFAULT_TX_POWER        0x7D

    /*! Frame B enable/disable */
    #ifndef WMBUS_FRAME_B_ENABLED
      #define WMBUS_FRAME_B_ENABLED           FALSE
    #endif /* WMBUS_FRAME_B_ENABLED */
  /* #elif(WMBUS_MODE == WMBUS_MODE_C1) */
/*==============================================================================
                            C2 CONFIG
==============================================================================*/
  #elif(WMBUS_MODE == WMBUS_MODE_C2)
    /*! Enable Tx mode. */
    #define WMBUS_TX_ENABLED                  TRUE
    /*! Enable Rx mode. */
    #define WMBUS_RX_ENABLED                  TRUE

    /*! Specifies RF default channel mask for meter */
    #define RF_CFG_CHAN_MSK_DEFAULT           RF_CFG_CHAN_MSK_868_95
    /*! Specifies RF channel mask for meter */
    #define RF_CFG_CHAN_MSK                   RF_CFG_CHAN_MSK_868_MHZ_CHANNELS

    /*! TX codec */
    #define WMBUS_PHY_TX_CODEC_NRZ_C          TRUE
    /*! RF TX chiprate */
    #define WMBUS_RF_TX_CHIPRATE_100000baud   TRUE

    /*! RX codec */
    #define WMBUS_PHY_RX_CODEC_NRZ_C          TRUE
    /*! RF RX chiprate */
    #define WMBUS_RF_RX_CHIPRATE_50000baud    TRUE

    /*! Default TX power: -5dBm.
        Tx power from -130dBm (0x0) to 125dBm (0xFE).*/
    #define WMBUS_PHY_DEFAULT_TX_POWER        0x7D

    /*! Frame B enable/disable */
    #ifndef WMBUS_FRAME_B_ENABLED
      #define WMBUS_FRAME_B_ENABLED           FALSE
    #endif /* WMBUS_FRAME_B_ENABLED */
  /* #elif(WMBUS_MODE == WMBUS_MODE_C2) */
  #else
    #error Please use a supported mode!
  #endif /* (WMBUS_MODE == WMBUS_MODE_*) */
#endif /* != MODE_all */

#endif /* __WMBUS_METER_CONFIG_H__ */

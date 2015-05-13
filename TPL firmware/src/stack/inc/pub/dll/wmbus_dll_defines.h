#ifndef __DLL_DEFINES_H__
#define __DLL_DEFINES_H__
#ifndef __DECL_DLL_DEFINES_H__
#define __DECL_DLL_DEFINES_H__ extern
#else
#define __DLL_DEFINES_INIT_VAR__
#endif /* __DECL_DLL_DEFINES_H__ */

/**
  @file       wmbus_dll_defines.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      This file includes defines which are used from the
              dll and the tpl header.
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/

/* Stack specific includes */
#include "wmbus_global.h"

/*==============================================================================
                            DEFINES
==============================================================================*/

/*========================= ERRORS ===========================================*/
/*! The telegram is not available. */
#define DLL_ERR_TLG_NOT_AVAILABLE     0xFFU
/*! The parameter is out of range. */
#define DLL_ERR_PARAM_OUT_OF_RANGE    0xFFU
/*! The data could not be read because the reading index is out of range. */
#define DLL_ERR_INDEX_OUT_OF_RANGE    0xFFFFU
/*! The data could not be read because the meter index is out of range. */
#define DLL_ERR_METER_OUT_OF_RANGE    0xFFFFU

/*========================= STATUS BYTE ======================================*/
/*! The data link layer is busy. */
#define DLL_STATUS_BUSY               0x01U
/*! The meter device is in installation mode. */
#define DLL_STATUS_INSTALL            0x02U
/*! The access demand flag is set. */
#define DLL_STATUS_ACCESS_DEMAND      0x04U
/*! The meter device is connected to a data collector. */
#define DLL_STATUS_CONNECTED          0x08U
/*! The meter device is in a sleep mode. The wakeUp-function must be called to
     wake up the device */
#define DLL_STATUS_SLEEP              0x10U

/*========================= CONTROL FIELD VALUES (C-field) ===================*/
/*! ACK: positive acknowledgement */
#define DLL_FIELD_C_SEC_ACK           0x00U

#if DSMR_V22_PLUS_ENABLED
/*! ACK: positive acknowledgement but no further data (Landis+Gyr) */
#define DLL_FIELD_C_SEC_ACK_NO_DATA   0x02U
#endif /* DSMR_V22_PLUS_ENABLED */

/*! User data */
#define DLL_FIELD_C_SEC_UD            0x08U
/*! Reset of remote link */
#define DLL_FIELD_C_PRM_NKE           0x40U
/*! User data (Send/Confirm) */
#define DLL_FIELD_C_SND_UD2           0x43U
/*! User data (Send/Confirm) */
#define DLL_FIELD_C_PRM_UD_CONF       0x53U
/*! User data (Send/No reply) */
#define DLL_FIELD_C_PRM_UD_NOREPL     0x44U
/*! Access no reply */
#define DLL_FIELD_C_PRM_ACC_NOREPL    0x47U
/*! Expected respond specifies access demand */
#define DLL_FIELD_C_PRM_AD            0x48U
/*! Request user data class 1 */
#define DLL_FIELD_C_PRM_UD1           0x4AU
/*! Request user data class 2 */
#define DLL_FIELD_C_PRM_UD2           0x4BU

/*! Primary communication. */
#define DLL_FIELD_C_PRM               0x40U

/*! Invalid C-Field: Bit 8 must be alway 0. */
#define DLL_FIELD_C_INVALID           0x8FU

/*========================= SPECIAL CONTROL FIELD VALUES (C-field) ===========*/
/*! Installation request */
#define DLL_FIELD_C_PRM_IR            0x46U

/*! Installation respond
    Be careful: On DSMR v3.0.0 @ref DLL_FIELD_C_SEC_ACK is used. */
#define DLL_FIELD_C_SEC_IR            0x06U

/*========================= TELEGRAM WRITING =================================*/
/*! Write append */
#define DLL_TLG_WRITE_APPEND          0xFFU

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/

/******************************************************************************/
/*! \addtogroup WMBUS_DLL_ENUMS
   @{ */

/*! Enumeration of the status of the dll functions. */
typedef enum
{
  /*! Error occured for unknown reasons. */
  E_DLL_STATUS_ERROR,
  /*! Invalid input parameter error */
  E_DLL_STATUS_INVALID_PARAM_ERROR,
  /*! Stack not initialized error.  */
  E_DLL_STATUS_NOT_INIT_ERROR,
  /*! Operation success.*/
  E_DLL_STATUS_SUCCESS
} E_DLL_STATUS_t;

/*! Enumeration of return values. */
typedef enum
{
  /*! All OK */
  E_DLL_RET_OK = 0U,
  /*! Error. */
  E_DLL_RET_ERR,
  /*! Stack is not ready */
  E_DLL_RET_NOT_READY,
  /*! Only used for the MeterAdd command.
   * Indicates that the meter ist already in the list */
  E_DLL_RET_DUPLICATED
} E_DLL_RET_t;

/*!@} end of WMBUS_DLL_ENUMS */
/******************************************************************************/

/*==============================================================================
                             TYPEDEF STRUCTS
==============================================================================*/
/******************************************************************************/
/*! \addtogroup WMBUS_DLL_STRUCTS
   @{ */

/*! Structure of telegram attributes.  */
typedef struct S_DLL_TLGATTR_T
{
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
      TPL_FIELD_CI_NULL. */
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
} s_dll_tlgAttr_t;

/*! Structure of one meter entry in the collectors meter list. */
PACKED_STRUCT(typedef struct S_DLL_METERENTRY_T
{
  /*! Address of the meter device */
  s_wmbus_addr_t s_meterAddr;
  /*! Wmbus mode. */
  E_WMBUS_MODE_t e_wmbusMode;
}, s_dll_meterEntry_t);

/*! Structure of the meter list. Please note, that the meter entry array must
    be a packed list!. */
PACKED_STRUCT(typedef struct S_DLL_METERLIST_T
{
  /*! Number of meter devices in the list. */
  uint16_t i_numberOfMeters;
  /*! Pointer to the first meter entry. */
  s_dll_meterEntry_t* ps_meterEntry;
}, s_dll_meterList_t);

/*! Start structure to start a meter device */
PACKED_STRUCT(typedef struct S_DLL_STARTATTR_T
{
  /*! Frequency offset of the carrier. */
  sint16_t si_freqOffset;
  /*! Address of the device */
  s_wmbus_addr_t s_deviceAddr;

  /*! The address of the collector. If the collector is not known, set it to
      zero. */
  s_wmbus_addr_t s_collectorAddr;
  /*! Tell the device to bind to a data collector. Only possible, if the
      collector address is valid. */
  bool_t b_connected;
  /*! The interval for periodical user data in ms. */
  uint32_t l_interval;

  /*! Static meters to install at startup. If no static meters are available,
      set the parameter to NULL. */
  s_dll_meterList_t* ps_meterList;
}, s_dll_startAttr_t);

/*! Start structure holding common attributes for any WMBus device
 *  Structure is referenced by device specific start structures
 *  @ref s_dll_start_collector_attr_t and @ref s_dll_start_meter_attr_t */
PACKED_STRUCT(typedef struct S_DLL_STARTCOMMONATTR_T
{
  /*! Frequency offset of the carrier. If the parameter is not known,
      set it to 0. */
  sint16_t si_freqOffset;
  /*! Address of the device */
  s_wmbus_addr_t s_deviceAddr;
}, s_dll_startCommonAttr_t);

/*! Structure of the return value of the function wmbus_mem_mgmt_mlMeterAdd. */
PACKED_STRUCT(typedef struct S_DLL_ADDMETERRET_T
{
  /* Return status of the function. */
  E_DLL_RET_t e_ret;
  /* Meter index. */
  uint16_t i_meterId;
}, s_dll_addMeterRet_t);

/*!@} end of WMBUS_DLL_STRUCTS */
/******************************************************************************/

#endif /* __DLL_DEFINES_H__ */

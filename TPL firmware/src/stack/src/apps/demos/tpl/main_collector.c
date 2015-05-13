 /**
  @file       main_collector.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Demo application of a collector device using the application layer.

              Demo of point to point communication.
*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/

#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\utils\wmbus_clock_api.h"
#include "inc\pub\utils\wmbus_api.h"
#include "inc\prv\cfg\wmbus_config.h"
#include "inc\pub\dll\wmbus_dll_defines.h"
#include "inc\pub\tpl\wmbus_tpl_api.h"
#include "inc\pub\hal\wmbus_hal.h"

/*==============================================================================
                            DEFINES
==============================================================================*/
#ifndef WMBUS_CFG_DEVICE
#error Please define the device configuration to a COLLECTOR device!
#elif WMBUS_CFG_DEVICE != WMBUS_CFG_DEVICE_COLLECTOR
#error Please define the device configuration to a COLLECTOR device!
#endif /* WMBUS_CFG_DEVICE */

/*==============================================================================
                            ENUMS
==============================================================================*/

/*==============================================================================
                            VARIABLES
==============================================================================*/
/* example collector address */
s_wmbus_addr_t gs_collector = {{0xce,0x9a},   /* Manufacturer (here STZ) */
                    {0x80,0x00,0x00,0x02},    /* ident number            */
                     0x23,                    /* version                 */
                    WMBUS_DEV_TYPE_OTHER};    /* type, here other        */

uint8_t gpc_key[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
                    0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};

/* meter entry. */
s_tpl_meterEntry_t gs_meter_entry = {
                {{0xce,0x9a},{0x80,0x00,0x00,0x01},0x23,WMBUS_DEV_TYPE_WATER},
                E_WMBUS_MODE_UNKNOWN,
                {{0x0,0x0},{0x0,0x0,0x0,0x0},0x0,0x0},
                {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
                 0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF}};

/* meterlist */
s_tpl_meterList_t gs_meter_list = {0x0001U, &gs_meter_entry};

s_tpl_startAttr_t gs_start_attr =
{
  /* Init start strucutre */
  /* Frequency offset for the carrier. */
  0,
  /* Device address. */
  &gs_collector,
  /*! Static meters to install at startup. If no static meters are available,
      set the parameter to NULL. Only for collector devices. */
  &gs_meter_list,
};

/* Number of all received telegrams */
uint32_t gl_rxTelegramCnt;

/*! Clock. */
s_clock_t gs_clock;
/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/

/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief Main program.
 */
/*============================================================================*/
void main(void)
{
  /* Initialize global variable */
  gl_rxTelegramCnt = 0x00;

  /* Initialises the hal. */
  if(wmbus_hal_init() == E_HAL_STATUS_SUCCESS)
  {
     /* initialize tpl */
     wmbus_tpl_init();
    
     /* Initialisation of the clock */
     wmbus_clock_init(&gs_clock);
    
     /* start the tpl */
     wmbus_tpl_start(&gs_start_attr);
    
     /* start the clock */
     wmbus_clock_start(&gs_clock);
    
     while(TRUE)
     {
       /* run the tpl layer */
       wmbus_tpl_run();
    
       /* runs the clobal clock */
       wmbus_clock_run(&gs_clock);
     } /* while */
  }
} /* main() */

/*============================================================================*/
/*! wmbus_tpl_evt_getCiHeader() */
/*============================================================================*/
E_TPL_HEADER_TYPE_t wmbus_tpl_evt_getCiHeader(uint8_t c_ci)
{
  E_TPL_HEADER_TYPE_t e_return = E_TPL_HEADER_TYPE_INVALID;

  switch(c_ci)
  {
    case 0xA1U:   /* STACKFORCE specific: Transmit string with no header. */
      e_return = E_TPL_HEADER_TYPE_NO;
      break;
    case 0xA2U:   /* STACKFORCE specific: Transmit string with short header. */
      e_return = E_TPL_HEADER_TYPE_SHORT;
      break;
    case 0xA3U:   /* STACKFORCE specific: Transmit string with long header. */
      e_return = E_TPL_HEADER_TYPE_LONG;
      break;
    case 0xA4U:   /* STACKFORCE specific: Transmit string with short header. */
      e_return = E_TPL_HEADER_TYPE_SHORT;
      break;
    default:      /* The application does not know the CI field. */
      e_return = E_TPL_HEADER_TYPE_INVALID;
      break;

      /* please insert specific CI fields here */

  } /* switch(c_ci) */

  return e_return;
} /* wmbus_tpl_evt_getCiHeader() */

/*============================================================================*/
/*! wmbus_tpl_evt_tlgAvailable() */
/*============================================================================*/
void wmbus_tpl_evt_col_tlgAvailable(E_WMBUS_RX_t e_status, uint8_t c_tlgReqId,
                          uint8_t c_tlgId)
{
  /* All telegrams have to be deleted.*/
  if(c_tlgId != DLL_ERR_TLG_NOT_AVAILABLE)
  {
    gl_rxTelegramCnt++;
    wmbus_tpl_destroyTlg(c_tlgId);
  } /* if */
} /* wmbus_tpl_evt_tlgAvailable() */

/*============================================================================*/
/*! wmbus_tpl_evt_opened() */
/*============================================================================*/
void wmbus_tpl_evt_col_opened(uint8_t c_tlgId)
{
  /*
   * This function is called if a bidirectional communication with a meter
   * device is started. It is the acknowledgement to wmbus_dll_open().
   */
} /* wmbus_tpl_evt_opened() */

/*============================================================================*/
/*! wmbus_tpl_evt_tx() */
/*============================================================================*/
void wmbus_tpl_evt_col_tx(uint8_t c_tlgId)
{
  /*
   * Whenever a radio telegram is sent this event is called. You can use it
   * to toggle LEDs or count transmitted telegrams.
   * Function can be disabled using APL_EVT_TX_ENABLED in "wmbus_global.h".
   */
}/* wmbus_tpl_evt_tx() */

/*============================================================================*/
/*! wmbus_tpl_evt_ACCDMDReceived() */
/*============================================================================*/
void wmbus_tpl_evt_col_ACDBitSet(uint8_t c_tlgId)
{
  /* This function is called if the ACD bit of a meter telegram is set.
     Triggered by the ACD-bit the MUC should request alarm data (class 1)
     with the next unsolicited transmission of the Meter.*/
} /* wmbus_tpl_evt_ACCDMDReceived() */
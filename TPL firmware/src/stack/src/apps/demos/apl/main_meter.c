/**
  @file       main_meter.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Demo application of a meter device using the application layer.

              Demo of point to point communication.
*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\utils\wmbus_api.h"
#include "inc\prv\cfg\wmbus_config.h"
#include "inc\pub\utils\wmbus_clock_api.h"
#include "inc\pub\hal\wmbus_hal.h"
/* Include common APL API */
#include "inc\pub\apl\wmbus_apl_api.h"
/* Include meter device specific APL API functions */
#include "inc\pub\apl\wmbus_apl_mtr_api.h"


/*==============================================================================
                            DEFINES
==============================================================================*/
#ifndef WMBUS_CFG_DEVICE
#error Please define the device configuration to a METER device!
#elif WMBUS_CFG_DEVICE != WMBUS_CFG_DEVICE_METER
#error Please define the device configuration to a METER device!
#endif /* WMBUS_CFG_DEVICE */

#ifndef CUSTOMER_FREQ_OFFSET
#define CUSTOMER_FREQ_OFFSET 0x00
#endif /* CUSTOMER_FREQ_OFFSET */

/*==============================================================================
                            VARIABLES
==============================================================================*/
/* Example meter address (own address) */
s_wmbus_addr_t gs_addr = {{0xce,0x9a},        /* Manufacturer (here STZ) */
                    {0x80,0x00,0x00,0x01},    /* ident number            */
                    0x23,                     /* version                 */
                    WMBUS_DEV_TYPE_WATER};    /* type, here water        */

/* Example collector address */
s_wmbus_addr_t gs_collector = {{0xce,0x9a},   /* Manufacturer (here STZ) */
                    {0x80,0x00,0x00,0x02},    /* ident number            */
                     0x23,                    /* version                 */
                    WMBUS_DEV_TYPE_OTHER};    /* type, here other        */

/* Example meter key (own key)*/
uint8_t gpc_key[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
                    0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};

/* Init start strucutre for meter device */
s_apl_startMeterAttr_t gs_startAttr =
{
  /* Frequency offset for the carrier. */
  CUSTOMER_FREQ_OFFSET,
  /* Device address */
  &gs_addr,
  /* Encryption key */
  gpc_key,
  /* Collector address. */
  &gs_collector,
  /* Set the device to connected. Only if the device is a meter device.
     Otherwise this field is ignored. */
  TRUE,
  /* Periodical interval for sending data. Only if the device is a meter
     device. [ms] */
  3000U
};

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
  /* Initialises the hal. */
  if(wmbus_hal_init() == E_HAL_STATUS_SUCCESS)
  {
    /* initialize APL */
    wmbus_apl_mtr_init();

    /* start the APL for device type meter */
    wmbus_apl_mtr_start(&gs_startAttr);

    /* Set the channel which should be used (for mode N-Devices only) */
    #if WMBUS_CHECK_MODE_or(WMBUS_MODE_N1 | WMBUS_MODE_N2)
    wmbus_apl_setRfChannel(E_RF_CFG_CHAN_169_1A);
    #endif /* WMBUS_CHECK_MODE_or(WMBUS_MODE_N1 | WMBUS_MODE_N2) */

    while(TRUE)
    {
      /* run the application layer */
      wmbus_apl_mtr_run();
    } /* while */
  }/* if */
} /* main() */

/*============================================================================*/
/*! wmbus_apl_evt_rx() */
/*============================================================================*/
void wmbus_apl_evt_rx(void)
{
  /*
   * This function is used in particular if device is configured as: COLLECTOR
   * This event is called whenever a radio telegram is received (device
   * independent). You can use it to toggle LEDs or count received telegrams.
   * Function can be disabled using APL_EVT_RX_ENABLED in "wmbus_global.h".
   */

  /** Do something. */
} /* wmbus_apl_evt_rx() */

/*============================================================================*/
/*! wmbus_apl_evt_tx() */
/*============================================================================*/
void wmbus_apl_evt_tx(uint8_t c_tlgId)
{
  /*
   * This function is used in particular if device is configured as: METER
   * This event is called whenever a radio telegram is sent (device
   * independent). You can use it to toggle LEDs or count transmitted telegrams.
   * Function can be disabled using APL_EVT_TX_ENABLED in "wmbus_global.h".
   */

  /** Do something. */
} /* wmbus_apl_evt_tx() */

/*============================================================================*/
/*! wmbus_apl_evt_userDataRequested() */
/*============================================================================*/
bool_t wmbus_apl_evt_userDataRequested(uint8_t c_tlgId, bool_t b_periodical)
{
  /*
   * This function is used if device is configured as: METER
   * The periodical data includes the time. Further data can be added here
   * to the telegram:
   * Record 0: time information (already set automatically by the stack!)
   * Record 1: our example data (pc_staticData[])
   */
  uint8_t pc_staticData[]={ 0x0C,  /* Record 1: DIB: Data=8 digit BCD, Function=Instantaneous*/
                            0x13,  /* Record 1: VIB: Unit= Volume(m^3), Multiplier= 1dm^3 */
                            0x27,  /* Record 1: Value LSB */
                            0x04,  /* Record 1: Value: (= 2850427) */
                            0x85,  /* Record 1: Value: (= 2850427) */
                            0x02,  /* Record 1: Value MSB */
                            0x0B,  /* Record 2: DIB: Data=6 digit BCD, Function=Instantaneous*/
                            0x3B,  /* Record 2: VIB: Unit=  Volume Flow(m^3/h), Multiplier= 1dm^3/h */
                            0x27,  /* Record 2: Value LSB */
                            0x01,  /* Record 2: Value   (= 127) */
                            0x00}; /* Record 2: Value MSB */

  /* Write the data to the telegram */
  wmbus_apl_writeData(c_tlgId, pc_staticData, sizeof(pc_staticData), FALSE);

  /* Tell the stack to send out the telegram by returning TRUE. If set to FALSE
   * the stack will ignore the request and no telegram is sent. */
  return TRUE;
} /* wmbus_apl_evt_userDataRequested() */

/*============================================================================*/
/*! wmbus_apl_evt_getCiHeader() */
/*============================================================================*/
E_APL_HEADER_TYPE_t wmbus_apl_evt_getCiHeader(uint8_t c_ci)
{
  /*
   * This function is used if the stack receives an unknown CI field (e.g. for
   * customer specific CI fields). In order to parse the header properly
   * the stack needs to distinguish between:
   *   - No Header
   *   - Short Header
   *   - Long Header
   *   - Invalid Header
   */
  E_APL_HEADER_TYPE_t e_return = E_APL_HEADER_TYPE_INVALID;

  switch(c_ci)
  {
    case 0xA1U:   /* STACKFORCE specific: Transmit string with no header. */
      e_return = E_APL_HEADER_TYPE_NO;
      break;
    case 0xA2U:   /* STACKFORCE specific: Transmit string with short header. */
      e_return = E_APL_HEADER_TYPE_SHORT;
      break;
    case 0xA3U:   /* STACKFORCE specific: Transmit string with long header. */
      e_return = E_APL_HEADER_TYPE_LONG;
      break;
    case 0xA4U:   /* STACKFORCE specific: Transmit string with short header. */
      e_return = E_APL_HEADER_TYPE_SHORT;
      break;
    default:      /* The application does not know the CI field. */
      e_return = E_APL_HEADER_TYPE_INVALID;
      break;

      /* please insert specific CI fields here */

  } /* switch(c_ci) */

  return e_return;
} /* wmbus_apl_evt_getCiHeader() */

/*============================================================================*/
/*! wmbus_apl_evt_tlgAvailable() */
/*============================================================================*/
void wmbus_apl_evt_tlgAvailable(E_WMBUS_RX_t e_status, uint8_t c_tlgReqId,
                          s_apl_tlgAttr_t *ps_tlgAttr)
{
  /*
   * This function is used to signal the event that a telegram was received
   * successfully. The application is now able to handle the telegram.
   */

  /* check for the current status. */
  switch(e_status)
  {
    case E_WMBUS_RX_REQUEST_TIMEOUT:
      /* A timeout occured while sending a request. The request telegram must be
         destroyed */
      wmbus_apl_destroyTlg(c_tlgReqId);
      break;
  }/* switch */
  /* delete telegram after handling it */
  wmbus_apl_destroyTlg(ps_tlgAttr->c_tlgId);
} /* wmbus_apl_evt_tlgAvailable() */

/*============================================================================*/
/*! wmbus_apl_evt_alarmRequested() */
/*============================================================================*/
uint8_t wmbus_apl_evt_alarmRequested(void)
{
  uint8_t c_alarm = APL_ALARM_NONE;

  c_alarm = wmbus_apl_mtr_getAlarmCode();
  wmbus_apl_mtr_clrErrorFlag(APL_FIELD_STATUS_ALARM);
  wmbus_apl_mtr_clrAlarmCode(APL_ALARM_ALL);

  return c_alarm;
} /* wmbus_apl_evt_alarmRequested() */

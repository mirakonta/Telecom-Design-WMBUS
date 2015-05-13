/**
  @file       app_serial.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Application to access the STACKFORCE serial layer.
*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\utils\wmbus_api.h"
#include "inc\prv\cfg\wmbus_config.h"
#include "inc\pub\hal\wmbus_hal.h"
/* Stack specific includes */
#include "wmbus_global.h"
/* Include common APL API functions */
#include "inc\pub\serial\wmbus_serial_api.h"

/*==============================================================================
                            DEFINES
==============================================================================*/

/*==============================================================================
                            ENUMS
==============================================================================*/

#ifndef CUSTOMER_FREQ_OFFSET
#define CUSTOMER_FREQ_OFFSET 0x00
#endif /* CUSTOMER_FREQ_OFFSET */

/* example meter address */
s_wmbus_addr_t gs_meterAddr = {{0xce,0x9a},         /* Manufacturer (here STZ) */
               {0x80,0x00,0x00,0x1},          /* ident number            */
                0x23,                         /* version                 */
                WMBUS_DEV_TYPE_WATER};        /* type, here water        */

/* example collector address */
s_wmbus_addr_t gs_collectorAddr = {{0xce,0x9a},   /* Manufacturer (here STZ) */
                    {0x80,0x00,0x00,0x02},    /* ident number            */
                     0x23,                    /* version                 */
                    WMBUS_DEV_TYPE_OTHER};    /* type, here other        */

uint8_t gpc_key[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
                     0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};

#if WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_COLLECTOR)
/* meter entry. */
s_serial_meterEntry_t gs_meterEntry = {
                {{0xce,0x9a},{0x80,0x00,0x00,0x01},0x23,WMBUS_DEV_TYPE_WATER},
                E_WMBUS_MODE_UNKNOWN,
                {{0x0,0x0},{0x0,0x0,0x0,0x0},0x0,0x0},
                {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
                 0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF}};

/* meterlist */
s_serial_meterList_t gs_meterList = {0x0001U, &gs_meterEntry};

s_serial_startCollectorAttr_t gs_startAttr =
{
  /* Init start strucutre */
  /* Frequency offset for the carrier. */
  CUSTOMER_FREQ_OFFSET,
  /* Device address. */
  &gs_collectorAddr,
  /* Static meters to install at startup. If no static meters are available,
     set the parameter to NULL. Only for collector devices. */
  &gs_meterList
};
#endif /* WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_COLLECTOR) */

#if WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_METER)
s_serial_startMeterAttr_t gs_startAttr =
{
  /* Init start strucutre */
  /* Frequency offset for the carrier. */
  CUSTOMER_FREQ_OFFSET,
  /* Device address. */
  &gs_meterAddr,
  /* Encryption key */
  gpc_key,
  /* Collector address. */
  &gs_collectorAddr,
  /* Set the device to connected. Only if the device is a meter device.
     Otherwise this field is ignored. */
  TRUE,
  /* Periodical interval for sending data. Only if the device is a meter
     device. [ms] */
  0U
};
#endif /* WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_METER) */

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
    #if WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_COLLECTOR)
      wmbus_serial_initCollector();
      wmbus_serial_startCollector(&gs_startAttr);
    #elif WMBUS_CHECK_DEVICE_and(WMBUS_DEVICE_METER)
      wmbus_serial_initMeter();
      wmbus_serial_startMeter(&gs_startAttr);
    #endif /* #if ... #elif */

    while(TRUE)
    {
      wmbus_serial_run();
    } /* while */
  } /* if */
} /* main() */

/*============================================================================*/
/*! wmbus_serial_evt_manufrRx() */
/*============================================================================*/
bool_t wmbus_serial_evt_manufrRx(uint8_t c_bufId, uint16_t i_len)
{
  return FALSE;
}

/*============================================================================*/
/*! wmbus_serial_evt_rf_rx() */
/*============================================================================*/
void wmbus_serial_evt_rf_rx(void)
{
  /** Do something */
} /* wmbus_serial_evt_rf_rx() */

/*============================================================================*/
/*! wmbus_serial_evt_rf_tx() */
/*============================================================================*/
void wmbus_serial_evt_rf_tx(void)
{
  /** Do something */
} /* wmbus_serial_evt_rf_tx() */

/*============================================================================*/
/*! wmbus_serial_evt_rx() */
/*============================================================================*/
void wmbus_serial_evt_rx(void)
{
  /** Currently not used*/
} /* wmbus_serial_evt_rx() */

/*============================================================================*/
/*! wmbus_serial_evt_tx() */
/*============================================================================*/
void wmbus_serial_evt_tx(void)
{
    /** Currently not used*/
} /* wmbus_serial_evt_tx() */

/*============================================================================*/
/*! wmbus_serial_evt_getCiHeader() */
/*============================================================================*/
E_APL_HEADER_TYPE_t wmbus_serial_evt_getCiHeader(uint8_t c_ci)
{
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
  } /* if ... else */

  return e_return;
} /* wmbus_serial_evt_getCiHeader() */

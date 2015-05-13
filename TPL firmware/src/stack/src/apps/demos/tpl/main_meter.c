 /**
  @file       main_meter.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Demo application of a meter device using the application layer.

              Demo of point to point communication.
*/

/*============================================================================*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\utils\wmbus_clock_api.h"
#include "inc\pub\utils\wmbus_api.h"
#include "inc\prv\cfg\wmbus_config.h"
#include "inc\pub\dll\wmbus_dll_defines.h"
#include "inc\pub\tpl\wmbus_tpl_api.h"
#include "inc\pub\utils\wmbus_timer_api.h"
#include "inc\pub\hal\wmbus_hal.h"

/*==============================================================================
                            DEFINES
==============================================================================*/
#ifndef WMBUS_CFG_DEVICE
#error Please define the device configuration to a METER device!
#elif WMBUS_CFG_DEVICE != WMBUS_CFG_DEVICE_METER
#error Please define the device configuration to a METER device!
#endif /* WMBUS_CFG_DEVICE */

/*========================= CLOCK ============================================*/
/* 7 Extracts the fields of the date format I. */
/*! Bit 1..6 */
#define CLOCK_SECOND_GET(x)       ((x)[5U] & 0x3FU)
#define CLOCK_SECOND_SET(x,y)     (x)[5U] &= ~(0x3FU); (x)[5U] += (y)

/*! Bit 9..14 */
#define CLOCK_MINUTE_GET(x)       ((x)[4U] & 0x3FU)
#define CLOCK_MINUTE_SET(x,y)     (x)[4U] &= ~(0x3FU); (x)[4U] += (y)

/*! Bit 17..21 */
#define CLOCK_HOUR_GET(x)         ((x)[3U] & 0x1FU)
#define CLOCK_HOUR_SET(x,y)       (x)[3U] &= ~(0x1FU); (x)[3U] += (y)

/*! CLOCK_DAY_MAX is defined by CLOCK_GET_DAYS_OF_MONTH */
#define CLOCK_DAY_GET(x)          ((x)[2U] & 0x1FU)
#define CLOCK_DAY_SET(x,y)        (x)[2U] &= ~(0x1FU); (x)[2U] += (y)

/*! Bit 33..36, 0 = not specified */
#define CLOCK_MONTH_GET(x)        ((x)[1U] & 0x0FU)
#define CLOCK_MONTH_SET(x,y)      (x)[1U] &= ~(0x0FU); (x)[1U] += (y)

/*! Bit 30..32+37..40, 0x7F = not specified */
#define APL_CLOCK_YEAR_GET(x)         ((((x)[2U] & 0xE0U) >> 5U) + \
                                        (((x)[1U] & 0xF0U) >> 1U))


#define APL_CLOCK_YEAR_SET(x,y)    (x)[1U] &= (0xFU); \
                                        (x)[1U] += ((((y) % 100U) & 0x78U) << 1U); \
                                          (x)[2U] &= (0x1FU); \
                                            (x)[2U] += ((((y) % 100U) & 0x7U) << 5U); \

/*! Bit 22..24, 0 = not specified, 1 = Monday, 7 = Sunday. */
#define CLOCK_DAY_OF_WEEK_NULL    0U

/*! Bit 41..46, 0 = not specified */
#define CLOCK_WEEK_NULL           0U

/*! Bit 22..24, 0 = not specified, 1 = Monday, 7 = Sunday. */
#define CLOCK_DAY_OF_WEEK_GET(x)  (((x)[3U] & 0xE0U) >> 5U)
#define CLOCK_DAY_OF_WEEK_SET(x,y)  (x)[3U] &= ~(0xE0U); (x)[3U] += ((y) << 5U)

/*! @todo Weeks are not provided yet. */
/*! Bit 41..46, 0 = not specified */
#define CLOCK_WEEK_GET(x)         ((x)[0U] & 0x3FU)
#define CLOCK_WEEK_SET(x,y)       (x)[0U] &= ~(0x3FU); (x)[4U] += (y)

/*========================= DIF and VIF=======================================*/
/*! Instaneous value */
#define DIF_FUNC_INSTANEOUS                 0x00U
/*! 48 Bit IntegerBinary */
#define DIF_DATA_FIELD_48_INT               0x06U
/*! E110 1101 -> data field 0100b, type F
    E110 1101 -> data field 0011b, type J
    E110 1101 -> data field 0110b, type I */
#define VIF_DATE_TIME                       0x6DU
/*==============================================================================
                            ENUMS
==============================================================================*/

/*==============================================================================
                            VARIABLES
==============================================================================*/
/* Collector and meter address */
/* example meter address */
s_wmbus_addr_t gs_addr = {{0xce,0x9a},        /* Manufacturer (here STZ) */
                    {0x80,0x00,0x00,0x01},    /* ident number            */
                    0x23,                     /* version                 */
                    WMBUS_DEV_TYPE_WATER};    /* type, here water        */

/* example collector address */
s_wmbus_addr_t gs_collector = {{0xce,0x9a},   /* Manufacturer (here STZ) */
                    {0x80,0x00,0x00,0x02},    /* ident number            */
                     0x23,                    /* version                 */
                    WMBUS_DEV_TYPE_OTHER};    /* type, here other        */

uint8_t gpc_key[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
                    0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};

s_tpl_startAttr_t gs_start_attr =
{
  /* Init start strucutre */
  /* Frequency offset for the carrier. */
  0,
  /* Device address. */
  &gs_addr,
  /* Collector address. */
  &gs_collector,
  /* Set the device to connected. Only if the device is a meter device.
      Otherwise this field is ignored. */
  TRUE,
  /* Periodical interval for sending data. Only if the device is a meter
      device. [ms] */
  3000U,
  /*! Encryption key */
  gpc_key,
};

/* Global acc-number */
uint8_t gc_acc;

/*! Clock. */
s_clock_t gs_clock;
/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/
void loc_clockCreateData(uint8_t* pc_dst, s_clock_t* ps_src);
/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  Converts the time of ps_src to telegram format.
 * @param pc_dst  Destination memory.
 * @param ps_src  Clock source.
 */
/*============================================================================*/
void loc_clockCreateData(uint8_t* pc_dst, s_clock_t* ps_src)
{
  if((pc_dst != NULL) && (ps_src != NULL))
  {
    CLOCK_SECOND_SET(pc_dst,      ps_src->c_seconds);
    CLOCK_MINUTE_SET(pc_dst,      ps_src->c_minutes);
    CLOCK_HOUR_SET(pc_dst,        ps_src->c_hours);
    CLOCK_DAY_SET(pc_dst,         ps_src->c_days);
    CLOCK_MONTH_SET(pc_dst,       ps_src->c_months);
    APL_CLOCK_YEAR_SET(pc_dst,        ps_src->i_years);
    CLOCK_DAY_OF_WEEK_SET(pc_dst, CLOCK_DAY_OF_WEEK_NULL);
    CLOCK_WEEK_SET(pc_dst,        CLOCK_WEEK_NULL);
  } /* if */
} /* loc_clockCreateData() */
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
/*! wmbus_tpl_evt_sendUserData() */
/*============================================================================*/
void wmbus_tpl_evt_mtr_sendUserData(void)
{
  /* The periodical data includes the time. Further data can be added here
   * to the telegram:
   * Record 0: time information (already set automatically!)
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
  /* Header of the meter telegram */
  s_tpl_headerShort_t  s_headerShort;
  /* Timestamp data to append. */
  uint8_t pc_data[6U];
  /* ID of the created telegram */
  uint8_t c_tlgId;
  /* boolean which cheks if the telegram must be deleted */
  bool_t b_deleteTelegram = TRUE;

  /* Creates the telegram. */
  c_tlgId = wmbus_tpl_createTlg(DLL_FIELD_C_PRM_UD_NOREPL,  /* User data / no replay */
                              NULL,                       /* Use default meter address */
                              TPL_FIELD_CI_HEADER_SHORT);
  if(c_tlgId != DLL_ERR_TLG_NOT_AVAILABLE)
  {
    s_headerShort.e_type = E_TPL_HEADER_TYPE_SHORT;
    s_headerShort.c_accNo = gc_acc;
    s_headerShort.c_status = 0x00;
    s_headerShort.i_signature = 0x8500;

    wmbus_tpl_setHeader(c_tlgId, (s_tpl_header_t*)&s_headerShort);

    wmbus_tpl_encryptPrepare(c_tlgId);

    /* Add the date to the telegram */
    *pc_data = DIF_FUNC_INSTANEOUS + DIF_DATA_FIELD_48_INT;
    if(wmbus_tpl_writeTlg(c_tlgId, pc_data, 1U, DLL_TLG_WRITE_APPEND, TRUE) == TRUE)
    {
      /* Value information field (VIF) */
      *pc_data = VIF_DATE_TIME;

      if(wmbus_tpl_writeTlg(c_tlgId, pc_data, 1U, DLL_TLG_WRITE_APPEND, TRUE) == TRUE)
      {
        /* Data */
        loc_clockCreateData(pc_data, &gs_clock);

        wmbus_tpl_writeTlg(c_tlgId, pc_data, 6U, DLL_TLG_WRITE_APPEND, TRUE);

        wmbus_tpl_writeTlg(c_tlgId, pc_staticData, sizeof(pc_staticData), DLL_TLG_WRITE_APPEND ,FALSE);

        if(wmbus_tpl_encrypt(c_tlgId) == E_TPL_CRYPT_RET_OK)
        {
          /* Sends the telegram. */
          if(wmbus_tpl_sendTlg(c_tlgId))
          {
            /* The telelgramm was send successfully */
            b_deleteTelegram = FALSE;
            if(gc_acc != 0xFF)
              gc_acc++;
            else
              gc_acc = 0;
          }/* if */
        }/* if */
      }/* if */
    }/* if */
    if(b_deleteTelegram == TRUE)
    {
      wmbus_tpl_destroyTlg(c_tlgId);
    }/* if */
  }/* if */
} /* wmbus_tpl_evt_sendUserData() */

/*============================================================================*/
/*! wmbus_tpl_evt_tx() */
/*============================================================================*/
void wmbus_tpl_evt_mtr_tx(uint8_t c_tlgId)
{
  /*
   * Whenever a radio telegram is sent this event is called. You can use it
   * to toggle LEDs or count transmitted telegrams.
   * Function can be disabled using APL_EVT_TX_ENABLED in "wmbus_global.h".
   */
}/* wmbus_tpl_evt_tx() */

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
void wmbus_tpl_evt_mtr_tlgAvailable(E_WMBUS_RX_t e_status, uint8_t c_tlgReqId,
                          uint8_t c_tlgId)
{
  /* delete telegram after handling it */
  wmbus_tpl_destroyTlg(c_tlgId);
} /* wmbus_tpl_evt_tlgAvailable() */

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
#include "inc\pub\utils\wmbus_api.h"
#include "inc\prv\cfg\wmbus_config.h"
#include "inc\pub\utils\wmbus_clock_api.h"
#include "inc\pub\hal\wmbus_hal.h"
/* Include common APL API */
#include "inc\pub\apl\wmbus_apl_api.h"
/* Include meter device specific APL API functions */
#include "inc\pub\apl\wmbus_apl_col_api.h"

/*==============================================================================
                            DEFINES
==============================================================================*/
#ifndef WMBUS_CFG_DEVICE
#error Please define the device configuration to a COLLECTOR device!
#elif WMBUS_CFG_DEVICE != WMBUS_CFG_DEVICE_COLLECTOR
#error Please define the device configuration to a COLLECTOR device!
#endif /* WMBUS_CFG_DEVICE */

#define DO_CLK_SYNC_TEST        TRUE

#if DO_CLK_SYNC_TEST
#define TLG_BEFORE_CLK_SYNC    5
#endif /* DO_CLK_SYNC_TEST */

#ifndef CUSTOMER_FREQ_OFFSET
#define CUSTOMER_FREQ_OFFSET 0x00
#endif /* CUSTOMER_FREQ_OFFSET */
/*==============================================================================
                            ENUMS
==============================================================================*/

/*==============================================================================
                    data storage in RAM/FLASH
==============================================================================*/
/*! example entry for a message to store in RAM/FLASH */
/*  for efficient memory usage, entry sizes of 16/32/64/128 bytes would be positive */

#define APP_FLASHPAGE_SIZE    512    /* page size in FLASH */
#define APP_ENTRY_SIZE        64     /* just an example */
#define APP_ENTRIES_PER_PAGE  (APP_FLASHPAGE_SIZE/APP_ENTRY_SIZE)
#define APP_METADATA_SIZE     4      /* 2 bytes meter ID, 1 byte RSSI, 1 byte */
#define APP_DATA_SIZE         (APP_ENTRY_SIZE - APP_METADATA_SIZE)

/* Start address fort the array in FLASH*/
#define APP_DATA_BASE_ADDRESS 0xB600
/* Upper limit: page containing the interrupt vectors */
#define MCU_VECTOR_PAGE_ADDRESS    0xFE00
/* number of pages before stop/roll-over --> to be decided */
/* in page 32, the interrupt vectors reside.*/
#define APP_DATA_PAGE_COUNT   (MCU_VECTOR_PAGE_ADDRESS - APP_DATA_BASE_ADDRESS)/APP_FLASHPAGE_SIZE

typedef struct S_APP_TLG_ENTRY_T
{
  /*! Id of the meter device the telegram was received from. A conversion of
      addresses to IDs is always possible. */
  uint16_t i_meterId;
  /*! Received signal strength for the packet. */
  uint8_t c_quality;
  /*! Access number of the request telegram. */
  uint8_t c_accNo;
  /*! feel free to add data here, but try to respect memory boundaries */
  uint8_t c_data[APP_DATA_SIZE];
} s_app_tlgEntry_t;

/* array in RAM to collect telegrams before writing to FLASH */
s_app_tlgEntry_t gs_dataArray[APP_ENTRIES_PER_PAGE];
/* next page to write */
uint8_t gc_nextFlashPage;
/* check if RAM array needs to be written to FLASH */
bool_t gb_tlgArrayComplete;
/* next array entry to write to RAM array */
uint8_t gc_nextRamEntry;

/*==============================================================================
                            VARIABLES
==============================================================================*/
/* Example collector address. */
s_wmbus_addr_t gs_collector = {{0xce,0x9a},   /* Manufacturer (here STZ) */
                    {0x80,0x00,0x00,0x02},    /* ident number            */
                     0x23,                    /* version                 */
                    WMBUS_DEV_TYPE_OTHER};    /* type, here other        */

/* Example meter entry for the meterlist of the collector. */
s_apl_meterEntry_t gs_meterEntry = {
                /* WMBus meter address */
                {{0xce,0x9a},{0x80,0x00,0x00,0x01},0x23,WMBUS_DEV_TYPE_WATER},
                /* WMBus mode of the meter */
                E_WMBUS_MODE_UNKNOWN,
                /* WMBus RF adapter address of the meter (unused) */
                {{0x0,0x0},{0x0,0x0,0x0,0x0},0x0,0x0},
                /* WMBus meter key */
                {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
                 0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF}};

/* Example meterlist */
s_apl_meterList_t gs_meterList = {0x0001U, &gs_meterEntry};

s_apl_startCollectorAttr_t gs_startAttr =
{
  /* Init start strucutre */
  /* Frequency offset for the carrier. */
  CUSTOMER_FREQ_OFFSET,
  /* Device address. */
  &gs_collector,
  /*! Static meters to install at startup. If no static meters are available,
      set the parameter to NULL. Only for collector devices. */
  &gs_meterList,
};

#if DO_CLK_SYNC_TEST
/* Counter for received telegrams */
uint8_t gc_noOfReceivedTlg = 0x0U;

/* Requested telegram id REQ-UD */
uint8_t gc_tlgIdReqUD = APL_ERR_TLG_NOT_AVAILABLE;
/* Requested telegram id CLK-SYNC */
uint8_t gc_tlgIdClkSync = APL_ERR_TLG_NOT_AVAILABLE;
#endif /* DO_CLK_SYNC_TEST */

/*==============================================================================
                            FUNCTION PROTOTYPES
==============================================================================*/
#if DO_CLK_SYNC_TEST
/*! Testing the new clock synchronisation method */
static void loc_clockSyncTest(uint8_t c_tlgReqId);
#endif /* DO_CLK_SYNC_TEST */

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
    wmbus_apl_col_init();

    /* start the APL for device type collector */
    wmbus_apl_col_start(&gs_startAttr);

    /* Set the channel which should be used (for mode N-Devices only) */
    #if WMBUS_CHECK_MODE_or(WMBUS_MODE_N1 | WMBUS_MODE_N2)
    wmbus_apl_setRfChannel(E_RF_CFG_CHAN_169_1A);
    #endif /* WMBUS_CHECK_MODE_or(WMBUS_MODE_N1 | WMBUS_MODE_N2) */

    while(TRUE)
    {
      /* run the application layer */
      wmbus_apl_col_run();
    } /* while */
  } /* if */
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
  E_APL_HEADER_TYPE_t e_return;

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
  /* Current offset. */
  uint16_t i_offset = 0;
  /* current telegram buffer if data should be stored locally */
  uint8_t pc_dataBuf[25];

  /* check for the current status. */
  switch(e_status)
  {
    case E_WMBUS_RX_TLG_AVAILABLE:
    {
      /* new telegram available and the data may be read */
      switch(ps_tlgAttr->c_controlInfo)
      {
        case APL_FIELD_CI_HEADER_LONG:
        case APL_FIELD_CI_HEADER_SHORT:
        case APL_FIELD_CI_LINK_FROM_DEVICE_SHORT:
        {
          /* Read the whole telegram to local buffer */
          wmbus_apl_readData(ps_tlgAttr->c_tlgId, pc_dataBuf, ps_tlgAttr->i_dataLen, i_offset);

          /*
           * 11 bytes of data received with record 0 and record 1 in reverse order:
           * pc_dataBuf[18]...[11]: record 0 (default: timestamp)
           * pc_dataBuf[10]...[5] : record 1 (water volume)
           * pc_dataBuf[4]...[0] : record 2 (water volume)
           *
           * Record 0 (timestamp):
           * pc_dataBuf[18] is DIB: 0x6 = 48Bit Integer, Instantanous
           * pc_dataBuf[17] is VIB: 0x6D = special value used for timestamp
           * pc_dataBuf[16]...[11] is data: 48bit timestamp value
           *
           * Record 1 (water volume):
           * pc_dataBuf[10] is DIB: 0x0C = 8 digit BCD, Function=Instantaneous
           * pc_dataBuf[9] is VIB: 0x13 = Unit= Volume(m^3), Multiplier: 1m^3
           * pc_dataBuf[8] is data: 0x27 = Value LSB
           * pc_dataBuf[7] is DIB: 0x04 = Value: (= 2850427)
           * pc_dataBuf[6] is VIB: 0x85 = Value: (= 2850427)
           * pc_dataBuf[5] is data: 0x02 = Value MSB
           *
           * Record 2 (water volume):
           * pc_dataBuf[4] is DIB: 0x0B = 6 digit BCD, Function=Instantaneous
           * pc_dataBuf[3] is VIB: 0x3B = Unit=  Volume Flow(m^3/h), Multiplier= 1dm^3/h
           * pc_dataBuf[2] is DIB: 0x27 = Value LSB
           * pc_dataBuf[1] is VIB: 0x01 = Value   (= 127)
           * pc_dataBuf[0] is data: 0x00 = Value MSB
           */

          /*
           * Extract records here
           */

          #if DO_CLK_SYNC_TEST
          loc_clockSyncTest(c_tlgReqId);
          #endif /* DO_CLK_SYNC_TEST */
          break;
        }

        default: break;
     } /* switch(c_controlInfo) */

      break;
    } /* case E_WMBUS_RX_TLG_AVAILABLE */


    case E_WMBUS_RX_SIGNATURE_ERROR:
      /* signature was wrong */
      break;

    case E_WMBUS_RX_SIGNATURE_UNKNOWN:
      if(ps_tlgAttr != NULL)
      {
        /* The telegram is encrypted and can not be decrypted. */
      }
      break;

    case E_WMBUS_RX_REQUEST_TIMEOUT:
      /* A timeout occured while sending a request. The request telegram must be
         destroyed */
      wmbus_apl_destroyTlg(c_tlgReqId);
      break;

    default:
      break;

  } /* switch(e_status) */

  /* delete telegram after handling it */
  wmbus_apl_destroyTlg(ps_tlgAttr->c_tlgId);

} /* wmbus_apl_evt_tlgAvailable() */

/*============================================================================*/
/*! apl_evt_newMeter() */
/*============================================================================*/
bool_t wmbus_apl_evt_newMeter(s_wmbus_addr_t *ps_meter, s_apl_tlgAttr_t *ps_tlgAttr)
{
  /*
   * This function is used if device is configured as: COLLECTOR
   * Since we added the meter device for this demo manually to the collector and
   * we don't want any other meters in our list we don't add new meters here
   * by returning FALSE.
   */
  return FALSE;
} /* wmbus_apl_evt_newMeter() */

/*============================================================================*/
/*! wmbus_apl_evt_ACCDMDReceived() */
/*============================================================================*/
void wmbus_apl_evt_ACCDMDReceived(uint8_t c_tlgId)
{
  /*
   * This function is used if device is configured as: COLLECTOR
   * The event is triggered when the collector receives an ACC-DMD telegram
   * from connected meter. According to the EN-13757 and OMS, the collector
   * should perform REQ-UD and REQ-UD2. For DSMR v4.0.5, the collector shall
     do nothing.
   */
  return;
} /* wmbus_apl_evt_ACCDMDReceived() */

#if (DSMR_V405_ENABLED || DSMR_V22_PLUS_ENABLED)
/*============================================================================*/
/*! wmbus_apl_evt_keyExchangeCmdAcked_DSMR() */
/*============================================================================*/
void wmbus_apl_evt_keyExchangeCmdAcked_DSMR(void)
{
  /*
   * This function is used if device is configured as: COLLECTOR
   * The event is triggered when the meter acknowledes the DSMR key exchange
   * command. This is to let the collector know that the command is transmitted
   * successfully and the collector can start to use the new key.
   */
} /* wmbus_apl_evt_keyExchangeCmdAcked_DSMR() */
#endif /* DSMR_V405_ENABLED || DSMR_V22_PLUS_ENABLED */

#if DO_CLK_SYNC_TEST
/*============================================================================*/
/*! loc_clockSyncTest() */
/*============================================================================*/
static void loc_clockSyncTest(uint8_t c_tlgReqId)
{
  /* Error Flag */
  bool_t b_errorFlag = FALSE;

  /* Increment the number of received telegrams */
  gc_noOfReceivedTlg++;

  /* Start clock synchronization every received x telegrams */
  if(gc_noOfReceivedTlg == TLG_BEFORE_CLK_SYNC)
  {
    if(wmbus_apl_col_open() == TRUE)
    {
      /* Request User Data first */
      gc_tlgIdReqUD = wmbus_apl_col_createUserDataRequest(0x0U); /* Meter entry 0 */
      if(gc_tlgIdReqUD != APL_ERR_TLG_NOT_AVAILABLE)
        b_errorFlag = wmbus_apl_col_sendQueued(gc_tlgIdReqUD, TRUE);
      if(!b_errorFlag || gc_tlgIdReqUD == APL_ERR_TLG_NOT_AVAILABLE)
      {
        /* The telegram could not be sent */
        /* Reset parameters */
        gc_noOfReceivedTlg = 0;
        wmbus_apl_destroyTlg(gc_tlgIdReqUD);
        gc_tlgIdReqUD = APL_ERR_TLG_NOT_AVAILABLE;
      }/* if */
    }/* if */
  }
  else if(c_tlgReqId != APL_ERR_TLG_NOT_AVAILABLE)
  {
    if (c_tlgReqId == gc_tlgIdReqUD)
    {
       /* If the REQ-UD is successful then begin the actual clock sync */
      gc_tlgIdClkSync = wmbus_apl_col_createCmdClkSync(0x0U); /* Meter entry 0 */

      if(gc_tlgIdClkSync != APL_ERR_TLG_NOT_AVAILABLE)
        b_errorFlag = wmbus_apl_col_sendQueued(gc_tlgIdClkSync, TRUE);
      if(!b_errorFlag || gc_tlgIdReqUD == APL_ERR_TLG_NOT_AVAILABLE)
      {
        /* The telegram could not be sent */
        /* Reset parameters */
        gc_noOfReceivedTlg = 0;
        wmbus_apl_destroyTlg(gc_tlgIdClkSync);
        gc_tlgIdClkSync = APL_ERR_TLG_NOT_AVAILABLE;
      }

      /* Resets the telegram ID */
      gc_tlgIdReqUD = APL_ERR_TLG_NOT_AVAILABLE;
    }
    else if(c_tlgReqId == gc_tlgIdClkSync)
    {
      /* Close the bidirectional communication */
      wmbus_apl_col_close(0x0U, TRUE);

      /* Reset parameters */
      gc_noOfReceivedTlg = 0;
      b_errorFlag = FALSE;
      gc_tlgIdClkSync = APL_ERR_TLG_NOT_AVAILABLE;
    }
  }
  else if(gc_noOfReceivedTlg >= 10)
  {
    /* Reset parameters */
    gc_noOfReceivedTlg = 0;
  }

  return;
} /* loc_clockSyncTest */
#endif /* DO_CLK_SYNC_TEST */

/*============================================================================*/
/*! wmbus_apl_evt_ACDBitSet() */
/*============================================================================*/
void wmbus_apl_evt_ACDBitSet(uint8_t c_tlgId)
{
  /* This function is called if the ACD bit of a meter telegram is set.
     Triggered by the ACD-bit the MUC should request alarm data (class 1)
     with the next unsolicited trans-mission of the Meter.*/
  return;
} /* wmbus_apl_evt_ACDBitSet() */

#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_mcu.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for implementations relevant to the MCU core.

  @addtogroup WMBUS_HAL_MCU
  
  All these functions are implemented in `/src/target/`sf_hal_mcu.c
  
*/
/**@{*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"

/*! Includes required by the EFM librarry */
/**@{*/
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usb.h"
/**@}*/

/*==============================================================================
                          DEFINE CHECKS
==============================================================================*/
/** Verification if macro specifying the MCU speed has been set. */
#ifndef MCU_SPEED
  #error Define MCU_SPEED according to HFRCO band returned from em lib 
#endif

/*==============================================================================
                           LOCAL FUNCTIONS
==============================================================================*/

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* wmbus_hal_mcu_init() */
/*============================================================================*/
bool_t wmbus_hal_mcu_init(void)
{
  /** First, globally disabling interrupts */
  __disable_irq();

  /** Then applying, chip errata */
  CHIP_Init();

  /** Set the clock speed */
  #if MCU_SPEED == _CMU_HFRCOCTRL_BAND_1MHZ
    CMU_HFRCOBandSet(cmuHFRCOBand_1MHz);
  #elif MCU_SPEED == _CMU_HFRCOCTRL_BAND_7MHZ
    CMU_HFRCOBandSet(cmuHFRCOBand_7MHz);
  #elif MCU_SPEED == _CMU_HFRCOCTRL_BAND_11MHZ
    CMU_HFRCOBandSet(cmuHFRCOBand_11MHz);
  #elif MCU_SPEED == _CMU_HFRCOCTRL_BAND_14MHZ
    CMU_HFRCOBandSet(cmuHFRCOBand_14MHz);
  #elif MCU_SPEED == _CMU_HFRCOCTRL_BAND_21MHZ
    CMU_HFRCOBandSet(cmuHFRCOBand_21MHz);
  #elif MCU_SPEED == _CMU_HFRCOCTRL_BAND_28MHZ
    CMU_HFRCOBandSet(cmuHFRCOBand_28MHz);
  #elif MCU_SPEED == MCU_SPEED_EXT_OSC
    CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
  #else
    #error MCU_SPEED is invalid.
  #endif /* MCU_SPEED */

  /** Enabled GPIO clock */
  CMU_ClockEnable(cmuClock_HFPER, true);  
  CMU_ClockEnable (cmuClock_GPIO, true);

  /** Finally, globally re-enabling interrupts */
  __enable_irq();
  return TRUE;
} /* wmbus_hal_mcu_init() */

/*============================================================================*/
/* wmbus_hal_mcu_reset() */
/*============================================================================*/
void wmbus_hal_mcu_reset(void)
{
  /** Forcing a system reset by using the system reset request provided by the
      EFM library. */
  NVIC_SystemReset();
} /* wmbus_hal_mcu_reset() */

/*============================================================================*/
/* wmbus_hal_mcu_getClockSpeed() */
/*============================================================================*/
/**
  @ingroup SF_RF_HAL_MCU
  @note Please note, this is the only MCU related hardware abstracting function
        required by the Si446x driver module and has been implemented in
        `/src/target/`@ref sf_hal_mcu.c
*/
uint32_t sf_hal_mcu_getClockSpeed(void)
{
  uint32_t l_freq = 0U;
  uint8_t c_speed = 0U;

  c_speed = (uint8_t) CMU_HFRCOBandGet();

  switch(c_speed)
  {
    case _CMU_HFRCOCTRL_BAND_1MHZ:
      l_freq = 1000000U;
      break;
    case _CMU_HFRCOCTRL_BAND_7MHZ:
      l_freq = 7000000U;
      break;
    case _CMU_HFRCOCTRL_BAND_11MHZ:
      l_freq = 11000000U;
      break;
    case _CMU_HFRCOCTRL_BAND_14MHZ:
      l_freq = 14000000U;
      break;
    case _CMU_HFRCOCTRL_BAND_21MHZ:
      l_freq = 21000000U;
      break;
/* for cortex M0 there is no 28MHz setting */      
#if !(__CORE__ == __ARM6M__)
    case _CMU_HFRCOCTRL_BAND_28MHZ:
      l_freq = 28000000U;
      break;
#endif
    default:
      l_freq = 1000000U;
      break;
  } /* if */

  return l_freq;
} /* wmbus_hal_mcu_getClockSpeed() */

/**@}*/

#ifdef __cplusplus
}
#endif

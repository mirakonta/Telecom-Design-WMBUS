#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_rf.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for RF implementations.

  @addtogroup WMBUS_HAL_RF
  
  This is the implementation of the RF driver interface. However, as this
  delivery is designed for Silabs products only, all the RF driver interfaces
  are simply forwarded to the Si446x RF driver library.
  The implementation can be found in `/src/target/`sf_hal_rf.c.
*/
/**@{*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\utils\wmbus_tlg_api.h"
#include "inc\pub\utils\wmbus_api.h"
#include "inc\pub\hal\wmbus_hal_rf.h"
#include "sf_rf.h"
#include "sf_hal_gpio.h"


/*==============================================================================
                            FUNCTIONS
==============================================================================*/


/*============================================================================*/
/* wmbus_hal_rf_init() */
/*============================================================================*/
bool_t wmbus_hal_rf_init(void)
{
  bool_t b_ret = FALSE;

  if(sf_rf_init())
  {
    if(sf_rf_setInternalGpio(E_RF_GPIO_0, E_RF_GPIO_1))
    {
      b_ret = TRUE;
    } /* if */
  } /* if */

  return b_ret;
} /* wmbus_hal_rf_init() */

/*============================================================================*/
/* wmbus_hal_rf_powerOff() */
/*============================================================================*/
void wmbus_hal_rf_powerOff(void)
{
  sf_rf_powerOff();
} /* wmbus_hal_rf_powerOff() */

/*============================================================================*/
/* wmbus_hal_rf_powerOn() */
/*============================================================================*/
void wmbus_hal_rf_powerOn(void)
{
  sf_rf_powerOn();
} /* wmbus_hal_rf_powerOn() */

/*============================================================================*/
/* wmbus_hal_rf_start() */
/*============================================================================*/
void wmbus_hal_rf_start(void)
{
  sf_rf_start();
} /* wmbus_hal_rf_start() */

/*============================================================================*/
/* wmbus_hal_rf_txInit() */
/*============================================================================*/
bool_t wmbus_hal_rf_txInit(uint16_t i_len, E_WMBUS_FRAME_t e_frameType,
                            E_WMBUS_MODE_t e_mode)
{
  return sf_rf_txInit(i_len, e_frameType, e_mode);
} /* wmbus_hal_rf_txInit() */

/*============================================================================*/
/* wmbus_hal_rf_txData() */
/*============================================================================*/
bool_t wmbus_hal_rf_txData(uint8_t *pc_data, uint16_t i_len)
{
  return sf_rf_txData(pc_data, i_len);
} /* wmbus_hal_rf_txData() */

/*============================================================================*/
/* wmbus_hal_rf_txFinish() */
/*============================================================================*/
bool_t wmbus_hal_rf_txFinish(void)
{
  return sf_rf_txFinish();
} /* wmbus_hal_rf_txFinish() */

/*============================================================================*/
/* wmbus_hal_spi_init() */
/*============================================================================*/
bool_t wmbus_hal_rf_rxInit(uint8_t *pc_quality, uint8_t c_len)
{
  return sf_rf_rxInit(pc_quality, c_len);
} /* wmbus_hal_rf_start() */

/*============================================================================*/
/* wmbus_hal_rf_rxData() */
/*============================================================================*/
bool_t wmbus_hal_rf_rxData(uint8_t *pc_data, uint16_t i_len)
{
  return sf_rf_rxData(pc_data, i_len);
} /* wmbus_hal_rf_rxData() */

/*============================================================================*/
/* wmbus_hal_rf_rxFinish() */
/*============================================================================*/
bool_t wmbus_hal_rf_rxFinish(E_HAL_RF_MODE_t e_mode)
{
  return sf_rf_rxFinish((E_RF_MODE_t) e_mode);
} /* wmbus_hal_rf_rxFinish() */

/*============================================================================*/
/* wmbus_hal_rf_reset() */
/*============================================================================*/
bool_t wmbus_hal_rf_reset(E_HAL_RF_CALIBRATE_t e_calibrate)
{
  return sf_rf_reset((E_RF_CALIBRATE_t) e_calibrate);
} /* wmbus_hal_rf_reset() */

/*============================================================================*/
/* wmbus_hal_rf_setRfChannel() */
/*============================================================================*/
bool_t wmbus_hal_rf_setRfChannel(uint16_t i_channel)
{
  return sf_rf_setRfChannel(i_channel);
} /* wmbus_hal_rf_setRfChannel() */

/*============================================================================*/
/* wmbus_hal_rf_txSetPostamble() */
/*============================================================================*/
void wmbus_hal_rf_txSetPostamble(E_HAL_RF_POSTAMBLE_t e_postamble)
{
  sf_rf_txSetPostamble((E_RF_POSTAMBLE_t) e_postamble);
} /* wmbus_hal_rf_txSetPostamble() */

/*============================================================================*/
/* wmbus_hal_rf_getRfChannel() */
/*============================================================================*/
uint16_t wmbus_hal_rf_getRfChannel(void)
{
  return sf_rf_getRfChannel();
} /* wmbus_hal_rf_getRfChannel() */

/*============================================================================*/
/* wmbus_hal_rf_setPowerMode() */
/*============================================================================*/
bool_t wmbus_hal_rf_setPowerMode(E_HAL_RF_POWERMODE_t e_powermode)
{
  return sf_rf_setPowerMode((E_RF_POWERMODE_t) e_powermode);
} /* wmbus_hal_rf_setPowerMode() */

/*============================================================================*/
/* wmbus_hal_rf_setSignalStrength() */
/*============================================================================*/
bool_t wmbus_hal_rf_setSignalStrength(uint8_t c_signal)
{
  return sf_rf_setSignalStrength(c_signal);
} /* wmbus_hal_rf_setSignalStrength() */

/*============================================================================*/
/* wmbus_hal_rf_getSignalStrength() */
/*============================================================================*/
uint8_t wmbus_hal_rf_getSignalStrength(void)
{
  return sf_rf_getSignalStrength();
} /* wmbus_hal_rf_getSignalStrength() */

/*============================================================================*/
/* wmbus_hal_rf_sleep() */
/*============================================================================*/
void wmbus_hal_rf_sleep(void)
{
  sf_rf_sleep();
} /* wmbus_hal_rf_sleep() */

/*============================================================================*/
/* wmbus_hal_rf_wake() */
/*============================================================================*/
void wmbus_hal_rf_wake(void)
{
  sf_rf_wake();
} /* wmbus_hal_rf_wake() */

/*============================================================================*/
/* wmbus_hal_rf_run() */
/*============================================================================*/
void wmbus_hal_rf_run(void)
{
  sf_rf_run();
} /* wmbus_hal_rf_run() */

/*============================================================================*/
/* wmbus_hal_rf_getTelegramDelay() */
/*============================================================================*/
uint16_t wmbus_hal_rf_getTelegramDelay(void)
{
  return sf_rf_getTelegramDelay();
} /* wmbus_hal_rf_getTelegramDelay() */

/*============================================================================*/
/* wmbus_hal_rf_setCallback() */
/*============================================================================*/
bool_t wmbus_hal_rf_setCallback(fp_hal_rf_evt_tx fp_tx, fp_hal_rf_evt_rx fp_rx)
{
  return sf_rf_setCallback(fp_tx, fp_rx);
} /* wmbus_hal_rf_setCallback() */

/*============================================================================*/
/* wmbus_hal_rf_setFrequencyOffset() */
/*============================================================================*/
bool_t wmbus_hal_rf_setFrequencyOffset(sint16_t si_freqOffset)
{
  return FALSE;
} /* wmbus_hal_rf_setFrequencyOffset() */


/*============================================================================*/
/* wmbus_rf_evt_criticalError() */
/*============================================================================*/
void sf_rf_evt_criticalError(E_RF_ERROR_t e_err)
{
  return;
} /* wmbus_hal_rf_fifoEmpty() */


/*========================= ODD GPIO ISR =====================================*/
void GPIO_ODD_IRQHandler(void)
{
  /* handle interrupt call backs */
  /* rf interrupts */
  if(sf_hal_gpio_irqFlagIsSetGPIO0() || sf_hal_gpio_irqFlagIsSetGPIO1())
  {
    /* run rf isr handler */
    sf_rf_isr();

    /* check gdo0 and gdo2 */
    if(sf_hal_gpio_irqFlagIsSetGPIO0())
    	sf_hal_gpio_irqDisableGPIO0();
    else
    	sf_hal_gpio_irqDisableGPIO1();
  }
}

/*========================= EVEN GPIO ISR =====================================*/
void GPIO_EVEN_IRQHandler(void)
{
  /* handle interrupt call backs */
  /* rf interrupts */
  if(sf_hal_gpio_irqFlagIsSetGPIO0() || sf_hal_gpio_irqFlagIsSetGPIO1())
  {
    /* run rf isr handler */
    sf_rf_isr();

    /* check gdo0 and gdo2 */
    if(sf_hal_gpio_irqFlagIsSetGPIO0())
    	sf_hal_gpio_irqDisableGPIO0();
    else
    	sf_hal_gpio_irqDisableGPIO1();
  }
}


/**@}*/
#ifdef __cplusplus
}
#endif

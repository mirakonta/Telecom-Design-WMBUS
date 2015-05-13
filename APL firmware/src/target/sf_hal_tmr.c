#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_tmr.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for TMR implementations.
  
  @addtogroup WMBUS_HAL_TMR
  
  All these functions are implemented in `/src/target/`sf_hal_tmr.c
 
*/
/**@{*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\hal\wmbus_hal_tmr.h"

#include "em_cmu.h"
#include "em_timer.h"

/*==============================================================================
                            DEFINES
==============================================================================*/
/** Timer settings required for the stack. @warning As the timer is very
    important to the stack, do not changes these settings unless you know what
    you're doing. */
#if defined( TIMER_CTRL_X2CNT ) && defined( TIMER_CTRL_ATI )
#define TMR_DEFAULT                                                                     \
{   true,                   /* Enable timer when init complete. */                      \
    false,                  /* Stop counter during debug halt. */                       \
    timerPrescale1,         /* No prescaling. */                                        \
    timerClkSelHFPerClk,    /* Select HFPER clock. */                                   \
    false,                  /* Not 2x count mode. */                                    \
    false,                  /* No ATI. */                                               \
    timerInputActionNone,   /* No action on falling input edge. */                      \
    timerInputActionNone,   /* No action on rising input edge. */                       \
    timerModeUp,            /* Up-counting. */                                          \
    false,                  /* Do not clear DMA requests when DMA channel is active. */ \
    false,                  /* Select X2 quadrature decode mode (if used). */           \
    false,                  /* Continuous mode. */                                      \
    false                   /* Not started/stopped/reloaded by other timers. */         \
}
#else
#define TMR_DEFAULT                                                                     \
{   true,                   /* Enable timer when init complete. */                      \
    false,                  /* Stop counter during debug halt. */                       \
    timerPrescale1,         /* No prescaling. */                                        \
    timerClkSelHFPerClk,    /* Select HFPER clock. */                                   \
    timerInputActionNone,   /* No action on falling input edge. */                      \
    timerInputActionNone,   /* No action on rising input edge. */                       \
    timerModeUp,            /* Up-counting. */                                          \
    false,                  /* Do not clear DMA requests when DMA channel is active. */ \
    false,                  /* Select X2 quadrature decode mode (if used). */           \
    false,                  /* Continuous mode. false:diable one shot mode */           \
    false                   /* Not started/stopped/reloaded by other timers. */         \
}
#endif

/*==============================================================================
                            VARIABLES
==============================================================================*/
static fp_hal_tmr_cb gfp_tmr1_tick = NULL;

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* wmbus_hal_tmr_init() */
/*============================================================================*/
bool_t wmbus_hal_tmr_init(uint16_t i_ticksPerSecond)
{
  TIMER_Init_TypeDef timer = TMR_DEFAULT;

  /* Initialize callback function. */
  gfp_tmr1_tick = NULL;

  /* Enable clock for TIMER1 module */
  CMU_ClockEnable(cmuClock_TIMER1, true);

  /* Set TIMER Top value to 1s */
  TIMER_TopSet(TIMER1, (CMU_ClockFreqGet(cmuClock_HFPER)/i_ticksPerSecond));
  /* Init */
  TIMER_Init(TIMER1, &timer);

  return TRUE;
} /* wmbus_hal_tmr_init() */

/*============================================================================*/
/* wmbus_hal_tmr_deinit() */
/*============================================================================*/
bool_t wmbus_hal_tmr_deinit(void)
{
  return FALSE;
} /* wmbus_hal_tmr_deinit() */

/*============================================================================*/
/* wmbus_hal_tmr_setCallback() */
/*============================================================================*/
bool_t wmbus_hal_tmr_setCallback(fp_hal_tmr_cb fp_tmr)
{
  bool_t b_ret = FALSE;

  if(fp_tmr)
  {
    gfp_tmr1_tick = fp_tmr;

     /* Enable overflow interrupt */
    TIMER_IntEnable(TIMER1, TIMER_IF_OF);
    /* Enable TIMER1 interrupt vector in NVIC */
    NVIC_EnableIRQ(TIMER1_IRQn);
    b_ret = TRUE;
  }
  return b_ret;
} /* wmbus_hal_tmr_setCallback() */

/*============================================================================*/
/* wmbus_hal_tmr_enable() */
/*============================================================================*/
void wmbus_hal_tmr_enable(void)
{
  /* Enable clock */
  CMU_ClockEnable(cmuClock_TIMER1, true);
  /* Enable TIMER1 interrupt vector in NVIC */

  NVIC_EnableIRQ(TIMER1_IRQn);
  /* Enable TIMER1 */
  TIMER_Enable(TIMER1, true);
  
} /* wmbus_hal_tmr_enable() */

/*============================================================================*/
/* wmbus_hal_tmr_disable() */
/*============================================================================*/
void wmbus_hal_tmr_disable(void)
{
  /* Disable TIMER1 interrupt vector in NVIC */
  NVIC_DisableIRQ(TIMER1_IRQn);
  /* Disable TIMER1 */
  TIMER_Enable(TIMER1, false);
  /* Disable clock source for TIMER1 */
  CMU_ClockEnable(cmuClock_TIMER1, false);
} /* wmbus_hal_tmr_disable() */

/*============================================================================*/
/* wmbus_hal_tmr_set() */
/*============================================================================*/
bool_t wmbus_hal_tmr_set(uint16_t ui_counterValue)
{
  return FALSE;
} /* wmbus_hal_tmr_set() */

/*============================================================================*/
/* wmbus_hal_tmr_offset() */
/*============================================================================*/
bool_t wmbus_hal_tmr_offset(sint16_t si_offset)
{
  return FALSE;
} /* wmbus_hal_tmr_offset() */


/*==============================================================================
                            INTERRUPTS
==============================================================================*/
/*========================= TIMER 1 ISR =====================================*/
void TIMER1_IRQHandler(void)
{
  /* Clear flag for TIMER1 overflow interrupt */
  TIMER_IntClear(TIMER1, TIMER_IF_OF);

  if(gfp_tmr1_tick)
  {
    /* Call callback function. */
    gfp_tmr1_tick();
  } /* if */
} /* TIMER1_IRQHandler() */

/**@}*/
#ifdef __cplusplus
}
#endif

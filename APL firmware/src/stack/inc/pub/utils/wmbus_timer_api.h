#ifndef __TIMER_API_H__
#define __TIMER_API_H__
#ifndef __DECL_TIMER_API_H__
#define __DECL_TIMER_API_H__ extern
#else
#define __TIMER_API_INIT_VAR__
#endif  /* __DECL_TIMER_API_H__ */

/**
  @file       wmbus_timer_api.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Utility functions for timings and delay generation.

              Include before:
              - stezdn_typedefs.h

              In order for the timers to work properly the following must be
              considered:
              - A ISR or other mean of periodic function call must call the
                function wmbus_tmr_tick() to update a local counter. In an OS
                environment this can be called out of a OS timer or a separate
                task.
              - To check for events the function wmbus_tmr_handleEvents() must
                also be called periodically. This function is to be called out
                of the main application and calls the timer callback functions
                for event generations.

              Even though in certain environments sophisticated timer functions
              exist these functions in this file do provide a platform
              independent API.

              Interrupt safe timers: in order to be able to use timers in
              interrupts, the macros TOT2_CRITICAL_START and TOT2_CRITICAL_END
              must be defined so that all concurrent access to the linked list
              of timers is prevented.
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/
/* Stack specific includes */
#include "wmbus_global.h"

/*==============================================================================
                           DEFINES
==============================================================================*/
#ifndef TMR_TICKS_PER_SECOND
  /*!  Number of ticks per second. */
  #define TMR_TICKS_PER_SECOND          2000U

  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning TMR_TICKS_PER_SECOND set to default value: 2000
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */

#else
  /* Minimum 1 tick per second. */
  #if (TMR_TICKS_PER_SECOND < 1000U)
  #error TMR_TICKS_PER_SECOND has to be set at least to 2000 ticks.
  #endif /* TMR_TICKS_PER_SECOND < 1000U */
#endif /* TMR_TICKS_PER_SECOND */

/*! Tick divider to get milliseconds. */
#define TMR_TICKS_DIVIDER   (TMR_TICKS_PER_SECOND / 1000U)

/*==============================================================================
                           TYPEDEF ENUMS
==============================================================================*/
/*! State of timers */
typedef enum
{
  /*! The timer is running  */
  E_TMR_STATUS_RUNNING = 1,
  /*! The timer expired */
  E_TMR_STATUS_EXPIRED,
  /*! The timer does not exist */
  E_TMR_STATUS_NOEXIST
} E_TMR_STATUS_t;

/*==============================================================================
                           TYPEDEF STRUCTS
==============================================================================*/
/*!
 * Function pointer to a callback function for a timer event
 */
typedef uint32_t (pf_tmr_Callback_t)(void);

/*!Structure of a timer */
typedef struct S_TMR_T
{
  /*!
   * Current state of the timer
   * If the timer was not yet initialized this field has an undefined value
   */
  E_TMR_STATUS_t e_tmrState;

  /*!
   * The number of ticks after this timer expires
   * This is an absolute value calculated from the actual timer tick on
   * to the end of the delay
   */
  uint32_t l_ticks;

  /*! Previous timer in chain */
  void* p_tmrPrev;
  /*! Next timer in chain */
  void* p_tmrNext;

  /*!
   * Callback function pointer. If set to a function this function will be
   * called when the timeout expires. If set to NULL, then the function
   * is not being called and the timer is most likely to be polled
   */
  pf_tmr_Callback_t *pf_Callback;

  /*!
   * For debugging purposes a description can be set. This field is not
   * required
   */
  const char* pr_desc;

  /*! Flag which indicates if this timer should be checked in the isr of tmr_tick */
  bool_t b_isWdt;

} s_tmr_t;

/*! Structure of global timer variables. */
typedef struct S_TMR_CTX_T
{
  /*! First timer in the timer chain */
  s_tmr_t* ps_tmrFirst;

  /*! Timer Tick Counter */
  volatile uint32_t gl_tmr_tickCnt;

  /*! Timer tick counter of timer B. */
  volatile uint32_t gl_tmr_tickCntB;

  /*! Global WDT counter */
  volatile uint32_t gl_tmrWdt;
} s_tmr_ctx_t;

/*==============================================================================
                           FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief Initialization of the timer module.
 *        This function calls the initialization of a hardware timer and
 *        initializes all timeouts as provided.
 *        The hardware initialization must return the number of ticks per
 *        second as an event counter in order to work with the absolute
 *        timer values.
 */
/*============================================================================*/
void wmbus_tmr_init(void);

/*============================================================================*/
/*!
 * @brief This function calls the event functions from expired timers.
 *        This function must be called as often as possible in order to
 *        handle the timers most accurately.
 */
/*============================================================================*/
void wmbus_tmr_handleEvents(void);

/*============================================================================*/
/*!
 * @brief This function calls the event functions from expired wdt timers.
 *        This function must be called in the tmr_tick() function.
 */
/*============================================================================*/
void wmbus_tmr_handleWdtEvents(void);

/*============================================================================*/
/*!
 * @brief Set a timer based on the number of timer ticks.
 *        This function sets a timer based on the number of ticks of the timer
 *        interval. Note that on different platforms the timer interval might
 *        differ.
 *        This function adds the given timer to the list of timer at the
 *        position after the timer that expires before the given timer.
 *        If this function is being applied to a running timer, then the
 *        timer is being first reset and started again.
 *
 * @param ps_tmr      Pointer to a timer variable. This timer must reside in a
 *                    static memory location.
 * @param l_ms        Delay in milliseconds.
 * @param pf_cbFunc   Callback function pointer. If a function needs to be
 *                    called once the timeout expired then this function need
 *                    to get called. If this pointer is set to NULL then no
 *                    function is called and it is assumed, that the timer is
 *                    used in polled manner.
 */
/*============================================================================*/
void  wmbus_tmr_set(s_tmr_t* ps_tmr, uint32_t l_ms, pf_tmr_Callback_t pf_cbFunc);

/*============================================================================*/
/*!
 * @brief This function resets a timer variable. If the timer variable is
 *        already contained in the list then it is being removed first.
 *        To reset running timers normally the function @ref wmbus_tmr_reset() is used.
 *
 * @param ps_tmr      Pointer to a timer variable. This timer must reside in a
 *                    static memory location.
 * @param b_isWdt     Flag which indicates if the timer should be checked in the
 *                    isr of the function tmr_tick()
 */
/*============================================================================*/
void wmbus_tmr_initDefault(s_tmr_t* ps_tmr, bool_t b_isWdt);

/*============================================================================*/
/*!
 * @brief Remove a running timer from the list of timers. It is being checked
 *        if the timer is running and then it is being removed from the list
 *        of timers. If the timer is not running then it is only be marked
 *        as @ref E_TMR_STATUS_NOEXIST.
 *
 * @param ps_tmr      Pointer to a timer variable. This timer must reside in a
 *                    static memory location.
 */
/*============================================================================*/
void wmbus_tmr_reset(s_tmr_t* ps_tmr);

/*============================================================================*/
/*!
 * @brief Returns the state of a timer
 *        This function returns the current status of the timer.
 *        In many cases this function is sufficient to check a timer and is
 *        especially on low performance platforms a faster function to
 *        check the state of the timer.
 *
 * @param ps_tmr                    Pointer to a timer variable. This timer must
 *                                  reside in a static memory location.
 * @return @ref E_TMR_STATUS_t
 *         - @ref E_TMR_STATUS_RUNNING   The timer has not expired yet
 *         - @ref E_TMR_STATUS_EXPIRED   The timer expired
 */
/*============================================================================*/
E_TMR_STATUS_t wmbus_tmr_getStatus(s_tmr_t* ps_tmr);

/*============================================================================*/
/*!
 * @brief Enables the software timer interrupt.
 */
/*============================================================================*/
void wmbus_tmr_enable(void);

/*============================================================================*/
/*!
 * @brief Disables the software timer interrupt.
 */
/*============================================================================*/
void wmbus_tmr_disable(void);

/*============================================================================*/
/*!
 * @brief Returns the value of the tick counter and l_ms in milliseconds.
 * @param l_ms  Time to add in milliseconds.
 * @return  Value of the tick counter.
 */
/*============================================================================*/
uint32_t wmbus_tmr_getTimeout(uint32_t l_ms);

/*============================================================================*/
/*!
 * @brief   Utility function to check a given value against the current
 *          system tick counter.
 *          A typical example is, if in a function no timer can be used but
 *          a loop might must time out. Then this function can be used to
 *          check for the condition that the given time expired.
 *
 * @param l_timeTicks   The tick-count to check against the current system
 *                      tick counter.
 * @return    If l_timeTicks is greater than the current system ticks, this
 *            function returns the number of ticks that are left until the
 *            system tick counter reaches the value of l_timeTicks.
 * @return    0 if the system tick counter is equal or greater than
 *            l_timeTicks.
*/
/*============================================================================*/
uint32_t wmbus_tmr_ticksToExpire (uint32_t l_timeTicks);

/*============================================================================*/
/*!
 * @brief  Increment the timer's internal tick counter by 1.
 */
/*============================================================================*/
void wmbus_tmr_tick(void);

/*============================================================================*/
/*!
 * @brief   Utility function to check a given value against the current
 *          system tick counter.
 *          A typical example is, if in a function no timer can be used but
 *          a loop might must time out. Then this function can be used to
 *          check for the condition that the given time expired.
 *
 * @param l_timeTicks   The tick-count to check against the current system
 *                      tick counter.
 * @return    If l_timeTicks is greater than the current system ticks, this
 *            function returns the number of ticks that are left until the
 *            system tick counter reaches the value of l_timeTicks.
 * @return    0 if the system tick counter is equal or greater than
 *            l_timeTicks.
 */
/*============================================================================*/
uint32_t wmbus_tmr_ticksToExpireB (uint32_t l_timeTicks);

/*============================================================================*/
/*!
 * @brief  Increment the timer's internal tick counter by 1.
 */
/*============================================================================*/
void wmbus_tmr_tickB(void);

/*============================================================================*/
/*!
 * @brief Returns the value of the tick counter.
 * @return  Value of the tick counter.
 */
/*============================================================================*/
uint32_t wmbus_tmr_getTicksB(void);

/*============================================================================*/
/*!
 * @brief Returns a random number between l_min and l_max using the timer.
 * @param l_min   Minimum value.
 * @param l_max   Maximum value.
 * @return        Random number.
 */
/*============================================================================*/
uint32_t wmbus_tmr_getRandomNumber(uint32_t l_min, uint32_t l_max);

#endif  /* __TIMER_API_H__ */

#ifndef __WMBUS_HAL_TMR_H__
#define __WMBUS_HAL_TMR_H__

/**
  @file       wmbus_hal_tmr.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Hardware Abstraction Layer Application Programming Interface
              for timer implementations.

  @defgroup WMBUS_HAL_TMR WMBUS-HAL - Hardware timer interface
  
  This HAL module shall provide a hardware timer for the stack internally
  maintained timer module and is mandatory and very important for proper
  functioning of the stack.

*/
/**@{*/

/*==============================================================================
                         CALLBACKS
==============================================================================*/

/**
  @brief Callback which indicates a finished transmission.
*/
typedef void (*fp_hal_tmr_cb)(void);


/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Initializes the timer.
          Requests the driver for the hardware timer to initialize for timer
          interrupt at an interval of the given value.
  @param  i_ticksPerSecond    Specifies the number of timer tick indications
                              to be done per second.
  @return Returns @c TRUE if initialisation succeeded.
*/
bool_t wmbus_hal_tmr_init(uint16_t i_ticksPerSecond);

/**
  @brief  Sets the callback for the timer event.
          Provides a pointer to the function to be called, when the hardware
          timer is causing an interrupt due to the configured interval.
  @param  fp_tmr      Pointer to the callback function.
  @return Returns @c TRUE if setting the callback has been successful.
*/
bool_t wmbus_hal_tmr_setCallback(fp_hal_tmr_cb fp_tmr);

/**
  @brief  Enables the timer interrupts.
          As soon as the stack wants to be informed about timer ticks, it'll
          enable the hardware timer interrupts by calling this function.
*/
void wmbus_hal_tmr_enable(void);

/**
  @brief  Disables the timer interrupts.
          The very same like wmbus_hal_tmr_enable, but the other way around.
*/
void wmbus_hal_tmr_disable(void);

/**
  @brief  Sets the timer tick counter.
          For the dynamic timer function, the stack may request the hardware
          timer driver to set the tick counter to the requested value.
  @param  ui_counterValue  Tick counter value to be set.
  @return Returns @c TRUE if successful.
*/
bool_t wmbus_hal_tmr_set(uint16_t ui_counterValue);

/**
  @brief  Adds a positive or negative offset to the timer tick counter.
  @param  si_offset         Offset to be applied on the current tick counter.
  @return Returns @c TRUE if successful.
*/
bool_t wmbus_hal_tmr_offset(sint16_t si_offset);


/**@}*/
#endif /* __WMBUS_HAL_TMR_H__ */

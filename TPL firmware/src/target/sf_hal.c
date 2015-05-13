#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Core HAL module.

  @addtogroup WMBUS_HAL

  The file `/src/target/`sf_hal.c needs to be touched only in case
  additional HAL modules have been added and need to be initialized during
  startup.
*/
/**@{*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
/* STACK */
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\utils\wmbus_timer_api.h"
#include "inc\pub\utils\wmbus_tlg_api.h"
#include "inc\pub\utils\wmbus_api.h"
#include "inc\pub\utils\wmbus_timer_api.h"

/* HAL */
#include "inc\pub\hal\wmbus_hal.h"
#include "inc\pub\hal\wmbus_hal_mcu.h"
#include "inc\pub\hal\wmbus_hal_mem.h"
#include "inc\pub\hal\wmbus_hal_tmr.h"
#include "inc\pub\hal\wmbus_hal_uart.h"
#include "inc\pub\hal\wmbus_hal_aes.h"
#include "inc\pub\hal\wmbus_hal_rf.h"

/*==============================================================================
                            MACROS
==============================================================================*/
/*! Simple macro for checking the value returned on initialization of each HAL
    module. */
#define HAL_STATUS_OK(A)                    ( A == E_HAL_STATUS_SUCCESS )

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* wmbus_hal_init() */
/*============================================================================*/
E_HAL_STATUS_t wmbus_hal_init(void)
{
   E_HAL_STATUS_t e_hal_status = E_HAL_STATUS_SUCCESS;

  if( !( wmbus_hal_mcu_init() ) )
  {
    e_hal_status = E_HAL_STATUS_MCU_ERROR;
  } /* if */

  if( !(wmbus_hal_mem_init()) && (HAL_STATUS_OK(e_hal_status)) )
  {
    e_hal_status = E_HAL_STATUS_MEM_ERROR;
  } /* if */
  
  #if (UART_ENABLED || SERIAL_USB_TO_HOST_ENABLED)
  if( !(wmbus_hal_uart_init()) && (HAL_STATUS_OK(e_hal_status)) )
  {
    e_hal_status = E_HAL_STATUS_UART_ERROR;
  } /* if */
  #endif
 
  /* make sure the uart is already initialized before initialization of timer */
  if( !(wmbus_hal_tmr_init(TMR_TICKS_PER_SECOND)) && (HAL_STATUS_OK(e_hal_status)) )
  {
    e_hal_status = E_HAL_STATUS_TMR_ERROR;
  } /* if */
  
  if( !(wmbus_hal_aes_init()) && (HAL_STATUS_OK(e_hal_status)) )
  {
    e_hal_status = E_HAL_STATUS_AES_ERROR;
  } /* if */

  if( !(wmbus_hal_rf_init()) && (HAL_STATUS_OK(e_hal_status)) )
  {
    e_hal_status = E_HAL_STATUS_RF_ERROR;
  } /* if */


  
  return e_hal_status;

} /* wmbus_hal_init() */

/**@}*/
#ifdef __cplusplus
}
#endif

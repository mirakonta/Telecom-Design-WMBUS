#ifndef __WMBUS_HAL_MCU_H__
#define __WMBUS_HAL_MCU_H__

/**
  @file       wmbus_hal_mcu.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL module for MCU core related functions.

  @defgroup   WMBUS_HAL_MCU WMBUS-HAL - MCU core

  The HAL module for the Microcontroller Unit (MCU) is for handling functions
  that are closely related to the MCU core.
*/
/**@{*/

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Initializes the MCU core.
          In case the MCU core needs some kind of initialization (e.g. setting
          up the core clock, ...), this will be handled within the MCU
          initialization.
  @return Returns @c FALSE in case initialization failed.
*/
bool_t wmbus_hal_mcu_init(void);

/**
  @brief  Resets the MCU.
          This function handles the proper reset/restart of the complete MCU.
*/
void wmbus_hal_mcu_reset(void);


/**@}*/
#endif /* __WMBUS_HAL_MCU_H__ */

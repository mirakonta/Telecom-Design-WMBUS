#ifndef __SF_RF_HAL_MCU_H__
#define __SF_RF_HAL_MCU_H__

/**
  @file       sf_rf_hal_mcu.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for MCU implementations needed by RF driver.
  
  @defgroup SF_RF_HAL_MCU Si446x driver MCU HAL
  
  This module is required to provide some MCU core related functionality to
  the RF driver.
*/
 
/*==============================================================================
                            ENUMS
==============================================================================*/


/*==============================================================================
                         CALLBACKS
==============================================================================*/

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Function for retrieving the MCU clock speed.
          This function is required by the RF driver in order to implement tiny
          delays, which are necessar for proper communication with the attached
          transceiver.
  @return Returns configured MCU frequency in MHz
*/
uint32_t sf_hal_mcu_getClockSpeed(void);


#endif /* __SF_RF_HAL_MCU_H__ */

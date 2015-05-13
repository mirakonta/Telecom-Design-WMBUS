#ifndef __WMBUS_HAL_H__
#define __WMBUS_HAL_H__

/**
  @file       wmbus_hal.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Hardware Abstraction Layer Application Programming Interface.

  @defgroup   WMBUS_HAL Wireless M-Bus Hardware Abstraction Layer (WMBUS-HAL)
  
  This is the main module for the HAL. Typically this module handles the
  initialization of all the other HAL modules only.
*/
/**@{*/

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/
/*! Enumeration of HAL operation status. */
typedef enum
{
  /*! Invalid return status. */
  E_HAL_STATUS_INVALID,
  /*! Initialization has been successful. */
  E_HAL_STATUS_SUCCESS,
  /*! An error occurred in the MCU module. */
  E_HAL_STATUS_MCU_ERROR,
  /*! An error occurred in the MEM module. */
  E_HAL_STATUS_MEM_ERROR,
  /*! An error occurred in the RF module. */
  E_HAL_STATUS_RF_ERROR,
  /*! An error occurred in the AES module. */
  E_HAL_STATUS_AES_ERROR,
  /*! An error occurred in the UPDATE module. */
  E_HAL_STATUS_UPDATE_ERROR,
  /*! An error occurred in the TMR module. */
  E_HAL_STATUS_TMR_ERROR,
  /*! An error occurred in the UART module. */
  E_HAL_STATUS_UART_ERROR,
  /*! An unknown error occurred during initialization. */
  E_HAL_STATUS_UNKNOWN_ERROR
} E_HAL_STATUS_t;

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief   Initializes all hardware components.
  
  This function must be called the main application at the very beginning and
  in order to initialize all the hardware prior to initializing the stack.
  Usually this function simply calls the initialization routines of all the
  other more specific HAL modules and returns an error if one them fails.
 
  @return  Status of the operation.
 */
E_HAL_STATUS_t wmbus_hal_init(void);

/**@}*/

#endif /* __WMBUS_HAL_H__ */

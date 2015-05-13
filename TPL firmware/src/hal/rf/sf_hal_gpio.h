#ifndef __SF_HAL_GPIO_H__
#define __SF_HAL_GPIO_H__

/**
  @file       sf_hal_gpio.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for GPIO implementations.

  @defgroup SF_HAL_GPIO Si446x driver GPIO HAL
  
  The GPIO HAL module provides access to the GPIO pins by the transceiver by
  abstracting the appropriate board and pin-out dependent MCU pins.
  
  All the Si446x transceivers provide four GPIO pins (0-3). The RF driver uses only
  two of them. The two GPIO pins used are differentiated by GPIO0 and GPIO1.
  However, this HAL module may map the pin interactions to any of the four
  transceiver GPIO pins and may use the remaining two GPIO pins for other
  purposes (e.g. an external PA).
  
*/
/**@{*/

/*==============================================================================
                         CALLBACKS
==============================================================================*/

/** Template for callback pointer for registering interrupt callback functions
    used for indicating an interrupt by one of the radio GPIO pins by the
    transceiver. */
typedef void (*fp_hal_gpio_radioIsr)(void);


/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/** Function for _enabling_ power supply of the transceiver. */
void sf_hal_gpio_powerOff(void);
/** Function for _disabling_ power supply of the transceiver. */
void sf_hal_gpio_powerOn(void);


/** Initializes the MCU pins for accessing GPIO0 and GPIO1. */
void sf_hal_gpio_initGPIOx(void);


/*========================= GPIO1 =============================================*/
/** Sets the interrupt for the GPIO0 pin to _rising_ edge sensitive. */
void sf_hal_gpio_irqRisingEdgeGPIO0(void);
/** Sets the interrupt for the GPIO0 pin to _falling_ edge sensitive. */
void sf_hal_gpio_irqFallingEdgeGPIO0(void);
/** _Enables_ the interrupt for GPIO0 pin. */
void sf_hal_gpio_irqEnableGPIO0(void);
/** _Disables_ the interrupt for GPIO0 pin. */
void sf_hal_gpio_irqDisableGPIO0(void);
/** _Clears_ the interrupt flag for GPIO0 pin. */
void sf_hal_gpio_irqClearFlagGPIO0(void);
/** Returns _TRUE_ if the GPIO0 IRQ flag is set. */
bool_t sf_hal_gpio_irqFlagIsSetGPIO0(void);

/**
  This function is for setting the parameters and registers to enable the
  requested GPIO0 pin functionality in Rx Mode. In Rx Mode the GPIO0 pin
  signalizes that the Rx FIFOs almost full threshold has been reached by a
  _rising_ edge.
*/
void sf_hal_gpio_modeRxSetGPIO0(void);

/**
  This function is for setting the parameters and registers to enable the
  required GPIO0 PIN functionality in Tx Mode. In Tx Mode the GPIO0 pin
  signalizes that the Tx FIFOs almost full threshold has been reached by a
  _falling_ edge.
*/
void sf_hal_gpio_modeTxSetGPIO0(void);

/** Returns TRUE if GPIO0 pin level is _high_. */
bool_t sf_hal_gpio_isHighGPIO0(void);
/** Returns TRUE if GPIO0 pin level is _low_. */
bool_t sf_hal_gpio_isLowGPIO0(void);


/*========================= GPIO1 =============================================*/
/** Sets the interrupt for the GPIO1 pin to _rising_ edge sensitive. */
void sf_hal_gpio_irqRisingEdgeGPIO1(void);
/** Sets the interrupt for the GPIO1 pin to _falling_ edge sensitive. */
void sf_hal_gpio_irqFallingEdgeGPIO1(void);
/** _Enables_ the interrupt for GPIO1 pin. */
void sf_hal_gpio_irqEnableGPIO1(void);
/** _Disables_ the interrupt for GPIO1 pin. */
void sf_hal_gpio_irqDisableGPIO1(void);
/** _Clears_ the interrupt flag for GPIO1 pin. */
void sf_hal_gpio_irqClearFlagGPIO1(void);
/** Returns _TRUE_ if the GPIO1 IRQ flag is set. */
bool_t sf_hal_gpio_irqFlagIsSetGPIO1(void);

/**
  This function is for setting the parameters and registers to enable the
  requested GPIO1 pin functionality in Rx Mode. In Rx Mode the GPIO1 pin
  signalizes that the Rx FIFOs almost full threshold has been reached by a
  _rising_ edge.
*/
void sf_hal_gpio_modeRxSetGPIO1(void);

/**
  This function is for setting the parameters and registers to enable the
  required GPIO1 PIN functionality in Tx Mode. In Tx Mode the GPIO1 pin
  signalizes that the Tx FIFOs almost full threshold has been reached by a
  _falling_ edge.
*/
void sf_hal_gpio_modeTxSetGPIO1(void);

/** Returns _TRUE_ if GPIO1 pin level is high. */
bool_t sf_hal_gpio_isHighGPIO1(void);
/** Returns _TRUE_ if GPIO1 pin level is low. */
bool_t sf_hal_gpio_isLowGPIO1(void);



/**@}*/
#endif /* __SF_HAL_GPIO_H__ */

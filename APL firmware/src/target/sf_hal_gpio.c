#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_gpio.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE 
  @brief      HAL for GPIO implementations.
  
  @addtogroup SF_HAL_GPIO
  
  All the GPIO hardware abstraction for the RF driver is implemented within
  `/src/target/`sf_hal_gpio.c.

*/
/**@{*/

/*==============================================================================
                         INCLUDE FILES
 =============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "sf_hal_gpio.h"
#include "em_gpio.h"

/*==============================================================================
                            CHECKS
==============================================================================*/ 
#ifndef RF_GPIO0_PORT
#error: define RF_GPIO0_PORT
#endif

  
#ifndef RF_GPIO0_PIN
#error: define RF_GPIO0_PIN
#endif

#ifndef RF_GPIO1_PIN
#error: define RF_GPIO1_PIN
#endif

#ifndef RF_GPIO1_PORT
#error: define RF_GPIO1_PORT
#endif

#ifndef RF_SDN_PORT
#error: define RF_SDN_PORT
#endif

#ifndef RF_SDN_PIN
#error: define RF_SDN_PIN
#endif

#ifdef EZR32WG330F256R60   
   #undef RF_GPIO0_PORT
   #define RF_GPIO0_PORT           gpioPortA  
#warning:  RF_GPIO0_PORT redefined for EZR devices, due to a bug \
in EFMLib  @version 3.20.12 file: ezr32wg330f256r60.h
#endif

#ifdef EZR32LG330F256R60   
   #undef RF_GPIO0_PORT
   #define RF_GPIO0_PORT           gpioPortA  
#warning:  RF_GPIO0_PORT redefined for EZR devices, due to a bug \
in EFMLib  @version 3.20.12 file: ezr32lg330f256r60.h
#endif
/*==============================================================================
                            DEFINES
==============================================================================*/ 
#define RF_GPIO0_FLAG     (1 << RF_GPIO0_PIN)                                     
#define RF_GPIO1_FLAG     (1 << RF_GPIO1_PIN)        
/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*========================= SDN =============================================*/

/*============================================================================*/
/* sf_hal_gpio_powerOn() */
/*============================================================================*/
/** Pulling down the MCU pin connected to the shutdown pin (SDN) will power
    down the Si446x transceiver. The MCU pin is specified by the appropriate
    configuration (have a look at \c /src/configs/ ) using the
    @ref RF_GPIO0_PORT and @ref RF_SDN_PIN macros. */
void sf_hal_gpio_powerOn(void){
  GPIO_PinModeSet((GPIO_Port_TypeDef)RF_SDN_PORT, RF_SDN_PIN, gpioModePushPull, 0);
}

/*============================================================================*/
/* sf_hal_gpio_powerOff() */
/*============================================================================*/
void sf_hal_gpio_powerOff(void){
  GPIO_PinModeSet((GPIO_Port_TypeDef)RF_SDN_PORT, RF_SDN_PIN, gpioModePushPull, 1);
}
     
/*========================= GPIO  INIT =======================================*/

/*============================================================================*/
/* sf_hal_gpio_initGPIOx() */
/*============================================================================*/
void sf_hal_gpio_initGPIOx(void) {
  NVIC_EnableIRQ(GPIO_ODD_IRQn); 
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);  
  
  /* SET_TO_DEFAULT */  
  GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO0_PORT,
               	   RF_GPIO0_PIN,0,0,0);
  GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO1_PORT,
               	   RF_GPIO1_PIN,0,0,0);    

  /* Set Mode and Pinout*/  
  GPIO_PinModeSet((GPIO_Port_TypeDef) RF_GPIO0_PORT, RF_GPIO0_PIN, gpioModeInputPull, 1);    
  GPIO_PinOutSet((GPIO_Port_TypeDef) RF_GPIO0_PORT, RF_GPIO0_PIN);
  GPIO_PinModeSet((GPIO_Port_TypeDef) RF_GPIO1_PORT, RF_GPIO1_PIN, gpioModeInputPull, 1);    
  GPIO_PinOutSet((GPIO_Port_TypeDef) RF_GPIO1_PORT, RF_GPIO1_PIN);
}


/*========================= GPIO 0 ===========================================*/

/*============================================================================*/
/* sf_hal_gpio_irqRisingEdgeGPIO0() */
/*============================================================================*/
void sf_hal_gpio_irqRisingEdgeGPIO0(void) {   
   GPIO_IntDisable(RF_GPIO0_FLAG);
   GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO0_PORT,
               	   RF_GPIO0_PIN, 1, 0, 0);
}

/*============================================================================*/
/* sf_hal_gpio_irqFallingEdgeGPIO0() */
/*============================================================================*/
void sf_hal_gpio_irqFallingEdgeGPIO0(void) {  
  GPIO_IntDisable(RF_GPIO0_FLAG); 
  GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO0_PORT,
        	  RF_GPIO0_PIN, 0, 1, 0);
}

/*============================================================================*/
/* sf_hal_gpio_irqEnableGPIO0() */
/*============================================================================*/
void sf_hal_gpio_irqEnableGPIO0(void) {
   GPIO_IntClear(RF_GPIO0_FLAG);	
   GPIO_IntEnable(RF_GPIO0_FLAG);
}

/*============================================================================*/
/* sf_hal_gpio_irqDisableGPIO0() */
/*============================================================================*/
void sf_hal_gpio_irqDisableGPIO0(void) {	
  GPIO_IntDisable(RF_GPIO0_FLAG);
}

/*============================================================================*/
/* sf_hal_gpio_irqClearFlagGPI00() */
/*============================================================================*/
void sf_hal_gpio_irqClearFlagGPIO0(void) {
  GPIO_IntClear(RF_GPIO0_FLAG);
}

/*============================================================================*/
/* sf_hal_gpio_irqFlagIsSetGPIO0() */
/*============================================================================*/
bool_t sf_hal_gpio_irqFlagIsSetGPIO0(void) {
if (  (GPIO_IntGet() & RF_GPIO0_FLAG)  > 0  )
  {return TRUE;}
else 
  {return FALSE;}
}

/*============================================================================*/
/* sf_hal_gpio_modeRxSetGPIO0() */
/*===========================================================================*/
void sf_hal_gpio_modeRxSetGPIO0(void) {
   sf_hal_gpio_irqRisingEdgeGPIO0();
}

/*============================================================================*/
/* sf_hal_gpio_modeTxSetGPIO0() */
/*============================================================================*/
void sf_hal_gpio_modeTxSetGPIO0(void) {
   sf_hal_gpio_irqFallingEdgeGPIO0();
}

/*============================================================================*/
/* sf_hal_gpio_isHighGPIO0() */
/*============================================================================*/
bool_t sf_hal_gpio_isHighGPIO0(void) {
  return (bool_t)GPIO_PinInGet((GPIO_Port_TypeDef) RF_GPIO0_PORT, RF_GPIO0_PIN);
}

/*============================================================================*/
/* sf_hal_gpio_isLowGPIO0() */
/*============================================================================*/
bool_t sf_hal_gpio_isLowGPIO0(void) {
return (bool_t)!(GPIO_PinInGet((GPIO_Port_TypeDef) RF_GPIO0_PORT, RF_GPIO0_PIN));
}



/*========================= GPIO 2 =============================================*/

/*============================================================================*/
/* sf_hal_gpio_irqRisingEdgeGPIO1() */
/*============================================================================*/
void sf_hal_gpio_irqRisingEdgeGPIO1(void) {   
   GPIO_IntDisable(RF_GPIO1_FLAG);
   GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO1_PORT,
               	   RF_GPIO1_PIN, 1, 0, 0);
}

/*============================================================================*/
/* sf_hal_gpio_irqFallingEdgeGPIO1() */
/*============================================================================*/
void sf_hal_gpio_irqFallingEdgeGPIO1(void) {  
  GPIO_IntDisable(RF_GPIO1_FLAG); 
  GPIO_IntConfig((GPIO_Port_TypeDef) RF_GPIO1_PORT,
        	  RF_GPIO1_PIN, 0, 1, 0);
}

/*============================================================================*/
/* sf_hal_gpio_irqEnableGPIO1() */
/*============================================================================*/
void sf_hal_gpio_irqEnableGPIO1(void) {
   GPIO_IntClear(RF_GPIO1_FLAG);	
   GPIO_IntEnable(RF_GPIO1_FLAG);
}

/*============================================================================*/
/* sf_hal_gpio_irqDisableGPIO1() */
/*============================================================================*/
void sf_hal_gpio_irqDisableGPIO1(void) {	
  GPIO_IntDisable(RF_GPIO1_FLAG);
}

/*============================================================================*/
/* sf_hal_gpio_irqClearFlagGPI00() */
/*============================================================================*/
void sf_hal_gpio_irqClearFlagGPIO1(void) {
	GPIO_IntClear(RF_GPIO1_FLAG);
}

/*============================================================================*/
/* sf_hal_gpio_irqFlagIsSetGPIO1() */
/*============================================================================*/
bool_t sf_hal_gpio_irqFlagIsSetGPIO1(void) {
if (  (GPIO_IntGet() & RF_GPIO1_FLAG)  > 0  )
  {return TRUE;}
else 
  {return FALSE;}
}

/*============================================================================*/
/* sf_hal_gpio_modeRxSetGPIO1() */
/*===========================================================================*/
void sf_hal_gpio_modeRxSetGPIO1(void) {
   sf_hal_gpio_irqRisingEdgeGPIO1();
}

/*============================================================================*/
/* sf_hal_gpio_modeTxSetGPIO1() */
/*============================================================================*/
void sf_hal_gpio_modeTxSetGPIO1(void) {
   sf_hal_gpio_irqFallingEdgeGPIO1();
}

/*============================================================================*/
/* sf_hal_gpio_isHighGPIO1() */
/*============================================================================*/
bool_t sf_hal_gpio_isHighGPIO1(void) {
  return (bool_t)GPIO_PinInGet((GPIO_Port_TypeDef) RF_GPIO1_PORT, RF_GPIO1_PIN);
}

/*============================================================================*/
/* sf_hal_gpio_isLowGPIO1() */
/*============================================================================*/
bool_t sf_hal_gpio_isLowGPIO1(void) {
return (bool_t)!(GPIO_PinInGet((GPIO_Port_TypeDef) RF_GPIO1_PORT, RF_GPIO1_PIN));
}

/**@}*/
#ifdef __cplusplus
}
#endif

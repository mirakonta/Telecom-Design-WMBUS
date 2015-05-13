/*============================================================================*/
/**
 * @file       prj_config.h
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @brief      Pre-include configurations serial application
 *
 */
/*============================================================================*/

#define WMBUS_APP_SERIAL

/* include the pin settings-file for the selected board  */
#ifdef STK3600
  #include "STK3600.h"
#elif defined STK3200
  #include "STK3200.h"
#elif defined STK3800
  #include "STK3800.h"
#elif defined SLWSTK6220A
  #include "SLWSTK6220A.h"
#elif defined SLWSTK6200A
  #include "SLWSTK6200A.h"
#else
  #error: Please create a board configuration or use an existing one (see above)
#endif

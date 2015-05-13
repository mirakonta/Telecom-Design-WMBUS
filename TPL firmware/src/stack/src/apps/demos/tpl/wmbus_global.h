/**
  @file       wmbus_global.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Global configurations for the stack.
*/

/* Include customer specific macros */
#include"release.h"

/* Further settings are set in the preprocessor area of the compiler! */

/*! Enable additional debug output */
#define STZ_INFO                                TRUE
#define __SUPPORT_WARNINGS__                    FALSE

/*! Enables AES128 encrytpion with dynamic initialization vector.
    Overwrites the makro from wmbus_dll_plus_api.h */
#define AES128_DYNAMIC_IV_ENCRYPT_ENABLED       TRUE

/*! Enables AES128 decryption with dynamic initialization vector.
    Overwrites the makro from wmbus_dll_plus_api.h */
#define AES128_DYNAMIC_IV_DECRYPT_ENABLED       TRUE

/*! Always use the address of the meter for de- and encryptiom. Regarding to EN 13757 */
#define AES_INITIALIZATION_VECOR_ADDRESS        WMBUS_IV_METER_ADDR


/*! Enables the Open Metering extensions.
    Overwrites the makro from wmbus_api.h */
#define OMS_ENABLED                             TRUE

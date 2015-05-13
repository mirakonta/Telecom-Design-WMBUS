/**
  @file       wmbus_global.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Global configurations for the stack.
*/

/* Include customer specific macros */
#include "release.h"

/* Further settings are set in the preprocessor area of the compiler! */

/*! Enable additional debug output */
#define STZ_INFO                                TRUE
#define __SUPPORT_WARNINGS__                    FALSE

/*! Enables handling of configuration commands on serial application layer.
    Overwrites the makro from wmbus_serial_api.h */
#define SERIAL_CFG_APL_ENABLED                  FALSE

/*! Enables the application layer functions of serial library.
    Overwrites the makro from wmbus_serial_api.h */
#define SERIAL_APL_ENABLED                      FALSE

/*! Enable to call the function wmbus_serial_evt_rx() if a telegram is received.
    Overwrites the makro from wmbus_serial_api.h */
#define SERIAL_EVT_RX_ENABLED                   FALSE

/*! Enable to call the function wmbus_serial_evt_tx() if a telegram is sent.
    Overwrites the makro from wmbus_serial_api.h */
#define SERIAL_EVT_TX_ENABLED                   FALSE

/*! Enables AES128 encrytpion with dynamic initialization vector.
    Overwrites the makro from wmbus_tpl_api.h */
#define AES128_DYNAMIC_IV_ENCRYPT_ENABLED       TRUE

/*! Enables AES128 decryption with dynamic initialization vector.
    Overwrites the makro from wmbus_tpl_api.h */
#define AES128_DYNAMIC_IV_DECRYPT_ENABLED       TRUE

/*! Enables AES128 encrytpion with static initialization vector.
    Overwrites the makro from wmbus_tpl_api.h */
#define AES128_STATIC_IV_ENCRYPT_ENABLED        FALSE

/*! Enables AES128 decryption with static initialization vector.
    Overwrites the makro from wmbus_tpl_api.h */
#define AES128_STATIC_IV_DECRYPT_ENABLED        FALSE

/*! Always use the address of the meter for de- and encryptiom. Regarding to EN 13757 */
#define AES_INITIALIZATION_VECOR_ADDRESS        WMBUS_IV_METER_ADDR

/*! Enables the internal clock.
    Overwrites the makro from wmbus_apl_api.h */
#ifndef APL_CLOCK_ENABLED
#define APL_CLOCK_ENABLED                       TRUE
#endif /* APL_CLOCK_ENABLED */

/*! Enable to call the function wmbus_apl_evt_rx() if a telegram is received.
    Overwrites the makro from wmbus_apl_api.h */
#define APL_EVT_RX_ENABLED                      TRUE

/*! Enable to call the function wmbus_apl_evt_tx() if a telegram is sent.
    Overwrites the makro from wmbus_apl_api.h  */
#define APL_EVT_TX_ENABLED                      TRUE

/*! Default records are enabled.
    Overwrites the makro from wmbus_apl_api.h  */
#define APL_RECORDS_ENABLED                     FALSE

/*! Disables the reception of unencrypted commands
    (sent from collector to meter)*/
#define APL_IGNORE_UNENCRYPTED_COLLECTOR_COMMANDS TRUE

/*! Enable sending ACC-DMD when the meter has alarm */
#define APL_ALARM_ACC_DMD_ENABLED               FALSE

/*! Enables the Open Metering extensions.
    Overwrites the makro from wmbus_api.h */
#define OMS_ENABLED                             TRUE

/*! Enables the DSMR V.4.0.5 extensions.
    There is no makro from wmbus_api.h at the moment */
#define DSMR_V405_ENABLED                       FALSE

/*! Enables the DSMR V.2.2+ (Landis+Gyr) extensions.
    There is no makro from wmbus_api.h at the moment */
#define DSMR_V22_PLUS_ENABLED                   FALSE

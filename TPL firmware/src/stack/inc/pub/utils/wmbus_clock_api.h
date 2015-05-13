#ifndef __WMBUS_CLOCK_H__
#define __WMBUS_CLOCK_H__
#ifndef __DECL_WMBUS_CLOCK_H__
#define __DECL_WMBUS_CLOCK_H__ extern
#else
#define __WMBUS_CLOCK_INIT_VAR__
#endif /* __DECL_CLOCK_H__ */

/**
  @file       wmbus_clock_api.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Wireless M-Bus clock module Application Programming Interface.

              Include before:
              - wmbus_typedefs.h
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/

/* Stack specific includes */
#include "wmbus_global.h"

/*! @defgroup WMBUS_CLOCK Clock Interface Description
 *  This section describes the API for the STACKFORCE clock module.
 *  @{
 */

/*==============================================================================
                            TYPEDEF ENUMS
==============================================================================*/
/*! \defgroup WMBUS_CLOCK_ENUM Enumerations
 *  Enumerations for a common device.
 *  @{
 */

/*! Elements of the clock. */
typedef enum
{
  E_CLOCK_SECONDS,
  E_CLOCK_MINUTES,
  E_CLOCK_HOURS,
  E_CLOCK_DAYS,
  E_CLOCK_MONTHS,
  E_CLOCK_YEARS
} E_CLOCK_t;

/*! @} end of WMBUS_CLOCK_ENUM */
/******************************************************************************/

/*! \defgroup WMBUS_CLOCK_STRUCTS Structures
 *  Structures for a common device.
 *  @{
 */

/*==============================================================================
                            TYPEDEF STRUCTS
==============================================================================*/
/*! Structure of a clock. */
typedef struct S_CLOCK_T
{
  /*! System time in milliseconds. */
  uint32_t l_ms;
  /*! Seconds (0...59) */
  uint8_t c_seconds;
  /*! Minutes (0...59) */
  uint8_t c_minutes;
  /*! Hours (0...23) */
  uint8_t c_hours;
  /*! Days of month (1...28.30.31) */
  uint8_t c_days;
  /*! Months of year (1...12) */
  uint8_t c_months;
  /*! Year (0...9999) */
  uint16_t i_years;
  /*! Set if the clock is running. */
  bool_t b_running;
} s_clock_t;

/*!@} end of WMBUS_CLOCK_STRUCTS */
/******************************************************************************/

/*! \defgroup WMBUS_CLOCK_API Public API functions
 *  Public APIs for a common device.
 *  @{
 */

/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief Initializes the clock.
 * @param ps_clock  Clock to initialize.
 */
/*============================================================================*/
void wmbus_clock_init(s_clock_t *ps_clock);

/*============================================================================*/
/*!
 * @brief Runs a clock.
 * @param ps_clock  Clock to run.
 * @return          @ref TRUE if one or more elements of the clock are changed.
 */
/*============================================================================*/
bool_t wmbus_clock_run(s_clock_t *ps_clock);

/*============================================================================*/
/*!
 * Checks if the year is a leap year.
 * @param i_year   Year.
 * @return         @ref TRUE if the year is a leap year.
 */
/*============================================================================*/
bool_t wmbus_clock_isLeap(uint16_t i_year);

/*============================================================================*/
/*!
 * @brief Starts the clock.
 * @param ps_clock  Clock to start.
 */
/*============================================================================*/
void wmbus_clock_start(s_clock_t *ps_clock);

/*============================================================================*/
/*!
 * @brief Stops the clock.
 * @param ps_clock  Clock to stop.
 */
/*============================================================================*/
void wmbus_clock_stop(s_clock_t *ps_clock);

/*============================================================================*/
/*!
 * @brief Increments an element of the clock.
 * @param ps_clock  Clock to increment.
 * @param e_element Element to increment.
 * @param b_single  Set if only the single element has to be changed. If not
 *                  set all other elements are updated if necessary.
 */
/*============================================================================*/
void wmbus_clock_inc(s_clock_t *ps_clock, E_CLOCK_t e_element, bool_t b_single);

/*============================================================================*/
/*!
 * @brief Decrements an element of the clock.
 * @param ps_clock  Clock to decrement.
 * @param e_element Element to decrement.
 * @param b_single  Set if only the single element has to be changed. If not
 *                  set all other elements are updated if necessary.
 */
/*============================================================================*/
void wmbus_clock_dec(s_clock_t *ps_clock, E_CLOCK_t e_element, bool_t b_single);

/*============================================================================*/
/*!
 * @brief Calc the minutes since the clock is running. (Max. 64 Years).
 *        This function is needed for meter devices which use the CI-field 0x8D
 * @param ps_clock  pointer to the clock.
 */
/*============================================================================*/
uint32_t wmbus_clock_calcMinutes(s_clock_t* ps_clock);

/*!@} end of WMBUS_CLOCK_API */
/******************************************************************************/

/*!@} end of WMBUS_CLOCK */
/******************************************************************************/

#endif/* __WMBUS_CLOCK_H__ */

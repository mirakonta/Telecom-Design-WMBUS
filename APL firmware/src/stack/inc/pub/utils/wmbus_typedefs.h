#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

/**
  @file       wmbus_typedefs.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Type definitions.
*/

/*==============================================================================
                            INCLUDES
==============================================================================*/
/* Library includes */
#include <string.h>

/*==============================================================================
                            DEFINES
==============================================================================*/
/*! Definition of FALSE value */
#ifndef FALSE
#define FALSE                         0U
#endif /* FALSE */

/*! Definition of TRUE value */
#ifndef TRUE
#define TRUE                          1U
#endif /* TRUE */

/*! Definition of NULL value */
#ifndef NULL
#define NULL                          0U
#endif

/*==============================================================================
                            INCLUDES
==============================================================================*/
/* Stack specific includes */
#include "wmbus_global.h"

/*! Only enable if the stdint.h should be used. It is recommended not to used the stdint.h */
#ifndef USE_STDINT
#define USE_STDINT                 FALSE
  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning USE_STDINT set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* USE_STDINT */

/*! Only enable if the stdbool.h should be used. It is recommended not to used the stdbool.h */
#ifndef USE_STDBOOL
#define USE_STDBOOL                FALSE
  #if (STZ_INFO && __SUPPORT_WARNINGS__)
  #warning USE_STDBOOL set to default value: FALSE
  #endif /* STZ_INFO && __SUPPORT_WARNINGS__ */
#endif /* USE_STDBOOL */

#if USE_STDINT == TRUE
#include <stdint.h>
#endif /* USE_STDINT == TRUE */

#if USE_STDBOOL == TRUE
#include <stdbool.h>
#endif /* USE_STDBOOL == TRUE */

/*==============================================================================
                            COMPILER SPECIFIC
==============================================================================*/

#if defined(__IAR_SYSTEMS_ICC__)
  #define __SUPPORT_WARNINGS__    FALSE
  #define STZ_INLINE              inline
  #define PACKED_STRUCT(__declaration__,__name__) \
    _Pragma("pack(push,1)") __declaration__  __name__ _Pragma("pack(pop)")
  #define BIG_ENDIAN              FALSE
  #define LITTLE_ENDIAN           TRUE
  #define STZ_CONST
#elif defined(_MSC_VER)
  #define __SUPPORT_WARNINGS__    FALSE
  #define STZ_INLINE              __inline
  #define PACKED_STRUCT(__declaration__, __name__) \
    __pragma( pack(push, 1) ) __declaration__ __name__ __pragma( pack(pop) )
  #define BIG_ENDIAN              FALSE
  #define LITTLE_ENDIAN           TRUE
  #define STZ_CONST
#elif defined(__CCE__)
  #define __SUPPORT_WARNINGS__    FALSE
  #define STZ_INLINE
  #define PACKED_STRUCT(__declaration__,__name__) \
    __declaration__  __name__
  #define BIG_ENDIAN              FALSE
  #define LITTLE_ENDIAN           TRUE
  #define STZ_CONST
#elif defined(__C51__)
  #define __SUPPORT_WARNINGS__    FALSE
  #define PACKED_STRUCT(__declaration__, __name__) \
    __declaration__ __name__
  #define BIG_ENDIAN              TRUE
  #define LITTLE_ENDIAN           FALSE
  #define STZ_INLINE
  #define STZ_CONST               code
#elif defined (__GNUC__)
  #define __SUPPORT_WARNINGS__    FALSE
  #define PACKED_STRUCT(__declaration__, __name__) \
    __declaration__ __name__
  #ifndef BIG_ENDIAN
  #define BIG_ENDIAN              FALSE
  #endif
  #ifndef LITTLE_ENDIAN
  #define LITTLE_ENDIAN           TRUE
  #endif
  #define STZ_INLINE
  #define STZ_CONST
  #define __no_init
#elif defined(__RENESAS__)
  #define __SUPPORT_WARNINGS__    FALSE
  #define PACKED_STRUCT(__declaration__, __name__) \
    __declaration__ __name__
  #define BIG_ENDIAN              FALSE
  #define LITTLE_ENDIAN           TRUE
  #define STZ_INLINE
  #define STZ_CONST
  #define __no_init
#else
  #error The compiler is not supported.
#endif /* Compiler */

#ifndef STZ_INFO
#define STZ_INFO                  TRUE
#endif

/*============================================================================*/
/*!
 * @brief Converts an uint16_t to an uint8_t array.
 * @param x           uint8_t array to write the value in.
 * @param y           Value to convert.
 */
/*============================================================================*/
#define UINT16_TO_UINT8(x, y)         ((x)[0] = (uint8_t)((uint8_t)((y)>>8U) & 0xFFU)); \
                                      ((x)[1] = (uint8_t)((y) & 0xFFU))

/*============================================================================*/
/*!
 * @brief Converts an uint16_t to an uint8_t array.
 *        The lower byte is index 0, the higher byte index 1.
 * @param x           uint8_t array to write the value in.
 * @param y           Value to convert.
 */
/*============================================================================*/
#define UINT16_TO_UINT8_REV(x, y)     ((x)[0U] = ((y) & 0xFFU)); \
                                      ((x)[1U] = (((y) >> 8U) & 0xFFU))

/*============================================================================*/
/*!
 * @brief Converts an uint8_t array to an uint16_t.
 * @param x           uint8_t array to convert.
 * @return            Converted value.
 */
/*============================================================================*/
#define UINT8_TO_UINT16(x)           (uint16_t)(((uint16_t)((x)[0])<<8) + (uint16_t)((x)[1]))

/*============================================================================*/
/*!
 * @brief Converts an uint8_t array to an uint16_t.
 * @param x           uint8_t array to convert.
 * @param y           uint16_t variable to store the converted value in.
 */
/*============================================================================*/
#define UINT8_TO_UINT16_REV(x, y)        y = (uint16_t)((x)[1U]); \
                                          (y<<=8);\
                                           (y |= (uint16_t)((x)[0U]))

/*============================================================================*/
/*!
 * @brief Converts an uint8_t array to an uint32_t.
 * @param x           uint8_t array to convert.
 * @return            Converted value.
 */
/*============================================================================*/
#define UINT8_TO_UINT32(x)            ((((uint32_t) (x)[0U])<<24U) + \
                                       (((uint32_t) (x)[1U])<<16U) + \
                                       (((uint32_t) (x)[2U])<<8U) + \
                                                    (x)[3U])

/*============================================================================*/
/*!
 * @brief Converts an uint32_t to an uint8_t array.
 * @param x           uint8_t array to write the value in.
 * @param y           Value to convert.
 */
/*============================================================================*/
#define UINT32_TO_UINT8(x,y)          ((x)[0] = (uint8_t)((uint8_t)((y)>>24U) & 0xFFU)); \
                                      ((x)[1] = (uint8_t)((uint8_t)((y)>>16U) & 0xFFU)); \
                                      ((x)[2] = (uint8_t)((uint8_t)((y)>>8U) & 0xFFU)); \
                                      ((x)[3] = (uint8_t)((uint8_t)((y) & 0xFFU)))

/*============================================================================*/
/*!
 * @brief Copies a byte array from one to another memory.
 * @param x   Destination memory.
 * @param y   Source memory.
 * @param z   Number of bytes to copy.
 */
/*============================================================================*/
#define MEMCPY(x,y,z)                 memcpy((x), (y), (z))

/*============================================================================*/
/*!
 * @brief Compares two memory areas.
 * @param x   Memory 1 to compare.
 * @param y   Memory 2 to compare.
 * @param z   Number of bytes to compare.
 * @return    0 if the bytes are equal.
 */
/*============================================================================*/
#define MEMCMP(x,y,z)                 memcmp((x), (y), (uint_t) (z))

/*============================================================================*/
/*!
 * @brief Writes bytes into a specific memory.
 * @param x   Destination memory to write to.
 * @param y   Byte to write into the destination memory.
 * @param z   Number of bytes to write.
 */
/*============================================================================*/
#define MEMSET(x,y,z)                 memset((x), (y), (uint_t) (z))


/*============================================================================*/
/*!
 * @brief Swaps the byte order of a 16Bit integer.
 *
 * @param x   Integer to swap.
 */
/*============================================================================*/
#define ENDIAN_SWAP_16(x)   (x = ( x >> 8) | ( x<<8 ) )

/*============================================================================*/
/*!
 * @brief Swaps the byte order of a 32Bit integer.
 *
 * @param x   Integer to swap.
 */
/*============================================================================*/
#define ENDIAN_SWAP_32(x)   (                     \
                                  x =   (x >> 24)| \
                                        ((x << 8) & 0x00FF0000) | \
                                        ((x >> 8) & 0x0000FF00) | \
                                        (x << 24)                 \
                            )

/*==============================================================================
                            TYPEDEFS
==============================================================================*/
#ifndef sint8_t
  /*! Signed 8BIT integer */
  typedef char           sint8_t;
  /*! Signed 8BIT integer */
  #define sint8_t        sint8_t
#endif /* sint8_t */

#if USE_STDINT == FALSE
  #ifndef uint8_t
    /*! Unsigned 8BIT integer */
    typedef unsigned char  uint8_t;
    /*! Unsigned 8BIT integer */
	#define uint8_t        uint8_t
  #endif /* uint8_t */
#endif /* USE_STDINT == FALSE_ */

#ifndef sint16_t
  /*! Signed 16BIT integer */
  typedef signed short   sint16_t;
  /*! Signed 16BIT integer */
  #define sint16_t       sint16_t
#endif /* sint16_t */

#if USE_STDINT == FALSE
  #ifndef uint16_t
    /*! Unsigned 16BIT integer */
	#ifdef __GNUC__
	  typedef unsigned short u16;
	  /*! Unsigned 16BIT integer */
	  #define uint16_t 	     u16
	#else
	  typedef unsigned short uint16_t;
	  /*! Unsigned 16BIT integer */
	  #define uint16_t       uint16_t
	#endif
  #endif /* uint16_t */
#endif /* USE_STDINT == FALSE */

#ifndef sint32_t
  /*! Signed 32BIT integer */
  typedef signed long    sint32_t;
  /*! Signed 32BIT integer */
  #define sint32_t       sint32_t
#endif /* sint32_t */

#if USE_STDINT == FALSE
  #ifndef uint32_t
    /*! Unsigned 32BIT integer */
		#ifdef __GNUC__
			typedef unsigned long u32;
			/*! Unsigned 16BIT integer */
			#define uint32_t 	     u32
		#else
			typedef unsigned long  uint32_t;
			/*! Unsigned 32BIT integer */
			#define uint32_t       uint32_t
		#endif
	#endif /* uint32_t */
#endif /* USE_STDINT == FALSE */

#if USE_STDBOOL == TRUE
  #ifndef bool_t
    /*! Boolean value (c.f. @ref TRUE, @ref FALSE) */
    #define bool_t         bool
  #endif /* bool_t */
#else
  #ifndef bool_t
    /*! Boolean value (c.f. @ref TRUE, @ref FALSE) */
    typedef unsigned char  bool_t;
    #define bool_t         bool_t
  #endif /* bool_t */
#endif /* USE_STDBOOL == TRUE */

#ifndef uint_t
  /*! Default unsigned integer to use for standard functions. */
  typedef unsigned int   uint_t;
  #define uint_t         uint_t
#endif /* uint_t */

#ifndef sint_t
  /*! Default signed integer to use for standard functions. */
  typedef signed int     sint_t;
  #define sint_t         sint_t
#endif /* sint_t */

/*! Common callback function without arguments */
typedef void (*callback_t) (void);
/*! Common callback function with an @ref uint8_t argument */
typedef uint8_t (*callbackU8_t) (uint8_t c_len);
/*! Common callback function with an @ref uint8_t argument */
typedef uint16_t (*callbackU16_t) (uint16_t i_len);

#endif /* __TYPEDEFS_H__ */

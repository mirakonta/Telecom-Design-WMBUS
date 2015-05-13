#ifndef __WMBUS_HAL_MEM_H__
#define __WMBUS_HAL_MEM_H__

/**
  @file       wmbus_hal_mem.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Hardware Abstraction Layer Application Programming Interface
              for memory implementations.

  @defgroup WMBUS_HAL_MEM WMBUS-HAL - Non-volatile memory

  This module defines the Hardware Abstraction Layer for the non-volatile memory
  unit. The stack requires non-volatile for storing data that should be kept
  even if the device looses power supply, e.g. the currently configured address
  of the device.
*/
/**@{*/

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Initializes the memory module, in case the non-volatile needs any
          preparation before using it.
  @return Returns @c TRUE if initialization has been successful.
 */
bool_t wmbus_hal_mem_init(void);

/**
  @brief  Writes data into the non-volatile memory.
          This function provides access to the non-volatile memory for storing
          stack internal information that need to be kept in case of power loss.
  @param  pc_data   Data to be written into the memory.
  @param  i_len     Number of bytes to be written.
  @param  l_offset  Offset from start address of the non-volatile memory,
                    equivalent to a virtual mapped address.
  @return Number of bytes that have been written.
*/
uint16_t wmbus_hal_mem_write(uint8_t *pc_data, uint16_t i_len, uint32_t l_offset);

/**
  @brief  Reads data from the non-volatile memory.
          Especially on startup of the device, the stack needs to read importand
          data that has been saved earlier (e.g. device address).
  @param  pc_data   Destination where to copy the read bytes.
  @param  i_len     Number of bytes to be read.
  @param  l_offset  Offset from start address of the non-volatile memory,
                    equivalent to a virtual mapped address.
  @return Number of bytes that have been read.
*/
uint16_t wmbus_hal_mem_read(uint8_t *pc_data, uint16_t i_len, uint32_t l_offset);

/**@}*/
#endif /* __WMBUS_HAL_MEM_H__ */

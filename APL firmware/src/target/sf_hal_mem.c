#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_mem.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL for access to non-volatile memory.
 
  @addtogroup WMBUS_HAL_MEM
  
  All these functions are implemented in `/src/target/`sf_hal_mem.c

*/
/**@{*/


/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "inc\pub\hal\wmbus_hal_mem.h"

#include "em_device.h"
#include "em_msc.h"


/** Check if FLASH_PAGE_SIZE macro has been set by EFM library. */
#if !defined(FLASH_PAGE_SIZE)
  #error Macro FLASH_PAGE_SIZE needs to be specified! Usually it is specified \
         by the EFM library according to the selected derivative.
#endif

/** Check if FLASH_SIZE macro has been set by EFM library. */
#if !defined(FLASH_SIZE)
  #error Macro FLASH_SIZE needs to be specified! Usually it is specified \
         by the EFM library according to the selected derivative.
#endif


/*! In case flash access fails, the driver retries it. The number of retries
    can be specified by setting the MEM_FLASH_WRITE_RETRIES macro. */
#define MEM_FLASH_WRITE_RETRIES   (3U)

/** Setting macro for start address of flash to be used as non-volatile memory
    for the stack. Usually using the very last flash page is preferred. */
#define MEM_START_ADDR      (FLASH_SIZE - FLASH_PAGE_SIZE)
/*! Setting macro for end address of flash. */
#define MEM_END_ADDR        (MEM_START_ADDR + FLASH_PAGE_SIZE)

/*==============================================================================
                            LOCAL FUNCTIONS
==============================================================================*/
/*============================================================================*/
/**
  @brief  Handles writing of data.
          This function handles the write procedure to the flash.
  @param  l_addr      Address within flash where to write data.
  @param  pc_data     Pointer to the data to be written into flash.
  @param  i_len       Number of bytes to copied from pc_data to l_addr.
  @return Returns the number of written bytes.
  @retval (0)         Returns zero in case write operation has failed.
*/
/*============================================================================*/
uint16_t loc_datamemory_writeData(uint32_t l_addr, uint8_t *pc_data, uint16_t i_len)
{
  uint8_t c_retry_count;
  msc_Return_TypeDef msc_ret;

  /* disable interrupts */
  __disable_irq();

  /* init */
  MSC_Init();
  c_retry_count = 0;
  msc_ret = mscReturnUnaligned;

  /* Erase the page */
  while((c_retry_count < MEM_FLASH_WRITE_RETRIES) && (msc_ret != mscReturnOk))
  {
    /* erase segment */
    msc_ret = MSC_ErasePage((uint32_t *) l_addr);
    c_retry_count++;
  } /* while */

  /* reset counter */
  c_retry_count = 0U;
  msc_ret = mscReturnUnaligned;

  /* Write data to the userpage */
  while((c_retry_count < MEM_FLASH_WRITE_RETRIES) && (msc_ret != mscReturnOk))
  {
    msc_ret = MSC_WriteWord((uint32_t *) l_addr, (void *) pc_data, i_len);
    c_retry_count++;
  } /* while */

  if (mscReturnOk != msc_ret)
  {
    i_len = 0;
  }

  /* de-init */
  MSC_Deinit();

  /* reenable interrupts*/
  __enable_irq();

  return i_len;
} /* loc_datamemory_writeData() */


/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* wmbus_hal_mem_init() */
/*============================================================================*/
bool_t wmbus_hal_mem_init(void)
{
  return TRUE;
} /* wmbus_hal_mem_init() */

/*============================================================================*/
/* wmbus_hal_mem_write() */
/*============================================================================*/
uint16_t wmbus_hal_mem_write(uint8_t *pu8_data, uint16_t u16_len, 
                          uint32_t u32_addr)
{
  uint16_t u16_ret = 0;
  /* Counter variable. */
  uint16_t i;
  /* Start of the segment to write into. */
  uint8_t *pu8_memory;
  /* Number of written bytes. */
  uint16_t u16_tmpLen;
  /* Address of the first segment. */
  uint32_t l_addrSegmStart;

  uint32_t l_addrSegmStartShortMemory;
  /* Temporary data buffer. */
  static uint8_t u8_segment[FLASH_PAGE_SIZE];

  u32_addr += MEM_START_ADDR;

  if((u32_addr + u16_len) <= FLASH_SIZE)
  {
    l_addrSegmStart = u32_addr; /* Start of flash memory. */

    while((l_addrSegmStart % FLASH_PAGE_SIZE) != 0U)
    {
      l_addrSegmStart--;
    } /* while */

    /* Calculates the start to overwrite of the first segment. */
    u32_addr %= FLASH_PAGE_SIZE;

    u16_tmpLen = 0;
    /* Copies p_data into the flash. Allows overwriting of several segments. */
    while(u16_tmpLen < u16_len)
    {
      l_addrSegmStartShortMemory = l_addrSegmStart & 0xFFFFFFFFU;
      pu8_memory = (uint8_t*) l_addrSegmStartShortMemory;

      /* Copies the current memory content into a temporary buffer. */
      for(i = 0;i < FLASH_PAGE_SIZE;i++)
      {
        u8_segment[i] = pu8_memory[i];
      } /* for */

      /* Updates the current segment. */
      for(i = 0;
          u16_tmpLen < u16_len && (u32_addr + i) < FLASH_PAGE_SIZE;
          i++)
      {
        if(pu8_data == NULL)
        {
          u8_segment[u32_addr + i] = 0U;
        }
        else
        {
          u8_segment[u32_addr + i] = pu8_data[u16_tmpLen];
        } /* if ... else */
        u16_tmpLen++;
      } /* for */

      /* Writes the data to the flash memory. */

      u16_ret = loc_datamemory_writeData(l_addrSegmStart, u8_segment, FLASH_PAGE_SIZE);
      if(FLASH_PAGE_SIZE == u16_ret)
      {
        u16_ret = u16_len;
      }/* if */
      l_addrSegmStart += FLASH_PAGE_SIZE;
      u32_addr = 0U;
    } /* while */
  }
  return u16_ret;
} /* wmbus_hal_mem_write() */

/*============================================================================*/
/* wmbus_hal_mem_read() */
/*============================================================================*/
uint16_t wmbus_hal_mem_read(uint8_t *pu8_data, uint16_t u16_len, uint32_t u32_addr)
{
  uint16_t u16_ret = 0;
  uint16_t i;
  uint8_t* pc_nvm_addr;

  u32_addr += MEM_START_ADDR;

  /* disable interrupts */
  __disable_irq();

  /* set address to read */
  pc_nvm_addr = (uint8_t*)(u32_addr);

  for(i = 0; i < u16_len; i++)
  {
    *pu8_data++ = *pc_nvm_addr++;
  } /* for */

  /* reenable interrupts*/
  __enable_irq();

  u16_ret = u16_len;
  return u16_ret;
} /* wmbus_hal_mem_read() */

/**@}*/
#ifdef __cplusplus
}
#endif

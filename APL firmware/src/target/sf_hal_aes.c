#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_hal_aes.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE 
  @brief      HAL for AES implementations.

  @addtogroup WMBUS_HAL_AES

  All the EFM/EZR devices do provide an AES hardware acceleration. This HAL
  module abstracts access to the EFM/EZR hardware for the Wireless M-Bus Stack.
  The implementations can be found in file `/src/target/`sf_hal_aes.c.
*/
/**@{*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/
#include "inc\pub\utils\wmbus_typedefs.h"
#include "em_cmu.h"
#include "em_aes.h"

/*==============================================================================
                            MACROS
==============================================================================*/

/*! Specifies the length of the key to be used with AES module by EFM/EZR
    devices.
    @warning This value should not be changed, unless you know what you're
    doing! */
#define EFM_AES_KEY_LEN     (16U)
/*! Specifies the length of encryption blocks to be processed by the AES module.
    @warning This value is fixed for AES and must not be changed! */
#define EFM_AES_BLOCK_LEN   (16U)

/*==============================================================================
                            VARIABLES
==============================================================================*/
/** Module global variable for storing the encryption key. */
static uint8_t gac_enkey[EFM_AES_KEY_LEN];

/*==============================================================================
                            FUNCTIONS
==============================================================================*/
/*============================================================================*/
/* wmbus_hal_aes_init() */
/*============================================================================*/
bool_t wmbus_hal_aes_init(void)
{
  MEMSET(gac_enkey, 0U, EFM_AES_KEY_LEN);
  CMU_ClockEnable (cmuClock_AES, true);
  return TRUE;
} /* wmbus_hal_aes_init */

/*============================================================================*/
/* wmbus_hal_aes_setKey() */
/*============================================================================*/
bool_t wmbus_hal_aes_setKey(const uint8_t* pc_key)
{
  bool_t b_ret = FALSE;

  if(pc_key)
  {
    MEMCPY(gac_enkey, pc_key, EFM_AES_KEY_LEN);
    b_ret = TRUE;
  } /* if */

  return b_ret;
} /* wmbus_hal_aes_setKey */

/*============================================================================*/
/* wmbus_hal_aes_cbcDecrypt() */
/*============================================================================*/
bool_t wmbus_hal_aes_cbcDecrypt(const uint8_t* pc_in, uint8_t* pc_out,
                                 uint16_t n_block, uint8_t* pc_iv)
{
  bool_t b_ret = FALSE; 
  uint8_t ac_dekey[EFM_AES_KEY_LEN];
  uint8_t ac_out[EFM_AES_BLOCK_LEN];

  if(pc_in && pc_out && pc_iv)
  {
    AES_DecryptKey128(ac_dekey, gac_enkey);
    AES_CBC128(ac_out, pc_in, EFM_AES_KEY_LEN, ac_dekey, pc_iv, 0);
    MEMCPY(pc_out, ac_out, EFM_AES_BLOCK_LEN);
    b_ret = TRUE;
  } /* if */
  
  return b_ret;  
} /* wmbus_hal_aes_cbcDecrypt */

/*============================================================================*/
/* wmbus_hal_aes_cbcEncrypt() */
/*============================================================================*/
bool_t wmbus_hal_aes_cbcEncrypt(const uint8_t* pc_in, uint8_t* pc_out,
                                 uint16_t n_block, uint8_t* pc_iv)
{
  bool_t b_ret = FALSE;
  uint8_t ac_out[EFM_AES_BLOCK_LEN];

  if(pc_in && pc_out && pc_iv)
  {
    AES_CBC128(ac_out, pc_in, EFM_AES_KEY_LEN, gac_enkey, pc_iv, 1);
    MEMCPY(pc_out, ac_out, EFM_AES_BLOCK_LEN);
    wmbus_hal_aes_cbcDecrypt(pc_out, ac_out,1, pc_iv);
    b_ret = TRUE;
  } /* if */ 
  

  return b_ret;
} /* wmbus_hal_aes_cbcEncrypt */

/*============================================================================*/
/* wmbus_hal_aes_encrypt() */
/*============================================================================*/
bool_t wmbus_hal_aes_encrypt(const uint8_t* pc_in, uint8_t* pc_out)
{
  return FALSE;
}

/**@}*/
#ifdef __cplusplus
}
#endif

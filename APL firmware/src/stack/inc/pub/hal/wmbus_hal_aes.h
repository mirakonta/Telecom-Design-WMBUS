#ifndef __WMBUS_HAL_AES_H__
#define __WMBUS_HAL_AES_H__

/**
  @file       wmbus_hal_aes.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      HAL module for hardware accelerated AES en-/decryption.

  @defgroup   WMBUS_HAL_AES WMBUS-HAL - Hardware accelerated AES
  
  This module defines the Hardware Abstraction Layer for the hardware
  accelerated Advanced Encryption Standard (AES).
*/
/**@{*/

/*==============================================================================
                         FUNCTION PROTOTYPES OF THE API
==============================================================================*/

/**
  @brief  Performs the initialization of the AES HAL module.
          This function usually will be called by wmbus_hal_init() and enables
          the AES HAL module to initialize the hardware.
  @return On successful initialization the function should return @c TRUE.
          Just in case the initialization wasn't possible for any reason, this
          function should return @c FALSE.
*/
bool_t wmbus_hal_aes_init(void);

/**
  @brief  Sets key for en-/decryption.
          Sets key to be used for any encryption or decryption procedure by the
          AES HAL module. Basically the key will be maintained by the stack and
          given to the AES HAL module for maintaing the underlying hardware.
          There is no need to call this function by user application.
  @param  pc_key    Pointer to the buffer which is holding the key.
  @return TRUE, if key was set successfully, FALSE otherwise
*/
bool_t wmbus_hal_aes_setKey(const uint8_t* pc_key);

/*!
  @brief  Encrypts a single block only.
          Encrypts a single block only, using the key that is currently stored
          within the HAL module. Block length for AES is fixed to 16 bytes.
  @param  pc_in     Pointer to the data to be encrypted.
  @param  pc_out    Pointer where to store the encrypted data.
  @return Returns @c TRUE if data has been encrypted successfully. In case of
          any problem (e.g. missing key) it'll return @c FALSE.
*/
bool_t wmbus_hal_aes_encrypt(const uint8_t* pc_in, uint8_t*  pc_out);

/**
  @brief  Decrypts a single block only.
          Decrypts a single block only, using the key that is currently stored
          within the HAL module. Block length for AES is fixed to 16 bytes.
  @param  pc_in     Pointer containing data to be decrypted.
  @param  pc_out    Pointer where to store the decrypted data.
  @return Returns @c TRUE if data has been decrypted successfully. In case of
          any problem (e.g. missing key) it'll return @c FALSE.
*/
bool_t wmbus_hal_aes_decrypt(const uint8_t* pc_in, uint8_t* pc_out);

/**
  @brief  Performs _CBC encryption_ on a given number of blocks.
          This function performs _CBC encryption_ on a given number of blocks,
          using the given initialization vector (iv).
  @param  pc_in     Pointer to the data to be encrypted.
  @param  pc_out    Pointer where to store the encrypted data.
  @param  n_block   Number of blocks to be encrypted.
  @param  pc_iv     Buffer holding 128 bit initialization vector to be used.
  @return Returns @c TRUE if data has been encrypted successfully. In case of
          any problem (e.g. missing key) it'll return @c FALSE.
*/
bool_t wmbus_hal_aes_cbcEncrypt(const uint8_t* pc_in, uint8_t* pc_out,
                                 uint16_t n_block, uint8_t* pc_iv);

/**
  @brief  Performs _CBC decryption_ on a given number of blocks.
          This function performs _CBC decryption_ on a given number of blocks,
          using the given initialization vector (iv).
  @param  pc_in     Pointer to the data to be decrypted.
  @param  pc_out    Pointer where to store the decrypted data.
  @param  n_block   Number of blocks to be decrypted.
  @param  pc_iv     Buffer holding 128 bit initialization vector to be used.
  @return Returns @c TRUE if data has been decrypted successfully. In case of
          any problem (e.g. missing key) it'll return @c FALSE.
*/
bool_t wmbus_hal_aes_cbcDecrypt(const uint8_t* pc_in, uint8_t* pc_out,
                                 uint16_t n_block, uint8_t* pc_iv);

/**
  @brief  Performs _CTR encryption_ on a given number of blocks.
          This function performs _CTR encryption_ on a given number of blocks,
          using the given initialization vector (iv).
  @param  pc_in     Pointer to the data to be encrypted.
  @param  pc_out    Pointer where to store the encrypted data.
  @param  n_block   Number of blocks to be encrypted.
  @param  pc_iv     Buffer holding 128 bit initialization vector to be used.
  @return Returns @c TRUE if data has been encrypted successfully. In case of
          any problem (e.g. missing key) it'll return @c FALSE.
*/
bool_t wmbus_hal_aes_ctrEncrypt(const uint8_t* pc_in, uint8_t* pc_out,
                                 uint8_t c_len, uint8_t* pc_iv);

/**
  @brief  Performs _CTR decryption_ on a given number of blocks.
          This function performs _CTR decryption_ on a given number of blocks,
          using the given initialization vector (iv).
  @param  pc_in     Pointer to the data to be decrypted.
  @param  pc_out    Pointer where to store the decrypted data.
  @param  n_block   Number of blocks to be decrypted.
  @param  pc_iv     Buffer holding 128 bit initialization vector to be used.
  @return Returns @c TRUE if data has been decrypted successfully. In case of
          any problem (e.g. missing key) it'll return @c FALSE.
*/
bool_t wmbus_hal_aes_ctrDecrypt(const uint8_t* pc_in, uint8_t* pc_out,
                                 uint8_t c_len, uint8_t* pc_iv);

/**@}*/
#endif /* __WMBUS_HAL_AES_H__ */

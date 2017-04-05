#ifndef MGH_HEADER_AES_256_WRAPPER_ENC_H
#define MGH_HEADER_AES_256_WRAPPER_ENC_H

#include <openssl/aes.h>

////
/// Functions
//


/**
 * A wrapper to an AES encrypt/decrypt block
 * @param  in   Pointer to the incoming data (16 bytes)
 * @param  out  Pointer to the outgoing data (16 bytes)
 * @param  key  Pointer to the 256-bit (32-byte) key
 *
 * Using key, aes_256_wrapper will <mode> 16 bytes located at in and store
 * the result at out. <mode> is either encrypt if 0 or decrypt if 1.
 */
int aes_256_wrapper_enc(const uint8_t *in, uint8_t *out, const uint8_t *key);


#endif  /* MGH_HEADER_AES_256_WRAPPER_ENC_H */

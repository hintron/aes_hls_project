#ifndef MGH_HEADER_AES_256_WRAPPER_H
#define MGH_HEADER_AES_256_WRAPPER_H

#include <openssl/aes.h>

////
/// Defines
//

#define ENCRYPT_MODE_MGH 0
#define DECRYPT_MODE_MGH 1

////
/// Functions
//


/**
 * A wrapper to an AES encrypt/decrypt block
 * @param  in   Pointer to the incoming data (16 bytes)
 * @param  out  Pointer to the outgoing data (16 bytes)
 * @param  key  Pointer to the 256-bit (32-byte) key
 * @param  mode 0 means encrypt, 1 means decrypt
 *
 * Using key, aes_256_wrapper will <mode> 16 bytes located at in and store
 * the result at out. <mode> is either encrypt if 0 or decrypt if 1.
 */
int aes_256_wrapper(const uint8_t *in, uint8_t *out, const uint8_t *key, int mode);


#endif  /* MGH_HEADER_AES_256_WRAPPER_H */

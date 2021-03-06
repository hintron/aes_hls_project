#include <stdio.h>
#include <openssl/aes.h>
#include "aes_256_wrapper.h"

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
int aes_256_wrapper(const uint8_t in[16], uint8_t out[16], const uint8_t key[32], int mode) {

    // TODO: Check to make sure incoming data is good

    AES_KEY aes_key_schedule;
    int response;

    if(mode == ENCRYPT_MODE_MGH){
        // Set encryption key and generate all round keys
        response = AES_set_encrypt_key(key, 256, &aes_key_schedule);
        // Encrypt a single plaintext block
        AES_encrypt(in, out, &aes_key_schedule);
    }
    else {
        // Set decryption key and generate all round keys
        response = AES_set_decrypt_key(key, 256, &aes_key_schedule);
        // Decrypt a single ciphertext block
        AES_decrypt(in, out, &aes_key_schedule);
    }

    return response;
}
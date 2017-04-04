// This is a testbench file that will use aes_wrapper
// HLS needs a top-level function (inside aes_256_wrapper) for source,
// and main for the test bench.
#include <stdio.h>
#include <openssl/aes.h>
#include "aes_256_wrapper.h"

// This code is compiled in the Developer Command Prompt for VS2015 with the following command:
// cl /EHsc /I C:\crypto\boringssl\include aes_testbench.cpp crypto.lib /link /LIBPATH:C:\crypto\boringssl\build\crypto /verbose:lib /NODEFAULTLIB:MSVCRTD

int main(int argc, char const *argv[]) {

    printf("========================================================\n");
    printf("AES Test Bench:\n");
    printf("========================================================\n");
    printf("\n");


    ////
    /// Set up keys and data
    //

    // Key
    // deadba1100000000deadbeef00000000deadface00000000deadfeed00000000
    const uint8_t key[32] = {
        0xdeU, 0xadU, 0xbaU, 0x11U, 0x00U, 0x00U, 0x00U, 0x00U,
        0xdeU, 0xadU, 0xbeU, 0xefU, 0x00U, 0x00U, 0x00U, 0x00U,
        0xdeU, 0xadU, 0xfaU, 0xceU, 0x00U, 0x00U, 0x00U, 0x00U,
        0xdeU, 0xadU, 0xfeU, 0xedU, 0x00U, 0x00U, 0x00U, 0x00U,
    };

    // Data
    const uint8_t plaintext[16] = {
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a',0x0aU,
    };
    uint8_t ciphertext[16];
    uint8_t plaintext_reconstructed[16];

    ////
    /// Print out key to use
    //

    printf("Key: ");
    for (int i = 0; i < 32; ++i) {
        printf("%02x", key[i]);
    }
    printf("\n");

    ////
    /// Encrypt, then decrypt data
    //

    int response_encrypt;
    int response_decrypt;

    response_encrypt = aes_256_wrapper(plaintext, ciphertext, key, ENCRYPT_MODE_MGH);
    response_decrypt = aes_256_wrapper(ciphertext, plaintext_reconstructed, key, DECRYPT_MODE_MGH);

    ////
    /// Print out results
    //
    printf("Plaintext (ascii): ");
    for (int j = 0; j < 16; ++j) {

        if(plaintext[j] == 0x0aU){
            // Print the LF character
            printf("<LF>");
        } else {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");

    printf("Encrypted with response %d\n", response_encrypt);
    printf("Ciphertext (hex): ");
    for (int j = 0; j < 16; ++j) {
        printf("%02x", ciphertext[j]);
    }
    printf("\n");

    printf("Decrypted with response %d\n", response_decrypt);
    printf("Reconstructed Plaintext (ascii): ");
    for (int j = 0; j < 16; ++j) {
        if(plaintext_reconstructed[j] == 0x0aU){
            // Print the LF character
            printf("<LF>");
        } else {
            printf("%c", plaintext_reconstructed[j]);
        }
    }
    printf("\n");

    return 0;
}
// This is a testbench file that will use aes_wrapper
// HLS needs a top-level function (inside aes_256_wrapper) for source,
// and main for the test bench.

//Gough: This has been modified to only test the encrypt functions.

#include <stdio.h>
#include <openssl/aes.h>
#include "aes_256_wrapper_enc.h"

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
    const uint8_t plaintext[160] = {
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a',0x0aU,
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','1',
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','2',
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','3',
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','4',
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','5',
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','6',
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','7',
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','8',
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a','9',
    };
    uint8_t ciphertext[160];

    ////
    /// Print out key to use
    //

    printf("Key: ");
    for (int i = 0; i < 32; ++i) {
        printf("%02x", key[i]);
    }
    printf("\n");

    ////
    /// Encrypt data
    //

    int response_encrypt;
    //int response_decrypt;

    response_encrypt = aes_256_wrapper_enc(plaintext, ciphertext, key);

    ////
    /// Print out results
    //
    printf("Plaintext (ascii):\n");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 16; ++j) {
            // printf("(%d)", i*16+j);
            if(plaintext[i*16+j] == 0x0aU){
                // Print the LF character
                printf("<LF>");
            } else {
                printf("%c", plaintext[i*16+j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Encrypted with response %d\n", response_encrypt);
    printf("Ciphertext (hex):\n");
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 16; ++j) {
            printf("%02x", ciphertext[i*16+j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

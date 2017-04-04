// This is a standalone file demonstrating how to directly use an AES block from BoringSSL
#include <stdio.h>
#include <openssl/aes.h>

// This code is compiled in the Developer Command Prompt for VS2015 with the following command:
// cl /EHsc /I C:\crypto\boringssl\include aes_test.cpp crypto.lib /link /LIBPATH:C:\crypto\boringssl\build\crypto /verbose:lib /NODEFAULTLIB:MSVCRTD
int main(int argc, char const *argv[]) {

    printf("========================================================\n");
    printf("AES Test!:\n");
    printf("========================================================\n");
    printf("\n");

    AES_KEY aes_key_struct;

    // 4 lines x 8 bytes/line * 8 bits/bytes - 256 bits
    const uint8_t key_zeroes[32] = {
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
        0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U,
    };


    // deadba1100000000deadbeef00000000deadface00000000deadfeed00000000
    const uint8_t key_hlsproject[32] = {
        0xdeU, 0xadU, 0xbaU, 0x11U, 0x00U, 0x00U, 0x00U, 0x00U,
        0xdeU, 0xadU, 0xbeU, 0xefU, 0x00U, 0x00U, 0x00U, 0x00U,
        0xdeU, 0xadU, 0xfaU, 0xceU, 0x00U, 0x00U, 0x00U, 0x00U,
        0xdeU, 0xadU, 0xfeU, 0xedU, 0x00U, 0x00U, 0x00U, 0x00U,
    };


    printf("Key:\n");
    printf("========================================================\n");

    // printf("Zero Key:\n");
    // for (int i = 0; i < 32; ++i) {
    //     printf("%02x", key_zeroes[i]);
    // }
    // printf("\n");
    // printf("HLS Project Key:\n");
    for (int i = 0; i < 32; ++i) {
        printf("%02x", key_hlsproject[i]);
    }
    printf("\n");
    printf("\n");


    printf("Encrypting ciphertext and reconstructing original data:\n");
    printf("========================================================\n");

    // Set encryption key and generate all the round keys
    int response = AES_set_encrypt_key(key_hlsproject, 256, &aes_key_struct);
    printf("Set aes encrypt key with response %d\n", response);

    const uint8_t plaintext[16] = {
        'C','l','a','s','s','i','f','i','e','d',' ','D','a','t','a',0x0aU,
    };
    uint8_t ciphertext[16];

    // Encrypt a single plaintext block
    AES_encrypt(plaintext, ciphertext, &aes_key_struct);

    printf("Plaintext:\n");
    for (int j = 0; j < 16; ++j) {
        printf("%c", plaintext[j]);
    }
    printf("\n");

    printf("Ciphertext:\n");
    for (int j = 0; j < 16; ++j) {
        printf("%02x", ciphertext[j]);
    }
    printf("\n");
    // for (int j = 0; j < 16; ++j) {
    //     printf("%02x|", ciphertext[j]);
    // }
    // printf("\n");
    printf("\n");


    printf("Decrypting ciphertext and reconstructing original data:\n");
    printf("========================================================\n");
    // Decrypt the ciphertext back into plaintext to prove it is the same
    response = AES_set_decrypt_key(key_hlsproject, 256, &aes_key_struct);
    printf("Set aes decrypt key with response %d\n", response);

    uint8_t plaintext_reconstructed[16];
    AES_decrypt(ciphertext, plaintext_reconstructed, &aes_key_struct);

    printf("Ciphertext:\n");
    for (int j = 0; j < 16; ++j) {
        printf("%02x", ciphertext[j]);
    }
    printf("\n");

    printf("Reconstructed Plaintext:\n");
    for (int j = 0; j < 16; ++j) {
        printf("%c", plaintext_reconstructed[j]);
    }
    printf("\n");

    return 0;
}
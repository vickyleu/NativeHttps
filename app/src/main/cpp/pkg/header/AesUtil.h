//
// Created by vicky on 2017.06.30.
//

#ifndef NATIVEHTTPS_AESUTIL_H
#define NATIVEHTTPS_AESUTIL_H

#include <android/log.h>
#include <stdlib.h>
#include <stdint.h>
#include <jni.h>
#include "base64.h"

// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC enables AES128 encryption in CBC-mode of operation and handles 0-padding.
// ECB enables the basic ECB 16-byte block algorithm. Both can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC
#define CBC 1
#endif

#ifndef ECB
#define ECB 1
#endif
static const unsigned char HEX[16] = {0x10, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
                                      0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
static const uint8_t AES_KEY[] = "1234567890abcdef";
#if defined(ECB) && ECB

JNIEXPORT void JNICALL
AES128_ECB_encrypt(uint8_t *input, const uint8_t *key, uint8_t *output);

JNIEXPORT void JNICALL
AES128_ECB_decrypt(uint8_t *input, const uint8_t *key, uint8_t *output);

JNIEXPORT char *JNICALL
AES_128_ECB_PKCS5Padding_Encrypt(const char *in, const uint8_t *key);

JNIEXPORT char *JNICALL
AES_128_ECB_PKCS5Padding_Decrypt(const char *in, const uint8_t *key);

int *findPaddingIndex(uint8_t *str, size_t length);

#endif // #if defined(ECB) && ECB


#if defined(CBC) && CBC

void AES128_CBC_encrypt_buffer(uint8_t *output, uint8_t *input, uint32_t length, const uint8_t *key,
                               const uint8_t *iv);

void AES128_CBC_decrypt_buffer(uint8_t *output, uint8_t *input, uint32_t length, const uint8_t *key,
                               const uint8_t *iv);

#endif // #if defined(CBC) && CBC
#endif //NATIVEHTTPS_AESUTIL_H
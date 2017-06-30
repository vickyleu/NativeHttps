//
// Created by vicky on 2017.06.30.
//

#ifndef NATIVEHTTPS_CRYPTOUTILS_H
#define NATIVEHTTPS_CRYPTOUTILS_H
#ifdef __cplusplus
extern "C" {
#endif
#define LEN 128
#define MSG_LEN 128

int aes_encrypt(char *in, char *key, char *out);

int aes_decrypt(char *in, char *key, char *out);
#ifdef __cplusplus
}
#endif
#endif //NATIVEHTTPS_CRYPTOUTILS_H

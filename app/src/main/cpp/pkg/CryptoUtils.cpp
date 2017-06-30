#include <openssl/aes.h>
#include <cstring>
#include "header/CryptoUtils.h"

//
// Created by vicky on 2017.06.30.
//

int aes_encrypt(char *in, char *key, char *out) {
    AES_KEY aes;
    int len = strlen(in), en_len = 0;
    if (!in || !key || !out) return 0;

    if (AES_set_encrypt_key((unsigned char *) key, 128, &aes) < 0) {
        return 0;
    }

    while (en_len < len) {
        AES_encrypt((unsigned char *) in, (unsigned char *) out, &aes);
        in += AES_BLOCK_SIZE;
        out += AES_BLOCK_SIZE;
        en_len += AES_BLOCK_SIZE;
    }
    return 1;
}

int aes_decrypt(char *in, char *key, char *out) {
    AES_KEY aes;

    int len = MSG_LEN, en_len = 0;
    for (size_t i = MSG_LEN - 1; !in[i]; i--)//修改计算in长度方式，以防出现加密内容包含'\0'的情况
    {

        len = i;
    }

    if (!in || !key || !out) return 0;

    if (AES_set_decrypt_key((unsigned char *) key, 128, &aes) < 0) {
        return 0;
    }

    while (en_len < len) {
        AES_decrypt((unsigned char *) in, (unsigned char *) out, &aes);
        in += AES_BLOCK_SIZE;
        out += AES_BLOCK_SIZE;
        en_len += AES_BLOCK_SIZE;
    }
    return 1;
}

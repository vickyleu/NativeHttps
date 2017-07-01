//
// Created by vicky on 2017.06.30.
//

#ifndef NATIVEHTTPS_BASE64_H
#define NATIVEHTTPS_BASE64_H

#include <stddef.h>
#include <jni.h>

struct MyString {
    char *data;
    int length;
};
static const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

JNIEXPORT char *JNICALL
base64_encode(const char *var1, int var2);

JNIEXPORT char * JNICALL
base64_decode(const char *var1, int var2);

char find_pos(char var);

#endif //NATIVEHTTPS_BASE64_H

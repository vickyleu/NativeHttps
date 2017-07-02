//
// Created by vicky on 2017.06.30.
//

#ifndef NATIVEHTTPS_BASE64_H
#define NATIVEHTTPS_BASE64_H

#include <stddef.h>
#include <jni.h>
#ifdef __cplusplus
extern "C" {
#endif
struct MyString {
    char *data;
    int length;
};
static const char base[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

JNIEXPORT char *JNICALL
base64_encode(const char *var1, int var2);

JNIEXPORT char * JNICALL
base64_decode(const char *var1, int var2);

JNIEXPORT char * JNICALL
base64_decode2(const char* str);
JNIEXPORT char * JNICALL
base64_encode2(const char* str);

char* translate_3to_4_3(char a, char b, char c);
char* translate_3to_4_2(char a, char b);
char* translate_3to_4_1(char a);
char num2base64char(char n);
char* translate_3to_4_4(char a, char b, char c, char d);
char base64char2num(char b);


char find_pos(char var);
#ifdef __cplusplus
}
#endif
#endif //NATIVEHTTPS_BASE64_H

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


//char* translate3to4(char a,char b,char c);
//char* translate3to4(char a,char b);
//char* translate3to4(char a);
//char num2base64char(char n);
char* translate4to3(char a,char b,char c,char d);
char base64char2num(char b);
JNIEXPORT char * JNICALL
base64_decode2(const char* str);

char find_pos(char var);
#ifdef __cplusplus
}
#endif
#endif //NATIVEHTTPS_BASE64_H

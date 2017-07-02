//
// Created by Administrator on 2016/12/14.
//
#ifndef MES_STRING_UTIL_H
#define MES_STRING_UTIL_H

#include <iostream>
#include "log.h"

using namespace std;
static const char *const JNI_UTIL = "jni/http/JniUtil";
static const char *const CPP_PROXY = "jni/http/CppProxy";
static const char *const NATIVE_CRASH_HANDLER = "jni/http/Exception/NativeCrashHandler";
static const char *const JSON_OBJECT ="org/json/JSONObject";
static const char *const JSON_ARRAY ="org/json/JSONArray";


static void trim(char *str);
int ascii2hex(char* ascii, char* hex);
jstring char2Jstring(JNIEnv* env, char *src);
jstring cToJstringutf(JNIEnv *env, const char *pat);
jstring cTojstringbk(JNIEnv *env, char *pat);

const char *ss(string pJstring);

char *string2char(string pJstring);

const char *ch2cs(char *ch);

std::string Jstring2string(JNIEnv *env, jstring jstr);

jstring Str2Jstring(JNIEnv *env, const char *pStr);

string ch2str(const char *cs);
char *currentTime();
char *jstring2char(JNIEnv *env, jstring jstr);

string double2String(double value);
string int2String(int value);

string tm2String();

#endif //MES_STRING_UTIL_H

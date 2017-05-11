//
// Created by Administrator on 2017/5/11.
//

#ifndef NATIVEHTTPS_NATIVE_H
#define NATIVEHTTPS_NATIVE_H

#include <jni.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#ifdef __cplusplus
extern "C" {
#endif
jbyteArray Java_jni_http_CppProxy_HmacSha256(JNIEnv *env, jobject obj, jbyteArray content);

jstring toBuildJson(JNIEnv *env, jobject thiz, jint id, jstring name);

jstring Java_jni_http_CppProxy_httpGET(JNIEnv *env, jclass type, jstring url_, jstring params_,
                                       jobjectArray header_);

jstring Java_jni_http_CppProxy_httpPOST(JNIEnv *env, jclass type, jstring url_, jobject params,
                                        jstring header_);

jstring Java_jni_http_CppProxy_httpFromJNITest(JNIEnv *env, jclass type, jobject /* this */);

#ifdef __cplusplus
}
#endif
#endif //NATIVEHTTPS_NATIVE_H

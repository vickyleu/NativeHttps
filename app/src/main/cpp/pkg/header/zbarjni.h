//
// Created by vicky on 2017.06.09.
//

#ifndef NATIVEHTTPS_ZBARJNI_H
#define NATIVEHTTPS_ZBARJNI_H



#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_SymbolSet_init(JNIEnv *env, jclass cls);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_SymbolSet_destroy(JNIEnv *env, jobject obj, jlong peer);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_SymbolSet_size(JNIEnv *env, jobject obj);

JNIEXPORT jlong JNICALL
Java_jni_http_Qrcode_zbar_SymbolSet_firstSymbol(JNIEnv *env, jobject obj, jlong peer);


JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Symbol_init(JNIEnv *env, jclass cls);
JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Symbol_destroy(JNIEnv *env, jobject obj, jlong peer);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getType(JNIEnv *env, jobject obj, jlong peer);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getConfigMask(JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getModifierMask(JNIEnv *env, jobject obj);

JNIEXPORT jstring JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getData(JNIEnv *env, jobject obj);

JNIEXPORT jstring JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getDataBytes(JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getQuality(JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getCount(JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getLocationSize(JNIEnv *env, jobject obj, jlong peer);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getLocationX(JNIEnv *env, jobject obj, jlong peer, jint idx);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getLocationY(JNIEnv *env, jobject obj, jlong peer, jint idx);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getOrientation(JNIEnv *env, jobject obj);

JNIEXPORT jlong JNICALL
Java_jni_http_Qrcode_zbar_Symbol_getComponents(JNIEnv *env, jobject obj, jlong peer);

JNIEXPORT jlong JNICALL
Java_jni_http_Qrcode_zbar_Symbol_next(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_init(JNIEnv *env, jclass cls);

JNIEXPORT jlong JNICALL
Java_jni_http_Qrcode_zbar_Image_create(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_destroy(JNIEnv *env, jobject obj, jlong peer);

JNIEXPORT jlong JNICALL
Java_jni_http_Qrcode_zbar_Image_convert(JNIEnv *env, jobject obj, jlong peer, jstring format);

JNIEXPORT jstring JNICALL
Java_jni_http_Qrcode_zbar_Image_getFormat(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_setFormat(JNIEnv *env, jobject obj, jstring format);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Image_getSequence(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_setSequence(JNIEnv *env, jobject obj, jint seq);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Image_getWidth(JNIEnv *env, jobject obj);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_Image_getHeight(JNIEnv *env, jobject obj);

JNIEXPORT jobject JNICALL
Java_jni_http_Qrcode_zbar_Image_getSize(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_setSize__II(JNIEnv *env, jobject obj, jint width, jint height);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_setSize___3I(JNIEnv *env, jobject obj, jintArray size);

JNIEXPORT jobject JNICALL
Java_jni_http_Qrcode_zbar_Image_getCrop(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_setCrop__IIII(JNIEnv *env, jobject obj, jint x, jint y, jint w,
                                              jint h);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_setCrop___3I(JNIEnv *env, jobject obj, jintArray crop);

JNIEXPORT jobject JNICALL
Java_jni_http_Qrcode_zbar_Image_getData(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_setData___3B(JNIEnv *env, jobject obj, jbyteArray data);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_Image_setData___3I(JNIEnv *env, jobject obj, jintArray data);

JNIEXPORT jlong JNICALL
Java_jni_http_Qrcode_zbar_Image_getSymbols(JNIEnv *env, jobject obj, jlong peer);


JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_ImageScanner_init(JNIEnv *env, jclass cls);

JNIEXPORT jlong JNICALL
Java_jni_http_Qrcode_zbar_ImageScanner_create(JNIEnv *env, jobject obj);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_ImageScanner_destroy(JNIEnv *env, jobject obj, jlong peer);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_ImageScanner_setConfig(JNIEnv *env, jobject obj, jint symbology,
                                                 jint config, jint value);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_ImageScanner_parseConfig(JNIEnv *env, jobject obj, jstring cfg);

JNIEXPORT void JNICALL
Java_jni_http_Qrcode_zbar_ImageScanner_enableCache(JNIEnv *env, jobject obj, jboolean enable);

JNIEXPORT jlong JNICALL
Java_jni_http_Qrcode_zbar_ImageScanner_getResults(JNIEnv *env, jobject obj, jlong peer);

JNIEXPORT jint JNICALL
Java_jni_http_Qrcode_zbar_ImageScanner_scanImage(JNIEnv *env, jobject obj, jobject image);

#ifdef __cplusplus
}
#endif
#endif //NATIVEHTTPS_ZBARJNI_H

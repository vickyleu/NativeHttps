//
// Created by Administrator on 2017/5/11.
//
#include <jni.h>
#include "Utils/CDebuger.h"

void getAbi(JNIEnv *pEnv);

#ifdef __cplusplus

void getAbi(JNIEnv *env) {
    env->GetVersion();
}

extern "C" {
#endif
jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    JNIEnv *env = NULL;
    jint result = -1;
    if ((vm)->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
//    nativeCrashHandler_onLoad(vm);
    init(env);
    getAbi(env);
    printMsg("JNI启动");
//    free(&env);
    // 返回jni的版本
    return JNI_VERSION_1_6;
}
#ifdef __cplusplus
}
#endif
//
// Created by Administrator on 2017/5/11.
//
#include <jni.h>
#include "Utils/CDebuger.h"
#include "Exception/NativeCrashHandler.h"

#ifdef __cplusplus
extern "C" {
#endif
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    printMsg("JNI启动");
    JNIEnv *env = NULL;
    jint result = -1;
    if ((vm)->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }
    nativeCrashHandler_onLoad(vm);
    // 返回jni的版本
    return JNI_VERSION_1_6;
}
#ifdef __cplusplus
}
#endif
//
// Created by Administrator on 2017/4/1.
//
#include "../Utils/CDebuger.h"
#include "../Utils/StringUtil.h"

bool isDebug = 0;

void printMsg(char const *log) {
    if (isDebug) {
        LOGE("%s", log);
    }
}

void printMsgMerge(char const *log, char const *log2) {
    if (isDebug) {
        LOGE("%s%s", log, log2);
    }
}

void printMsgMerge(char const *log, char const *log2, char const *log3) {
    if (isDebug) {
        LOGE("%s%s%s", log, log2, log3);
//        free(&log);
//        log=NULL;
    }
}

void printMsg1(const char *pstring, jstring pJstring, JNIEnv *pEnv) {
    if (isDebug) {
        char *VAR1 = string2char(pstring);
        char *VAR2 = jstring2char(pEnv, pJstring);
        LOGE("%s", strcat(VAR1, VAR2));
    }
}

void printMsg2(const char *pstring, string pJstring) {
    if (isDebug) {
        char *VAR1 = string2char(pstring);
        char *VAR2 = string2char(pJstring);
        LOGE("%s", strcat(VAR1, VAR2));
    }
}


bool log_for_debug(JNIEnv *env) {
    jclass my_class = env->FindClass(CPP_PROXY);
    if (my_class == NULL) {
        LOGE("混淆CppProxy出错");
        return false;
    }
    jfieldID fieldID = env->GetStaticFieldID(my_class, "isDebug", "Z");
    jboolean debug = env->GetStaticBooleanField(my_class, fieldID);
    isDebug = debug;
    LOGE("哎哟");
    return isDebug;
}

void init(JNIEnv *env) {
    //todo 本地方法读取不到java类,后续解决
    if (env == NULL)
        return;
    bool logeEnable = log_for_debug(env);
    isDebug = logeEnable;
//    globalVar = logeEnable;
    if (!isDebug) {
        printMsg("log模式没有开启");
    } else {
        printMsg("log模式已经开启");
    }
}




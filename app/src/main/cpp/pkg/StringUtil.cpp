//
// Created by Administrator on 2017/4/7.
//
//

#include <malloc.h>
#include "../Utils/log.h"
#include "../Utils/StringUtil.h"

typedef unsigned char BYTE;

/*class StringFormatException : public exception {
    virtual const char *what() const throw() {
        return "String Format not a valid arguments";
    }
} formatException;*/

static void trim(char *str) {
    char *p = str + strlen(str) - 1;
    while (p > str) {
        if (*p == '\r') {
            *p = '\0';
        } else if (*p == '\n') {
            *p = '\0';
        } else {
            break;
        }
    }
}

jstring char2Jstring(JNIEnv *env, char *src) {
    jsize len = (jsize) strlen(src);
    jclass clsstring = (env)->FindClass("java/lang/String");
    jstring strencode = (env)->NewStringUTF("UTF-8");
    jmethodID mid = (env)->GetMethodID(clsstring, "<init>", "([BLjava/lang/String;)V");
    jbyteArray barr = (env)->NewByteArray(len);
    (env)->SetByteArrayRegion(barr, 0, len, (jbyte *) src);
    jstring ret = (jstring) (env)->NewObject(clsstring, mid, barr, strencode);
    env->DeleteLocalRef(clsstring);
    return ret;
}


jstring cToJstringutf(JNIEnv *env, const char *pat) {
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>",
                                        "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    jstring encoding = env->NewStringUTF("utf-8");
    return (jstring) env->NewObject(strClass, ctorID, bytes, encoding);
}

jstring cTojstringbk(JNIEnv *env, char *pat) {
    jclass strClass = env->FindClass("java/lang/String");
    jmethodID ctorID = env->GetMethodID(strClass, "<init>",
                                        "([BLjava/lang/String;)V");
    jbyteArray bytes = env->NewByteArray(strlen(pat));
    env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte *) pat);
    jstring encoding = env->NewStringUTF("gbk");
    return (jstring) env->NewObject(strClass, ctorID, bytes, encoding);
}


const char *ss(string pJstring) {
    const char *c_s = pJstring.c_str();
    return c_s;
}

char *string2char(string str) {
    size_t len = str.length();
    char *c= (char *) malloc(len + 1);
    strcpy(c, str.c_str());
    return c;
}


const char *ch2cs(char *ch) {
    string s(ch);
    return ss(s);
}

string ch2str(const char *cs) {
    string s(cs);
    return s;
}

int ascii2hex(char *ascii, char *hex) {
    int i, len = strlen(ascii);
    char chHex[] = "0123456789ABCDEF";

    for (i = 0; i < len; i++) {
        hex[i * 3] = chHex[((BYTE) ascii[i]) >> 4];
        hex[i * 3 + 1] = chHex[((BYTE) ascii[i]) & 0xf];
        hex[i * 3 + 2] = ' ';
    }

    hex[len * 3] = '\0';

    return len * 3;
}


/**

* 工具方法

* 作用: 把java中的string 转化成一个c语言中的char数组

* 接受的参数 envjni环境的指针

* jstr 代表的是要被转化的java的string 字符串

* 返回值 : 一个c语言中的char数组的首地址 (char 字符串)

*/
char *jstring2char(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    if (jstr == NULL) {
        return string2char("");
    }
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = (env)->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc((size_t) (alen + 2));
        memcpy(rtn, ba, (size_t) alen);
        rtn[alen] = 0;

    }

    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}


string double2String(double value) {
    char buffer[20];
    sprintf(buffer, "%f", value);
    string str = buffer;
    return str;
}

string int2String(int value) {
    char buffer[20];
    sprintf(buffer, "%d", value);
    string str = buffer;
    return str;
}

char *currentTime() {
    return string2char(tm2String());
}

/**
 * 把java的string转化成c的字符串
 */
string Jstring2string(JNIEnv *env, jstring jstr) {
    char *rtn = nullptr;
    jclass clsstring = env->FindClass("java/lang/String");  //String
    jstring strencode = env->NewStringUTF("GB2312"); //"gb2312"
    jmethodID mid = env->GetMethodID(clsstring, "getBytes",
                                     "(Ljava/lang/String;)[B"); //getBytes(Str);
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid,
                                                         strencode); // String .getByte("GB2312");
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc((size_t) (alen + 2));         //"\0"
        memcpy(rtn, ba, (size_t) alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);  //释放内存空间
    string var;
    if (rtn!=NULL){
        var=ch2str(rtn);
    }
    return var;
}

/**
 * C字符串转java字符串
 */
jstring Str2Jstring(JNIEnv *env, const char *pStr) {
    int strLen = strlen(pStr);
    jclass jstrObj = env->FindClass("java/lang/String");
    jmethodID methodId = env->GetMethodID(jstrObj, "<init>", "([BLjava/lang/String;)V");
    jbyteArray byteArray = env->NewByteArray(strLen);
    jstring encode = env->NewStringUTF("utf-8");
    env->SetByteArrayRegion(byteArray, 0, strLen, (jbyte *) pStr);
    return (jstring) env->NewObject(jstrObj, methodId, byteArray, encode);
}


/**
 *
 * @param time1  time_t 当前时间long
 * @return  转成本地时间格式字符串
 */
string tm2String() {
    time_t now = time(NULL);
    tm *value = localtime(&now);
    char buffer[40];
    strftime(buffer, sizeof(buffer), "%Y年%m月%d日 %H时%M分%S秒", value);
    string str(buffer);
//    free(value);
    return str;
}

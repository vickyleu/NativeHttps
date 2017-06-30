//
// Created by Administrator on 2017/5/11.
//

#ifndef NATIVEHTTPS_NATIVE_H
#define NATIVEHTTPS_NATIVE_H

#include <jni.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <string>
#include "../../Utils/CDebuger.h"
#include "../../Utils/StringUtil.h"
#include "../../network/web_task.h"
#include "../../../../../jni/libjsoncpp/json.h"
#include "../../Utils/JsonUtil.h"

#ifdef __cplusplus
extern "C" {
#endif

jbyteArray Java_jni_http_CppProxy_HmacSha256(JNIEnv *env, jobject obj, jbyteArray content);

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
jstring Java_jni_http_CppProxy_AesDecryptUnwork(JNIEnv *env, jclass type, jstring cipher,jstring key);
jstring Java_jni_http_CppProxy_AesEncryptUnwork(JNIEnv *env, jclass type, jstring plainText,jstring key);
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

jstring Java_jni_http_CppProxy_AesEncrypt(JNIEnv *env, jobject instance, jstring str_);
jstring Java_jni_http_CppProxy_AesDecrypt(JNIEnv *env, jobject instance, jstring str_);



int aes_encrypt(char *in, char *key, char *out);
int aes_decrypt(char *in, char *key, char *out);
jstring toBuildJson(JNIEnv *env, jobject thiz, jint id, jstring name);

jstring Java_jni_http_CppProxy_httpGET(JNIEnv *env, jclass type, jstring url_, jstring params_,
                                       jobjectArray header_);

jstring Java_jni_http_CppProxy_httpPOST(JNIEnv *env, jclass type, jstring url_, jobject params,
                                        jstring header_);

jstring Java_jni_http_CppProxy_httpFromJNITest(JNIEnv *env, jclass type, jobject /* this */);

std::string nativeHttpGet(JNIEnv *env, std::string url, std::string params) {
    if (url == "") {
        return "URL请求不正确";
    }
    printMsg("开始打印");
    jclass jniUtil = env->FindClass(JNI_UTIL);
    jmethodID checkUrl = env->GetStaticMethodID(jniUtil, "checkUrl", "(Ljava/lang/String;)Z");
    char *uc = string2char(url);
    jstring url_ = env->NewStringUTF(uc);
    bool valid = env->CallStaticBooleanMethod(jniUtil, checkUrl, url_);
    env->ReleaseStringUTFChars(url_, uc);
    if (!valid) {
        printMsg("Url正则不匹配");
        return "Url正则不匹配";
    } else {
        printMsg("Url正则匹配");
    }

    //GET请求
    WebTask task;
    if (strcmp(string2char(params), "") != 0) {
        url = strcat(string2char(url), "?");
        url = strcat(string2char(url), string2char(params));
    }
    printMsg1("使用的请求地址是:", url_, env);
    printMsg2("使用的请求方法是:", "GET");
    printMsg2("请求超时:", int2String(5));
    printMsg2("开始时间是:", currentTime());

    bool isAvailable = task.checkNetWorkAvailable();
    if (!isAvailable) {
        return "网络无连接！";
    }
    printMsg("网络测试成功");
    task.SetUrl(string2char(url));
    task.useSSl(ch2str(string2char(url)).find("https://") != 0);
    task.setDebugMode(true);
    task.userAgent("Mozilla/5.0 (Windows NT 5.1; rv:17.0) Gecko/20100101 Firefox/17.0");
    task.SetConnectTimeout(5);
    task.DoGetString();
    if (task.WaitTaskDone() == 0) {
        //请求服务器成功
        std::string jsonResult = task.GetResultString();
        printMsgMerge("返回的json数据是：\n", jsonResult.c_str());
        Json::Reader reader;
        Json::Value root;
        //从字符串中读取数据
        if (reader.parse(jsonResult, root)) {
            printJson(root);
//            std::string city = root["weatherinfo"]["city"].asString();
//            std::string temp = root["weatherinfo"]["temp"].asString();
//            std::string WD = root["weatherinfo"]["WD"].asString();
//            std::string WS = root["weatherinfo"]["WS"].asString();
//            std::string time = root["weatherinfo"]["time"].asString();
//            std::string result =
//                    "城市：" + city + "\n温度：" + temp + "\n风向：" + WD + "\n风力：" + WS + "\n时间：" + time;
////            return result.c_str();
            return jsonResult.c_str();
        }
        return "Json格式异常！";
    } else {
        printMsg("网络连接失败\n");
        return "网络连接失败！";
    }
}
#ifdef __cplusplus
}
#endif
#endif //NATIVEHTTPS_NATIVE_H

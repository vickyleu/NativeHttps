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
#include "../../Utils/JsonUtil.h"

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jbyteArray JNICALL
Java_jni_http_CppProxy_HmacSha256(JNIEnv *env, jobject obj, jbyteArray content);

JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_AesEncrypt(JNIEnv *env, jobject instance, jstring str_);
JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_AesDecrypt(JNIEnv *env, jobject instance, jstring str_);


JNIEXPORT int JNICALL
aes_encrypt(char *in, char *key, char *out);
JNIEXPORT int JNICALL
aes_decrypt(char *in, char *key, char *out);
JNIEXPORT jstring JNICALL
toBuildJson(JNIEnv *env, jobject thiz, jint id, jstring name);
JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_httpGET(JNIEnv *env, jclass type, jstring url_, jstring params_,
                               jobjectArray header_);
JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_httpPOST(JNIEnv *env, jclass type, jstring url_, jobject params,
                                jstring header_);
JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_httpFromJNITest(JNIEnv *env, jclass type, jobject /* this */);
std::string nativeHttpGet(JNIEnv *env, std::string url, std::string params) {
    if (url == "") {
        return "URL请求不正确";
    }
    printMsg("开始打印");
    jclass jniUtil = env->FindClass(JNI_UTIL);

    if (jniUtil==NULL){
        std::string var="";
        return var+JNI_UTIL;
    }
    jmethodID checkUrl = env->GetStaticMethodID(jniUtil, "checkUrl", "(Ljava/lang/String;)Z");
    char *uc = string2char(url);
    jstring url_ = env->NewStringUTF(uc);
    if (url_==NULL)
        return "URL请求不正确";;
    bool valid = env->CallStaticBooleanMethod(jniUtil, checkUrl, url_);
    env->ReleaseStringUTFChars(url_, uc);

    env->DeleteLocalRef(jniUtil);

    if (!valid) {

        printMsg("Url正则不匹配");
        return "Url正则不匹配";
    } else {
        printMsg("Url正则匹配");
    }

    //GET请求
    WebTask task;
    char *p_ = string2char(params);
    char *u_ = string2char(url);
    if (strcmp(p_, "") != 0) {
        url = strcat(u_, "?");
        url = strcat(u_, p_);
    }
    free(p_);
    p_ = NULL;
    free(u_);
    u_ = NULL;

    printMsg1("使用的请求地址是:", url_, env);
    printMsg2("使用的请求方法是:", string2char("GET"));
    printMsg2("请求超时时间:", string2char(int2String(5) + "秒"));
    printMsg2("开始时间是:", currentTime());

    bool isAvailable = task.checkNetWorkAvailable();
    if (!isAvailable)return "网络无连接！";
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
        curl_easy_cleanup(task.m_curl);
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
            const char *cs = jsonResult.c_str();
            free(&jsonResult);
            return cs;
        }
        free(&jsonResult);
        return "Json格式异常！";
    } else {
        curl_easy_cleanup(task.m_curl);

        printMsg("网络连接失败\n");
        return "网络连接失败！";
    }
}
#ifdef __cplusplus
}
#endif
#endif //NATIVEHTTPS_NATIVE_H

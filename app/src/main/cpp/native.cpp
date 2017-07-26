//
// Created by Administrator on 2017/5/11.
//
#include <openssl/aes.h>
#include "pkg/header/native.h"
#include "pkg/header/AesUtil.h"
#include "pkg/header/Constant.h"

JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_AesEncrypt(JNIEnv *env, jobject instance, jstring str_) {
    const char *in = (env)->GetStringUTFChars(str_, JNI_FALSE);
    char *baseResult =AES_128_ECB_PKCS5Padding_Encrypt(in, AES_KEY_C);
    (env)->ReleaseStringUTFChars(str_, in);
    in = NULL;
    jstring ret = cToJstringutf(env, baseResult);
    free(baseResult);
    baseResult = NULL;
    return ret;
}

JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_AesDecrypt(JNIEnv *env, jobject instance, jstring str_) {
    const char *in = (env)->GetStringUTFChars(str_, JNI_FALSE);
    char *desResult = AES_128_ECB_PKCS5Padding_Decrypt(in, AES_KEY_C);
    (env)->ReleaseStringUTFChars(str_, in);
    in = NULL;
    //不用系统自带的方法NewStringUTF是因为如果desResult是乱码,会抛出异常
    jstring ret = cToJstringutf(env, desResult);
//    jstring ret=char2Jstring(env,desResult);
    free(desResult);
    desResult = NULL;
    return ret;
}

JNIEXPORT jbyteArray JNICALL
Java_jni_http_CppProxy_HmacSha256(JNIEnv *env, jobject obj, jbyteArray content) {
    unsigned char key[] = {0x6B, 0x65, 0x79};

    unsigned int result_len;
    unsigned char result[EVP_MAX_MD_SIZE];

    // get data from java array
    jbyte *data = env->GetByteArrayElements(content, NULL);
    size_t dataLength = env->GetArrayLength(content);


    HMAC(EVP_sha256(),
         key, 3,
         (unsigned char *) data, dataLength,
         result, &result_len);

    // release the array
    env->ReleaseByteArrayElements(content, data, JNI_ABORT);

    // the return value
    jbyteArray return_val = env->NewByteArray(result_len);
    env->SetByteArrayRegion(return_val, 0, result_len, (jbyte *) result);
    return return_val;
}

JNIEXPORT jstring JNICALL
toBuildJson(JNIEnv *env, jobject thiz, jint id, jstring name) {
    jboolean isCopy = 0;
    const char *c_name = env->GetStringUTFChars(name, &isCopy);
    printMsgMerge("on calling,id:%d,name:%s", string2char(int2String(id)), c_name);
    // to build a json object with id and name
    Json::Value user;
    user["id"] = id;
    user["name"] = c_name;
    const char *json_str = user.toStyledString().c_str();
    jstring result = env->NewStringUTF(json_str);
    env->ReleaseStringUTFChars(name, c_name);
    return result;
}

JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_httpGET(JNIEnv *env, jclass type, jstring url_, jstring params_,
                               jobjectArray header_) {






    if (env==NULL){
        printMsg("env为空");
    }
    if (url_ == NULL) {
        const char *str = "URL请求不正确";
        jstring rlt =env->NewStringUTF(str);
        return rlt;
    }
    const char *url = env->GetStringUTFChars(url_, 0);
    const char *params = params_ != NULL ? env->GetStringUTFChars(params_, 0) : "";
    const string &cs = nativeHttpGet(env, url, params);
    if (params_!=NULL){
       env->ReleaseStringUTFChars(params_,params);
    }


    char *str = string2char(cs);
    free((void *) &cs);
    printMsg2("原生请求>>>>>>",str );
    char *rlt = string2char(str);
    free(str);
    return env->NewStringUTF(rlt);
}

JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_httpPOST(JNIEnv *env, jclass type, jstring url_, jobject params,
                                jstring header_) {
    const char *url = env->GetStringUTFChars(url_, 0);
    const char *header = env->GetStringUTFChars(header_, 0);
    //POST请求,举例来说
    WebTask task;
    task.SetUrl(url);
    task.SetConnectTimeout(5);
//    task.AddPostString("username", username);
//    task.AddPostString("password", password);
//    task.AddPostString("email", email);
    env->ReleaseStringUTFChars(url_, url);
    env->ReleaseStringUTFChars(header_, header);
    jstring rlt = env->NewStringUTF("");
    return rlt;
}


JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_httpFromJNITest(JNIEnv *env, jclass type, jobject /* this */) {
    //GET请求
    const char *url = "http://120.25.195.170:8880/api/statistics/detail?type=1&time=2&no=-2";
    //todo  const std::string 无法释放内存,会破坏内存结构
//    char *u1 = string2char(url);




    if (env==NULL){
        printMsg("env为空");
    }
    jstring urls = env->NewStringUTF(url);
    jstring rlt = Java_jni_http_CppProxy_httpGET(env, type, urls, NULL, NULL);
//    free(u1);
    return rlt;
}
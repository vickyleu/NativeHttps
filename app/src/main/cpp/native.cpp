//
// Created by Administrator on 2017/5/11.
//
#include "pkg/header/native.h"
#include "pkg/header/AesUtil.h"

JNIEXPORT jstring JNICALL
 Java_jni_http_CppProxy_AesEncrypt(JNIEnv *env, jobject instance, jstring str_) {
    const char *in=  (env)->GetStringUTFChars(str_, JNI_FALSE);
    char *baseResult= AES_128_ECB_PKCS5Padding_Encrypt(in,  AES_KEY);
    (env)->ReleaseStringUTFChars(str_, in);
    return (env)->NewStringUTF(baseResult);
}
JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_AesDecrypt(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = (env)->GetStringUTFChars(str_, JNI_FALSE);
    char * desResult=AES_128_ECB_PKCS5Padding_Decrypt(str,AES_KEY);
    (env)->ReleaseStringUTFChars(str_, str);
//    return (*env)->NewStringUTF(env, desResult);
    //不用系统自带的方法NewStringUTF是因为如果desResult是乱码,会抛出异常
    return char2Jstring(env,desResult);
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
    if (url_ == NULL) {
        return env->NewStringUTF("URL请求不正确");
    }
    const char *url = env->GetStringUTFChars(url_, 0);
    const char *params = params_ != NULL ? env->GetStringUTFChars(params_, 0) : "";
    const string &cs = nativeHttpGet(env, url, params);
    printMsg2("原生请求>>>>>>", string2char(cs));
    return env->NewStringUTF(string2char(cs));
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
    return env->NewStringUTF("");
}


JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_httpFromJNITest(JNIEnv *env, jclass type, jobject /* this */) {
    //GET请求
    std::string url = "http://www.weather.com.cn/data/sk/101280601.html";
    return Java_jni_http_CppProxy_httpGET(env, type, env->NewStringUTF(string2char(url)), NULL,
                                          NULL);
}
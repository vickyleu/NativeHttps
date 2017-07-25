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


//void test(){
//
//    AES_KEY aes;
////加密
//    unsigned char *userKey= (unsigned char *) "12347895a2d5q6c5";
//    int result=AES_set_encrypt_key(userKey,128,&aes);//设置加密密钥
//    if(result<0)//如果设置失败,退出
//        return 0;
//    unsigned char *inr= (unsigned char *) "加密超级工厂";
//    unsigned char *out;
//    unsigned char *plain;
//    out=(unsigned char *)malloc(sizeof(unsigned char)*17);
//    memset((void *)out,0,17);//设置17位,并初始为0,这样当printf到第17位的0时就结束了.
//    plain=(unsigned char *)malloc(sizeof(unsigned char)*17);
//    memset((void *)plain,0,17);
//    printf("in=%s\n",inr);
//    printMsg2("in=%s\n", (const char *)inr);

//    char *inr2 = base64_encode2((const char *) inr);

//    AES_ecb_encrypt((const unsigned char *) inr, out, &aes, AES_ENCRYPT);
//    printMsg2("out= %s\n", (const char *)out);
//    char *out2 = base64_encode2((const char *) out);
//    printf("out=%s\n",out2);//输出密文
//    printMsg2("out= %s\n", out2);
//    jstring out2=  cToJstringutf(env,(char *)out);
//    char * out3=jstring2char(env,out2);
//    printMsg(out3);

//    if(AES_set_decrypt_key(userKey,128,&aes)<0)
//        return 0;
//    char *base64 = base64_decode2((const char *) out2);
//    AES_ecb_encrypt((const unsigned char *) base64, plain, &aes, AES_DECRYPT);
//    printf("plain=%s\n",plain);//输出解密后的明文
//    printMsg2("plain=%s\n",(char *)plain);

//    char *plain2 = base64_decode2((const char *) plain);
//    printMsg(plain2);
//    const char *inOrigin=  (env)->GetStringUTFChars(str_, JNI_FALSE);
//    jstring conv=  cToJstringutf(env,inOrigin);
//    (env)->ReleaseStringUTFChars(str_, inOrigin);
//    const char *in=  (env)->GetStringUTFChars(conv, JNI_FALSE);
//    size_t size= strlen(str);
//    char *strConvert= (char *) malloc(size);
//    memset(strConvert,0,size);
//    one_unicode_2_utf8(str, size, strConvert);
//    free(&str);
//    str=NULL;
//    str=ch2cs(strConvert);
//    free(strConvert);
//    strConvert=NULL;
//}


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
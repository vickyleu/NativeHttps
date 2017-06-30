//
// Created by Administrator on 2017/5/11.
//
#include "pkg/header/native.h"
#include "pkg/header/CryptoUtils.h"
#include "pkg/header/AesUtil.h"

jstring
Java_jni_http_CppProxy_AesEncryptUnwork(JNIEnv *env, jclass type, jstring plainText_, jstring key_) {
    //将需要加密的字符串转化为const char*类型
    const char *plainText = env->GetStringUTFChars(plainText_, 0);
    //密钥字符串转化成char*
    char *key = (char *)env->GetStringUTFChars(key_, 0);
    int i;
    char source[LEN];
    char dst[LEN];
    memset((char *) source, 0, LEN);
    memset((char *) dst, 0, LEN);
    strcpy(source, plainText);
    if (!aes_encrypt(source, key, dst))//(in,key,out)//加密
    {
        printf("encrypt error\n");
    }
    char t[3];
    string tempStr;
    int realLen = LEN;
    for (i = LEN -
             1; !dst[i]; i--) {// 加密结果中可能包含‘\0’，而‘\0’是C++中字符串的结尾标志，所以为了保证‘\0’之后的密文可以被取出，从数组尾部开始往前，第一个不是‘\0’的元素就是我们要取的最后一个值
        realLen = i;
    }
    for (i = 0; i <= realLen - 1; i += 1) {//将加密结果转化为十六进制，拼接成字符串输出
        sprintf(t, "%x", (unsigned char) dst[i]);
        if ((unsigned char) dst[i] <= 0x0f) {
            tempStr = tempStr + "0" + t;
        } else {
            tempStr = tempStr + t;
        }

    }
    char *data = (char *) tempStr.data();

    env->ReleaseStringUTFChars(plainText_, plainText);
    env->ReleaseStringUTFChars(key_, key);

    return env->NewStringUTF(data);
}
jstring
Java_jni_http_CppProxy_AesDecryptUnwork(JNIEnv *env, jclass type, jstring cipherText_, jstring key_) {
    const char *plainText = env->GetStringUTFChars(cipherText_, 0);
    char *key = (char *) env->GetStringUTFChars(key_, 0);

    int i;
    char source[LEN];
    char dst[LEN];
    memset((char *) source, 0, LEN);
    memset((char *) dst, 0, LEN);
    strcpy(dst, plainText);
    char data[LEN];
    int j = 0;
    memset((char *) data, 0, LEN);
    int len = (int) strlen(dst);
    for (i = 0; dst[i]; i++) {
        if ((i + 1) % 2 == 0) {//加密结果中字符串两两分隔组成十六进制转化为具体值存入数组以供解密
            data[j] = (char) (ascii2hex(&dst[i - 1], (char *) 1) * 16 + ascii2hex(&dst[i], (char *) 1));
            j++;
        }
    }
    if (!aes_decrypt(data, key, source)) {
        printf("decrypt error\n");
    }
    env->ReleaseStringUTFChars(cipherText_, plainText);
    env->ReleaseStringUTFChars(key_, key);

    return env->NewStringUTF(source);
}





jstring Java_jni_http_CppProxy_AesEncrypt(JNIEnv *env, jobject instance, jstring str_) {
    const char *in=  (env)->GetStringUTFChars(str_, JNI_FALSE);
    char *baseResult= AES_128_ECB_PKCS5Padding_Encrypt(in,  AES_KEY);
    (env)->ReleaseStringUTFChars(str_, in);
    return (env)->NewStringUTF(baseResult);
}

jstring Java_jni_http_CppProxy_AesDecrypt(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = (env)->GetStringUTFChars(str_, JNI_FALSE);
    char * desResult=AES_128_ECB_PKCS5Padding_Decrypt(str,AES_KEY);
    (env)->ReleaseStringUTFChars(str_, str);
//    return (*env)->NewStringUTF(env, desResult);
    //不用系统自带的方法NewStringUTF是因为如果desResult是乱码,会抛出异常
    return char2Jstring(env,desResult);
}

jbyteArray Java_jni_http_CppProxy_HmacSha256(JNIEnv *env, jobject obj, jbyteArray content) {
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

jstring toBuildJson(JNIEnv *env, jobject thiz, jint id, jstring name) {
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


jstring Java_jni_http_CppProxy_httpGET(JNIEnv *env, jclass type, jstring url_, jstring params_,
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

jstring Java_jni_http_CppProxy_httpPOST(JNIEnv *env, jclass type, jstring url_, jobject params,
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


jstring
Java_jni_http_CppProxy_httpFromJNITest(JNIEnv *env, jclass type, jobject /* this */) {
    //GET请求
    std::string url = "http://www.weather.com.cn/data/sk/101280601.html";
    return Java_jni_http_CppProxy_httpGET(env, type, env->NewStringUTF(string2char(url)), NULL,
                                          NULL);
}
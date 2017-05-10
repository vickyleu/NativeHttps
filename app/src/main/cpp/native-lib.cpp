#include <jni.h>
#include <string>
#include <openssl/hmac.h>
#include "../../../jni/libjsoncpp/json.h"
#include "network/web_task.h"
#include "Utils/StringUtil.h"
#include "Utils/CDebuger.h"
#include "Exception/NativeCrashHandler.h"
#include "Utils/JsonUtil.h"


#ifdef __cplusplus
extern "C" {
#endif


jbyteArray
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

JNIEXPORT jstring JNICALL
Java_jni_http_CppProxy_httpGET(JNIEnv *env, jclass type, jstring url_, jstring params_,
                               jstring header_) {
    if (url_ == NULL || url_ == (jstring) "") {
        return env->NewStringUTF("URL请求不正确");
    }
    printMsg("开始打印");
    jclass jniUtil = env->FindClass(JNI_UTIL);
    jmethodID checkUrl = env->GetStaticMethodID(jniUtil, "checkUrl", "(Ljava/lang/String;)Z");
    bool valid = env->CallStaticBooleanMethod(jniUtil, checkUrl, url_);
    if (!valid) {
        printMsg("Url正则不匹配");
        return env->NewStringUTF("Url正则不匹配");
    } else {
        printMsg("Url正则匹配");
    }



    const char *url = env->GetStringUTFChars(url_, 0);
//    const char *params = jstring2char(env,params_);
    const char *params = params_ != NULL ? env->GetStringUTFChars(params_, 0) : "";
    const char *header = header_ != NULL ? env->GetStringUTFChars(header_, 0) : "";
    //GET请求
    WebTask task;
    if (strcmp(params,"")!=0){
      url=strcat(string2char(url),"?");
      url=strcat(string2char(url),params);
    }
    printMsg1("使用的请求地址是:", url_, env);
    printMsg2("使用的请求方法是:", "GET");
    printMsg2("请求超时:", int2String(5));
    printMsg2("开始时间是:", currentTime());

    bool isAvailable=task.checkNetWorkAvailable();
    if (!isAvailable){
        env->ReleaseStringUTFChars(url_, url);
        if (params_ != NULL)env->ReleaseStringUTFChars(params_, params);
        if (header_ != NULL)env->ReleaseStringUTFChars(header_, header);
        return env->NewStringUTF("网络无连接！");
    }
    task.SetUrl(url);
//    task.useSSl(true);
    task.setDebugMode(true);
//    task.addHeader("Connection: keep-alive");
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
            /*//根节点
            Json::Value weatherinfo = root["weatherinfo"];
            string js1 = weatherinfo["city"].asString();
            LOGI("根节点解析: %s\n", js1.c_str());*/

            //读取子节点信息
            std::string city = root["weatherinfo"]["city"].asString();
            std::string temp = root["weatherinfo"]["temp"].asString();
            std::string WD = root["weatherinfo"]["WD"].asString();
            std::string WS = root["weatherinfo"]["WS"].asString();
            std::string time = root["weatherinfo"]["time"].asString();
            std::string result =
                    "城市：" + city + "\n温度：" + temp + "\n风向：" + WD + "\n风力：" + WS + "\n时间：" + time;
            env->ReleaseStringUTFChars(url_, url);
            if (params_ != NULL)env->ReleaseStringUTFChars(params_, params);
            if (header_ != NULL)env->ReleaseStringUTFChars(header_, header);

            return Str2Jstring(env, result.c_str());
        }
        env->ReleaseStringUTFChars(url_, url);
        if (params_ != NULL)env->ReleaseStringUTFChars(params_, params);
        if (header_ != NULL)env->ReleaseStringUTFChars(header_, header);
        return env->NewStringUTF("Json格式异常！");
    } else {
        env->ReleaseStringUTFChars(url_, url);
        if (params_ != NULL)env->ReleaseStringUTFChars(params_, params);
        if (header_ != NULL)env->ReleaseStringUTFChars(header_, header);
        printMsg("网络连接失败\n");
        return env->NewStringUTF("网络连接失败！");
    }
}

JNIEXPORT jobject JNICALL
Java_jni_http_CppProxy_httpPOST(JNIEnv *env, jclass type, jstring url_, jobject params,
                                jstring header_) {
    const char *url = env->GetStringUTFChars(url_, 0);
    const char *header = env->GetStringUTFChars(header_, 0);

    // TODO

    env->ReleaseStringUTFChars(url_, url);
    env->ReleaseStringUTFChars(header_, header);
}


jstring
Java_jni_http_CppProxy_httpFromJNITest(JNIEnv *env, jobject /* this */) {

/*    //POST请求,举例来说
    std::string url = "http://www.weather.com.cn/user/add";
    WebTask task;
    task.SetUrl(url.c_str());
    task.SetConnectTimeout(5);
    task.AddPostString("username", username);
    task.AddPostString("password", password);
    task.AddPostString("email", email);*/

    //GET请求
    std::string url = "http://www.weather.com.cn/data/sk/101280601.html";
    WebTask task;
    bool isAvailable=task.checkNetWorkAvailable();
    if (!isAvailable){
        return env->NewStringUTF("网络无连接！");
    }
    task.SetUrl(url.c_str());
//    task.useSSl(true);
    task.setDebugMode(true);
//    task.addHeader("Connection: keep-alive");

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
            /*//根节点
            Json::Value weatherinfo = root["weatherinfo"];
            string js1 = weatherinfo["city"].asString();
            LOGI("根节点解析: %s\n", js1.c_str());*/
            //读取子节点信息
            std::string city = root["weatherinfo"]["city"].asString();
            std::string temp = root["weatherinfo"]["temp"].asString();
            std::string WD = root["weatherinfo"]["WD"].asString();
            std::string WS = root["weatherinfo"]["WS"].asString();
            std::string time = root["weatherinfo"]["time"].asString();
            std::string result =
                    "城市：" + city + "\n温度：" + temp + "\n风向：" + WD + "\n风力：" + WS + "\n时间：" + time;
            return Str2Jstring(env, result.c_str());
        }
    } else {
//        LOGI("网络连接失败\n");
        return env->NewStringUTF("网络连接失败！");
    }
}


#ifdef __cplusplus
}
#endif

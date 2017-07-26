//
// Created by Administrator on 2017/5/9.
//

#ifndef LIBCURL_JSONUTIL_H
#define LIBCURL_JSONUTIL_H

#include "../../../../jni/libjsoncpp/json.h"


void printJson(Json::Value v) {
    Json::Value::Members mem = v.getMemberNames();
    for (auto iter = mem.begin(); iter != mem.end(); iter++) {
        if (v[*iter].type() == Json::objectValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char("obj"));
            printJson(v[*iter]);
        } else if (v[*iter].type() == Json::arrayValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char("array"));
            auto cnt = v[*iter].size();
            for (auto i = 0; i < cnt; i++) {
                printJson(v[*iter][i]);
            }
        } else if (v[*iter].type() == Json::nullValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char("null"));
        } else if (v[*iter].type() == Json::booleanValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char(v[*iter].asBool() ? "true" : "false"));
        } else if (v[*iter].type() == Json::stringValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":\"")),
                          strcat(string2char(v[*iter].asString()), "\""));
        } else if (v[*iter].type() == Json::realValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char(double2String(v[*iter].asDouble())));
        } else if (v[*iter].type() == Json::uintValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":\"")),
                          strcat(string2char(int2String(v[*iter].asUInt())), "\""));
        } else {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":\"")),
                          strcat(string2char(int2String(v[*iter].asInt())), "\""));
        }
    }
    return;
}

void buildingJsonObject(JNIEnv *env, jobject json, Json::Value v) {
    if (json == NULL /*|| v == NULL*/) {
        printMsg("请勿传入空值结构体或空的Json容器");
        return;
    }
    jclass jclazz = env->GetObjectClass(json);
    jclass origin = env->FindClass(JSON_OBJECT);
    jclass originArray = env->FindClass(JSON_ARRAY);
    jmethodID mid = env->GetMethodID(jclazz, "equals", "(Ljava.lang.Object;)Z");
    if (!env->CallBooleanMethod(jclazz, mid, origin) &&
        !env->CallBooleanMethod(jclazz, mid, originArray)) {

        env->DeleteLocalRef(jclazz);
        env->DeleteLocalRef(origin);
        env->DeleteLocalRef(originArray);
        printMsg("Json容器类型不正确");
        return;
    }
    env->DeleteLocalRef(jclazz);
    env->DeleteLocalRef(origin);
    env->DeleteLocalRef(originArray);

    Json::Value::Members mem = v.getMemberNames();
    for (auto iter = mem.begin(); iter != mem.end(); iter++) {
        if (v[*iter].type() == Json::objectValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char("obj"));
            printJson(v[*iter]);
        } else if (v[*iter].type() == Json::arrayValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char("array"));
            auto cnt = v[*iter].size();
            for (auto i = 0; i < cnt; i++) {
                printJson(v[*iter][i]);
            }
        } else if (v[*iter].type() == Json::nullValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char("null"));
        } else if (v[*iter].type() == Json::booleanValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char(v[*iter].asBool() ? "true" : "false"));
        } else if (v[*iter].type() == Json::stringValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":\"")),
                          strcat(string2char(v[*iter].asString()), "\""));
        } else if (v[*iter].type() == Json::realValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":")),
                          string2char(double2String(v[*iter].asDouble())));
        } else if (v[*iter].type() == Json::uintValue) {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":\"")),
                          strcat(string2char(int2String(v[*iter].asUInt())), "\""));
        } else {
            printMsgMerge(strcat(string2char("\""), strcat(string2char(*iter), "\":\"")),
                          strcat(string2char(int2String(v[*iter].asInt())), "\""));
        }
    }
    return;


}

//搜索json得到指定key的值,只支持stringvalue
//如果strcontent不为空，使用strcontent解析,如果为空直接使用v
string GetJsonStringValue(string strContent, string &strKey, Json::Value v) {
    if (!strContent.empty()) {
        Json::Reader reader;
        if (!reader.parse(strContent, v)) {
            return string("");
        }
    }

    Json::Value::Members mem = v.getMemberNames();
    Json::Value::Members::iterator it;
    //遍历所有key广度搜索
    for (it = mem.begin(); it != mem.end(); it++) {
        if (*it == strKey) {
            if (v[*it].type() == Json::stringValue) {
                return v[*it].asString();
            }
            return string("");
        }
    }

    //如果未找到，再深度搜索
    for (it = mem.begin(); it != mem.end(); it++) {
        Json::ValueType type = v[*it].type();
        if (type == Json::objectValue) {
            string strvalue = GetJsonStringValue(string(""), strKey, v[*it]);
            if (!strvalue.empty()) {
                return strvalue;
            }
        } else if (type == Json::arrayValue) {
            for (int i = 0; i < v[*it].size(); i++) {
                //如果在递归的过程中已找到，则返回
                string strvalue = GetJsonStringValue(string(""), strKey, v[*it][i]);
                if (!strvalue.empty()) {
                    return strvalue;
                }
            }
        }
    }

    return string("");
}

#endif //LIBCURL_JSONUTIL_H

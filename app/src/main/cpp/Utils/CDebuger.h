//
// Created by Administrator on 2017/4/1.
//

#ifndef MES_CDEBUGER_H
#define MES_CDEBUGER_H

#include <string>
#include "log.h"
using namespace std;
void init(JNIEnv *env);
void printMsg(char const *log);
void printMsgMerge(char const *log,char const *log2);
void printMsgMerge(char const *log,char const *log2,char const *log3);
void printMsg1(const char *pstring, jstring pJstring,JNIEnv *pEnv);
void printMsg2(const char *pstring, char *pJstring);

#endif //MES_CDEBUGER_H

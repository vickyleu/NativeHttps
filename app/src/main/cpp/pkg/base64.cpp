//
// Created by vicky on 2017.06.30.
//


#include <jni.h>
#include <cstdio>
#include <malloc.h>
#include <stdlib.h>
#include <string>
#include "header/base64.h"
#include "../Utils/CDebuger.h"

JNIEXPORT char *JNICALL
base64_encode(const char *data, int data_len) {
    //int data_len = strlen(data);
    int prepare = 0;
    int ret_len;
    int temp = 0;
    char *ret = NULL;
    char *f = NULL;
    int tmp = 0;
    char changed[4];
    int i = 0;
    ret_len = data_len / 3;
    temp = data_len % 3;
    if (temp > 0) {
        ret_len += 1;
    }
    ret_len = ret_len * 4 + 1;
    ret = (char *) malloc((size_t) ret_len);

    if (ret == NULL) {
        printf("No enough memory.\n");
        exit(0);
    }
    memset(ret, 0, (size_t) ret_len);
    f = ret;
    while (tmp < data_len) {
        temp = 0;
        prepare = 0;
        memset(changed, '\0', 4);
        while (temp < 3) {
            //printf("tmp = %d\n", tmp);
            if (tmp >= data_len) {
                break;
            }
            prepare = ((prepare << 8) | (data[tmp] & 0xFF));
            tmp++;
            temp++;
        }
        prepare = (prepare << ((3 - temp) * 8));
        //printf("before for : temp = %d, prepare = %d\n", temp, prepare);
        for (i = 0; i < 4; i++) {
            if (temp < i) {
                changed[i] = 0x40;
            } else {
                changed[i] = (char) ((prepare >> ((3 - i) * 6)) & 0x3F);
            }
            *f = base[changed[i]];
            //printf("%.2X", changed[i]);
            f++;
        }
    }
    *f = '\0';
    return ret;
}

/* */
char find_pos(char ch) {
    char *ptr = (char *) strrchr(base, ch);//the last position (the only) in base[]
    return (char) (ptr - base);
}

/* */
JNIEXPORT char * JNICALL
base64_decode(const char *data, int data_len) {
    int ret_len = (data_len/4)*3+1;
    ret_len+=100;
    int equal_count = 0;
    char *ret=NULL;
    char *f = NULL;
    int tmp = 0;
    int temp = 0;
    char need[3];
    int prepare = 0;
    int i = 0;
    if (*(data + data_len - 1) == '=') {
        equal_count += 1;
    }
    if (*(data + data_len - 2) == '=') {
        equal_count += 1;
    }
    if (*(data + data_len - 3) == '=') {//seems impossible
        equal_count += 1;
    }
    switch (equal_count) {
        case 0:
            ret_len += 4;//3 + 1 [1 for NULL]
            break;
        case 1:
            ret_len += 4;//Ceil((6*3)/8)+1
            break;
        case 2:
            ret_len += 3;//Ceil((6*2)/8)+1
            break;
        case 3:
            ret_len += 2;//Ceil((6*1)/8)+1
            break;
        default:
            break;
    }
    size_t len = (size_t) ret_len;
    ret = (char *) malloc(len+20000);
    if (ret == NULL) {
        printf("No enough memory.\n");
        exit(0);
    }
    memset(ret, 0, len);

    f = ret;
    while (tmp < (data_len - equal_count)) {
        temp = 0;
        prepare = 0;
        memset(need, 0, 4);
        while (temp < 4) {
            if (tmp >= (data_len - equal_count)) {
                break;
            }
            prepare = (prepare << 6) | (find_pos(data[tmp]));
            temp++;
            tmp++;
        }
        prepare = prepare << ((4 - temp) * 6);
        for (i = 0; i < 3; i++) {
            if (i == temp) {
                break;
            }
            *f = (char) ((prepare >> ((2 - i) * 8)) & 0xFF);
            f++;
        }
    }
    *f = '\0';
    char *output= new char[strlen(ret)+1];
    strcpy(output,ret);
    free(ret);
    ret=NULL;
    return output;
}


JNIEXPORT char * JNICALL
base64_encode2(const char* str){
    int len = (int) strlen(str);
    int rel_len=(len/3)*4+4+1;
    char* rel;
    if(len<3){
        rel = (char*)malloc(5*sizeof(char));
    }else{
        rel = (char*)malloc(rel_len*sizeof(char));
    }
    //LOGD("num2base64char %d",rel_len);
    *(rel+rel_len-1) = '\0';
    *(rel+rel_len-2) = '\0';
    *(rel+rel_len-3) = '\0';
    *(rel+rel_len-4) = '\0';
    *(rel+rel_len-5) = '\0';
    int i=0;
    int j=0;
    //int n=0;
    for(i=0;i<len;){
        char* encode=NULL;
        if(i+2<=len-1){
            encode = translate_3to_4_3(*(str + i), *(str + i + 1), *(str + i + 2));
            *(rel+j) = num2base64char(*encode);
            *(rel+j+1) = num2base64char(*(encode+1));
            *(rel+j+2) = num2base64char(*(encode+2));
            *(rel+j+3) = num2base64char(*(encode+3));
        }else if(i == len-1){
            encode = translate_3to_4_1(*(str + i));
            *(rel+j) = num2base64char(*encode);
            *(rel+j+1) = num2base64char(*(encode+1));
            *(rel+j+2) = num2base64char(*(encode+2));
            *(rel+j+3) = num2base64char(*(encode+3));
        }else if(i+1 == len-1){
            encode = translate_3to_4_2(*(str + i), *(str + i + 1));
            *(rel+j) = num2base64char(*encode);
            *(rel+j+1) = num2base64char(*(encode+1));
            *(rel+j+2) = num2base64char(*(encode+2));
            *(rel+j+3) = num2base64char(*(encode+3));
        }else{
            encode = 0;//NULL;
        }
        j+=4;
        i+=3;
        free(encode);
        encode=NULL;
    }
    return rel;
}
JNIEXPORT char * JNICALL
base64_decode2(const char* str){
    int len = (int) strlen(str);
    int rel_len = (len/4)*3+1;
    char* rel = (char*)malloc(rel_len*sizeof(char));
    *(rel+rel_len-1)='\0';
    int i=0;
    int j=0;
    for(i=0;i<len;){
        if(i+3<=len-1){
            char* decode = translate_3to_4_4(base64char2num(*(str + i)),
                                             base64char2num(*(str + i + 1)),
                                             base64char2num(*(str + i + 2)),
                                             base64char2num(*(str + i + 3)));
            if(*(str+i+3)!='='){
                *(rel+j)=*decode;
                *(rel+j+1)=*(decode+1);
                *(rel+j+2)=*(decode+2);
            }else if(*(str+i+2)!='='){
                *(rel+j)=*decode;
                *(rel+j+1)=*(decode+1);
                *(rel+j+2)='\0';
                break;
            }else{
                *(rel+j)=*decode;
                *(rel+j+1)='\0';
                *(rel+j+2)='\0';
                break;
            }
            printMsg(decode);
            free(decode);
        }
        i+=4;
        j+=3;
    }
    return rel;
}
char* translate_3to_4_3(char a, char b, char c){
    char* result = (char*)malloc(4*sizeof(char));
    *result = (a>>2)&0b00111111;
    *(result+1) = ((a<<4)&0b00110000)+((b>>4)&0b00001111);
    *(result+2) = ((c>>6)&0b00000011) + ((b<<2)&0b00111100);
    *(result+3) = c&0b00111111;
    return result;
}

char* translate_3to_4_1(char a){
    char* result = (char*)malloc(4*sizeof(char));
    *result = (a>>2)&0b00111111;
    *(result+1) = (a<<4)&0b00110000;
    *(result+2) = 64;
    *(result+3) = 64;
    return result;
}

char* translate_3to_4_2(char a, char b){
    char* result = (char*)malloc(4*sizeof(char));
    *result = (a>>2)&0b00111111;
    *(result+1) = ((a<<4)&0b00110000)+((b>>4)&0b00001111);
    *(result+2) = (b<<2)&0b00111100;
    *(result+3) = 64;
    return result;
}

char num2base64char(char n){
    char result;
    if(n<26){
        result = 'A'+n;
    }else if(n<52){
        result = 'a'+n-26;
    }else if(n<62){
        result = '0'+n-52;
    }else if(n==62){
        result = '+';
    }else if(n==63){
        result = '/';
    }else if(n==64){
        result = '=';
    } else{
        result = '=';
    }
    return result;
}

char* translate_3to_4_4(char a, char b, char c, char d){
    char* result = (char*)malloc(3*sizeof(char));
    *result =((a<<2)&0b11111100)+((b>>4)&0b00001111);
    *(result+1)=((c>>2)&0b00001111)+((b<<4)&0b11110000);
    *(result+2)=d+((c<<6)&0b11000000);

    return result;
}
char base64char2num(char b){
    char result;
    if(b>='A' && b<='Z'){
        result = b-'A';
    }else if(b>='a' && b<='z'){
        result = b-'a'+26;
    }else if(b>='0' && b<='9'){
        result = b-'0'+52;
    }else if(b=='+'){
        result = 62;
    }else if(b=='/'){
        result = 63;
    }else if(b=='='){
        result = 0;//64;
    } else{
        result = '=';//NULL;
    }
    return result;
}
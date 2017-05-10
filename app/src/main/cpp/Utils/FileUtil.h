//
// Created by Administrator on 2016/12/14.
//
#include <sys/stat.h>
#include <stdlib.h>

#ifndef MES_FILTUTIL_H
#define MES_FILTUTIL_H

unsigned long getFileSize(const char *path) {
    unsigned long filesize = -1;
    struct stat statbuff;
    if (stat(path, &statbuff) < 0) {
        return filesize;
    } else {
        filesize = statbuff.st_size;
    }
    return filesize;
}

#endif //MES_FILTUTIL_H

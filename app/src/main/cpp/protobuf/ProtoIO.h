//
// Created by vicky on 2017.08.03.
//

#ifndef NATIVEHTTPS_PROTOIO_H
#define NATIVEHTTPS_PROTOIO_H

#include "sample.pb.h"

#ifdef __cplusplus
extern "C" {
#endif
using namespace Proto;
using namespace google::protobuf::io;
using namespace google::protobuf;
int read(User user);
int white(User user);
#ifdef __cplusplus
}
#endif
#endif //NATIVEHTTPS_PROTOIO_H

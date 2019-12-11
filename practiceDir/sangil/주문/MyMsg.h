#ifndef __MYMSG_H__
#define __MYMSG_H__

#include "people.hpp"
#include <string>

#define MSG_TYPE_CUS 1

#define MSG_SIZE_CUS (sizeof(MsgCus) - sizeof(long))

struct __MsgList {
    char name[256];
    int count;
};
typedef struct __MsgList MsgList;

struct __MsgCus {
    long mtype;

    MsgList msgList[7]; // 음식
    int num;    // 대기 번호
    int menuTotal;  // 음식 수
};
typedef struct __MsgCus MsgCus;

#endif

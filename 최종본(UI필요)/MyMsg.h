#ifndef __MYMSG_H__
#define __MYMSG_H__

#include "people.hpp"
#include <string>

#define MSG_TYPE_CUS 6
#define IDX_STORE_RCV 1
#define IDX_STORE_SND 2
#define IDX_REMOVE_RCV 3
#define IDX_REMOVE_SND 4
#define ORDER_NUM 5

#define MSG_SIZE_RSLT (sizeof(MsgRslt) - sizeof(long))
#define MSG_SIZE_CUS (sizeof(MsgCus) - sizeof(long))

struct __MsgList {
    char name[256];
    int count;
};
typedef struct __MsgList MsgList;

struct __MsgCus {
    long mtype;

    MsgList msgList[7];
    int num;
    int menuTotal;
};
typedef struct __MsgCus MsgCus;
struct __MsgRslt {
    long mtype;
    int rslt;
};
typedef struct __MsgRslt MsgRslt;

#endif

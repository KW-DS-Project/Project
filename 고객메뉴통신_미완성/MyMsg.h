#ifndef __MYMSG_H__
#define __MYMSG_H__

#include "people.hpp"

#define MSG_TYPE_CUS 1

#define MSG_SIZE_CUS (sizeof(MsgCus) - sizeof(long))

struct __MsgCus {
    long mtype;
    person people;
    int menuTotal;
};
typedef struct __MsgCus MsgCus;

#endif

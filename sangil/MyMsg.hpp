#ifndef __MYMSG_H__
#define __MYMSG_H__

#define IDX_STORE_RCV 1
#define IDX_STORE_SND 2
#define IDX_REMOVE_RCV 3
#define IDX_REMOVE_SND 4

#define MSG_SIZE_RSLT (sizeof(MsgRslt) - sizeof(long))

struct __MsgRslt {
    long mtype;
    int rslt;
};
typedef struct __MsgRslt MsgRslt;

#endif

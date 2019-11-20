#include "MyMsg.hpp"
#include <iostream>
#include <csignal>
#include <cstring>
#include <cstdlib>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

using namespace std;

int main(int argc, char const *argv[]){
    key_t mykey1=ftok("mykey1",1);
    int msqid1=msgget(mykey1,IPC_CREAT);
    MsgRslt msgRslt;
    int idx=0;

    while(1){
        cout<<"<<< ";
        cin>>idx;
        fflush(stdout);
        fflush(stdin);

        memset(&msgRslt,0x00,sizeof(MsgRslt));
        msgRslt.mtype=IDX_STORE_SND;
        msgRslt.rslt=idx;
        msgsnd(msqid1,&msgRslt,MSG_SIZE_RSLT,0);

        memset(&msgRslt,0x00,sizeof(MsgRslt));
        msgrcv(msqid1,&msgRslt,MSG_SIZE_RSLT,IDX_STORE_RCV,0);
        cout<<">>> "<<idx;

    }
    return 0;
}
#include "MyMsg.h"
//#include "people.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <list>
#include <pthread.h>

using namespace std;

void *myThread(void *arg);

pthread_t tid=0;
key_t mykey = ftok("customer", 1);
key_t mykey1 = ftok("cusToServ", 2);
int msqid = msgget(mykey, IPC_CREAT);
int msqid1=msgget(mykey1,IPC_CREAT);

vector<MsgCus> arr;
list<MsgCus> cusList;
list<MsgCus>::iterator iter;

MsgCus msgCus;
MsgRslt msgRslt;
int menuTotal;
int cnt = 0;
int *status;
int main() {
    system("clear");




    while (1) {
        cout << "*** 대기 *** " << endl;
        memset(&msgCus, 0x00, sizeof(MsgCus));

        msgrcv(msqid, &msgCus, MSG_SIZE_CUS, MSG_TYPE_CUS, 0);

//        cusList.insert(iter,msgCus);
//        iter++;

        arr.push_back(msgCus);

        menuTotal = msgCus.menuTotal;

        // cout << "메뉴토탈 : " << msgCus.menuTotal << endl << endl;

        cout << "주문번호 : " << msgCus.num << endl << endl;

        // menuTotal = 5;
        for (int i = 0; i < menuTotal; i++) {
            if (msgCus.msgList[i].count != 0) {
                cout << msgCus.msgList[i].name << " " << msgCus.msgList[i].count
                     << endl;
            }
        }
        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        msgRslt.mtype = IDX_STORE_SND;
        msgRslt.rslt = msgCus.num;
        msgsnd(msqid1, &msgRslt, MSG_SIZE_RSLT, 0);
        cout << "Send to mainServer: " << msgRslt.rslt << endl;

        if(pthread_create(&tid,NULL,myThread,NULL)){
            perror("pthread_create() error");
        }
        //pthread_join(tid,(void**) &status);




        fflush(stdin);
        fflush(stdout);


    }

    return 0;
}

void *myThread(void *arg) {
    if(msgrcv(msqid1,&msgRslt,MSG_SIZE_RSLT,IDX_REMOVE_RCV,0)>0)
        cout<<"삭제할 인덱스 : "<<msgRslt.rslt<<endl<<endl;

    pthread_exit((void *)&status);
}
#include "MyMsg.hpp"
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

using namespace std;

MsgRslt msgRslt;
int msqid1;
int idx;
int msqid;

void signalHandler(int signum);
void sendMsg(int qid, long type, int data);
void getMsg(int qid, int type);

int main(int argc, char const *argv[]) {
    key_t mykey1 = ftok("mykey1", 1);
    msqid1 = msgget(mykey1, IPC_CREAT);
    key_t mykey = ftok("mykey", 1);
    msqid = msgget(mykey, IPC_CREAT);
    idx = 0;

    vector<int> orders;
    vector<int>::iterator iter;
    // 메인 서버로부터 받는 SIGUSR1 signal.. 삭제 모드 실행
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    sendMsg(msqid1, IDX_STORE_SND, getpid());
    // system("clear");
    while (1) {
        system("clear");
        cout << " ----O r d e r e d   L I S T---- " << endl;
        for (iter = orders.begin(); iter != orders.end(); ++iter) {
            cout << "Consumer Number: " << *iter << endl;
            cout << "---------------------------------" << endl;
        }
        getMsg(msqid, ORDER_NUM);
        orders.push_back(msgRslt.rslt);
        fflush(stdout);
        fflush(stdin);

        idx = msgRslt.rslt;
        sendMsg(msqid1, IDX_STORE_SND, idx);
        cout << endl;
    }
    return 0;
}
void getMsg(int qid, int type) {
    msgrcv(qid, &msgRslt, MSG_SIZE_RSLT, type, 0);
}

void sendMsg(int qid, long type, int data) {
    memset(&msgRslt, 0x00, sizeof(MsgRslt));
    msgRslt.mtype = type;
    msgRslt.rslt = data;
    msgsnd(qid, &msgRslt, MSG_SIZE_RSLT, 0);
}
void signalHandler(int signum) {
    if (signum == SIGUSR1) {
        signal(SIGUSR2, signalHandler);
        cout << "Remove Mode ON" << endl;
        pause();
    } else if (signum == SIGUSR2) {
        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        getMsg(msqid1, IDX_REMOVE_RCV);
        cout << ">>> ??? ??: " << idx << endl;
        cout << "Remove Mode OFF" << endl;
    }
}

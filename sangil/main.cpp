#include "MyMsg.hpp"
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

using namespace std;
void signalHandler(int signum);

key_t mykey1 = 0;
key_t mykey2 = 0;
int msqid1 = 0;
int msqid2 = 0;
MsgRslt msgRslt;
int pidOfOrders;
int idx;

void sendMsg(int qid, long type, int data);
int getMsg(int qid, int type);
void compl_order();

int main(int argc, char const *argv[]) {
    // MsgRslt msgRslt;

    mykey1 = ftok("mykey1", 1);
    mykey2 = ftok("mykey2", 2);

    msqid1 = msgget(mykey1, IPC_CREAT | 0644);
    msqid2 = msgget(mykey2, IPC_CREAT | 0644);

    signal(SIGINT, signalHandler);
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    getMsg(msqid1, IDX_STORE_SND);
    pidOfOrders = msgRslt.rslt;

    sendMsg(msqid2, IDX_STORE_RCV, getpid());
    while (1) {
        cout << "pid of Orders: " << pidOfOrders << endl;
        puts("Hello I'm main server ...");

        if (msgrcv(msqid1, &msgRslt, MSG_SIZE_RSLT, IDX_STORE_SND, 0) > 0) {
            cout << "Receive from cutomer: " << msgRslt.rslt << endl;
            idx = msgRslt.rslt;

            sendMsg(msqid2, IDX_STORE_RCV, idx);

            cout << "Send to kitchen: " << msgRslt.rslt << endl;

        } else {
            perror("msgrcv1 error");
            exit(-1);
        }

        if (idx < 0)
            return 0;
        // fflush(stdout);
    }
    return 0;
}
int getMsg(int qid, int type) { return msgrcv(qid, &msgRslt, MSG_SIZE_RSLT, type, 0); }

void sendMsg(int qid, long type, int data) {
    memset(&msgRslt, 0x00, sizeof(MsgRslt));
    msgRslt.mtype = type;
    msgRslt.rslt = data;
    msgsnd(qid, &msgRslt, MSG_SIZE_RSLT, 0);
}
void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid1, IPC_RMID, NULL);
        msgctl(msqid2, IPC_RMID, NULL);
        exit(0);
    } else if (signum == SIGUSR1) {
        signal(SIGUSR2, signalHandler);
        cout << "Remove Mode ON" << endl;
        kill(pidOfOrders, SIGUSR1);
        pause();    // ??? ?? ??? ???
    } else if (signum == SIGUSR2){
        compl_order();
        cout << "Remove Mode OFF" << endl;
    }
}
void compl_order(){
    if (getMsg(msqid2, IDX_REMOVE_SND) > 0) {
            cout << "Receive from kitchen: " << idx << endl;
            idx = msgRslt.rslt;

            sendMsg(msqid1, IDX_REMOVE_RCV, idx);
            kill(pidOfOrders, SIGUSR2);
            cout << "Send to customer: " << msgRslt.rslt << endl;

        } else {
            perror("msgrcv2 error");
            exit(-1);
        }
}

#include "MyMsg.hpp"
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

using namespace std;
void signalHandler(int signum);

key_t mykey1 = 0;
key_t mykey2 = 0;
int msqid1 = 0;
int msqid2 = 0;

int main(int argc, char const *argv[]) {
    int idx;
    MsgRslt msgRslt;

    mykey1 = ftok("mykey1", 1);
    mykey2 = ftok("mykey2", 2);

    msqid1 = msgget(mykey1, IPC_CREAT | 0644);
    msqid2 = msgget(mykey2, IPC_CREAT | 0644);

    signal(SIGINT, signalHandler);

    while (1) {
        puts("Wait ...");

        if (msgrcv(msqid1, &msgRslt, MSG_SIZE_RSLT, IDX_STORE_SND, 0) > 0) {
            cout << "Receive from server 1: " << msgRslt.rslt << endl;
            idx = msgRslt.rslt;

            memset(&msgRslt, 0x00, sizeof(MsgRslt));
            msgRslt.mtype = IDX_STORE_RCV;
            msgRslt.rslt = idx;
            msgsnd(msqid2, &msgRslt, MSG_SIZE_RSLT, 0);

            cout << "Send to server 2: " << msgRslt.rslt << endl;

        } else {
            perror("msgrcv1 error");
            exit(-1);
        }
        if (msgrcv(msqid2, &idx, MSG_SIZE_RSLT, IDX_REMOVE_SND, 0) > 0) {
            cout << "Receive from server 2: " << idx << endl;
            idx = msgRslt.rslt;

            memset(&msgRslt, 0x00, sizeof(MsgRslt));
            msgRslt.mtype = IDX_REMOVE_RCV;
            msgRslt.rslt = idx;
            msgsnd(msqid1, &msgRslt, MSG_SIZE_RSLT, 0);

            cout << "Send to server 1: " << msgRslt.rslt << endl;

        } else {
            perror("msgrcv2 error");
            exit(-1);
        }
        if (idx < 0)
            return 0;
        // fflush(stdout);
    }
    return 0;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid1, IPC_RMID, NULL);
        msgctl(msqid2, IPC_RMID, NULL);
        exit(0);
    }
}

#include "MyMsg.h"
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;
void signalHandler(int signum);
void *myThread(void *arg);
pthread_t tid=0;
key_t mykey1 = 0;
key_t mykey2 = 0;
key_t key_remove;
int msqid1 = 0;
int msqid2 = 0;
int msqid_remove;
MsgRslt msgRslt;
int pidOfOrders;
int idx;
int *status;

void sendMsg(int qid, long type, int data);
int getMsg(int qid, int type);
void compl_order();

// main server로 주문받은 메뉴 표시판과, 주문번호 관리자 를 연동해주는 메인 서버
int main(int argc, char const *argv[]) {
    // MsgRslt msgRslt;

    mykey1 = ftok("cusToServ", 2);
    mykey2 = ftok("mykey2", 3);

    msqid1 = msgget(mykey1, IPC_CREAT | 0644);
    msqid2 = msgget(mykey2, IPC_CREAT | 0644);

    key_remove = ftok("removeKey",4);
    msqid_remove = msgget(key_remove,IPC_CREAT);

    signal(SIGINT, signalHandler);
    // SIGUSR1 signal을 주문 번호 관리자로부터 받는다.
    // 삭제 모드로 실행
//    signal(SIGUSR1, signalHandler);
//    signal(SIGUSR2, signalHandler);


    puts("Hello I'm main server ...");
    // 주문 번호 받고 바로 넘기기
    while (1) {

        getMsg(msqid1, IDX_STORE_SND);
        pidOfOrders = msgRslt.rslt;
        cout << "pid of Orders: " << pidOfOrders << endl;

        cout << "Receive from cutomer: " << msgRslt.rslt << endl;
        idx = msgRslt.rslt;

        sendMsg(msqid2, IDX_STORE_RCV, idx);

        cout << "Send to kitchen: " << msgRslt.rslt << endl;

        if(pthread_create(&tid,NULL,myThread,NULL)){
            perror("pthread_create() error");
        }
//        if(getMsg(msqid2, IDX_REMOVE_SND)>0) {
//            idx = msgRslt.rslt;
//            cout << "Receive from kitchen: " << idx << endl;
//
//
//            sendMsg(msqid1, IDX_REMOVE_RCV, idx);
//            kill(pidOfOrders, SIGUSR2);
//            cout << "Send to customer: " << msgRslt.rslt << endl;
//        } else
//            continue;
        fflush(stdin);
        fflush(stdout);

    }
    return 0;
}
int getMsg(int qid, int type) {
    return msgrcv(qid, &msgRslt, MSG_SIZE_RSLT, type, 0);
}

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
        // 삭제 모드 구현
        //signal(SIGUSR2, signalHandler);
        cout << "Remove Mode ON" << endl;
        // 주문 표시판으로 SIGUSR1 을 보내어 삭제모드로 변경 시킨다.
        kill(pidOfOrders, SIGUSR1);

        pause();
    } else if (signum == SIGUSR2) {

        cout << "Remove Mode OFF" << endl;
    }

}
// 삭제 모드시 호출할 함수
void compl_order() {
    if(getMsg(msqid_remove, IDX_REMOVE_SND)>0) {
        idx = msgRslt.rslt;
        cout << "Receive from kitchen: " << idx << endl;


        sendMsg(msqid1, IDX_REMOVE_RCV, idx);
        kill(pidOfOrders, SIGUSR2);
        cout << "Send to customer: " << msgRslt.rslt << endl;
    }

}

void *myThread(void *arg) {
    if(getMsg(msqid2, IDX_REMOVE_SND)>0) {
            idx = msgRslt.rslt;
            cout << "Receive from kitchen: " << idx << endl;


            sendMsg(msqid1, IDX_REMOVE_RCV, idx);
            kill(pidOfOrders, SIGUSR2);
            cout << "Send to customer: " << msgRslt.rslt << endl;
        }

    pthread_exit((void *) &status);
}

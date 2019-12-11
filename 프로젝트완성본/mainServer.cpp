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

void *myThread(void *arg);
pthread_t tid = 0;
key_t mykey1 = 0;
key_t mykey2 = 0;
key_t key_remove;

int msqid1 = 0;
int msqid2 = 0;
int msqid_remove;

MsgRslt msgRslt;

int idx;
int *status;

void sendMsg(int qid, long type, int data);
int getMsg(int qid, int type);
void signalHandler(int signum);

// main server로 주문받은 메뉴 표시판과, 주문번호 관리자 를 연동해주는 메인 서버
int main(int argc, char const *argv[]) {
    system("clear");
    // MsgRslt msgRslt;

    // customer -> main server
    mykey1 = ftok("cusToServ", 2);
    msqid1 = msgget(mykey1, IPC_CREAT | 0644);
    // mainserver -> kitchen(server2)
    mykey2 = ftok("mykey2", 3);
    msqid2 = msgget(mykey2, IPC_CREAT | 0644);

    // kitchen(server2) -> mainserver to remove
    key_remove = ftok("removeKey", 4);
    msqid_remove = msgget(key_remove, IPC_CREAT);

    signal(SIGINT, signalHandler);
    cout << " __  __    ___     ___    _  _                       ___     ___  "
            "   ___   __   __   ___     ___   "
         << endl;
    cout << "|  \\/  |  /   \\   |_ _|  | \\| |     o O O    o O O  / __|   | "
            "__|   | _ \\  \\ \\ / /  | __|   | _ \\  "
         << endl;
    cout << "| |\\/| |  | - |    | |   | .` |    o        o       \\__ \\   | "
            "_|    |   /   \\ V /   | _|    |   /  "
         << endl;
    cout << "|_|__|_|  |_|_|   |___|  |_|\\_|   TS__[O]  TS__[O]  |___/   "
            "|___|   |_|_\\   _\\_/_   |___|   |_|_\\  "
         << endl;
    cout << "_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| {======| "
            "{======|_|\"\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"|_| "
            "\"\"\"\"|_|\"\"\"\"\"|_|\"\"\"\"\"| "
         << endl;
    cout << "\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'./o--000'./"
            "o--000'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-'\"`-0-0-' "
         << endl;
    cout << "=================================================================="
            "================================"
         << endl;
    cout << ">> 메인 서버는 주문 받은 메뉴 표시판과 주문 번호 관리모드를 "
            "실시간으로 확인할 수 있습니다. <<"
         << endl;
    cout << endl << endl;

    // 주문 번호 받고 바로 넘기기
    while (1) {
        /*** UI 설정 ***/
        getMsg(msqid1, IDX_STORE_SND);
        cout << "접수된 고객 주문 번호 : " << msgRslt.rslt << endl;
        idx = msgRslt.rslt;

        sendMsg(msqid2, IDX_STORE_RCV, idx);

        cout << "고객 주문 정보를 주방으로 전달합니다. : " << msgRslt.rslt
             << "     . . . 전송 완료" << endl;
        cout << endl << endl;

        if (pthread_create(&tid, NULL, myThread, NULL)) {
            perror("pthread_create() error");
        }
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
    }
}
// 삭제 모드시 호출할 함수
void *myThread(void *arg) {
    /*** UI 설정 ***/
    if (getMsg(msqid2, IDX_REMOVE_SND) > 0) {
        cout << endl;
        puts("----주문 번호 삭제 대기 중입니다.----");
        idx = msgRslt.rslt;
        cout << "---주방으로부터 받은 주문 번호 : " << idx << "---" << endl;

        sendMsg(msqid1, IDX_REMOVE_RCV, idx);
        cout << "---삭제 완료 된 고객 주문 번호 : " << msgRslt.rslt << "---" << endl << endl;
        cout << endl;
    }

    pthread_exit((void *)&status);
}


#include "MyMsg.h"
#include <iostream>
#include <list>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

using namespace std;

void signalHandler(int signum);
void complete_order();
void sendMsg(int qid, long type, int data);
void getMsg(int qid, int type);

MsgRslt msgRslt;
key_t mykey2;
key_t key_remove;

int msqid2;
int msqid_remove;

int pidOfServer;

// 주방에서 주문 받은 번호 관리 및 삭제 역할
int main(int argc, char const *argv[]) {
    printf("\033[2J\033[1;1H");

    mykey2 = ftok("mykey2", 3);
    msqid2 = msgget(mykey2, IPC_CREAT);

    key_remove = ftok("removeKey",4);

    list<int> orders;
    list<int>::iterator iter;
    // Ctrl + c  누르면 삭제 모드로 변경
    // 메인서버에 SIGUSR1 signal을 보냄
    signal(SIGINT, signalHandler);

    //getMsg(msqid2, IDX_STORE_RCV);
    //pidOfServer = msgRslt.rslt;
    // 주문 번호 받는 상태
    puts("wait...주문번호!");

    while (1) {
        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        getMsg(msqid2, IDX_STORE_RCV);
        pidOfServer = msgRslt.rslt;
        cout << "Server's pid: " << pidOfServer << endl;

        //getMsg(msqid2, IDX_STORE_RCV);
        orders.push_back(msgRslt.rslt);
        cout << "주문 번호: ";
        for (iter = orders.begin(); iter != orders.end(); ++iter) {
            cout << *iter << " ";
        }
        cout << endl;
        fflush(stdin);
        fflush(stdout);
        // memset(&msgRslt, 0x00, sizeof(MsgRslt));
    }

    return 0;
}
void signalHandler(int signum) {
    if (signum == SIGINT) {
        cout << "\033[2J\033[1;1H";
        kill(pidOfServer, SIGUSR1);
        complete_order();
        // cin.clear();
    }
}
// 완료된 주문 보내는 함수
void complete_order() {
    int index;

    cout << "완료된 주문번호를 입력해 주세요(종료시 0): ";
    cin >> index;
    if (index == 0)
        exit(0);
    cout << index << " 이것이 인덱스! 엔터를 누르세요." << endl;
    // cout << "\033[2J\033[1;1H";
    // cout << "숫자 34343434입력: ";

    sendMsg(msqid2, IDX_REMOVE_SND, index);
    kill(pidOfServer, SIGUSR2);
    cout << "signal";
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

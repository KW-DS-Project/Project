#include "MyMsg.hpp"
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

MsgRslt sndIdx;
key_t mykey2;
int msqid2;

int main(int argc, char const *argv[]) {
    printf("\033[2J\033[1;1H");

    MsgRslt rcvIdx;

    mykey2 = ftok("mykey2", 2);
    msqid2 = msgget(mykey2, IPC_CREAT);

    list<int> orders;
    list<int>::iterator iter;
    signal(SIGINT, signalHandler);

    // while (1) {
    //     cout << "숫자 입력: ";
    //     int ind;
    //     cin >> ind;
    //     cout << ind * 100 << endl;
    //     cin.clear();
    // }

    // 주문 번호 받는 상태
    puts("wait...주문번호!");
    while (1) {
        memset(&rcvIdx, 0x00, sizeof(MsgRslt));
        msgrcv(msqid2, &rcvIdx, MSG_SIZE_RSLT, IDX_STORE_RCV, 0);
        orders.push_back(rcvIdx.rslt);
        // cout << "\033[2J\033[1;1H";
        cout << "주문 번호: ";
        for (iter = orders.begin(); iter != orders.end(); ++iter) {
            cout << *iter << " ";
        }
        cout << endl;
        // memset(&msgRslt, 0x00, sizeof(MsgRslt));
    }

    return 0;
}
void signalHandler(int signum) {
    if (signum == SIGINT) {
        cout << "\033[2J\033[1;1H";
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
    cout << "\033[2J\033[1;1H";
    // cout << "숫자 34343434입력: ";

    memset(&sndIdx, 0x00, sizeof(MsgRslt));
    sndIdx.mtype = IDX_REMOVE_SND;
    sndIdx.rslt = index;
    msgsnd(msqid2, &sndIdx, MSG_SIZE_RSLT, 0);
}

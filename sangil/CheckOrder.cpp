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

MsgRslt msgRslt;
key_t mykey;
int msqid;

int main(int argc, char const *argv[]) {
    cout << "\033[2J\033[1;1H";
    mykey = ftok("mykey", 1);
    msqid = msgget(mykey, IPC_CREAT);

    // MsgRslt msgRslt1;
    // MsgRslt msgRslt2;

    list<int> orders;
    list<int>::iterator iter;
    signal(SIGINT, signalHandler);

    while (1) {
        cout << "숫자 입력: ";
        int ind;
        cin >> ind;
        cout << ind * 100 << endl;
        cin.clear();
    }

    //주문 번호 받는 상태
    // while (1) {

    //     cout << "주문 번호: ";
    //     for (iter = orders.begin(); iter != orders.end(); ++iter) {
    //         cout << *iter << " ";
    //     }
    //     memset(&msgRslt, 0x00, sizeof(MsgRslt));
    //     msgrcv(msqid, &msgRslt, MSG_SIZE_RSLT, IDX_STORE_SND, 0);
    //     orders.push_back(msgRslt.rslt);
    //     cout << "\033[2J\033[1;1H";
    // }
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
    cout << "숫자 34343434입력: ";

    // memset(&msgRslt, 0x00, sizeof(MsgRslt));
    // msgRslt.mtype = IDX_REMOVE_RCV;
    // msgRslt.rslt = index;
    // msgsnd(msqid, &msgRslt, MSG_SIZE_RSLT, 0);
}

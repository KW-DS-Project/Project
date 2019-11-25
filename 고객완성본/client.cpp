#include "MyMsg.h"
//#include "people.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <vector>

using namespace std;

int main() {
    system("clear");
    key_t mykey = ftok("customer", 1);
    int msqid = msgget(mykey, IPC_CREAT);

    vector<MsgCus> arr;

    MsgCus msgCus;
    int menuTotal;
    int cnt = 0;

    while (1) {
        cout << "*** 대기 *** " << endl;
        memset(&msgCus, 0x00, sizeof(MsgCus));

        if (msgrcv(msqid, &msgCus, MSG_SIZE_CUS, MSG_TYPE_CUS, 0) == -1) {
            perror("Error!");
            exit(200);
        }

        arr.push_back(msgCus);

        menuTotal = msgCus.menuTotal;

        // cout << "메뉴토탈 : " << msgCus.menuTotal << endl << endl;

        cout << "주문번호 : " << msgCus.num << endl << endl;

        for (int i = 0; i < menuTotal; i++) {
            if (msgCus.msgList[i].count != 0) {
                cout << msgCus.msgList[i].name << " " << msgCus.msgList[i].count
                     << endl;
            }
        }
        cout << endl;
    }

    return 0;
}

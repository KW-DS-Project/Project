#include "MyMsg.h"
//#include "people.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

using namespace std;

int main() {
    system("clear");
    key_t mykey = ftok("customer", 1);
    int msqid = msgget(mykey, IPC_CREAT);

    list<MsgList> arr;
    list<MsgList>::iterator iter;

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

        arr.push_back(msgCus.msgList[0]);

        menuTotal = msgCus.menuTotal;

        cout << "주문번호 : " << msgCus.num << endl;
        // 메뉴 출력
        // count = 메뉴 수량, name = 메뉴 이름
        for (iter = arr.begin(); iter != arr.end(); ++iter) {
            if (iter->count != 0) {
                cout << iter->name << " " << iter->count << endl;
            }
        }
    }

    return 0;
}

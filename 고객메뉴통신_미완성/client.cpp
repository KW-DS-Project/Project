#include "MyMsg.h"
#include "people.hpp"
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
    key_t mykey = ftok("customer", 1);
    int msqid = msgget(mykey, IPC_CREAT);

    vector<person> arr;

    MsgCus msgCus;
    int menuTotal;
    int cnt = 0;

    while (1) {
        cout << "*** 대기 *** " << endl;
        memset(&msgCus, 0x00, sizeof(MsgCus));
        msgrcv(msqid, &msgCus, MSG_SIZE_CUS, MSG_TYPE_CUS, 0);

        cout << msgCus.menuTotal << endl;

        /*
                arr.push_back(msgCus.people);

                menuTotal = msgCus.menuTotal;

                cout << "주문 번호 : " << arr[cnt].getNum() << endl;
                for (int i = 0; i < menuTotal; i++) {
                    cout << "메뉴 : " << arr[cnt].getOrder(i).name << endl;
                    cout << "수량 : " << arr[cnt].getOrder(i).count << endl;
                }

                cnt++;
        */
    }

    return 0;
}

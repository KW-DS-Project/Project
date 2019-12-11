#include "MsgQue.hpp"
#include "input.hpp"
#include "table.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

using namespace std;

void signalHandler(int signum);
string setName(int num);

key_t mykey = 0;
int msqid = 0;

int main(void) {

    Menu men;

    mykey = ftok("mykey", 1);
    msqid = msgget(mykey, IPC_CREAT | 0644);

    signal(SIGINT, signalHandler);

    // input menu;

    int sel; // select
    memset(&men, 0x00, sizeof(men));
    men.menu.setName();
    men.mytype = MENU_TYPE;
    while (1) {

        cout << "press 0 to Exit !!" << endl;
        cout << endl;

        cout << "1. SangHai spicy burger set" << endl;
        cout << "2. Double bulgogi burger set" << endl;
        cout << "3. Wapper set" << endl;
        cout << "4. Thai burger set" << endl;
        cout << "5. Mozzalela cheese burger set" << endl;
        cout << "6. Zinger burger set" << endl;

        cout << endl;
        cout << "Select burger set : ";
        cin >> sel;

        if (sel == 0)
            break;

        men.menu.plusMenu(sel - 1);
        // men.menu.printCount();
        for (int i = 0; i < MENU_LEN; i++) {
            if (men.menu.getMenu(i) != 0) {
                cout << setName(i) << ", " << men.menu.getMenu(i) << endl;
            }
        }
    }

    // memset(&men, 0x00, sizeof(men));
    // men.mytype = MENU_TYPE;
    // men.menu = menu;
    msgsnd(msqid, &men, MENU_SIZE, 0);
    cout << "send >>> " << endl;

    return 0;
}

void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}
string setName(int num) {
    string name[MENU_LEN];
    name[0] = "SangHai spicy burger set";
    name[1] = "Double bulgogi burger set";
    name[2] = "Wapper set";
    name[3] = "Thai burger set";
    name[4] = "Mozzalela cheese burger set";
    name[5] = "Zinger burger set";

    return name[num];
}

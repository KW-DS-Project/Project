#include "MsgQue.hpp"
#include "input.h"
#include <iostream>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

using namespace std;

key_t mykey = 0;
int msqid = 0;

void signalHandler(int signum);
string setName(int num);
int main() {
    mykey = ftok("mykey", 1);
    msqid = msgget(mykey, IPC_CREAT);

    Menu menu;

    // signal(SIGINT, signalHandler);

    puts("Chosen Menu: ...");

    memset(&menu, 0x00, sizeof(Menu));
    msgrcv(msqid, &menu, MENU_SIZE, MENU_TYPE, 0);

    cout << "--- Selected Menu ---" << endl;
    // menu.menu.printCount();
    for (int i = 0; i < MENU_LEN; i++) {
        if (menu.menu.getMenu(i) != 0) {
            cout << setName(i) << ", " << menu.menu.getMenu(i) << endl;
        }
    }

    memset(&menu, 0x00, sizeof(Menu));

    return 0;
}
// void signalHandler(int signum) {
//     if (signum == SIGINT) {
//         msgctl(msqid, IPC_RMID, NULL);
//         exit(0);
//     }
// }
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

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
int main() {
    mykey = ftok("mykey", 1);
    msqid = msgget(mykey, IPC_CREAT);

    Menu menu;

    // signal(SIGINT, signalHandler);

    puts("Chosen Menu: ...");

    memset(&menu, 0x00, sizeof(Menu));
    msgrcv(msqid, &menu, MENU_SIZE, MENU_TYPE, 0);

    cout << "--- Selected Menu ---" << endl;
    menu.menu.printCount();

    return 0;
}
// void signalHandler(int signum) {
//     if (signum == SIGINT) {
//         msgctl(msqid, IPC_RMID, NULL);
//         exit(0);
//     }
// }

#include "MyMsg.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <list>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void *myThread(void *arg);

pthread_t tid = 0;
key_t mykey = ftok("customer", 1);
key_t mykey1 = ftok("cusToServ", 2);
int msqid = msgget(mykey, IPC_CREAT);
int msqid1 = msgget(mykey1, IPC_CREAT);

list<MsgCus> cusList;
list<MsgCus>::iterator iter;

MsgCus msgCus;
MsgRslt msgRslt;
int menuTotal;
int cnt = 0;
int *status;

int main() {
    system("clear");
    cout << "----------현재 대기 중인 주문 목록---------- " << endl;
    while (1) {
        // 주문번호 및 해당 주문 내역 받기
        memset(&msgCus, 0x00, sizeof(MsgCus));
        msgrcv(msqid, &msgCus, MSG_SIZE_CUS, MSG_TYPE_CUS, 0);
        // 메뉴 개수 받아오기
        menuTotal = msgCus.menuTotal;

        cusList.push_back(msgCus);
        system("clear");
        cout << "----------현재 대기 중인 주문 목록---------- " << endl;
        // 주문번호 및 해당 주문내역 출력
        for (iter = cusList.begin(); iter != cusList.end(); ++iter) {
            MsgCus customer = *iter;
            /*** UI 설정 ***/
            cout << "주문 번호 : " << customer.num << endl << endl;
            for (int i = 0; i < menuTotal; i++) {
                if (customer.msgList[i].count !=
                    0) { // msgList: 메뉴를 담은 배열, name: 선택된 메뉴 이름,
                         // count: 선택된 메뉴 개수!
                    cout << "식사 : " << customer.msgList[i].name
                         << " " << customer.msgList[i].count << "개" << endl;
                }
            }
	    cout << "-------------------------------------------- " << endl;
        }
        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        msgRslt.mtype = IDX_STORE_SND;
        msgRslt.rslt = msgCus.num;
        msgsnd(msqid1, &msgRslt, MSG_SIZE_RSLT, 0);
        /*** UI 설정 ***/
        cout << "메인 서버로 전달합니다. :  " << msgRslt.rslt << "번" << endl;

        if (pthread_create(&tid, NULL, myThread, NULL)) {
            perror("pthread_create() error");
        }

        fflush(stdin);
        fflush(stdout);
    }

    return 0;
}

void *myThread(void *arg) {
    /*** UI 설정 ***/
    if (msgrcv(msqid1, &msgRslt, MSG_SIZE_RSLT, IDX_REMOVE_RCV, 0) > 0)
        cout << endl;
    for (iter = cusList.begin(); iter != cusList.end(); ++iter) {
        int number = iter->num;
        if (number == msgRslt.rslt) {
            cusList.erase(iter);
            break;
        }
    }
    pthread_exit((void *)&status);
}


#include "MyMsg.h"
#include <iostream>
#include <list>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

void *complete_order(void *arg);
void sendMsg(int qid, long type, int data);
void getMsg(int qid, int type);

MsgRslt msgRslt;
key_t mykey2;
key_t key_remove;

int msqid2;
int msqid_remove;

pthread_t tid = 0;
int status = 0;

list<int> orders;
list<int>::iterator iter;
// 주방에서 주문 받은 번호 관리 및 삭제 역할
int main(int argc, char const *argv[]) {
    printf("\033[2J\033[1;1H");

    mykey2 = ftok("mykey2", 3);
    msqid2 = msgget(mykey2, IPC_CREAT);

    // 주문 번호 받는 상태
    puts("wait...주문번호!");

    while (1) {
        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        getMsg(msqid2, IDX_STORE_RCV);
        orders.push_back(msgRslt.rslt);
        system("clear");
        /*** UI 설정 ***/
        puts("주문 번호 완료시에 q 입력 후 설정..");
        cout << "주문 번호: ";
        for (iter = orders.begin(); iter != orders.end(); ++iter) {
            cout << *iter << " ";
        }
        cout << endl;
        // 삭제 thread 실행
        if (pthread_create(&tid, NULL, complete_order, NULL)) {
            perror("pthread_create() error!");
            return -1;
        }
        fflush(stdin);
        fflush(stdout);
    }

    return 0;
}
// 완료된 주문 보내는 함수
void *complete_order(void *arg) {
    char ans;
    cin >> ans;
    if (ans == 'q') {
        /*** UI 설정 ***/
        cout << "완료된 주문번호를 입력해 주세요: ";
        int index;
        cin >> index;
        orders.remove(index);
        sendMsg(msqid2, IDX_REMOVE_SND, index);
        cout << index << " 삭제 완료..." << endl;
        sleep(1);
        system("clear");
        cout << "계속 주문 받는 중.." << endl;
        cin.clear();
    } else {
        cin.clear();
    }
    pthread_exit((void *)&status);
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

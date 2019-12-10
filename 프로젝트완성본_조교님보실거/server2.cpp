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
int *status;

list<int> orders;
list<int>::iterator iter;
// 주방에서 주문 받은 번호 관리 및 삭제 역할
int main(int argc, char const *argv[]) {
    printf("\033[2J\033[1;1H");

    mykey2 = ftok("mykey2", 3);
    msqid2 = msgget(mykey2, IPC_CREAT);

    // 주문 번호 받는 상태
    puts("----------현재 대기 중인 주문 목록----------");

    while (1) {
        memset(&msgRslt, 0x00, sizeof(MsgRslt));
        getMsg(msqid2, IDX_STORE_RCV);
        orders.push_back(msgRslt.rslt);
        system("clear");
        puts("----------현재 대기 중인 주문 목록----------");
        /*** UI 설정 ***/
        cout << "대기중인 주문 번호 : ";
        for (iter = orders.begin(); iter != orders.end(); ++iter) {
            cout << *iter << " ";
        }
        cout << endl << endl << endl << endl << endl << endl;
	puts("**** Enter 입력시 최신 주문을 갱신합니다.****");
        puts("**** 조리 완료 모드( q to remove mode ) ****");
        cout << ">> ";
        // 삭제 thread 실행
        if (cin && cin.peek() == 'q') {
            pthread_create(&tid, NULL, complete_order, NULL);
            pthread_join(tid, (void **)&status);
            cin.ignore();
        } else if (cin && cin.peek() == '\n')
            cin.ignore();
        else
            cin.ignore();
        // pthread_join(tid, (void **)&status);
        fflush(stdin);
        fflush(stdout);
    }

    return 0;
}
// 완료된 주문 보내는 함수
void *complete_order(void *arg) {
    // char ans;
    // cin >> ans;
    // if (ans == 'q') {
    /*** UI 설정 ***/
    cout << "조리가 완료된 주문 번호를 입력하세요 : ";
    int index;
    cin.ignore();
    cin >> index;
    orders.remove(index);
    sendMsg(msqid2, IDX_REMOVE_SND, index);
    cout << index << " 삭제가 완료 되었습니다." << endl;
    sleep(1);
    cout << "계속 주문 목록을 받는 중입니다." << endl;
    cin.clear();
    // } else {
    //     cin.clear();
    // }
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


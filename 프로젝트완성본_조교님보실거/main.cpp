#include "MyMsg.h"
#include "menuClass.hpp"
#include "order.hpp"
#include "people.hpp"
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <signal.h>
#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644

using namespace std;

void title();
void signalHandler(int signum);

order orderList[256];

key_t mykey = 0;
int msqid = 0;

void signalHandler(int signum) {
    if (signum == SIGINT) {
        msgctl(msqid, IPC_RMID, NULL);
        exit(0);
    }
}

int main(void) {
    int count = 0;

    ssize_t rSize = 0;
    menuClass menu;

    string filepath = "./menu.dat";
    int fd = open(filepath.c_str(), O_RDONLY, PERMS);
    if (fd == -1) {
        perror("open() error!");
        exit(-1);
    }

    do {
        rSize = read(fd, (menuClass *)&menu, sizeof(menuClass));

        if (rSize == sizeof(menuClass)) {
            orderList[count].setName(menu.getName());
            orderList[count].setCount(0);

            count++;
        } else if (rSize == -1) {
            perror("read() error!");
            exit(-2);
        }
    } while (rSize > 0);

    person people;

    int main_check;
    int menu_;
    int size;
    int order_num = 1;
    int pay;

    // 메세지 큐 부분

    MsgCus msgCus;

    mykey = ftok("customer", 1);             // 키 생성
    msqid = msgget(mykey, IPC_CREAT | 0600); // 메세지 큐 생성

    signal(SIGINT, signalHandler);

    //

    while (1) {
        for (int i = 0; orderList[i].getCount() != -1; i++) {
            orderList[i].setCount(0);
        }

        system("clear");
	int mypay = 0;

        cout << "                                      ('-.     _   .-')      "
                "('-.       .-') _               .-') _                        "
                "                                    "
             << endl;
        cout << "      .--,   .--,                    ( OO ).-.( '.( OO )_   ( "
                "OO ).-.  (  OO) )             ( OO ) )                        "
                "                 .--,   .--,       "
             << endl;
        cout << "  .--'  /.--'  /                     / . --. / ,--.   ,--.) / "
                ". --. /,(_)----.   ,-.-') ,--./ ,--,'  ,----.                 "
                "             .--'  /.--'  /        "
             << endl;
        cout << " /  ---`/  ---`                      | \\-.  \\  |   `.'   |  "
                "| \\-.  \\ |       |   |  |OO)|   \\ |  |\\ '  .-./-')        "
                "                  /  ---`/  ---`   "
             << endl;
        cout << "`--'   `--'                        .-'-'  |  | |         "
                "|.-'-'  |  |'--.   /    |  |  \\|    \\|  | )|  |_( O- )      "
                "                  `--'   `--'           "
             << endl;
        cout << "                                    \\| |_.'  | |  |'.'|  | "
                "\\| |_.'  |(_/   /     |  |(_/|  .     |/ |  | .--, \\        "
                "                                     "
             << endl;
        cout << "                                     |  .-.  | |  |   |  |  | "
                " .-.  | /   /___  ,|  |_.'|  |\\    | (|  | '. (_/            "
                "                                   "
             << endl;
        cout << "                                     |  | |  | |  |   |  |  | "
                " | |  ||        |(_|  |   |  | \\   |  |  '--'  |             "
                "                                   "
             << endl;
        cout << "                                     `--' `--' `--'   `--'  "
                "`--' `--'`--------'  `--'   `--'  `--'   `------'             "
                "                                     "
             << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "                       _  .-')     ('-.    .-')    .-') _     "
                " ('-.                 _  .-')     ('-.         .-') _  .-') _ "
                "                                   "
             << endl;
        cout << "      .--,   .--,      ( \\( -O )  _(  OO)  ( OO ). (  OO) )  "
                "  ( OO ).-.            ( \\( -O )   ( OO ).-.    ( OO ) )(  "
                "OO) )              .--,   .--,       "
             << endl;
        cout << "  .--'  /.--'  /        ,------. (,------.(_)---\\_)/     '._ "
                "  / . --. / ,--. ,--.   ,------.   / . --. /,--./ ,--,' /     "
                "'._         .--'  /.--'  /         "
             << endl;
        cout << " /  ---`/  ---`         |   /`. ' |  .---'/    _ | |'--...__) "
                " | \\-.  \\  |  | |  |   |   /`. '  | \\-.  \\ |   \\ |  |\\ "
                "|'--...__)       /  ---`/  ---`     "
             << endl;
        cout << "`--'   `--'             |  /  | | |  |    \\  :` `. '--.  "
                ".--'.-'-'  |  | |  | | .-') |  /  | |.-'-'  |  ||    \\|  | "
                ")'--.  .--'      `--'   `--'             "
             << endl;
        cout << "                        |  |_.' |(|  '--.  '..`''.)   |  |    "
                "\\| |_.'  | |  |_|( OO )|  |_.' | \\| |_.'  ||  .     |/    | "
                " |                                 "
             << endl;
        cout << "                        |  .  '.' |  .--' .-._)   \\   |  |   "
                "  |  .-.  | |  | | `-' /|  .  '.'  |  .-.  ||  |\\    |     | "
                " |                                 "
             << endl;
        cout << "                        |  |\\  \\  |  `---.\\       /   |  | "
                "    |  | |  |('  '-'(_.-' |  |\\  \\   |  | |  ||  | \\   |   "
                "  |  |                             "
             << endl;
        cout << "                        `--' '--' `------' `-----'    `--'    "
                " `--' `--'  `-----'    `--' '--'  `--' `--'`--'  `--'     "
                "`--'                                   "
             << endl;
        cout << endl;
        cout << "--------------------------------------------------------------"
                "--------------------------------------------------------------"
                "--------------------------------   "
             << endl;
        cout << endl;
        cout << "                               _         ___          _       "
                "                ____          ___        _ _                  "
                "                                   "
             << endl;
        cout << "                              / |       / _ \\ _ __ __| | ___ "
                "_ __            |___ \\        / _ \\ _   _(_) |_             "
                "                                   "
             << endl;
        cout << "                              | |      | | | | '__/ _` |/ _ "
                "\\ '__|             __) |      | | | | | | | | __|            "
                "                                     "
             << endl;
        cout << "                              | |  _   | |_| | | | (_| |  __/ "
                "|               / __/   _   | |_| | |_| | | |_                "
                "                                   "
             << endl;
        cout << "                              |_| (_)   \\___/|_|  "
                "\\__,_|\\___|_|              |_____| (_)   "
                "\\__\\_\\\\__,_|_|\\__|                                       "
                "   "
             << endl;
        cout << endl;
        cout << "--------------------------------------------------------------"
                "--------------------------------------------------------------"
                "--------------------------------   "
             << endl;
        cout << endl;

        cout << " 무엇을 하시겠습니까? (1. 주문하기, 2. 나가기) : ";
        cin >> main_check;

        int menuTotal;

        int password;
        if (main_check == 2) {
            cout << endl;
            cout << "-- exit mode(only staff) -- 비밀번호 숫자 네자리를 입력하세요 : ";
            cin >> password;
            if (password == 1234) {
                msgctl(msqid, IPC_RMID, NULL);
                break;
            } else {
                cout << "비밀 번호가 올바르지 않습니다." << endl;
		cout << "Enter 입력시 초기화면으로 돌아갑니다. " << endl;
                cin.ignore().get();
                continue;
            }

        } else if (main_check == 1) {
            while (1) {
                menuTotal = 0;

                int sel;

                system("clear");

                cout << " ------------- M  E  N  U --------------- " << endl;
		cout << " -------모 든  메 뉴  5 0 0 0 원 !!------ " << endl;
                cout << endl;
		for (int i = 0; orderList[i].getCount() != -1; i++) {
                    printf("     %d. %-28s\n", i + 1,
                           orderList[i].getName().c_str());
                    menuTotal = i + 1;
                }
		cout << endl;
		cout << " -------모 든  메 뉴  5 0 0 0 원 !!------ " << endl;
                cout << " ---------------------------------------- " << endl;
                cout << "  주문을 완료하시려면 0 을 입력해주세요!!" << endl << endl;
                cout << "  도움말을 보시려면 99 를 입력해주세요!!" << endl << endl;
                cout << "  이전 화면 출력은 100을 입력해누세요!!" << endl;
                cout << " **************************************** " << endl;
                cout << endl;
                cout << endl;

                cout << " 메뉴 번호 입력 >> ";

                cin >> sel;
                if (sel == 100)
                    break;
                else if (sel >= 1 && sel <= menuTotal) {
			
                    cout << endl << endl << endl << endl << endl << endl;
                    cout << " " << orderList[sel - 1].getName() << "(이)가 1개 추가되었습니다."
                         << endl;
		    mypay += 1;
                    orderList[sel - 1].countUp();

                    cout << " **************** 나의 주문 목록 *************** "
                         << endl;
                    for (int i = 0; i < menuTotal; i++) {
                        if (orderList[i].getCount() != -1 &&
                            orderList[i].getCount() != 0) {
                            cout << "  " << orderList[i].getName() << "      "
                                 << orderList[i].getCount() << "개" << endl;
                        }
                    }
                    cout << " *********************************************** "
                         << endl;
		    cout << endl;
		    cout << " Enter키를 누르면 주문 목록을 저장합니다. " << endl;

                    cin.ignore().get();
                } else if (sel == 99) {
                    system("clear");
                    cout << "                _              ____ _   _ ___ "
                            "____  _____       "
                         << endl;
                    cout << "   ___  _ __ __| | ___ _ __   / ___| | | |_ _|  _ "
                            "\\| ____|     "
                         << endl;
                    cout << "  / _ \\| '__/ _` |/ _ \\ '__| | |  _| | | || || "
                            "| | |  _|      "
                         << endl;
                    cout << " | (_) | | | (_| |  __/ |    | |_| | |_| || || "
                            "|_| | |___       "
                         << endl;
                    cout << "  \\___/|_|  \\__,_|\\___|_|     "
                            "\\____|\\___/|___|____/|_____| "
                         << endl;
                    cout << endl;
                    cout << " -------------------------------------------------"
                            "--------------"
                         << endl;
                    cout << endl;
                    cout << endl;
                    cout << " 1. 주문하실 메뉴의 번호를 입력하세요. " << endl;
                    cout << endl;
                    cout << " 2. 수량을 추가하시려면 1번을 반복해주세요. " << endl;
                    cout << endl;
                    cout << " 3. 원하신 메뉴와 수량을 모두 결정하셨으면 0번을 "
                            "입력하여 주문을 완료하세요. "
                         << endl;
                    cout << endl;
                    cout << " 4. 주문 번호를 꼭 확인하시고 식사 나오는 곳을 "
                            "통해 식사를 수령하세요. "
                         << endl;
                    cout << endl;
                    cout
                        << "             ※※※ 도움말은 10초 동안 안내됩니다. ※※※"
                        << endl;
                    sleep(10);

                    system("clear");
                } else if (sel == 0) {
                    system("clear");
                    cout << "		 -------------결제 방법을 "
                            "선택하십시오.-------------"
                         << endl;
                    cout << endl;
                    cout << endl;
                    cout << "						       "
                            "                        __              "
                         << endl;
                    cout << "						       "
                            "                       |  \\            "
                         << endl;
                    cout << "						   "
                            "_______  ______    _______ | $$____         "
                         << endl;
                    cout << " .------..------..------..------.     	"
                            "	 /       \\|      \\  /       \\| $$    \\     "
                         << endl;
                    cout << " |C.--. ||A.--. ||R.--. ||D.--. |		|  "
                            "$$$$$$$ \\$$$$$$\\|  $$$$$$$| $$$$$$$\\        "
                         << endl;
                    cout << " | :/\\: || (\\/) || :(): || :/\\: |	"
                            "	| $$      /      $$ \\$$    \\ | $$  | $$      "
                         << endl;
                    cout
                        << " | :\\/: || :\\/: || ()() || (__) |		| "
                           "$$_____|  $$$$$$$ _\\$$$$$$\\| $$  | $$        "
                        << endl;
                    cout << " | '--'C|| '--'A|| '--'R|| '--'D|		 \\$$  "
                            "   \\\\$$    $$|       $$| $$  | $$     "
                         << endl;
                    cout << " `------'`------'`------'`------'		  "
                            "\\$$$$$$$ \\$$$$$$$ \\$$$$$$$  \\$$   \\$$    "
                         << endl;
                    cout << "--------------------------------------------------"
                            "-------------------------------------------- "
                         << endl;
                    cout << endl;

                    while (1) {
			cout << "\t 주문 금액 : " << mypay*5000 << endl << endl; 
                        cout << " 1. 카드결제   2. 현금결제" << endl << endl;
                        cout << " >> 결제 방법을 선택하십시오. : ";
                        cin >> pay;

                        memset(&msgCus, 0x00, sizeof(MsgCus));
                        msgCus.mtype = MSG_TYPE_CUS;

                        if (pay == 1) {
                            // 사용자 인터페이스 출력
                            system("clear");
			    cout << endl;
                            cout << " ★★★★★★★★ " << mypay*5000 << "원  카드 결제가 완료되었습니다. ★★★★★★★★"
                                 << endl;
                            cout << endl;
                            cout << " \t\t     ● 주문번호 : " << order_num << endl;

                            cout << endl;
                            cout << " ★★★★★ 주문 번호를 꼭 확인하시고 "
                                    "기다려 주십시오. ★★★★★"
                                 << endl;

                            // poeple 초기화 세팅 (메뉴 수량)
                            people.setNum(order_num);
                            int j = 0;
                            for (int i = 0; i < menuTotal; i++) {
                                people.setOrder(j, orderList[i].getName(),
                                                orderList[i].getCount());
                                j++;
                            }

                            // 전달 값 세팅
                            msgCus.num = order_num;
                            msgCus.menuTotal = menuTotal;

                            for (int i = 0; i < menuTotal; i++) {
                                strcpy(msgCus.msgList[i].name,
                                       people.getOrder(i).name.c_str());
                                msgCus.msgList[i].count =
                                    people.getOrder(i).count;
                            }
                            for (int i = menuTotal; i < 7; i++) {
                                strcpy(msgCus.msgList[i].name, "noMenu");
                                msgCus.msgList[i].count = -1;
                            }

                            // 데이터 통신
                            if (msgsnd(msqid, &msgCus, MSG_SIZE_CUS, 0) == -1) {
                                perror("send error!");
                                exit(100);
                            }

                            order_num += 1;
                            sleep(5);
                            break;
                        } else if (pay == 2) {
                            // 사용자 인터페이스 출력
                            system("clear");
			    cout << endl;
                            cout << " ★★★★★★★★ " << mypay*5000 << "원  현금 결제가 완료되었습니다. ★★★★★★★★"
                                 << endl;
                            cout << endl;
                            cout << " \t\t     ● 주문번호 : " << order_num << endl;

                            cout << endl;
                            cout << " ★★★★★ 주문 번호를 꼭 확인하시고 "
                                    "기다려 주십시오. ★★★★★"
                                 << endl;

                            // people 값 초기화(메뉴 수량)
                            people.setNum(order_num);
                            int j = 0;
                            for (int i = 0; i < menuTotal; i++) {
                                people.setOrder(j, orderList[i].getName(),
                                                orderList[i].getCount());
                                j++;
                            }

                            // 전달 값 세팅
                            msgCus.num = order_num;
                            msgCus.menuTotal = menuTotal;
                            for (int i = 0; i < menuTotal; i++) {
                                strcpy(msgCus.msgList[i].name,
                                       people.getOrder(i).name.c_str());
                                msgCus.msgList[i].count =
                                    people.getOrder(i).count;
                            }
                            for (int i = menuTotal; i < 7; i++) {
                                strcpy(msgCus.msgList[i].name, "noMenu");
                                msgCus.msgList[i].count = -1;
                            }

                            // 통신 시도
                            if (msgsnd(msqid, &msgCus, MSG_SIZE_CUS, 0) == -1) {
                                perror("send error!");
                                exit(100);
                            }
                            order_num += 1;
                            sleep(3);
                            break;
                        } else {
                            cout << "올바른 결제 방식을 선택하십시오." << endl;
                            continue;
                        }
                    }
                    break;
                } else {
                    system("clear");
                    cout << "* 정확하지 않은 입력입니다. 다시 시도 하십시오. * "
                         << endl;
                    cin.ignore().get();
                    continue;
                }

            }
        }
        continue;
    }

    return 0;
}


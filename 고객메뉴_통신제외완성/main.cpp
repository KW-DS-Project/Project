#include "menuClass.hpp"
#include "order.hpp"
#include "people.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <list>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644

using namespace std;

void title();

order orderList[256];

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

    title();

    return 0;
}

void title() {
    person people;

    int main_check;
    int menu;
    int size;
    int order_num = 1;
    int pay;

    while (1) {

        for (int i = 0; orderList[i].getCount() != -1; i++) {
            orderList[i].setCount(0);
        }

        system("clear");

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
            cout << "프로그램 종료) 비밀번호 숫자 네자리를 입력하세요 : "
                 << endl;
            cin >> password;
            if (password == 1234) {
                break;
            } else {
                cout << "비밀 번호가 틀렸습니다. 초기화면으로 ..." << endl;
                cin.ignore().get();
                continue;
            }

        } else if (main_check == 1) {
            while (1) {
                menuTotal = 0;

                int sel;

                system("clear");

                cout << " ------------- M  E  N  U --------------- " << endl;
                for (int i = 0; orderList[i].getCount() != -1; i++) {
                    printf("     %d. %-28s \n", i + 1,
                           orderList[i].getName().c_str());
                    menuTotal = i + 1;
                }

                cout << " ---------------------------------------- " << endl;
                cout << "  선택을 완료하시려면 0 을 입력해주세요!!" << endl;
                cout << "  도움말을 보시려면 99 를 입력해주세요!!" << endl;
                cout << "  취소를 하시려면 100을 입력해누세요!!" << endl;
                cout << " **************************************** " << endl;
                cout << endl;
                cout << endl;

                cout << "입력 >> ";

                cin >> sel;
                if (sel == 100)
                    break;
                else if (sel >= 1 && sel <= menuTotal) {
                    cout << endl;
                    cout << orderList[sel - 1].getName() << "가 선택되었습니다."
                         << endl;
                    orderList[sel - 1].countUp();

                    cout << " **************** 총 주문 *************** "
                         << endl;
                    for (int i = 0; i < menuTotal; i++) {
                        if (orderList[i].getCount() != -1 &&
                            orderList[i].getCount() != 0) {
                            cout << "  " << orderList[i].getName() << " "
                                 << orderList[i].getCount() << "개" << endl;
                        }
                    }
                    cout << " **************************************** "
                         << endl;

                    cin.ignore().get();
                } else if (sel == 99) {
                    system("clear");
                    cout << endl;
                    cout << "     !!! 주문 중 도움말을 출력하면 주문 목록을 "
                            "잃어버리게 됩니다. !!!"
                         << endl;
                    cout << endl;
                    sleep(2);
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
                    cout << " 2. 선택하신 메뉴의 수량을 입력하세요. " << endl;
                    cout << endl;
                    cout << " 3. 원하신 메뉴를 모두 선택하셨으면 0번을 "
                            "입력하여 주문을 완료하세요. "
                         << endl;
                    cout << endl;
                    cout << " 4. 주문번호를 꼭 확인하시고 기다려 주시면 알림을 "
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
                        cout << " 1. 카드결제   2. 현금결제" << endl;
                        cout << endl;
                        cout << " >> 결제 방법을 선택하십시오. : ";
                        cin >> pay;

                        if (pay == 1) {
                            cout << endl;
                            cout << " >>> 카드 결제가 완료되었습니다. <<<"
                                 << endl;
                            cout << endl;
                            cout << " ● 주문번호 : " << order_num << endl;

                            cout << endl;
                            cout << " >>> 주문번호를 꼭 확인하시고 "
                                    "기다려주십시오. <<<"
                                 << endl;

                            people.setNum(order_num);
                            order_num += 1;

                            int j = 0;
                            for (int i = 0; i < menuTotal; i++) {
                                if (orderList[i].getCount() != 0) {
                                    people.setOrder(j, orderList[i].getName(),
                                                    orderList[i].getCount());
                                    j++;
                                }
                            }

                            /*
                            // 확인용 코드
                                                        cout << endl << endl <<
                            "****" << endl; cout << "주문번호 : " <<
                            people.getNum() << endl; for (int i = 0; i < j; i++)
                            {

                                                            cout << "메뉴이름 :
                            " << people.getOrder(i).name
                                                                 << endl;
                                                            cout << "수량 : " <<
                            people.getOrder(i).count
                                                                 << endl;
                                                        }
                                                        cout << endl;
                            */

                            sleep(3);
                            break;
                        } else if (pay == 2) {
                            cout << endl;
                            cout << " >>> 현금 결제가 완료되었습니다. <<<"
                                 << endl;
                            cout << endl;
                            cout << " ● 주문번호 : " << order_num << endl;

                            cout << endl;
                            cout << " >>> 주문번호를 꼭 확인하시고 "
                                    "기다려주십시오. <<<"
                                 << endl;

                            people.setNum(order_num);
                            order_num += 1;

                            int j = 0;
                            for (int i = 0; i < menuTotal; i++) {
                                if (orderList[i].getCount() != 0) {
                                    people.setOrder(j, orderList[i].getName(),
                                                    orderList[i].getCount());
                                    j++;
                                }
                            }

                            /*
                            // 확인용 코드
                                                        cout << endl << endl <<
                            "****" << endl; cout << "주문번호 : " <<
                            people.getNum() << endl; for (int i = 0; i < j; i++)
                            {

                                                            cout << "메뉴이름 :
                            " << people.getOrder(i).name
                                                                 << endl;
                                                            cout << "수량 : " <<
                            people.getOrder(i).count
                                                                 << endl;
                                                        }
                                                        cout << endl;
                            */

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
                    cout << "* 잘못 입력 하셨습니다 !!! 다시 입력해 주세요 !!!"
                         << endl;
                    cin.ignore().get();
                    continue;
                }
            }
        }

        continue;
    }
}

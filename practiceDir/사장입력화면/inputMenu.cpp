#include "menuClass.hpp"
#include <fcntl.h>
#include <iostream>
#include <list>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(void) {
    list<menuClass> menuList;
    while (1) {
        string input;

        cout << "메뉴 이름을 입력하세요 (q 입력시 종료 ) : ";
        cin >> input;

        if (input.compare("q") == 0) {
            cout << "메뉴 저장이 종료되었습니다." << endl;
            break;
        }

        menuClass menu(input);

        menuList.push_back(menu);
        cout << input << " 메뉴의 저장이 완료되었습니다." << endl << endl;
    }

    string filepath = "./menu.dat";
    int fd = open(filepath.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1) {
        perror("open() error!");
        return 1;
    }

    list<menuClass>::iterator iter;
    for (iter = menuList.begin(); iter != menuList.end(); ++iter) {
        if (write(fd, &(*iter), sizeof(menuClass)) == -1) {
            perror("write() error");
            return 2;
        }
    }

    close(fd);

    cout << endl;
    cout << "데이터 저장이 완료되었으니 프로그램을 종료합니다!" << endl;
}

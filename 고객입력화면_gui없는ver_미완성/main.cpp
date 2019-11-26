#include "menuClass.hpp"
#include "order.hpp"
#include <fcntl.h>
#include <iostream>
#include <list>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PERMS 0644

using namespace std;

int main(void) {
    int count = 0;

    order orderList[256];

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

    for (int i = 0; orderList[i].getCount() != -1; i++) {
        cout << "메뉴 이름 : " << orderList[i].getName() << endl;
        cout << "수량     : " << orderList[i].getCount() << endl;
    }

    return 0;
}

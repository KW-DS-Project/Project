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
    system("clear");
    list<menuClass> menuList;
    cout << ".___  ___.  _______ .__   __.  __    __          _______. _______ .___________.___________. __  .__   __.   _______      " << endl;
    cout << "|   \\/   | |   ____||  \\ |  | |  |  |  |        /       ||   ____||           |           ||  | |  \\ |  |  /  _____|  " << endl;
    cout << "|  \\  /  | |  |__   |   \\|  | |  |  |  |       |   (----`|  |__   `---|  |----`---|  |----`|  | |   \\|  | |  |  __    " << endl;
    cout << "|  |\\/|  | |   __|  |  . `  | |  |  |  |        \\   \\    |   __|      |  |        |  |     |  | |  . `  | |  | |_ |   " << endl;
    cout << "|  |  |  | |  |____ |  |\\   | |  `--'  |    .----)   |   |  |____     |  |        |  |     |  | |  |\\   | |  |__| |    " << endl;
    cout << "|__|  |__| |_______||__| \\__|  \\______/     |_______/    |_______|    |__|        |__|     |__| |__| \\__|  \\______|  " << endl;
    cout << endl;
    cout << "**********************************************O N L Y * M A N A G E R**********************************************" << endl;
    cout << "**********************************************O N L Y * M A N A G E R**********************************************" << endl;
    cout << endl;
    cout << endl;
	
    while (1) {
        string input;
	
        cout << " > 메뉴 이름을 입력하세요 ( q 입력시 종료 ) : ";
        cin >> input;

        if (input.compare("q") == 0) {
            cout << " 메뉴 저장이 모두 완료되었습니다." << endl;
            break;
        }

        menuClass menu(input);

        menuList.push_back(menu);
        cout <<"        >> " << input << " 메뉴가 저장되었습니다. << " << endl << endl;
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
    cout << "프로그램을 종료합니다!" << endl;
    cout << "**********************************************O N L Y * M A N A G E R**********************************************" << endl;
    cout << "**********************************************O N L Y * M A N A G E R**********************************************" << endl;
}

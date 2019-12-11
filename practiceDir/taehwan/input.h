#pragma once

#include <iostream>
#include <string>
#define MENU_LEN 6

using namespace std;

class input {
  private:
    string name[MENU_LEN] = {"SangHai spicy burger set",
                             "Double bulgogi burger set",
                             "Wapper set",
                             "Thai burger set",
                             "Mozzalela cheese burger set",
                             "Zinger burger set"};

    int menu[MENU_LEN] = {
        0,
    };

  public:
    void plusMenu(int num) { (this->menu[num])++; }
    int getMenu(int num) { return this->menu[num]; }
    void printCount() {
        for (int i = 0; i < MENU_LEN; i++) {
            if (menu[i] != 0) {
                cout << name[i] << ", " << menu[i] << endl;
            }
        }
    }
};

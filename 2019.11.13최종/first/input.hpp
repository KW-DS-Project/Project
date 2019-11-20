#pragma once

#include <iostream>
#include <string>
#define MENU_LEN 6

using namespace std;

class input {
  private:
    string name[MENU_LEN]; //= {"SangHai spicy burger set",
    // "Double bulgogi burger set", "Wapper set", "Thai burger set",
    //     "Mozzalela cheese burger set", "Zinger burger set"};

    int menu[MENU_LEN] = {
        0,
    };

  public:
    // input() {
    //     name[0] = "SangHai spicy burger set";
    //     name[1] = "Double bulgogi burger set";
    //     name[2] = "Wapper set";
    //     name[3] = "Thai burger set";
    //     name[4] = "Mozzalela cheese burger set";
    //     name[5] = "Zinger burger set";
    // }
    void setName() {
        name[0] = "SangHai spicy burger set";
        name[1] = "Double bulgogi burger set";
        name[2] = "Wapper set";
        name[3] = "Thai burger set";
        name[4] = "Mozzalela cheese burger set";
        name[5] = "Zinger burger set";
    }
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

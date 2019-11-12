#include "input.h"
#include "table.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int main(void) {
    input menu;

    int sel; // select

    while (1) {
        cout << endl;
        cout << "1. SangHai spicy burger set" << endl;
        cout << "2. Double bulgogi burger set" << endl;
        cout << "3. Wapper set" << endl;
        cout << "4. Thai burger set" << endl;
        cout << "5. Mozzalela cheese burger set" << endl;
        cout << "6. Zinger burger set" << endl;

        cout << endl;
        cout << "Select burger set : ";
        cin >> sel;

        menu.plusMenu(sel - 1);
        menu.printCount();
    }

    return 0;
}

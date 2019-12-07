#include "people.hpp"
#include <string.h>
#include <string>

person::person() {
    for (int i = 0; i < 256; i++) {
        (this->order[i]).name = "";
        (this->order[i]).count = -1;
    }
    this->num = -1;
}

void person::setOrder(int index, std::string name, int count) {
    (this->order[index]).name = name;
    (this->order[index]).count = count;
}

void person::setNum(int num) { this->num = num; }

Ordered person::getOrder(int index) { return order[index]; }

int person::getNum() { return num; }

int person::getPresent() { //
    int count = 1;

    for (int i = 0; num != -1; i++) {
        count++;
    }

    return count;
}

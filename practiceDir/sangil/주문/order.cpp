#include "order.hpp"
#include <string.h>
#include <string>

order::order() {
    this->menuName = "";
    this->menuCount = -1;
}

order::order(std::string name, int menuCount) {
    this->menuName = name;
    this->menuCount = menuCount;
}

void order::countUp() { (this->menuCount)++; }
void order::countDown() { (this->menuCount)--; }

void order::setName(std::string name) { this->menuName = name; }
void order::setCount(int menuCount) { this->menuCount = menuCount; }

std::string order::getName() { return menuName; }
int order::getCount() { return menuCount; }

#include "menuClass.hpp"
#include <string.h>
#include <string>

menuClass::menuClass() { memset(this->name, 0x00, MAX_MENU_LEN + 1); }
menuClass::menuClass(std::string name) {
    memcpy(this->name, name.c_str(), MAX_MENU_LEN);
}

void menuClass::setName(std::string name) {
    memcpy(this->name, name.c_str(), MAX_MENU_LEN);
}

std::string menuClass::getName() { return std::string(this->name); }


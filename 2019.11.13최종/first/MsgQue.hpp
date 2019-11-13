#ifndef __MSGQUE_H__
#define __MSGQUE_H__

#include "input.hpp"

#define MENU_TYPE 1 // 숫자

#define MENU_SIZE (sizeof(Menu) - sizeof(long))

struct __Menu {
    long mytype;
    input menu;
};
typedef struct __Menu Menu;

#endif //!__MSGQUE_H__

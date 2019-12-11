#ifndef __MSGQUE_H__
#define __MSGQUE_H__

#include "input.h"

#define MENU_TYPE 1 // 숫자

#define MENU_SIZE (sizeof(input) - sizeof(long))

struct __Menu {
    long mytype;
    input menu;
};
typedef struct __Menu Menu;

#endif //!__MSGQUE_H__

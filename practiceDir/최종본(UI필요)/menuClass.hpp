#ifndef __MENUCLASS_H__
#define __MENUCLASS_H__

#include <string>

#define MAX_MENU_LEN 256

class menuClass {
  public:
    menuClass();
    menuClass(std::string name);

    void setName(std::string name);
    std::string getName(void);

  private:
    char name[MAX_MENU_LEN + 1];
};

#endif

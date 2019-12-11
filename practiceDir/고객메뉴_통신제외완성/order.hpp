#ifndef __ORDER_H__
#define __ORDER_H__
#include <string>

class order {
  public:
    order();
    order(std::string name, int menuCount);

    void setName(std::string name);
    void setCount(int count);

    std::string getName(void);
    int getCount(void);

    void countUp();
    void countDown();

  private:
    std::string menuName;
    int menuCount;
};

#endif

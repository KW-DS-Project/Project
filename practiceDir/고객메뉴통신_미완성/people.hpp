#ifndef __PEOPLE_H__
#define __PEOPLE_H__
#include <string>

typedef struct ordered {
    std::string name;
    int count;
} Ordered;

class person {
  public:
    person();
    void setOrder(int index, std::string name, int count);
    void setNum(int num);
    Ordered getOrder(int index);
    int getNum();

    int getPresent();

  private:
    Ordered order[256]; // 시킨 것 이름과 갯수 셋트 (배열)
    int num;            // 주문번호
};

#endif

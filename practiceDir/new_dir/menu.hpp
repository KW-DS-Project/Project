#include <string>
using namespace std;

class menuClass {
  private:
    string menu[10];
    int cnt[10];

  public:
    void setMenu(int i, string menu) { this->menu[i] = menu; }
    void setCnt(int i, int cnt) { this->cnt[i] = cnt; }
    string getMenu(int i) { return menu[i]; }
    int getCnt(int i) { return cnt[i]; }
};

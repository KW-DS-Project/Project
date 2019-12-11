class seat {
  private:
    bool table[5];

  public:
    void emptyTable() {
        for (int i = 0; i < 5; i++)
            table[i] = true;
    }
    void setTable(int num) { table[num] = false; }
};

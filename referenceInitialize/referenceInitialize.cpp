#include <iostream>

class T {
public:
  T(int v) : v_(v) {}
  int v() const {return v_;}
private:
  int v_;
};

class C {
public:
  C(const T& t = *new T(2)) : t_(t) {}
  void print() const {std::cout << "v= " << t_.v() << std::endl;}
private:
  const T& t_;
};

int main() {
  T t(1);
  C c(t);
  c.print();

  C cc;
  cc.print();

  return 0;
}


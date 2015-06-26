#include <iostream>

class Test {
public:
  enum T {A, B, C};
  Test(T vv) : v(vv) {};
  void test(std::string s) {
    std::cout << "v " + s + " = ";
    
    switch (v) {
    case A :
      std::cout << "A";
      break;
    case B :
      std::cout << "B";
      break;
    case C :
      std::cout << "C";
      break;
    default :
      std::cout << "ERR";
    }
    std::cout << std::endl;
  };

private:
  T v;
};


int main() {
  Test a(Test::A);
  Test b(Test::B);

  a.test("1");
  b.test("2");

  return 0;
}


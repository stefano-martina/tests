#include<iostream>

class Cla {
public:
  int val;
  Cla(int newval) {
    val = newval;
  }
};

int main() {
  Cla* point = new Cla(42);
  Cla* point2 = point;
  
  std::cout << "first " << point->val << std::endl;
  delete point;
  std::cout << "second " << point->val << std::endl;
  std::cout << "third " << point2->val << std::endl;

  return 0;
}

  

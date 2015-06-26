#include<iostream>

class Cla {
public:
  static const int var = 42;
};

int main() {
  std::cout << "var= " << Cla::var << std::endl;

  return 0;
}


#include<iostream>

void func(int p1, int p2 = 2, int p3 = 3) {
  std::cout << "p1=" << p1 << ", p2=" << p2 << ", p3=" << p3 << std::endl;
}

int main() {
  func(10);
  func(10, 20);
  func(10, 20, 30);

  //ERROR
  //func(10,,30);
  
  return 0;
}

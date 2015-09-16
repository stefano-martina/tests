#include <iostream>

void printNumber() {
 static int otherCount=0;
 std::cout << otherCount << std::endl;
 otherCount++; 
}

int main(int argc, char* argv[]) {
  int count=42;
  std::cout << count << std::endl;
  printNumber();
  printNumber();
  printNumber();
  return 0;
}

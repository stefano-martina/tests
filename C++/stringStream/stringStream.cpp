#include <iostream>
#include <sstream>

int main() {
  std::stringstream stringStreamVar;
  std::string stringVar;
  int i = 42;
  stringStreamVar << "test " << i;
  stringStreamVar >> stringVar;
  std::cout << stringVar << std::endl;

  stringStreamVar << "test-" << i;
  stringStreamVar >> stringVar;
  std::cout << stringVar << std::endl;
  


  std::stringstream stringStreamVar2;
  std::string stringVar2;
  stringStreamVar2 << "test2 " << i;
  stringVar2 = stringStreamVar2.str();
  std::cout << stringVar2 << std::endl;

  stringStreamVar2 << "test2-" << i;
  stringVar2 = stringStreamVar2.str();
  std::cout << stringVar2 << std::endl;
  
return 0;
}


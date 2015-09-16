#include <iostream>

int main() {
  std::string str("pippo");
  bool comp = std::string("pippo").compare("pippo") == 0;
  std::cout << comp << std::endl;

  return 0;
}


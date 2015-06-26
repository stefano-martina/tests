#include <map>
#include <iostream>
#include <stdexcept>

int main() {
  std::map<std::pair<int, int>, double> matrix = {
    {{1,1}, 1.1}, {{1,2}, 1.2},
    {{2,1}, 2.1}, {{2,2}, 2.2}
  };

  try {
    std::cout << "M[2,1] = " << matrix.at(std::make_pair(2,1)) << std::endl;
    std::cout << "M[1,2] = " << matrix.at({1,2}) << std::endl;
    std::cout << "M[2,3] = " << matrix.at({2,3}) << std::endl;
  } catch (const std::out_of_range& ex) {
    std::cerr << "Out of range. " << ex.what() << std::endl;
  }
    
  return 0;
}

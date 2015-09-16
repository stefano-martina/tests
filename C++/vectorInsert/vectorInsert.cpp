#include<vector>
#include<iostream>

int main() {
  std::vector<int> vec;
  vec.push_back(2);
  vec.push_back(3);
  
  vec.insert(vec.begin(), 4);
  
  std::cout << "vec =";
  for(int v : vec) {
    std::cout << " " << v;
  }
  std::cout << std::endl;

  return 0;
}

#include <boost/ptr_container/ptr_vector.hpp>
#include <iostream>

class Classe {
public:
  int value;
  Classe(int newval) : value(newval) {};
};

int main() {
  boost::ptr_vector<Classe> vec;
  Classe* one = new Classe(1);
  Classe* two = new Classe(2);
  Classe* three = new Classe(3);
  vec.push_back(two);
  vec.push_back(three);
  
  vec.insert(vec.begin(), one);
  
  std::cout << "vec =";
  for(auto& v : vec) {
    std::cout << " " << v.value;
  }
  std::cout << std::endl;

  return 0;
}

#include <vector>
#include <iostream>
#include <algorithm>

class Type {
public:
  Type(int v) : value(v) {};
  Type(const Type& original) : Type(original.value) {};

  int value;
};
  
typedef std::vector<Type*> PointersVector;
  
int main() {
  PointersVector vect;
  vect.push_back(new Type(1));
  vect.push_back(new Type(2));
  vect.push_back(new Type(3));

  PointersVector shallowCopy = vect;
  PointersVector deepCopy;

  
  std::for_each(vect.begin(), vect.end(), [](Type* current) {
      //      deepCopy.push_back(new Type(*current));
    });
  
  //for(auto& p : vect) deepCopy.push_back(new Type(*p));

  shallowCopy.front()->value = 4;
  deepCopy.front()->value = 5;

  std::cout << "vect:";
  for(auto& i : vect) std::cout << " " << i->value;

  std::cout << std::endl << "shallowCopy:";
  for(auto& i : shallowCopy) std::cout << " " << i->value;

  std::cout << std::endl << "deepCopy:";
  for(auto& i : deepCopy) std::cout << " " << i->value;

  std::cout << std::endl;

  return 0;
}


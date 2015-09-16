#include<iostream>
#include<vector>

class Functor {
public:
  Functor() {}

  int operator()(int a, int b) {
    return a+b;
  }
};

int main() {
  Functor func;
  std::cout << "func " << func(1,2) << std::endl;


  Functor* funcP;
  std::cout << "funcP " << (*funcP)(1,2) << std::endl;


  std::vector<Functor*> funcV;
  funcV.push_back(funcP);

  for(std::vector<Functor*>::iterator funcIter = funcV.begin(); funcIter != funcV.end(); ++funcIter) {
    std::cout << "funcV1 " << (**funcIter)(1,2) << std::endl;

    Functor& funcR = **funcIter;
    std::cout << "funcV1 " << funcR(1,2) << std::endl;
  }

  return 0;
}

#include <vector>
#include <iostream>

class C {
public:
  C(int nv) : v(nv) {};
  void setV(int nv) {v = nv;};
  int getV() {return v;};
private:
  int v;
};

int main() {
  std::vector<C> vec;

  C c1(1);
  C* c2 = new C(2);
  C* c3 = new C(3);
  C* c4 = new C(4);
  C* c5 = new C(5);
  C* c6 = new C(6);

  vec.push_back(c1);
  vec.push_back(*c2);
  vec.push_back(*c3);
  vec.push_back(*c4);
  vec.push_back(*c5);
  vec.push_back(*c6);

  c3->setV(-3);

  C v = vec.at(3);
  v.setV(-4);

  C* p = & vec.at(4);
  C* p2 = & vec.at(4);
  p->setV(-5);

  C& r = vec.back();
  r.setV(-6);

  for(C& i : vec) {
    std::cout << "v = " << i.getV() << std::endl;
  }  

  std::cout << "c3 = " << c3->getV() << std::endl;
  std::cout << "p2 = " << p2->getV() << std::endl;

}


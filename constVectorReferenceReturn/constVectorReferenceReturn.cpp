#include <vector>
#include <iostream>

class T {
public:
  T(int vv) : v_(vv) {};
  int v() {return v_;};
  void v(int vv) {v_ = vv;};
private:
  int v_;
};

class C {
public:
  C() {
    T* t1 = new T(1);
    T* t2 = new T(2);
    T* t3 = new T(3);
    vec_.push_back(t1);
    vec_.push_back(t2);
    vec_.push_back(t3);
  };
    
  const std::vector<T*>& vec() const {return vec_;};

  void print() {
    std::cout << "vec:";
    for(T* t : vec_) {
      std::cout << " " << t->v();
    }
    std::cout << std::endl;
  };
  
private:
  std::vector<T*> vec_;
};

int main() {
  C c;

  c.print();

  const std::vector<T*>& vecr = c.vec();

  vecr.front()->v(-1);

  //compiler error:
  //T* tt2 = new T(-2);
  //vecr.push_back(tt2);


  c.print();
  
  
  return 0;
}


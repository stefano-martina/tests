#include <iostream>

class T {
public:
  T(int vv) : v_(vv) {}
  
  int v() {
    return v_;
  }
  
  void v(int vv) {
    v_ = vv;
  }
private:
  int v_;
};

class C {
public:
  C(int tt) {
    t_ = new T(tt);
  }
    
  T* t() const {
    return t_;
  }

  void print() {
    std::cout << "t: " << t_->v() << std::endl;
  }
  
private:
  T* t_;
};


int main() {
  C c(1);

  c.print();
  c.t()->v(2);
  c.print();

  return 0;
}


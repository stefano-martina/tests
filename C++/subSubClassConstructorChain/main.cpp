class A {
public:
  A(int vv) : v(vv) {}
private:
  int v;
};

class B : public A {
public:
  B() {}
};

class C : public B {
public:
  C(int vv) : A(vv) {}
};

int main() {
  C c(1);

  return 0;
}
  


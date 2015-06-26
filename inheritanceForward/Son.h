#ifndef SON_H
#define SON_H

//FORWARD DECLARATION DON'T WORK
//class Base;
#include "Base.h"

class Son : public Base {
 public:
  Son(){};
  virtual ~Son() {}
  void print();
};

#endif
 

#include<set>
#include<iostream>

int main() {
  std::set<int> intSet;
  
  intSet.insert(1);
  intSet.insert(2);
  intSet.insert(2);
  intSet.insert(3);

  for(std::set<int>::iterator iter = intSet.begin(); iter != intSet.end(); ++iter) {
    std::cout<<"intSet "<<*iter<<std::endl;
  }


  std::set<std::string> stringSet;
  
  stringSet.insert(std::string("uno"));
  stringSet.insert(std::string("due"));
  stringSet.insert(std::string("due"));
  stringSet.insert(std::string("tre"));

  for(std::set<std::string>::iterator iter = stringSet.begin(); iter != stringSet.end(); ++iter) {
    std::cout<<"stringSet "<<*iter<<std::endl;
  }


  return 0;
}

  

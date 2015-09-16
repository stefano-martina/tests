#include<set>
#include<iostream>

int main(){
  std::set<std::string*> set;

  std::string* uno = new std::string("uno");
  std::string* due = new std::string("due");
  std::string* tre = new std::string("tre");

  set.insert(uno);
  set.insert(due);
  set.insert(tre);

  set.erase(set.begin());
  set.erase(set.find(due));
  //set.erase(set.find(due)); ERROR

  std::cout << "find2 " << (set.find(due) != set.end()) << std::endl;
  std::cout << "find3 " << (set.find(tre) != set.end()) << std::endl;


  std::cout << "strings: " << *uno << " " << *due << " " << *tre << std::endl;
  std::cout << "set: ";
  for(std::set<std::string*>::iterator iter = set.begin(); iter != set.end(); ++iter) {
    std::cout << **iter << " ";
  }
  std::cout << std::endl;

  return 0;
}


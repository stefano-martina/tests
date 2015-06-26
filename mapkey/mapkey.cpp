#include <map>
#include <string>
#include <iostream>

std::map<std::map<int, int>, std::string> globalMap;

void printMap(const std::map<int, int>& myMap) {
  std::cout << globalMap[myMap] << std::endl;
  std::map<int, int> copyMap;
  for (const auto it : myMap) {
    std::cout << it.first << " = " <<it.second << std::endl;
    copyMap.insert(it);
  } 
  for (auto it : copyMap) {
    std::cout << "Copied into " << it.first << " = " <<it.second << std::endl;
  }
}

int main() {
  std::map<int, int> aMapKey;
  aMapKey[1]=1;
  aMapKey[2]=1;
  aMapKey[3]=2;
  aMapKey[4]=3;
  aMapKey[5]=5;
  aMapKey[6]=8;
  aMapKey[7]=13;
  std::map<int, int> aMapKey2;
  aMapKey2[1]=10;
  aMapKey2[2]=20;
  aMapKey2[3]=30;
  globalMap[aMapKey]="Fibo";
  globalMap[aMapKey2]="Perdieci";
  printMap(aMapKey);
  if (aMapKey < aMapKey2) std::cout << "Minore" << std::endl;
  return 0;
}

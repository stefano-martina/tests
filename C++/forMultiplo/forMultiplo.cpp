#include<iostream>
#include<vector>

int main() {
  int arr [5] = {1,2,3,4,5};

  int i, j;
  for(i = 0, j = i+1; j<5; ++j, ++i){
    std::cout << "arr " << arr[i] << " " << arr[j] << std::endl;
  }


  std::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);

  std::vector<int>::iterator vecIter1;
  std::vector<int>::iterator vecIter2;
  //for(vecIter1 = vec.begin(), vecIter2 = vec.begin(), ++vecIter2; vecIter2 != vec.end(); ++vecIter1, ++vecIter2) {
  for(vecIter1 = vec.begin(), vecIter2 = vecIter1 + 1; vecIter2 != vec.end(); ++vecIter1, ++vecIter2) {
    std::cout << "vec " << *vecIter1 << " " << *vecIter2 << std::endl;
  }

  return 0;
}

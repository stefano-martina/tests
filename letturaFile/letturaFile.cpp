#include <fstream>
#include <iostream>
#include <sstream>

int main() {
  std::ifstream file("in.csv", std::ios::in);
  std::string line;
  std::string fieldString;
  int field1;
  std::string field2;
  double field3;
  
  while(std::getline(file, line)) {
    std::stringstream lineStream(line);

    std::getline(lineStream, fieldString, ',');
    std::stringstream field1Stream(fieldString);
    field1Stream >> field1;

    std::getline(lineStream, fieldString, ',');
    std::stringstream field2Stream(fieldString);
    field2Stream >> field2;

    std::getline(lineStream, fieldString, ',');
    std::stringstream field3Stream(fieldString);
    field3Stream >> field3;

    std::cout << field1 << "," << field2 << "," << field3 << std::endl;
  }

  file.close();
  return 0;
}

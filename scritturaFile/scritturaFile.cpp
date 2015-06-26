#include <fstream>

int main() {
  //std::ios::app append to existing file
  std::ofstream file("output.txt", std::ios::out | std::ios::app);
  file << "Hello world" << std::endl;
  file.close();
  return 0;
}

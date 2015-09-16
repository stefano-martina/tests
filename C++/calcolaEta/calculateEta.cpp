#include <string>
#include <iostream>
#include <cmath>
#include <exception>

int main(int argc, char** argv) {
  float z,r,l,eta;

  if (argc < 3) {
    std::cout << "Use: \"" << argv[0] << " z r\"" << std::endl;
    return 1;
  }
  
  try {
    z = std::stof(argv[1]);
    r = std::stof(argv[2]);
    l = sqrt(z*z + r*r);
    eta = - log(sqrt((l-z)/(l+z)));
  } catch(std::exception& e) {
    std::cout << "Exception in: " << e.what() << std::endl;
    return 2;
  }
  
  std::cout << "Eta = " << eta << std::endl;
  return 0;
}

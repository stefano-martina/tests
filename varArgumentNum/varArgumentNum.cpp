#include <iostream>
#include <cstdarg>


void funcErr(double* vec) {
  int vecSize = sizeof(vec)/sizeof(double);
  std::cout << "ERR, size: " << vecSize << std::endl;
}

void funcOk(int vecSize, double* vec) {
  std::cout << "OK, size: " << vecSize << std::endl;
  for(int i=0; i<vecSize; ++i) {
    std::cout << "    " << vec[i] << std::endl;
  }
}

void funcVar(int n, ...) {
  va_list vl;
  va_start(vl, n);
  std::cout << "VAR, size: " << n << std::endl;
  for(int i=0; i<n; i++) {
    std::cout << "    " << va_arg(vl, double) << std::endl;
  }
  va_end(vl);
}

int main() {
  double vec[] = {1.1, 2.2, 3.3};
  funcErr(vec);
  funcOk(sizeof(vec)/sizeof(double), vec);
  funcVar(3, 1.1, 2.2, 3.3);
  return 0;
}

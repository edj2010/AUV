#include <iostream>
#include "Eyes.h"

int main(){
  Eyes vision;
  double error = vision.getErrorLine(0,0,0,10,50);
  if(error < 1)
    std::cout << error << std::endl;
  else
    std::cout << "steep" << std::endl;
}

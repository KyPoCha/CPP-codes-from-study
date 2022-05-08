#include "matrix.h"
#include "CGem.h"
#include <iostream>

CGem::CGem(CMatrix matice) : _matice(matice){}

 void CGem::RunGem(){
  if(CheckForGem()){
    _matice.GEM();
  }
  else{
    std::cout << "Try Again! Invalid Matrix" << '\n';
  }
}

bool CGem::CheckForGem(){
  return _matice.rows() != _matice.cols();
}

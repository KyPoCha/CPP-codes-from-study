#include "matrix.h"
#include "CGemKomentare.h"
#include <iostream>

CGemKomentare::CGemKomentare(CMatrix a) : CGem(a){}

void CGemKomentare::RunGem(){
  if(CheckForGem()){
    _matice.GEMsKomentarem();
  }
  else{
    std::cout << "Try again! Invalid Matrix" << '\n';
  }
}

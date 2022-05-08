#include "DiffMatrix.h"
#include "matrix.h"

DiffMatrix::DiffMatrix(CMatrix first, CMatrix second) : _first(first) , _second(second){}

CMatrix DiffMatrix::Operation(){
  CMatrix result = _first - _second;
  return result;
}

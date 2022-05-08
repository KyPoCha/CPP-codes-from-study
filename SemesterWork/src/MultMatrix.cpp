#include "MultMatrix.h"
#include "matrix.h"

MultMatrix::MultMatrix(CMatrix first, CMatrix second) : DiffMatrix(first,second){}

CMatrix MultMatrix::Operation(){
  CMatrix result = _first * _second;
  return result;
}

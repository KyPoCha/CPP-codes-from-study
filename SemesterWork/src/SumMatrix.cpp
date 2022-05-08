#include "SumMatrix.h"
#include "matrix.h"

SumMatrix::SumMatrix(CMatrix first, CMatrix second) : DiffMatrix(first,second){}

CMatrix SumMatrix::Operation(){
  CMatrix result = _first + _second;
  return result;
}

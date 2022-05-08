#ifndef SUMMATRIX_H
#define SUMMATRIX_H

#include "matrix.h"
#include "DiffMatrix.h"
class SumMatrix : public DiffMatrix{
public:
  SumMatrix(CMatrix first, CMatrix second);

  CMatrix Operation() override;
};

#endif

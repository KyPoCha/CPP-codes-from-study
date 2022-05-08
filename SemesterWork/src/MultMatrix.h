#ifndef MULTMATRIX_H
#define MULTMATRIX_H

#include "matrix.h"
#include "DiffMatrix.h"

class MultMatrix : public DiffMatrix{
public:
  MultMatrix(CMatrix first, CMatrix second);

  CMatrix Operation() override;
};

#endif

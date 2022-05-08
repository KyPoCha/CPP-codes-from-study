#ifndef DIFFMATRIX_H
#define DIFFMATRIX_H

#include "matrix.h"

class DiffMatrix{
protected:
  CMatrix _first;
  CMatrix _second;
public:
  DiffMatrix(CMatrix first, CMatrix second);

  virtual CMatrix Operation();
};

#endif

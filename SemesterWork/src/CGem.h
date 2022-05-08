#ifndef CGEM_H
#define CGEM_H

#include "matrix.h"

class CGem{
protected:
  CMatrix _matice;
public:
  CGem(CMatrix matice);

  virtual void RunGem();

  bool CheckForGem();

};

#endif

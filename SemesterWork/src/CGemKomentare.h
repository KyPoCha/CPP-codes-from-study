#ifndef CGEMKOMENTARE_H
#define CGEMKOMENTARE_H

#include "matrix.h"
#include "CGem.h"

class CGemKomentare : public CGem{
public:
  CGemKomentare(CMatrix a);

  void RunGem() override;
};

#endif

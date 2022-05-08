#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <iostream>
class CMatrix
{
protected:
  size_t _rows;
  size_t _cols;
  float ** _data;

  void clearMemory(float** a, size_t n);

  int findDet(float** _data, int n);

  int l_min(int a, int b);

public:

  CMatrix(size_t rows = 1, size_t cols = 1);

  CMatrix(size_t rows, size_t cols, float ** data);

  CMatrix(const CMatrix& b);

  ~CMatrix();

  size_t rows() const;

  size_t cols() const;

  float ** data()const;

  void Power(size_t n);

  CMatrix Trans();

  bool IsSquare() const;

  bool IsRegular();

  size_t Rad();

  float Det();

  int Rank();

  CMatrix Inverse();

  CMatrix Split(size_t new_rows = 0, size_t new_cols = 0);

  CMatrix Merge(const CMatrix& a);

  void GEM();

  void GEMsKomentarem();

  friend std::ostream& operator << (std::ostream& out,const CMatrix& a);
  friend std::istream& operator >> (std::istream &s, CMatrix& c);
  friend CMatrix& operator += (CMatrix& a, const CMatrix& b);
  friend CMatrix& operator -= (CMatrix& a, const CMatrix& b);
  friend CMatrix operator + (CMatrix& a, const CMatrix& b);
  friend CMatrix operator - (CMatrix& a, const CMatrix& b);
  friend CMatrix operator * (CMatrix& a, const CMatrix& b);
  friend CMatrix operator * (const CMatrix& a, int);
  friend CMatrix& operator *= (CMatrix& a, int);
  friend CMatrix operator * (CMatrix& a, int x);

};

#endif /*MATRIX_H*/

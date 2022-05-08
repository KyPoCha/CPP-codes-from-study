#include <iostream>
#include <vector>
#include <math.h>
#include "matrix.h"


void CMatrix::clearMemory(float** a, size_t n) {
  for (size_t i = 0; i < n; i++) {
          delete[] a[i];
      }
      delete [] a;
  }

int CMatrix::findDet(float** _data, int n) {
    if(n < 1){
      return 404; //если порядок не найден возврат ошибки 404))))))0
    }
    if (n == 1){
      return _data[0][0];
    }
    else if (n == 2){
      return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0];
    }
    else {
      float d = 0;
      for (int k = 0; k < n; k++) {
        float** m = new float*[n-1];
          for (int i = 0; i < n - 1; i++) {
              m[i] = new float[n - 1];
          }
          for (int i = 1; i < n; i++) {
            int t = 0;
            for (int j = 0; j < n; j++) {
              if (j == k)
                continue;
              m[i-1][t] = _data[i][j];
              t++;
            }
          }
          d += pow(-1, k + 2) * _data[0][k] * findDet(m, n - 1);
          clearMemory(m, n - 1);
        }
        return d;
      }
  }

int CMatrix::l_min(int a, int b){
    if(a>=b)
        return b;
    else
        return a;
  }

CMatrix::CMatrix(size_t rows, size_t cols){
  if(rows <= 0 || cols <= 0){
    throw "Invalid size of matrix";
  }
  _rows = rows;
  _cols = cols;
  _data = new float * [_rows];

  for (size_t i = 0; i < _rows; i++) {
    _data[i] = new float[_cols];
    for(size_t j = 0; j < _cols; j++){
      _data[i][j] = 0.0f;
    }
  }
}

CMatrix::CMatrix(size_t rows, size_t cols, float ** data){
  if(rows <= 0 || cols <= 0){
    throw "Invalid size of matrix";
  }
  _rows = rows;
  _cols = cols;
  _data = new float * [_rows];
  for (size_t i = 0; i < _rows; i++) {
    _data[i] = new float[_cols];
    for(size_t j = 0; j < _cols; j++){
      _data[i][j] = data[i][j];
    }
  }
}

CMatrix::CMatrix(const CMatrix& b){
  _rows = b.rows();
  _cols = b.cols();
  _data = new float * [_rows];

  for (size_t i = 0; i < _rows; i++) {
    _data[i] = new float[_cols];
    for(size_t j = 0; j < _cols; j++){
      _data[i][j] = b.data()[i][j];
    }
  }
}

CMatrix::~CMatrix(){
  for(size_t i = 0; i < _rows; i++){
    delete [] _data[i];
  }
  delete [] _data;
}

size_t CMatrix::rows() const {
  return _rows;
}

size_t CMatrix::cols() const {
  return _cols;
}

float ** CMatrix::data()const{
  return _data;
}

void CMatrix::Power(size_t n){
  if(!IsSquare()) {
    throw "Invalid matrix for exponentiation";
  }
  if(n == 0) {
    for(size_t i = 0; i < _rows; i++){
      for(size_t j = 0; j < _cols; j++) {
        if(i != j) {
          _data[i][j] = 0;
        }
        else {
          _data[i][j] = 1;
        }
      }
    }
  }
  else {
    for(size_t degree = 1; degree < n; degree++){
      CMatrix buffer(_rows, _cols);
      for(size_t i = 0; i < _rows; i++) {
        for(size_t j = 0; j < _cols; j++) {
          for(size_t k = 0; k < _cols; k++) {
            buffer._data[i][j] += _data[i][k]*_data[k][j];
          }
        }
      }
      for(size_t l = 0; l < _rows; l++) {
        for(size_t j = 0; j < _cols; j++) {
          _data[l][j] = buffer._data[l][j];
        }
      }
    }
  }
}

CMatrix CMatrix::Trans(){
  CMatrix buffer(_cols,_rows);
  for (size_t i = 0; i < _rows;i++){
    for (size_t j = 0; j < _cols;j++){
      buffer._data[j][i] = _data[i][j];
      if (j == _rows - 1){
        break;
      }
    }
  }
  return buffer;
}

bool CMatrix::IsSquare() const {
  if(_rows == _cols){
    return true;
  }
  else{
    return false;
  }
}

bool CMatrix::IsRegular(){
  if((Det() == 0) && IsSquare()){
    return true;
  }
  else{
    return false;
  }
}

size_t CMatrix::Rad(){
  if(IsSquare()){
    return _rows;
  }
  else{
    return 0;
  }
}

float CMatrix::Det(){
  int res = -2;
  if(!IsSquare()){
    return sqrt(res);
  }
  else{
    res = findDet(_data,static_cast<int>(_rows));
    return static_cast<int>(res);
  }
}

int CMatrix::Rank(){
  int i = static_cast<int>(_rows);
  int j = static_cast<int>(_cols);
  int r = 0;
  int q = 1;

  while(q <= l_min(i,j)){
    float **new_data = new float*[q];
    for(int w = 0; w < q; ++w)
        new_data[w] = new float[q];

      for(int a = 0; a < (i-(q-1)); ++a){
          for(int b = 0; b < (j-(q-1)); ++b){
              for(int c = 0; c < q; ++c)
                  for(int d = 0; d < q; ++d)
                      new_data[c][d] = _data[a+c][b+d];

              if(!(findDet(new_data,q)==0)) {
                r = q;
              }
          }
      }
      for(int i = 0; i < q; i ++){
        delete[] new_data[i];
      }
      delete [] new_data;
      q++;
    }
    return r;
}

CMatrix CMatrix::Inverse(){
  if(Det() == 0 || !IsSquare()){
    //return *this;
    throw "This matrix can not have an inverse";
  }

  float a[10][10];

  for(size_t i = 1; i <= _rows; i++){
    for(size_t j = 1; j <= _rows;j++){
      a[i][j] = data()[i-1][j-1];
    }
  }

  float ratio;
  int n = Rank(), i, j, k;

  for(i = 1; i <= n; i++){
     for(j = 1; j <= n; j++){
        if(i == j){
           a[i][j+n] = 1;
        }
        else{
           a[i][j+n] = 0;
        }
     }
  }

  for(i = 1; i <= n; i++){
     for(j = 1; j <= n; j++){
        if(i != j){
           ratio = a[j][i]/a[i][i];
           for(k = 1; k <= 2*n; k++){
             a[j][k] = a[j][k] - ratio*a[i][k];
           }
        }
     }
  }

  for(i = 1;i <= n; i++){
     for(j = n+1; j<=2*n ;j++){
       a[i][j] = a[i][j]/a[i][i];
     }
  }
  std::vector<float> v;
  for(i = 1; i <= n; i++){
    for(j = n+1; j <= 2*n; j++){
      v.push_back(a[i][j]);
    }
  }
  float ** data = new float * [_rows];
  size_t count = 0;
  for (size_t i = 0; i < _rows; i++) {
    data[i] = new float[_cols];
    for(size_t j = 0; j < _cols; j++){
      data[i][j] = v[count];
      count++;
    }
  }

  CMatrix c(_rows,_rows,data);

  for(size_t i = 0; i < _rows; i++){
    delete [] data[i];
  }
  delete [] data;

  return c;
}

CMatrix CMatrix::Split(size_t new_rows, size_t new_cols){
  if(new_cols == 0 && new_rows == 0){
    return *this;
  }

  if(new_cols > _cols || new_rows > _rows){
    //return *this;
    throw "Invalid inputs for splitting matrix: parametrs for splitting are bigger then matrix have";
  }

  if(new_cols == 0){
    new_cols = _cols;
  }
  if(new_rows == 0){
    new_rows = _rows;
  }

  CMatrix c(new_rows, new_cols);

  for(size_t i = 0; i < new_rows; i++){
    for(size_t j = 0; j < new_cols; j++){
      c.data()[i][j] = _data[i][j];
    }
  }
  return c;
}

CMatrix CMatrix::Merge(const CMatrix& a){
  if(a.IsSquare() && IsSquare()){
    if(_cols == a.cols() && _rows == a.rows()){
      CMatrix c(a.rows() + _rows, _cols);
      for(size_t i = 0; i < _rows; i++){
        for(size_t j = 0; j < _cols; j++){
          c.data()[i][j] = _data[i][j];
        }
      }

      for(size_t i = _rows; i < a.rows() + _rows; i++){
        for (size_t j = 0; j < _cols; j++) {
          c.data()[i][j] = a.data()[i-_rows][j];
        }
      }
      return c;
    }
    else{
      return *this;
    }
  }
  else{
    //return *this;
    throw "Matrices can not merge together";
  }
}

void CMatrix::GEM(){
  if(_rows == _cols && _rows == 2){
    std::cout << "\t" << "\t" << "Reseni pomoci GEMovani matice:" << std::endl;
    std::cout << "\t\t";
    std::cout << "x[1] = " << data()[0][1] << " " << "x[2] = " << data()[1][1] << std::endl;
  }
  else if(_rows == _cols){
    std::cout << "Try again. This matrix is not for GEM" << '\n';
    return;
  }
  else{
    float a[10][10];
    float x[10];

    for(size_t i = 1; i <= _rows; i++){
      for(size_t j = 1; j <= _rows + 1;j++){
        a[i][j] = data()[i-1][j-1];
      }
    }

    float ratio;
    int n = _cols - 1, i, j, k;
    std::cout << "\t" << "\t" << "Reseni pomoci GEMovani matice:" << std::endl;

    for(i=1;i<=n-1;i++){
      if(a[i][i] == 0.0){
        std::cout<<"Matematicka chyba!";
        return;
      }
      for(j=i+1;j<=n;j++){
        ratio = a[j][i]/a[i][i];

        for(k=1;k<=n+1;k++){
          a[j][k] = a[j][k] - ratio*a[i][k];
        }
      }
    }
    x[n] = a[n][n+1]/a[n][n];

    for(i=n-1;i>=1;i--){
      x[i] = a[i][n+1];
      for(j=i+1;j<=n;j++){
        x[i] = x[i] - a[i][j]*x[j];
      }
      x[i] = x[i]/a[i][i];
    }
    for(int i = 1; i <= n; i++){
      if( isnan(x[n])){
        std::cout << "\t\t"<< "Matice nema neparametrickeho reseni" << '\n';
        return;
        break;
      }
    }

    std::cout << "\t\t";
    for(int i = 1; i <= n; i++){
      std::cout << "x[" << i << "] = "<< x[i] << " ";
    }
  }
}

void CMatrix::GEMsKomentarem(){
  if(_rows == 2 && _cols == 2){
    std::cout << "\t" << "\t" << "Reseni pomoci GEMovani matice:" << std::endl;
    std::cout << "\t\t";
    std::cout << "x[1] = " << data()[0][1] << " " << "x[2] = " << data()[1][1] << std::endl;
  }
  else{
    float a[10][10];
    float x[10];

    for(size_t i = 1; i <= _rows; i++){
      for(size_t j = 1; j <= _rows + 1;j++){
        a[i][j] = data()[i-1][j-1];
      }
    }

    float ratio;
    int n = _cols - 1, i, j, k;

    std::cout << "\t" << "\t" << "Reseni pomoci GEMovani matice:" << std::endl;
    for(i=1;i<=n-1;i++){
      if(a[i][i] == 0.0){
        std::cout<<"Matematicka chyba kvuli " << a[i][i] << std::endl;
        exit(0);
      }
      for(j=i+1;j<=n;j++){
        ratio = a[j][i]/a[i][i];
        std::cout << "\t\t"<<"Koeficienta = " << ratio << '\n';

        for(k=1;k<=n+1;k++){
          std::cout << "\t\t"<<"Z toho odvodime, ze a[" <<j << "][" << k << "] = a[" << j << "][" << k << "] - " << ratio << "*a[" << i << "][" << k <<"] " << '\n';
          a[j][k] = a[j][k] - ratio*a[i][k];
          std::cout << "\t\t" << " a[" << j<< "][" <<k << "] = "<< a[j][k] << '\n';
        }
      }
    }

    std::cout << "\t\t" <<"Ziskame reseni metodou zpetne substituce, kde \'x\' - pole reseni rovnic, a \'a\' je soustavy rovnic" << '\n';
    x[n] = a[n][n+1]/a[n][n];
    std::cout << "\t\t" << n << ". reseni = "<< x[n] << '\n';

    for(i=n-1;i>=1;i--){
      x[i] = a[i][n+1];
      for(j=i+1;j<=n;j++){
        std::cout << "\t\t" <<"x[" << i << "] = x[" << i << "] - a[" << i << "][" << j << "]*x[" << j << "]" << '\n';
        x[i] = x[i] - a[i][j]*x[j];
      }
      x[i] = x[i]/a[i][i];
      std::cout << "\t\t" << i << ". reseni = " << x[i] << std::endl;
    }

    for(int i = 1; i <= n; i++){
      if( isnan(x[n])){
        std::cout << "\t\t"<< "Matice nema neparametrickeho reseni" << '\n';
        return;
        break;
      }
    }

    std::cout << "\t\t";
    for(int i = 1; i <= n; i++){
      std::cout << "x[" << i << "] = "<< x[i] << " ";
    }
  }
}


std::ostream& operator << (std::ostream& out,const CMatrix& a){
  size_t rows = a.rows(), cols = a.cols();
  for (size_t j = 0;j < rows; j++){
    out << "{ ";
    for (size_t i = 0;i < cols; i++){
      out<<a.data()[j][i]<<"  ";
    }
    out << "}" << std::endl;
  }
  return out;
}

std::istream& operator >> (std::istream &s, CMatrix& c){
  for (size_t i = 0; i< c.rows(); i++){
    for (size_t j = 0; j< c.cols(); j++){
        s >> c._data[i][j];
    }
  }
  return s;
}

CMatrix& operator += (CMatrix& a, const CMatrix& b){
  if(a.rows() == b.rows() && a.cols() == b.cols()){
    for(size_t i = 0; i < a.rows(); i++){
      for(size_t j = 0; j < a.cols(); j++){
        a.data()[i][j] += b.data()[i][j];
      }
    }
    return a;
  }
  else{
    return a;
  }
}

CMatrix& operator -= (CMatrix& a, const CMatrix& b){
  if(a.rows() == b.rows() && a.cols() == b.cols()){
    for(size_t i = 0; i < a.rows(); i++){
      for(size_t j = 0; j < a.cols(); j++){
        a.data()[i][j] -= b.data()[i][j];
      }
    }
    return a;
  }
  else{
    return a;
  }
}

CMatrix operator + (CMatrix& a, const CMatrix& b){
  CMatrix c(a.rows(),a.cols());
  if(a.rows() == b.rows() && a.cols() == b.cols()){
    for(size_t i = 0; i < a.rows(); i++){
      for(size_t j = 0; j < a.cols(); j++){
        c.data()[i][j] = a.data()[i][j] + b.data()[i][j];
      }
    }
    return c;
  }
  else{
    return c;
  }
}

CMatrix operator - (CMatrix& a, const CMatrix& b){
  CMatrix c(a.rows(),a.cols());
  if(a.rows() == b.rows() && a.cols() == b.cols()){
    for(size_t i = 0; i < a.rows(); i++){
      for(size_t j = 0; j < a.cols(); j++){
        c.data()[i][j] = a.data()[i][j] - b.data()[i][j];
      }
    }
    return c;
  }
  else{
    return c;
  }
}

CMatrix& operator *= (CMatrix& a, int x){
  for(size_t i = 0; i < a.rows(); i++){
    for(size_t j = 0; j < a.cols(); j++){
      a.data()[i][j] *= x;
    }
  }
  return a;
}

CMatrix operator * (const CMatrix& a, int x){
  CMatrix c(a.rows(),a.cols());
  for(size_t i = 0; i < a.rows(); i++){
    for(size_t j = 0; j < a.cols(); j++){
      c.data()[i][j] = a.data()[i][j] * x;
    }
  }
  return c;
}

CMatrix operator * (CMatrix& a, int x){
  CMatrix c(a.rows(),a.cols());
  for(size_t i = 0; i < a.rows(); i++){
    for(size_t j = 0; j < a.cols(); j++){
      c.data()[i][j] = a.data()[i][j] * x;
    }
  }
  return c;
}

CMatrix operator * (CMatrix& a, const CMatrix& b){
  CMatrix c(a.rows(),b.cols());
  if(a.cols() == b.rows()){
    for(size_t i = 0; i < a.rows(); i++){
      for(size_t j = 0; j < b.cols(); j++){
        c.data()[i][j] = 0;
        for(size_t k = 0; k < a.cols(); k++){
          c.data()[i][j] += a.data()[i][k] * b.data()[k][j];
        }
      }
    }
  }
  else{
    return a;
  }
  return c;
}

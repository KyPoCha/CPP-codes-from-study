#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument
{
  public:
    InvalidDateException ( )
      : invalid_argument ( "invalid date or format" )
    {
    }
};
//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format ( const char * fmt ) ) ( ios_base & x )
{
  return [] ( ios_base & ios ) -> ios_base & { return ios; };
}
//=================================================================================================

//function to determine days in specific month: January = 1, February = 2, ..., December = 12
bool DaysInMonth(int days, int month){
  bool IsValid;
  if( month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 9 || month == 10 || month == 12){
    if(days <= 31 && days > 0){
      IsValid = true;
    }
    else{
      IsValid = false;
    }
  }
  else{
    if(days <= 30 && days > 0){
      IsValid = true;
    }
    else{
      IsValid = false;
    }
  }
  return IsValid;
}

class CDate
{
public:
  //initialization of object
  CDate(int year, int month, int day){
    if(year > 2030 || year < 2000){
      throw InvalidDateException();
    }
    else{
      this->_year = year;
    }
    if(month <= 0 || month > 12){
      throw InvalidDateException();
    }
    else{
      this->_month = month;
    }
    if(day <= 0 || day > 31){
      throw InvalidDateException();
    }
    else{
      this->_day = day;
    }
  };

  /*
  * Getters will return privates values from class object
  */

  int& GetY(){
    return _year;
  }

  int& GetM(){
    return _month;
  }

  int& GetD(){
    return _day;
  }

  /*
  * Metods for determine corrects values for class object
  */

  bool IsValidDay(int value){
    if(_year % 4 == 0 && _month == 2){
      if(value <= 29 && value > 0){
        return true;
      }
      else{
        return false;
      }
    }
    else{
      if(value <= 0 || value > 31){
        return false;
      }
      else{
        return true;
      }
    }
  }

  bool IsValidDay(int value, int year, int month){
    if(year % 4 == 0 && month == 2){
      if(value <= 29 && value > 0){
        return true;
      }
      else{
        return false;
      }
    }
    else if(month == 2){
      if(value <= 0 || value > 28){
        return false;
      }
      else{
        return true;
      }
    }
    else{
      if( value <= 0 || value > 31){
        return false;
      }
      else{
        return true;
      }
    }
  }

  bool IsValidMonth(int value){
    if(value <= 0 || value > 12){
      return false;
    }
    else{
      return true;
    }
  }

  bool IsValidYear(int value){
    if(value < 2000 || value > 2030){
      return false;
    }
    else{
      return true;
    }
  }

  /*
  *   Setting values into class object after the checking them for errors
  */

  void SetD(int value){
    if(IsValidDay(value)){
      _day = value;
    }
    else{
      _day = 0;
    }
  }

  void SetM(int value){
    if(IsValidMonth(value)){
      _month = value;
    }
    else{
      _month = 0;
    }
  }

  void SetY(int value){
    if(IsValidYear(value)){
      _year = value;
    }
    else{
      _year = 0;
    }
  }

/*
* Metod to convert date format time to number of days
*/

  long JDay() {
      if (_month <= 2){
        _year--;
        _month += 12;
      }
      unsigned long jday;
      int a = _year / 100;
      a = 2 - a + (a / 4);
      jday = 1461L * long(_year);
      jday /= 4L;
      unsigned long k = 306001L * long(_month + 1);
      k /= 10000L;
      jday += k + _day + 1720995L + a;
      return jday;
  }

  /*
  * Metod to convert number of days to date format
  */

  void GDate(long jday) {
    unsigned long a = (jday * 4L - 7468865L) / 146097L;
    a = (jday > 2299160) ? jday + 1 + a - (a / 4L) : jday;
    long b = a + 1524;
    long c = (b * 20L - 2442L) / 7305L;
    long d = (c * 1461L) / 4L;
    long e = (10000L * (b - d)) / 306001L;
    _day = int(b - d - ((e * 306001L) / 10000L));
    _month = int((e <= 13) ? e - 1 : e - 13);
    _year = int(c - ((_month > 2) ? 4716 : 4715));
  }

  /*
  * Overloads operators for CDate class : arithmetic operations, comparing, post,prefix increment and decrement with whole days in date
  */

  CDate& operator + (int date){
    long jd = JDay();
    GDate(jd + date);
    return *this;
  }

  CDate& operator - (int date){
    long jd = JDay();
    GDate(jd - date);
    return *this;
  }

  int operator - (CDate& b){
    long jd1 = JDay();
    long jd2 = b.JDay();
    return (jd1 - jd2);
  }

  bool operator == (CDate& b){
    return JDay() == b.JDay();
  }

  bool operator != (CDate& b){
    return JDay() != b.JDay();
  }

  bool operator < (CDate& b){
    return JDay() < b.JDay();
  }

  bool operator > (CDate& b){
    return JDay() > b.JDay();
  }

  bool operator >= (CDate& b){
    return JDay() >= b.JDay();
  }

  bool operator <= (CDate& b){
    return JDay() <= b.JDay();
  }

  friend CDate& operator++(CDate& i);

  friend CDate operator++(CDate& i, int);

  friend CDate& operator--(CDate& i);

  friend CDate operator--(CDate& i, int);

  friend bool operator >> (std::istringstream& out, CDate& a);

private:
  int _year, _month, _day;

};

/*
* Prefix operators will change amount of days and using them after "return"
* Prefix will using amount of days and then change them;
*/

CDate& operator++(CDate& i) {
  long jd = i.JDay();
  i.GDate(jd + 1);
  return i;
}

CDate operator++(CDate& i, int) {
  CDate oldDate(i.GetY(), i.GetM(), i.GetD());
  long jd = i.JDay();
  i.GDate(jd + 1);
  return oldDate;
}

CDate& operator--(CDate& i) {
  long jd = i.JDay();
  i.GDate(jd - 1);
  return i;
}

CDate operator--(CDate& i, int) {
  CDate oldDate(i.GetY(), i.GetM(), i.GetD());
  long jd = i.JDay();
  i.GDate(jd - 1);
  return oldDate;
}

/*
* Overloads for stream inputs and outputs for class
*/

std::ostringstream& operator << (std::ostringstream &oss, CDate& a){

  oss << a.GetY();
  /*
  * Creating output date format
  * If we have 1th of April 2012, we will have "2012-04-01" for string
  */
  if(a.GetM() < 10){
    oss << "-0" << a.GetM();
  }
  else{
    oss << "-" << a.GetM();
  }
  if(a.GetD() < 10){
    oss << "-0" << a.GetD();
  }
  else{
    oss << "-" << a.GetD();
  }

  return oss;
}

std::ostream& operator << (std::ostream &oss, CDate& a){

  oss << a.GetY();

  if(a.GetM() < 10){
    oss << "-0" << a.GetM();
  }
  else{
    oss << "-" << a.GetM();
  }
  if(a.GetD() < 10){
    oss << "-0" << a.GetD();
  }
  else{
    oss << "-" << a.GetD();
  }

  return oss;
}

bool operator >> (std::istringstream& out, CDate& a){

  bool IsValid;

  string token;
  out >> token;

  //deleting extra symbols from istreamstring
  token.replace(token.find("-"),1," ");
  token.replace(token.find("-"),1," ");
  std::istringstream buf(token);
  std::string tmp;
  int year, month, day, it = 0;
  while(it < 3){
    buf >> tmp;
    //casting from string type to int for CDate atributes with stoi() function
    if(it == 0){year = stoi(tmp);}
    if(it == 1){month = stoi(tmp);}
    if(it == 2){day = stoi(tmp);}
    it++;
  }
  //check values for errors in date formats
  if(!a.IsValidDay(day,year,month) || !a.IsValidMonth(month) || !a.IsValidYear(year) || !DaysInMonth(day,month)){
    IsValid = false;
  }
  else{
    IsValid = true;
    a.SetD(day);
    a.SetM(month);
    a.SetY(year);
  }

  return IsValid;
}

#ifndef __PROGTEST__
int main ( void )
{
  ostringstream oss;
  istringstream iss;

  CDate a ( 2000, 1, 2 );
  CDate b ( 2010, 2, 3 );
  CDate c ( 2004, 2, 10 );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2000-01-02" );
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2010-02-03" );
  oss . str ("");
  oss << c;
  assert ( oss . str () == "2004-02-10" );
  a = a + 1500;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2004-02-10" );
  b = b - 2000;
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2004-08-13" );
  assert ( b - a == 185 );
  assert ( ( b == a ) == false );
  assert ( ( b != a ) == true );
  assert ( ( b <= a ) == false );
  assert ( ( b < a ) == false );
  assert ( ( b >= a ) == true );
  assert ( ( b > a ) == true );
  assert ( ( c == a ) == true );
  assert ( ( c != a ) == false );
  assert ( ( c <= a ) == true );
  assert ( ( c < a ) == false );
  assert ( ( c >= a ) == true );
  assert ( ( c > a ) == false );
  a = ++c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-11" );
  a = --c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-10" );
  a = c++;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-11" );
  a = c--;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-10" );
  iss . clear ();
  iss . str ( "2015-09-03" );
  assert ( ( iss >> a ) );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-09-03" );
  a = a + 70;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-11-12" );

  CDate d ( 2000, 1, 1 );

  try
  {
    CDate e ( 2000, 32, 1 );
    assert ( "No exception thrown!" == nullptr );
  }
  catch ( ... )
  {
  }

  iss . clear ();
  iss . str ( "2000-12-33" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-11-31" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-02-29" );
  assert ( ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );
  iss . clear ();
  iss . str ( "2001-02-29" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );

  // //-----------------------------------------------------------------------------
  // // bonus test examples
  // //-----------------------------------------------------------------------------
  // CDate f ( 2000, 5, 12 );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2000-05-12" );
  // oss . str ("");
  // oss << date_format ( "%Y/%m/%d" ) << f;
  // assert ( oss . str () == "2000/05/12" );
  // oss . str ("");
  // oss << date_format ( "%d.%m.%Y" ) << f;
  // assert ( oss . str () == "12.05.2000" );
  // oss . str ("");
  // oss << date_format ( "%m/%d/%Y" ) << f;
  // assert ( oss . str () == "05/12/2000" );
  // oss . str ("");
  // oss << date_format ( "%Y%m%d" ) << f;
  // assert ( oss . str () == "20000512" );
  // oss . str ("");
  // oss << date_format ( "hello kitty" ) << f;
  // assert ( oss . str () == "hello kitty" );
  // oss . str ("");
  // oss << date_format ( "%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%" ) << f;
  // assert ( oss . str () == "121212121212050505200020002000%%%%%" );
  // oss . str ("");
  // oss << date_format ( "%Y-%m-%d" ) << f;
  // assert ( oss . str () == "2000-05-12" );
  // iss . clear ();
  // iss . str ( "2001-01-1" );
  // assert ( ! ( iss >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2000-05-12" );
  // iss . clear ();
  // iss . str ( "2001-1-01" );
  // assert ( ! ( iss >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2000-05-12" );
  // iss . clear ();
  // iss . str ( "2001-001-01" );
  // assert ( ! ( iss >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2000-05-12" );
  // iss . clear ();
  // iss . str ( "2001-01-02" );
  // assert ( ( iss >> date_format ( "%Y-%m-%d" ) >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2001-01-02" );
  // iss . clear ();
  // iss . str ( "05.06.2003" );
  // assert ( ( iss >> date_format ( "%d.%m.%Y" ) >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2003-06-05" );
  // iss . clear ();
  // iss . str ( "07/08/2004" );
  // assert ( ( iss >> date_format ( "%m/%d/%Y" ) >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2004-07-08" );
  // iss . clear ();
  // iss . str ( "2002*03*04" );
  // assert ( ( iss >> date_format ( "%Y*%m*%d" ) >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2002-03-04" );
  // iss . clear ();
  // iss . str ( "C++09format10PA22006rulez" );
  // assert ( ( iss >> date_format ( "C++%mformat%dPA2%Yrulez" ) >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2006-09-10" );
  // iss . clear ();
  // iss . str ( "%12%13%2010%" );
  // assert ( ( iss >> date_format ( "%%%m%%%d%%%Y%%" ) >> f ) );
  // oss . str ("");
  // oss << f;
  // assert ( oss . str () == "2010-12-13" );
  //
  // CDate g ( 2000, 6, 8 );
  // iss . clear ();
  // iss . str ( "2001-11-33" );
  // assert ( ! ( iss >> date_format ( "%Y-%m-%d" ) >> g ) );
  // oss . str ("");
  // oss << g;
  // assert ( oss . str () == "2000-06-08" );
  // iss . clear ();
  // iss . str ( "29.02.2003" );
  // assert ( ! ( iss >> date_format ( "%d.%m.%Y" ) >> g ) );
  // oss . str ("");
  // oss << g;
  // assert ( oss . str () == "2000-06-08" );
  // iss . clear ();
  // iss . str ( "14/02/2004" );
  // assert ( ! ( iss >> date_format ( "%m/%d/%Y" ) >> g ) );
  // oss . str ("");
  // oss << g;
  // assert ( oss . str () == "2000-06-08" );
  // iss . clear ();
  // iss . str ( "2002-03" );
  // assert ( ! ( iss >> date_format ( "%Y-%m" ) >> g ) );
  // oss . str ("");
  // oss << g;
  // assert ( oss . str () == "2000-06-08" );
  // iss . clear ();
  // iss . str ( "hello kitty" );
  // assert ( ! ( iss >> date_format ( "hello kitty" ) >> g ) );
  // oss . str ("");
  // oss << g;
  // assert ( oss . str () == "2000-06-08" );
  // iss . clear ();
  // iss . str ( "2005-07-12-07" );
  // assert ( ! ( iss >> date_format ( "%Y-%m-%d-%m" ) >> g ) );
  // oss . str ("");
  // oss << g;
  // assert ( oss . str () == "2000-06-08" );
  // iss . clear ();
  // iss . str ( "20000101" );
  // assert ( ( iss >> date_format ( "%Y%m%d" ) >> g ) );
  // oss . str ("");
  // oss << g;
  // assert ( oss . str () == "2000-01-01" );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

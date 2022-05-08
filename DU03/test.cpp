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


private:
  int _year, _month, _day;

};

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

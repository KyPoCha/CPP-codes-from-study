#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

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
void print_vector(std::vector<pair<std::string,int>>& a);

class CDate
{
public:
  //initialization of object
  CDate(int year, int month, int day){
    if(year > 2030 || year < 2000){
      throw "invalid date or format";
    }
    else{
      this->_year = year;
    }
    if(month <= 0 || month > 12){
      throw "invalid date or format";
    }
    else{
      this->_month = month;
    }
    if(day <= 0 || day > 31){
      throw "invalid date or format";
    }
    else{
      this->_day = day;
    }
  };
  CDate(void){}

  int GetY() const {
    return _year;
  }

  int GetM() const {
    return _month;
  }

  int GetD() const{
    return _day;
  }

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

  long JDay(){
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


    long JDay() const {
        int month = _month, year = _year, day = _day;
        if (_month <= 2){
          year--;
          month += 12;
        }
        unsigned long jday;
        int a = year / 100;
        a = 2 - a + (a / 4);
        jday = 1461L * long(year);
        jday /= 4L;
        unsigned long k = 306001L * long(month + 1);
        k /= 10000L;
        jday += k + day + 1720995L + a;
        return jday;
    }

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

  friend bool operator != (const CDate& a,const CDate& b);
  friend bool operator == (const CDate& a,const CDate& b);
  friend bool operator < (const CDate& a,const CDate& b);
  friend bool operator > (const CDate& a, const CDate& b);
  friend bool operator <= (const CDate& a, const CDate& b);

  friend std::ostream& operator << (std::ostream &oss,const CDate& a);
private:
  int _year, _month, _day;

};

bool operator != (const CDate& a,const CDate& b){
  return a.JDay() != b.JDay();
}

bool operator == (const CDate& a,const CDate& b){
  return a.JDay() == b.JDay();
}

bool operator < (const CDate& a,const CDate& b){
  return a.JDay() < b.JDay();
}

bool operator > (const CDate& a, const CDate& b){
  return a.JDay() > b.JDay();
}

bool operator <= (const CDate& a, const CDate& b){
  return a.JDay() <= b.JDay();
}
class CSupermarket
{
};


std::ostream& operator << (std::ostream &oss,const CDate& a){
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
#ifndef __PROGTEST__
int main ( void )
{
  CSupermarket s;
  s . store ( "bread", CDate ( 2016, 4, 30 ), 100 )
    . store ( "butter", CDate ( 2016, 5, 10 ), 10 )
    . store ( "beer", CDate ( 2016, 8, 10 ), 50 )
    . store ( "bread", CDate ( 2016, 4, 25 ), 100 )
    . store ( "okey", CDate ( 2016, 7, 18 ), 5 );

  list<pair<string,int> > l0 = s . expired ( CDate ( 2018, 4, 30 ) );
  //print_inside(l0);
  //std::cout << l0.size() << '\n';
  assert ( l0 . size () == 4 );
  assert ( ( l0 == list<pair<string,int> > { { "bread", 200 }, { "beer", 50 }, { "butter", 10 }, { "okey", 5 } } ) );
  //
  list<pair<string,int> > l1 { { "bread", 2 }, { "Coke", 5 }, { "butter", 20 } };
  s . sell ( l1 );
  //print_inside(l1);
  assert ( l1 . size () == 2 );
  assert ( ( l1 == list<pair<string,int> > { { "Coke", 5 }, { "butter", 10 } } ) );
  //
  //s.print();
  list<pair<string,int> > l2 = s . expired ( CDate ( 2016, 4, 30 ) );
  //print_inside(l2);
  assert ( l2 . size () == 1 );
  assert ( ( l2 == list<pair<string,int> > { { "bread", 98 } } ) );
  //
  list<pair<string,int> > l3 = s . expired ( CDate ( 2016, 5, 20 ) );
  assert ( l3 . size () == 1 );
  assert ( ( l3 == list<pair<string,int> > { { "bread", 198 } } ) );
  //
  //s.print();
  list<pair<string,int> > l4 { { "bread", 105 } };
  s . sell ( l4 );
  assert ( l4 . size () == 0 );
  assert ( ( l4 == list<pair<string,int> > {  } ) );
  //s.print();
  // //
  list<pair<string,int> > l5 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l5 . size () == 3 );
  //print_inside(l5);
  assert ( ( l5 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 } } ) );
  //
  s . store ( "Coke", CDate ( 2016, 12, 31 ), 10 );
  //s.print();

  list<pair<string,int> > l6 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 }, { "Cokes", 1 } };
  s . sell ( l6 );
  s.print();
  //print_inside(l6);
  assert ( l6 . size () == 3 );
  assert ( ( l6 == list<pair<string,int> > { { "cake", 1 }, { "cuke", 1 }, { "Cokes", 1 } } ) );
  //
  // list<pair<string,int> > l7 = s . expired ( CDate ( 2017, 1, 1 ) );
  // assert ( l7 . size () == 4 );
  // assert ( ( l7 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 7 }, { "okey", 5 } } ) );
  //
  // s . store ( "cake", CDate ( 2016, 11, 1 ), 5 );
  //
  // list<pair<string,int> > l8 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 } };
  // s . sell ( l8 );
  // assert ( l8 . size () == 2 );
  // assert ( ( l8 == list<pair<string,int> > { { "Cake", 1 }, { "coke", 1 } } ) );
  //
  // list<pair<string,int> > l9 = s . expired ( CDate ( 2017, 1, 1 ) );
  // assert ( l9 . size () == 5 );
  // assert ( ( l9 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 }, { "cake", 3 } } ) );
  //
  // list<pair<string,int> > l10 { { "cake", 15 }, { "Cake", 2 } };
  // s . sell ( l10 );
  // assert ( l10 . size () == 2 );
  // assert ( ( l10 == list<pair<string,int> > { { "cake", 12 }, { "Cake", 2 } } ) );
  //
  // list<pair<string,int> > l11 = s . expired ( CDate ( 2017, 1, 1 ) );
  // assert ( l11 . size () == 4 );
  // assert ( ( l11 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 } } ) );
  //
  // list<pair<string,int> > l12 { { "Cake", 4 } };
  // s . sell ( l12 );
  // assert ( l12 . size () == 0 );
  // assert ( ( l12 == list<pair<string,int> > {  } ) );
  //
  // list<pair<string,int> > l13 = s . expired ( CDate ( 2017, 1, 1 ) );
  // assert ( l13 . size () == 4 );
  // assert ( ( l13 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 }, { "Coke", 2 } } ) );
  //
  // list<pair<string,int> > l14 { { "Beer", 20 }, { "Coke", 1 }, { "bear", 25 }, { "beer", 10 } };
  // s . sell ( l14 );
  // assert ( l14 . size () == 1 );
  // assert ( ( l14 == list<pair<string,int> > { { "beer", 5 } } ) );
  //
  // s . store ( "ccccb", CDate ( 2019, 3, 11 ), 100 )
  //   . store ( "ccccd", CDate ( 2019, 6, 9 ), 100 )
  //   . store ( "dcccc", CDate ( 2019, 2, 14 ), 100 );
  //
  // list<pair<string,int> > l15 { { "ccccc", 10 } };
  // s . sell ( l15 );
  // assert ( l15 . size () == 1 );
  // assert ( ( l15 == list<pair<string,int> > { { "ccccc", 10 } } ) );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

//unsigned int DEFAULT_TABLE_SIZE1 = 1000;

template <typename T>
class Entry {
private:
	string _klic;
	T _hodnota;
	Entry *_next;
public:
	Entry ( string _klic, T _hodnota ) {
		this->_klic = _klic;
		this->_hodnota = _hodnota;
		this->_next = nullptr;
	}
	string GetKlic () { return _klic; }
	T GetHodnota () { return _hodnota; }
	void SetHodnota ( T _hodnota ) { this->_hodnota = _hodnota; }
	Entry *GetNext() { return _next; }
	void SetNext ( Entry *_next ) { this->_next = _next; }
};

template <typename T>
class HashMap {
private:
	float _hold;
	unsigned int _MSize;
	unsigned int _TSize;
	unsigned int _size;
	Entry<T> **_table;

	std::hash<std::string> Hash;

	void ResizeHasMap () {
		unsigned int old_TSize = _TSize;
		_TSize *= 2;
		_MSize = (unsigned int) ( _TSize * _hold );
		Entry<T> **Table = _table;
		_table = new Entry<T> * [_TSize];

		for ( unsigned int i = 0; i < _TSize; i++ )
			_table[i] = nullptr;
		_size = 0;

		for ( unsigned int hash_value = 0; hash_value < old_TSize; hash_value++ )
			if ( Table[hash_value] != nullptr )
			{
				Entry<T> *oldEntry;
				Entry<T> *entry = Table[hash_value];
				while ( entry != nullptr ) {
					PutPrvk ( entry->GetKlic(), entry->GetHodnota() );
					oldEntry = entry;
					entry = entry->GetNext();
					delete oldEntry;
				}
			}
		delete[] Table;
	}
public:
	HashMap () {
		_hold = 0.75;
		_MSize = 1000 * _hold;
		_TSize = 1000;
		_size = 0;
		_table = new Entry<T>*[_TSize];

		for ( unsigned int i = 0; i < _TSize; i++ )
			_table[i] = nullptr;
	}

	void Set ( float _hold ) {
		this->_hold = _hold;
		_MSize = (unsigned int) ( _TSize * _hold );
	}

	T GetPrvk ( string _klic ) const {

		auto value = Hash ( _klic );
		auto hash_value = value % _TSize;

		if ( _table[hash_value] == nullptr )
			throw false;
		else
		{
			auto entry = _table[hash_value];
			while ( entry != nullptr && entry->GetKlic() != _klic )
				entry = entry->GetNext();
			if ( entry == nullptr )
				throw false;
			else
				return entry->GetHodnota();
		}
	}

	void PutPrvk ( string _klic, T _hodnota ) {

		auto value = Hash ( _klic );
		auto hash_value = value % _TSize;

		if ( _table[hash_value] == nullptr ) {
			_table[hash_value] = new Entry<T> ( _klic, _hodnota );
			_size++;
		}
		else
		{
			auto entry = _table[hash_value];
			while ( entry->GetNext() != nullptr && entry->GetKlic() != _klic )
				entry = entry->GetNext();

			if ( entry->GetKlic() == _klic )
				entry->SetHodnota ( _hodnota );
			else
			{
				entry->SetNext ( new Entry<T> ( _klic, _hodnota ) );
				_size++;
			}
		}
		if ( _size >= _MSize )
			ResizeHasMap();
	}

	void RemovePrvk ( string _klic ) {

		auto value = Hash ( _klic );
		auto hash_value = value % _TSize;

		if ( _table[hash_value] != nullptr ) {
			Entry<T> *prevEntry = nullptr;
			auto entry = _table[hash_value];
			while ( entry->GetNext() != nullptr && entry->GetKlic() != _klic ) {
				prevEntry = entry;
				entry = entry->GetNext();
			}
			if ( entry->GetKlic() == _klic )
			{
				if ( prevEntry == nullptr )
				{
					auto nextEntry = entry->GetNext();
					delete entry;
					_table[hash_value] = nextEntry;
				}
				else
				{
					auto _next = entry->GetNext();
					delete entry;
					prevEntry->SetNext( _next );
				}
				_size--;
			}
		}
	}

	~HashMap() {
		for ( unsigned int hash_value = 0; hash_value < _TSize; hash_value++ )
			if ( _table[hash_value] != nullptr )
			{
				Entry<T> *prevEntry = nullptr;
				auto entry = _table[hash_value];
				while ( entry != nullptr ) {
					prevEntry = entry;
					entry = entry->GetNext();
					delete prevEntry;
				}
			}
		delete[] _table;
	}

};

class CVATRegister {
public:
  CVATRegister   ( void ){

  }
  ~CVATRegister  ( void ){
    delete[] data_base;
    //delete[] data_invoice;
  }

	bool newCompany ( const string & name, const string & addr, const string & taxID ) {
		string nameAdress = name + "´´^´ˇ´" + addr;
		std::transform ( nameAdress.begin(), nameAdress.end(), nameAdress.begin(), ::tolower );
		string companyID = taxID;

		try {
			Company_Id.GetPrvk ( companyID );
			return false;
		} catch ( bool e ) {};
		try {
			Company_Addr.GetPrvk ( nameAdress );
			return false;
		} catch ( bool e ) {};

		invoice_id.PutPrvk ( companyID, 0 );
		Company_Addr.PutPrvk ( nameAdress, companyID );
		Company_Id.PutPrvk ( companyID, nameAdress );

    bool result;

    if(size != 0){

      if(name == "" || addr == "" ||  name == " " || addr == " " || name == "\0" || addr == "\0"){
        result = false;
      }
      else{
        string _name = name;
        string _addr = addr;

        std::transform(_name.begin(), _name.end(),_name.begin(), [](unsigned char c){ return std::tolower(c);});
        std::transform(_addr.begin(), _addr.end(),_addr.begin(), [](unsigned char c){ return std::tolower(c);});

        for(size_t i = 0; i < size; i++){
          string nameF = data_base[i].name;
          string addrF = data_base[i].addr;
          std::transform(nameF.begin(), nameF.end(),nameF.begin(), [](unsigned char c){ return std::tolower(c);});
          std::transform(addrF.begin(), addrF.end(),addrF.begin(), [](unsigned char c){ return std::tolower(c);});
          if(nameF == _name && addrF == _addr && data_base[i].taxID != taxID){
            result = false;
            break;
          }
          else{
            result = true;
          }
        }
      }



      if(result){
        Company * new_data = new Company[size+1];

        for(size_t i = 0; i < size; i++) {
          new_data[i] = data_base[i];
        }

        delete[] data_base;
        data_base = new_data;
        result = true;
      }
    }
    else{
      Company * new_data = new Company[size+1];
      delete[]data_base;
      data_base = new_data;
      result = true;
    }
    if(result){
      data_base[size].name = name;
      data_base[size].addr = addr;
      data_base[size].taxID = taxID;
      data_base[size].inv = 0;
      size++;
    }
    return result;
    }

	bool cancelCompany ( const string & taxID ) {
		string companyID = taxID;
		string state;

		try {
			state = Company_Id.GetPrvk ( companyID );
		} catch ( bool e ) { return false; }


		Company_Id.RemovePrvk ( companyID );
		invoice_id.RemovePrvk ( companyID );
		Company_Addr.RemovePrvk ( state );


          bool result;

          if( taxID == " " || taxID == ""){
            result = false;
          }
          else{
            for(size_t i = 0; i < size; i++){
              if(data_base[i].taxID == taxID){
                result = true;
                break;
              }
              else{
                result = false;
              }
            }
          }


          if(result){
            if(size == 0){
              return false;
            }
            else{
              for(size_t i = 0; i < size; i++){
                if(data_base[i].taxID == taxID){
                  Company tmp = data_base[i];
                  data_base[i] = data_base[size-1];
                  data_base[size-1] = tmp;
                  break;
                }
              }
              Company* new_data = new Company[size-1];

              for(size_t i = 0; i < size-1; i++) {
                new_data[i] = data_base[i];
              }

              delete[] data_base;
              data_base = new_data;
              size--;
              result = true;
            }
          }

          return result;
    }

	bool cancelCompany ( const string & name, const string & addr ) {
		string nameAdress = name + "´´^´ˇ´" + addr;
		std::transform ( nameAdress.begin(), nameAdress.end(), nameAdress.begin(), ::tolower );
		string state;

		try {
			state = Company_Addr.GetPrvk ( nameAdress );
		} catch ( bool e ) { return false; }

		Company_Id.RemovePrvk ( state );
		invoice_id.RemovePrvk ( state );
		Company_Addr.RemovePrvk ( nameAdress );
    bool result;

    if((name == "" || addr == "") || (name == " " || addr == " ")){
      result = false;
    }
    else{
      string _name = name;
      string _addr = addr;

      std::transform(_name.begin(), _name.end(),_name.begin(), [](unsigned char c){ return std::tolower(c);});
      std::transform(_addr.begin(), _addr.end(),_addr.begin(), [](unsigned char c){ return std::tolower(c);});

      for(size_t i = 0; i < size; i++){
        string nameF = data_base[i].name;
        string addrF = data_base[i].addr;
        std::transform(nameF.begin(), nameF.end(),nameF.begin(), [](unsigned char c){ return std::tolower(c);});
        std::transform(addrF.begin(), addrF.end(),addrF.begin(), [](unsigned char c){ return std::tolower(c);});
        if(_name == nameF && _addr == addrF){
          result = true;
          break;
        }
        else{
          result = false;
        }
      }
    }

    if(result){
      if(size == 0){
        return false;
      }
      else{
        string _name = name;
        string _addr = addr;

        std::transform(_name.begin(), _name.end(),_name.begin(), [](unsigned char c){ return std::tolower(c);});
        std::transform(_addr.begin(), _addr.end(),_addr.begin(), [](unsigned char c){ return std::tolower(c);});
        for(size_t i = 0; i < size; i++){
          string nameF = data_base[i].name;
          string addrF = data_base[i].addr;
          std::transform(nameF.begin(), nameF.end(),nameF.begin(), [](unsigned char c){ return std::tolower(c);});
          std::transform(addrF.begin(), addrF.end(),addrF.begin(), [](unsigned char c){ return std::tolower(c);});
          if(_name == nameF && _addr == addrF){
            Company tmp = data_base[i];
            data_base[i] = data_base[size-1];
            data_base[size-1] = tmp;
            break;
          }
        }
        Company* new_data = new Company[size-1];

        for(size_t i = 0; i < size-1; i++) {
          new_data[i] = data_base[i];
        }

        delete[] data_base;
        data_base = new_data;
        size--;
        result = true;
      }
    }

    return result;
	}

  bool firstCompany ( string& name, string& addr ) const{
    if(size == 0){
      return false;
    }
    if(size == 1){
      name = data_base[0].name;
      addr = data_base[0].addr;
      return true;
    }

		std::vector<Company> vector;

 		for (size_t i = 0; i < size; i++){
		 	vector.push_back(data_base[i]);
 		}

		sort(vector.begin(),vector.end(),[](Company a, Company b){
			return a > b;
		});

		name = vector[0].name;
		addr = vector[0].addr;
    return true;
  }
	void print(std::ostream& out = std::cout) const {
		std::vector<Company> vector;

		for (size_t i = 0; i < size; i++){
			vector.push_back(data_base[i]);
		}

		sort(vector.begin(),vector.end(),[](Company a, Company b){
			return a > b;
		});
		for(size_t i = 0; i < size; i++){
			out << vector[i].name << " " << vector[i].addr << " " << vector[i].taxID << " " << vector[i].inv << std::endl;
		}
	}

  bool nextCompany ( string& name, string& addr ) const{
    if(size == 0){
      return false;
    }

		std::vector<Company> vector;

		for (size_t i = 0; i < size; i++){
			vector.push_back(data_base[i]);
		}

		sort(vector.begin(),vector.end(),[](Company a, Company b){
			return a > b;
		});

		bool result = false;

		if( name == "" || addr == "" ||  name == " " || addr == " " || name == "\0" || addr == "\0"){
			return result;
		}
		else{
			result = false;
			string _name = name;
			string _addr = addr;

			std::transform(_name.begin(), _name.end(),_name.begin(), [](unsigned char c){ return std::tolower(c);});
			std::transform(_addr.begin(), _addr.end(),_addr.begin(), [](unsigned char c){ return std::tolower(c);});

			for(size_t i = 0; i < size; i++){
				string nameF = vector[i].name;
				string addrF = vector[i].addr;
				std::transform(nameF.begin(), nameF.end(),nameF.begin(), [](unsigned char c){ return std::tolower(c);});
				std::transform(addrF.begin(), addrF.end(),addrF.begin(), [](unsigned char c){ return std::tolower(c);});
				if(nameF == _name && addrF == _addr){
					if(i != size - 1){
						name = vector[i+1].name;
						addr = vector[i+1].addr;
						result = true;
						break;
					}
				}
			}
		}

    return result;
  }

	bool invoice ( const string & taxID, unsigned int amount ) {
		unsigned int sum;
		try {
			sum = invoice_id.GetPrvk ( taxID );
		} catch ( bool e ) { return false; }

		sum += amount;
		median_invoice.push_back (amount);
		invoice_id.PutPrvk ( taxID, sum );
		return true;
	}

	bool invoice ( const string & name, const string & addr, unsigned int amount ) {
		string nameAdress = name + "´´^´ˇ´" + addr;
		std::transform ( nameAdress.begin(), nameAdress.end(), nameAdress.begin(), ::tolower );
		string state;

		try {
			state = Company_Addr.GetPrvk ( nameAdress );
		} catch ( bool e ) { return false; }

		unsigned int sum;
		try {
			sum = invoice_id.GetPrvk ( state );
		} catch ( bool e ) { return false; }

		sum += amount;
		median_invoice.push_back (amount);

		invoice_id.PutPrvk ( state, sum );
		return true;

	}

	bool audit ( const string & name, const string & addr, unsigned int & sumIncome ) const {
	}
	bool audit ( const string & taxID, unsigned int & sumIncome ) const {
	}
	unsigned int medianInvoice ( void ) const {
			median = 0;
		return median;
	}

 private:
 	HashMap<string> Company_Addr;
 	HashMap<string> Company_Id;
 	HashMap<unsigned int> invoice_id;
	std::vector<unsigned int> median_invoice;
  struct Company{
    std::string name;
    std::string addr;
    std::string taxID;
    unsigned int inv = 0;
    unsigned int& median(){
      return inv;
    }

    bool operator > (const Company& a){
      if(name < a.name){
        return true;
      }
      if(name > a.name){
        return false;
      }
      if(addr < a.addr){
        return true;
      }
      return false;
    }
  };

  Company * data_base = nullptr;
  //unsigned int * data_invoice = nullptr;
  size_t size = 0;
  //unsigned int invoice_count = 0;
  //unsigned int total_invoice = 0;
  };

#ifndef __PROGTEST__
int               main           ( void )
{
  string name, addr;
  unsigned int sumIncome;

  CVATRegister b1;
  assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );
  assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
  assert ( b1 . invoice ( "666/666", 2000 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "666/666/666", 3000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 4000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "aCmE", "Kolejni", 5000 ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
  assert ( b1 . audit ( "123456", sumIncome ) && sumIncome == 4000 );

  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
  assert ( b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
  assert ( b1 . nextCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "ACME", "KoLeJnI" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . cancelCompany ( "666/666" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . invoice ( "123456", 100 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 300 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 230 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 830 ) );
  assert ( b1 . medianInvoice () == 830 );
  assert ( b1 . invoice ( "123456", 1830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 3200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "123456" ) );
  assert ( ! b1 . firstCompany ( name, addr ) );

  CVATRegister b2;
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . newCompany ( "Dummy", "Kolejni", "123456" ) );
  assert ( ! b2 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
  assert ( b2 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
  assert ( b2 . medianInvoice () == 0 );
  assert ( b2 . invoice ( "ABCDEF", 1000 ) );
  assert ( b2 . medianInvoice () == 1000 );
  assert ( b2 . invoice ( "abcdef", 2000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( b2 . invoice ( "aCMe", "kOlEjNi", 3000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . invoice ( "1234567", 100 ) );
  assert ( ! b2 . invoice ( "ACE", "Kolejni", 100 ) );
  assert ( ! b2 . invoice ( "ACME", "Thakurova", 100 ) );
  assert ( ! b2 . audit ( "1234567", sumIncome ) );
  assert ( ! b2 . audit ( "ACE", "Kolejni", sumIncome ) );
  assert ( ! b2 . audit ( "ACME", "Thakurova", sumIncome ) );
  assert ( ! b2 . cancelCompany ( "1234567" ) );
  assert ( ! b2 . cancelCompany ( "ACE", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Thakurova" ) );
  assert ( b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . cancelCompany ( "ACME", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Kolejni" ) );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

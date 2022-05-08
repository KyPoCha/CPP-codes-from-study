#ifndef __PROGTEST__
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */

class CFile
{
  public:

    struct CData
    {
        uint8_t * _bytes;
        uint64_t _size;
        uint64_t _pos;
    };

    CFile( void ){
        data._bytes = (uint8_t *) malloc(0 * sizeof(uint8_t));
        _size = 0;
        _pos = 0;
        _data_version = 0;
        _versions = (CData *)malloc(0 * sizeof(CData));
    };

    ~CFile(){
        free(data._bytes);
        for(size_t i = 0; i < _data_version; i++){
            free(_versions[i]._bytes);
        }
        free(_versions);
    };

    CFile& operator = (const CFile & value) {
    }
    CFile(const CFile & value){
    }

     bool                     seek                          ( uint32_t          offset ){
        if(offset > _size || offset < 0){
          return false;
        }

        _pos = offset;

        return true;
    };

    uint32_t                 read                          ( uint8_t         * dst,
                                                             uint32_t          bytes ){
      uint32_t readed;
      if(_size - _pos < bytes){
        readed = _size - _pos;
      }
      else {
        readed = bytes;
      }
      memcpy(dst, data._bytes + _pos, readed);
      _pos += readed;
      return readed;
    };

    uint32_t                 write                         ( const uint8_t   * src,
                                                             uint32_t          bytes ){
        if(_size - _pos < bytes){
            _size += bytes - (_size - _pos);
            data._bytes = (uint8_t *)realloc(data._bytes, ((sizeof(uint8_t) + 1) * (_size+1)));
        }

        memcpy(data._bytes + _pos, src, bytes);
        _pos += bytes;

        return bytes;
    };

     void                     truncate                      ( void ){
        if(_pos == _size){
          return;
        }

        uint8_t * t = (uint8_t*)malloc(_pos * sizeof(uint8_t));

        memcpy(t, data._bytes, _pos);
        free(data._bytes);

        data._bytes = t;

        _size = _pos;
    };

    uint32_t                 fileSize                      ( void ) const{
        return _size;
    };

    void                     addVersion                    ( void ){
        _data_version++;
        _versions = (CData *)realloc(_versions, ((sizeof(CData) + 1) * (_data_version+1)));

        _versions[_data_version - 1]._bytes = (uint8_t *)malloc(_size * sizeof(uint8_t));
        memcpy(_versions[_data_version - 1]._bytes, data._bytes, _size);

        _versions[_data_version - 1]._size = _size;
        _versions[_data_version - 1]._pos = _pos;
    };

    bool                     undoVersion                   ( void ){
        if(_data_version == 0){
          return false;
        }

        free(data._bytes);
        data._bytes = (uint8_t *)malloc(_versions[_data_version -1]._size * sizeof(uint8_t));
        memcpy(data._bytes, _versions[_data_version - 1]._bytes, _versions[_data_version - 1]._size);

        _size = _versions[_data_version - 1]._size;
        _pos = _versions[_data_version - 1]._pos;
        _data_version--;


        CData * t = (CData *)malloc(_data_version * sizeof(CData));
        memcpy(t, _versions, _data_version);
        for(uint64_t i = 0; i < _data_version; i++){
            t[i]._bytes = _versions[i]._bytes;
            t[i]._size = _versions[i]._size;
            t[i]._pos = _versions[i]._pos;
        }
        free(_versions[_data_version]._bytes);
        free(_versions);
        _versions = t;
        return true;
    };
    //
    // uint64_t& getlen(){
    //   return data._size;
    // }
    // uint64_t& getdatasize(){
    //   return _size;
    // }
    // uint64_t& getpos(){
    //   return data._pos;
    // }
    // uint64_t& getversion(){
    //   return _data_version;
    // }
    //

  private:
    CData data;
    uint64_t _size;
    uint64_t _pos;
    uint64_t _data_version;
    CData * _versions;
};

#ifndef __PROGTEST__
bool               writeTest                               ( CFile           & x,
                                                             const initializer_list<uint8_t> & data,
                                                             uint32_t          wrLen )
{
  return x . write ( data . begin (), data . size () ) == wrLen;
}

bool               readTest                                ( CFile           & x,
                                                             const initializer_list<uint8_t> & data,
                                                             uint32_t          rdLen )
{
  uint8_t  tmp[100];
  uint32_t idx = 0;

  if ( x . read ( tmp, rdLen ) != data . size ())
    return false;
  for ( auto v : data )
    if ( tmp[idx++] != v )
      return false;
  return true;
}
// void               readTest2                                ( CFile           & x,
//                                                              const initializer_list<uint8_t> & data,
//                                                              uint32_t          rdLen )
// {
//   uint8_t  tmp[100];
//   uint32_t idx = 0;
//
//
//   std::cout << x.read(tmp,rdLen) << '\n';
//   for ( auto v : data )
//     std::cout << static_cast<int>(tmp[idx++]) << '\t' << static_cast<int>(v) <<'\n';
// }

int main ( void )
{
  CFile f0;

  assert ( writeTest ( f0, { 10, 20, 30 }, 3 ) );
  assert ( f0 . fileSize () == 3 );
  assert ( writeTest ( f0, { 60, 70, 80 }, 3 ) );
  assert ( f0 . fileSize () == 6 );
  assert ( f0 . seek ( 2 ));

  assert ( writeTest ( f0, { 5, 4 }, 2 ) );
  assert ( f0 . fileSize () == 6 );
  assert ( f0 . seek ( 1 ));
  //readTest2(f0, { 20, 5, 4, 70, 80 }, 7);
  assert ( readTest ( f0, { 20, 5, 4, 70, 80 }, 7 ));
  assert ( f0 . seek ( 3 ));

  f0 . addVersion();

  assert ( f0 . seek ( 6 ));

  assert ( writeTest ( f0, { 100, 101, 102, 103 }, 4 ) );
  f0 . addVersion();

  assert ( f0 . seek ( 5 ));
  CFile f1 ( f0 );
  f0 . truncate ();

  assert ( f0 . seek ( 0 ));
  //readTest2( f0, { 10, 20, 5, 4, 70 }, 20 );
  assert ( readTest ( f0, { 10, 20, 5, 4, 70 }, 20 ));
  assert ( f0 . undoVersion () );
  assert ( f0 . seek ( 0 ));
  assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80, 100, 101, 102, 103 }, 20 ));
  assert ( f0 . undoVersion () );
  assert ( f0 . seek ( 0 ));
  //readTest2(f0, { 10, 20, 5, 4, 70, 80 }, 20);
  assert ( readTest ( f0, { 10, 20, 5, 4, 70, 80 }, 20 ));
  assert ( !f0 . seek ( 100 ));
  assert ( writeTest ( f1, { 200, 210, 220 }, 3 ) );
  assert ( f1 . seek ( 0 ));
  //readTest2(f1, { 10, 20, 5, 4, 70, 200, 210, 220, 102, 103 }, 20);
  assert ( readTest ( f1, { 10, 20, 5, 4, 70, 200, 210, 220, 102, 103 }, 20 ));
  assert ( f1 . undoVersion () );
  assert ( f1 . undoVersion () );
  assert ( readTest ( f1, { 4, 70, 80 }, 20 ));
  assert ( !f1 . undoVersion () );
    assert ( writeTest ( f1, { 200, 210, 220 ,10,102,123,100,200,220,220,220}, 11 ) );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

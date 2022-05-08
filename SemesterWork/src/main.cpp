#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <map>
#include <cstring>
#include "matrix.h"
#include "DiffMatrix.h"
#include "SumMatrix.h"
#include "MultMatrix.h"
#include "CGem.h"
#include "CGemKomentare.h"

int main(int argc, char const *argv[]) {

  std::cout << "\t\t" << "Chosse beginning options" << '\n';
  std::cout << "\t\t" << "SCAN \'matice\'[x][y]" << '\n';
  std::map<char,CMatrix> DATA;
  while(true){
    if( DATA.size() == 1 ){
      std::cout << "\t\t" << "Chose another options" << '\n';
      std::cout << "\t\t" << "SCAN \'matice\'[x][y]" << '\n';
      std::cout << "\t\t" << "Inverse \'matice\'" << '\n';
      std::cout << "\t\t" << "Transporation \'matice\'" << '\n';
      std::cout << "\t\t" << "\'matice\' *= \'int\'" << '\n';
      std::cout << "\t\t" << "\'matice\' ^= \'int\'"<<'\n';
      std::cout << "\t\t" << "Determinant \'matice\'" << '\n';
      std::cout << "\t\t" << "Hodnost \'matice\'" << '\n';
      std::cout << "\t\t" << "GEM \'matice\' + -c(common) + -v(komentari)" << '\n';
      std::cout << "\t\t" << "PRINT \'matice\'" << '\n';
      std::string option;
      std::cin >> option;
      if(option.substr(0,4) == "SCAN"){
        char matrix;
        int row,col;
        scanf(" %c [%d] [%d]",&matrix, &row,&col);
        try{
          CMatrix b(row,col);
          std::cin >> b;
          DATA.emplace(std::make_pair(matrix, b));
          continue;
        }
        catch (std::bad_array_new_length& err){
          std::cout << "Invalid size of matrix." << '\n';
          std::cout << "Try Again." << '\n';
          continue;
        }
      }
      else if(option.size() == 1){
        char matrix = option[0];
        bool IsInMap;
        for(const auto& m : DATA){
          if( m.first == matrix){
            IsInMap = true;
          }
        }
          char tmp1;
          char tmp2;
          int value;
          scanf(" %c", &tmp1);
          if(tmp1 == '*' && IsInMap){
            scanf(" %c %d", &tmp2,&value);
            DATA.at(matrix) *= value;
            continue;
          }
          else if(tmp1 == '^' && IsInMap){
            scanf(" %c %d", &tmp2,&value);
            DATA.at(matrix).Power(value);
            continue;
          }
          else if(tmp1 == '=' && !IsInMap){
            char old_matrix, func;
            int value;
            scanf(" %c %c %d", &old_matrix,&func,&value);
            CMatrix d = DATA.at(old_matrix) * value;
            DATA.emplace(std::make_pair(matrix, d));
            continue;
          }
        else{
          std::cout << "Unknown matrix. Try again" << '\n';
          continue;
        }
      }
      else{
          if("Inverse" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << "Inverse of " << matrix << " matrix:\n"<< DATA.at(matrix).Inverse() << '\n';
            continue;
          }
          else if("Transporation" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << "Transporation of " << matrix << " matrix:\n" << DATA.at(matrix).Trans() << '\n';
            continue;
          }
          else if("Determinant" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << "Determinant of " << matrix << " matrix:\n" << DATA.at(matrix).Det()<< '\n';
            continue;
          }
          else if("Hodnost" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << "Hodnost of " << matrix << " matrix:\n" << DATA.at(matrix).Rank()<< '\n';
            continue;
          }
          else if("GEM" == option){
            // char matrix;
            // char func;
            // char minus;
            // scanf(" %c %c%c", &matrix, &minus, &func);
            // if(func == 'c'){
            //   DATA.at(matrix).GEM();
            // }
            // else if(func == 'v'){
            //   DATA.at(matrix).GEMsKomentarem();
            // }
            // else{
            //   std::cout << "Unknown parametrs" << '\n';
            // }
            // continue;
            char matrix;
            char func;
            char minus;
            scanf(" %c %c%c", &matrix, &minus, &func);
            CGem gemovani(DATA.at(matrix));
            if(func == 'c'){
              gemovani.RunGem();
            }
            else if(func == 'v'){
              CGemKomentare gemovani(DATA.at(matrix));
              gemovani.RunGem();
            }
            else{
              std::cout << "Unknown parametrs" << '\n';
            }
            continue;
          }
          else if("PRINT" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << DATA.at(matrix) << '\n';
            continue;
          }
          else{
            std::cout << "Unknown function" << '\n';
            continue;
          }
      }
    }
    if( DATA.size() > 1){
      std::cout << "\t\t" << "Chose another options" << '\n';
      std::cout << "\t\t" << "SCAN \'matice\'[x][y]" << '\n';
      std::cout << "\t\t" << "Inverse" << '\n';
      std::cout << "\t\t" << "Transporation" << '\n';
      std::cout << "\t\t" << "\'matice\' *= \'int\'" << '\n'; //vector nasobeni
      std::cout << "\t\t" << "\'matice\' = \'matice\' * \'int\'" << '\n'; //from chars
      std::cout << "\t\t" << "\'matice\' = \'matice\' * \'matice\'" << '\n';
      std::cout << "\t\t" << "\'matice\' ^= \'int\'"<<'\n';
      std::cout << "\t\t" << "\'matice\' += \'matice\'" << '\n';
      std::cout << "\t\t" << "\'matice\' = \'matice\' + \'matice\'" << '\n';
      std::cout << "\t\t" << "\'matice\' -= \'matice\'" << '\n';
      std::cout << "\t\t" << "\'matice\' = \'matice\' - \'matice\'" << '\n';
      std::cout << "\t\t" << "Determinant \'matice\'" << '\n';
      std::cout << "\t\t" << "Hodnost \'matice\'" << '\n';
      std::cout << "\t\t" << "GEM \'matice\' + -c(common) + -v(komentari)" << '\n';
      std::cout << "\t\t" << "\'matice\' = SPLIT \'matice\' (\'hodnota1\', \'hodnota2\')" << '\n';
      std::cout << "\t\t" << "\'matice\' = MERGE \'matice\' \'matice\'" << '\n';
      std::cout << "\t\t" << "PRINT \'matice\'" << '\n';
      std::string option;
      std::cin >> option;
      if(option.substr(0,4) == "SCAN"){
        char matrix;
        int row,col;
        scanf(" %c [%d] [%d]",&matrix ,&row,&col);
        try{
          CMatrix c(row,col);
          std::cin >> c;
          DATA.emplace(std::make_pair(matrix, c));
        }
        catch (std::bad_array_new_length& err){
          std::cout << "Invalid size of matrix." << '\n';
          std::cout << "Try Again." << '\n';
        }
      }
      else if(option.size() == 1){
        char matrix = option[0];
        bool IsInMap;
        for(const auto& m : DATA){
          if( m.first == matrix){
            IsInMap = true;
          }
        }
          char tmp1;
          char tmp2;
          int value;
          scanf(" %c", &tmp1);
          if(tmp1 == '*' && IsInMap){
            scanf(" %c %d", &tmp2,&value);
            DATA.at(matrix) *= value;
            continue;
          }
          else if(tmp1 == '^' && IsInMap){
            scanf(" %c %d", &tmp2,&value);
            DATA.at(matrix).Power(value);
            continue;
          }
          else if(tmp1 == '+' && IsInMap){
            char old_matrix;
            scanf(" %c %c", &tmp2,&old_matrix);
            bool IsValid;
            for(const auto& m : DATA){
              if( m.first == old_matrix){
                IsValid = true;
              }
            }
            if(IsValid){
              DATA.at(matrix) += DATA.at(old_matrix);
              continue;
            }
            else{
              std::cout << "Try again,  that matrix do not exists" << '\n';
              continue;
            }
          }
          else if(tmp1 == '-' && IsInMap){
            char old_matrix;
            scanf(" %c %c", &tmp2,&old_matrix);
            bool IsValid;
            for(const auto& m : DATA){
              if( m.first == old_matrix){
                IsValid = true;
              }
            }
            if(IsValid){
              DATA.at(matrix) -= DATA.at(old_matrix);
              continue;
            }
            else{
              std::cout << "Try again,  that matrix do not exists" << '\n';
              continue;
            }
          }
          else if(tmp1 == '='){
            // char old_matrix, func;
            // std::string SorM;
            // std::cin >> SorM;
            // if(SorM.size()==1){
            //   old_matrix = SorM[0];
            //   scanf(" %c", &func);
            //
            //   bool IsValid;
            //   for(const auto& m : DATA){
            //     if( m.first == old_matrix){
            //       IsValid = true;
            //     }
            //   }
            //   if(func == '+' && IsValid){
            //     char another_matrix;
            //     scanf(" %c", &another_matrix);
            //     bool ExistsM;
            //     for(const auto& m : DATA){
            //       if( m.first == another_matrix){
            //         ExistsM = true;
            //       }
            //     }
            //     if(ExistsM){
            //       CMatrix d = DATA.at(old_matrix) + DATA.at(another_matrix);
            //       DATA.emplace(std::make_pair(matrix, d));
            //       continue;
            //     }
            //     else{
            //       std::cout << "Try again,  that matrix do not exists" << '\n';
            //       continue;
            //     }
            //   }
            //   else if(func == '-' && IsValid){
            //     char another_matrix;
            //     scanf(" %c", &another_matrix);
            //     bool ExistsM;
            //     for(const auto& m : DATA){
            //       if( m.first == another_matrix){
            //         ExistsM = true;
            //       }
            //     }
            //     if(ExistsM){
            //       CMatrix d = DATA.at(old_matrix) - DATA.at(another_matrix);
            //       DATA.emplace(std::make_pair(matrix, d));
            //       continue;
            //     }
            //     else{
            //       std::cout << "Try again,  that matrix do not exists" << '\n';
            //       continue;
            //     }
            //   }
            //   else if(func == '*' && IsValid){
            //     char another_matrix;
            //     scanf(" %c", &another_matrix);
            //     if(another_matrix >= 48 && another_matrix <= 57){
            //       int value = another_matrix -'0';
            //       CMatrix d = DATA.at(old_matrix) * value;
            //       DATA.emplace(std::make_pair(matrix, d));
            //       continue;
            //     }
            //     else{
            //       bool ExistsM;
            //       for(const auto& m : DATA){
            //         if( m.first == another_matrix){
            //           ExistsM = true;
            //         }
            //       }
            //       if(ExistsM){
            //         CMatrix d = DATA.at(old_matrix) * DATA.at(another_matrix);
            //         DATA.emplace(std::make_pair(matrix, d));
            //         continue;
            //       }
            //       else{
            //         std::cout << "Try again,  that matrix do not exists" << '\n';
            //         continue;
            //       }
            //     }
            //   }
            //   else{
            //     std::cout << "Unknown algebra function for matrices" << '\n';
            //     continue;
            //   }
            char old_matrix, func;
            std::string SorM;
            std::cin >> SorM;
            if(SorM.size()==1){
              old_matrix = SorM[0];
              scanf(" %c", &func);

              bool IsValid;
              for(const auto& m : DATA){
                if( m.first == old_matrix){
                  IsValid = true;
                }
              }
              if(func == '+' && IsValid){
                char another_matrix;
                scanf(" %c", &another_matrix);
                bool ExistsM;
                for(const auto& m : DATA){
                  if( m.first == another_matrix){
                    ExistsM = true;
                  }
                }
                if(ExistsM){
                  SumMatrix algebra(DATA.at(old_matrix),DATA.at(another_matrix));
                  CMatrix d = algebra.Operation();
                  //CMatrix d = DATA.at(old_matrix) + DATA.at(another_matrix);
                  DATA.emplace(std::make_pair(matrix, d));
                  continue;
                }
                else{
                  std::cout << "Try again,  that matrix do not exists" << '\n';
                  continue;
                }
              }
              else if(func == '-' && IsValid){
                char another_matrix;
                scanf(" %c", &another_matrix);
                bool ExistsM;
                for(const auto& m : DATA){
                  if( m.first == another_matrix){
                    ExistsM = true;
                  }
                }
                if(ExistsM){
                  DiffMatrix algebra(DATA.at(old_matrix),DATA.at(another_matrix));
                  CMatrix d = algebra.Operation();
                  //CMatrix d = DATA.at(old_matrix) - DATA.at(another_matrix);
                  DATA.emplace(std::make_pair(matrix, d));
                  continue;
                }
                else{
                  std::cout << "Try again,  that matrix do not exists" << '\n';
                  continue;
                }
              }
              else if(func == '*' && IsValid){
                char another_matrix;
                scanf(" %c", &another_matrix);
                if(another_matrix >= 48 && another_matrix <= 57){
                  int value = another_matrix -'0';
                  CMatrix d = DATA.at(old_matrix) * value;
                  DATA.emplace(std::make_pair(matrix, d));
                  continue;
                }
                else{
                  bool ExistsM;
                  for(const auto& m : DATA){
                    if( m.first == another_matrix){
                      ExistsM = true;
                    }
                  }
                  if(ExistsM){
                    MultMatrix algebra(DATA.at(old_matrix),DATA.at(another_matrix));
                    CMatrix d = algebra.Operation();
                    //CMatrix d = DATA.at(old_matrix) * DATA.at(another_matrix);
                    DATA.emplace(std::make_pair(matrix, d));
                    continue;
                  }
                  else{
                    std::cout << "Try again,  that matrix do not exists" << '\n';
                    continue;
                  }
                }
              }
              else{
                std::cout << "Unknown algebra function for matrices" << '\n';
                continue;
              }
            }
            else{
              if(SorM == "SPLIT"){
                char another_matrix;
                int new_rows,new_cols;
                scanf(" %c (%d , %d)", &another_matrix, &new_rows, &new_cols);
                CMatrix d = DATA.at(another_matrix).Split(new_rows,new_cols);
                DATA.emplace(std::make_pair(matrix,d));
                continue;
              }
              else if (SorM == "MERGE"){
                char old_matrix,another_matrix;
                scanf(" %c %c", &old_matrix, &another_matrix);
                CMatrix d = DATA.at(old_matrix).Merge(DATA.at(another_matrix));
                DATA.emplace(std::make_pair(matrix,d));
                continue;
              }
              else{
                std::cout << "Unknown input" << '\n';
              }
            }
          }
        else{
          std::cout << "Unknown matrix. Try again" << '\n';
          continue;
        }
      }
      else{
          if("Inverse" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << "Inverse of "<< matrix << " matrix:\n"<< DATA.at(matrix).Inverse() << '\n';
            continue;
          }
          else if("Transporation" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << "Transporation of " << matrix << " matrix:\n" << DATA.at(matrix).Trans() << '\n';
            continue;
          }
          else if("Determinant" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << "Determinant of " << matrix<< " matrix:\n" << DATA.at(matrix).Det()<< '\n';
            continue;
          }
          else if("Hodnost" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << "Hodnost of " << matrix << " matrix:\n" << DATA.at(matrix).Rank()<< '\n';
            continue;
          }
          else if("GEM" == option){
            // char matrix;
            // char func;
            // char minus;
            // scanf(" %c %c%c", &matrix,&minus,&func);
            // if(func == 'c'){
            //   DATA.at(matrix).GEM();
            // }
            // else if(func == 'v'){
            //   DATA.at(matrix).GEMsKomentarem();
            // }
            // else{
            //   std::cout << "Unknown parametrs" << '\n';
            // }
            // continue;
            char matrix;
            char func;
            char minus;
            scanf(" %c %c%c", &matrix, &minus, &func);
            CGem gemovani(DATA.at(matrix));
            if(func == 'c'){
              gemovani.RunGem();
            }
            else if(func == 'v'){
              CGemKomentare gemovani(DATA.at(matrix));
              gemovani.RunGem();
            }
            else{
              std::cout << "Unknown parametrs" << '\n';
            }
            continue;
          }
          else if("PRINT" == option){
            char matrix;
            scanf(" %c", &matrix);
            std::cout << DATA.at(matrix) << '\n';
            continue;
          }
          else{
            std::cout << "Unknown function" << '\n';
            continue;
          }
      }
    }

    if(DATA.size() == 0){
      std::string option;
      std::string tmp;
      int row,col;
      std::cin >> option;
      //int iter = 0;
      if(option.substr(0,4) == "SCAN"){
        char matrix;
        scanf(" %c [%d] [%d]",&matrix ,&row,&col);
        try{
          CMatrix a(row,col);
          std::cin >> a;
          DATA.emplace(std::make_pair(matrix, a));
        }
        catch (std::bad_array_new_length& err){
          std::cout << "Invalid size of matrix." << '\n';
          std::cout << "Try Again." << '\n';
        }
      }
    }
  }
  return 0;
}

#include <stdio.h>
#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;
using namespace ariel;
 //limit of colums
 int const colum_limit = 100;
 /**
  * @brief A function that throws an execption if one of the arguments is negative
  */
void throw_negative(int page , int line , int colum){
    if (page < 0 || line < 0 || colum < 0 || colum > colum_limit)
        {
        throw invalid_argument("can't get negative numbers");
        }       
     }
    
    /**
     * @brief A function that check if specific page is already written
     */
     bool Notebook::if_written(int page, int line , int colum, Direction dir, int len_of_string){
         if (dir == ariel::Direction::Horizontal)
         {
            for (int i = 0; i < len_of_string; i++)
         {
                try
                    {
                    if( this->notebook.at(page).at(line).at(colum) != '_'){
                    return true;
                    }
                    }
                    catch(const std::exception& e)
                    {
                    dir == ariel::Direction::Horizontal ? colum++: line++;
                    }
                }
         }
         else{
             for (int j = 0; j < len_of_string; j++)
             {
                        try
                    {
                    if(this->notebook.at(page).at(line).at(colum) == '~' || this->notebook.at(page).at(line).at(colum) != '_'){
                    
                    return true;
                    }
                    }
                    catch(const std::exception& e)
                    {
                    line++;
                    }
             }
             
         }
         return false;
        }
     void Notebook::write(int page, int line , int colum, Direction dir , string const & to_write){
         int colum_1 = colum;
         for (char c:to_write){
             if (c == '\n' || c =='~'){
                 throw invalid_argument("can't write \n");
             }

         }
         //if get negative inputs or colum is out of bounds
        throw_negative(page,line,colum);
        if(if_written(page,line, colum, dir, to_write.length())){
            throw invalid_argument("written");
        }
        for (char ch : to_write){
            if(isprint(ch) == 0){
                throw invalid_argument("not printable character");
            } 
            if(dir == Direction::Horizontal){
                if((unsigned long)colum_1 + to_write.length() > colum_limit-1 ){
                throw invalid_argument("can't write this because string is out of colums bounds");
                                                                               }
                notebook[page][line][colum] = ch; 
                colum++;
                                            }
            else{
                if( colum < colum_limit){
                this->notebook[page][line][colum] = ch;
                line++;
                                        } 
                else {
                    throw invalid_argument("can't write over colum 99");
                    }
              }
         }    
        }

        string Notebook::read(int page, int line, int colum, Direction dir, int how_much_read){
        //if get negative inputs or colum is out of bounds
        throw_negative(page, line, colum);
        if (colum > colum_limit-1 || how_much_read < 0 || 
            (Direction::Horizontal == dir && colum + how_much_read > colum_limit)) {
            throw invalid_argument("read outside the line");
        }

         string return_text;
         for(int i = 0 ; i<how_much_read ; i++){
             try
             {
                 return_text += this->notebook.at(page).at(line).at(colum);
             }
             catch(const std::exception& e)
             {
                 this->notebook[page][line][colum] = '_';
                 return_text += "_";
             }
             dir == Direction::Horizontal ? colum++ : line++;
         }
         return return_text;
     } 


     void Notebook::erase(int page, int line, int colum, Direction dir, int num_of_char ){
        //if get negative inputs or colum is out of bounds
        throw_negative(page, line, colum);
        if(num_of_char < 0 || colum > colum_limit-1 ||
          (Direction::Horizontal == dir && colum + num_of_char > colum_limit-1)){
            throw invalid_argument ("erase outside the line");
        }

        for (int i = 0; i < num_of_char; i++)
        {
                try
                {
                    this->notebook.at(page).at(line).at(colum) = '~';
                }
                catch(const std::exception& e)
                {
                    this->notebook[page][line][colum] = '~';
                }
                dir == Direction::Horizontal ? colum++ : line++;
        }
     }

    void Notebook::show(int page){
        throw_negative(page,0,0);
        string ans;
        if(this->notebook.find(page) == this->notebook.end()){ // if end function return the last key in notebook so the page not exist
            // throw invalid_argument("page not exist");
            for (int i = 0; i <= colum_limit ; i++)
        {
                ans += std::string(colum_limit,'_');
                ans += '\n';
            }
        }
        else{
        int maximum_line = this->notebook.at(page).rbegin()->first;
        for (int i = 0; i <= maximum_line ; i++)
        {
            if(this->notebook.at(page).find(i) == this->notebook.at(page).end()){
                ans += std::string(colum_limit,'_');
                ans += '\n';
            }
            else{
                for (int j = 0; j < colum_limit; j++)
                {
                    try
                    {
                        ans += this->notebook.at(page).at(i).at(j);
                    }
                    catch(const std::exception& e)
                    {
                        ans += '_';
                    }
                    
                }

                ans += '\n';
            }
        }
        
        }
        cout << ans << endl;
    }


// int main(){
//     ariel::Notebook test;
//     test.write(1,0,0, ariel::Direction::Horizontal,"test");
//     //test.write(1,0,0, ariel::Direction::Horizontal,"haim");
//     test.write(1,2,3,ariel::Direction::Vertical,"haim");
//     test.show(1);
//     string read_test =  test.read(1,0,0,ariel::Direction::Horizontal,7);
//     cout << read_test << endl;
//     test.erase(1,0,0,ariel::Direction::Horizontal,4);
//     read_test = test.read(1,0,0,ariel::Direction::Horizontal,7);
//     cout << read_test <<endl;
//     test.write(0,2,90,ariel::Direction::Horizontal,"this is text to check if throw execption is working ");
//     test.write(1,3,0, ariel::Direction::Horizontal,"haim");
//     test.show(1);
//     Notebook note;
//     note.write(1,2,55,Direction::Horizontal,"hello world");
//     note.erase(1,2,60,Direction::Horizontal,6);
//     read_test=note.read(1,2,55,Direction::Horizontal,11);
//     cout << read_test <<endl;
//     note.erase(1,2,53,Direction::Horizontal,2);
//     read_test = note.read(1,2,50,Direction::Horizontal,16);
//     cout <<read_test <<endl;

//  }
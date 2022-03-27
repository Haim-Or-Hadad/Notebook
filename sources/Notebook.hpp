#include <stdio.h>
#include <iostream>
#include <string>
#include<map>
#include<vector>
#include "Direction.hpp"

namespace ariel{
class Notebook{
        /**The notebook's pages will be the keys of the map .
        The notebook is infinite as requested , because we always can Increase the data structure.
        Then each key that is a page will have its own page that consists of an matrix of vectors.
        **/
        std::map<int,std::map<int,std::map<int,char>>> notebook;

        public:
        Notebook(){
           int const len_row = 100;
           int num_of_pages = 1;
        }
        ~Notebook() {}
        /**
         * @brief Function that gets a location in the notebook and write the string that got in the appropriate place, 
         * if something is listed there or we deleted in the past from there the function will throw an error     
         * @param page : the page that we want to write there
         * @param line : the line in the page that we want write there
         * @param colum : the colum in the line that we want to write there
         * @param dir :the direction that we need to write
         * @param to_write :string to write
         */
            void write(int page, int line , int colum, Direction dir , std::string const & to_write);
        /**
         * @brief function that gets a loaction to read the text , the function return the string that right there.
         * @param page : the page that we want to read 
         * @param line :the line in the page that we want read from there
         * @param colum :the colum in the line that we want read from there
         * @param dir : the direction that we need to read 
         * @param how_much_read : how much charcter we want to read
         * @return std::string 
         */
            std::string read(int page, int line, int colum, Direction dir, int how_much_read);
        /**
         * @brief function that receives a position and deletes all the characters from the position it received
         * @param page : the page that we want to read from there
         * @param line :the line in the page that we want erase from there
         * @param colum :the colum in the line that we want erase from there
         * @param dir : the direction that we need to erase the string 
         * @param num_of_char : the numbers of the character that need to erase
         */
            void erase(int page, int line, int colum, Direction dir, int num_of_char );

        /**
         * @brief Receives a page number and presents it in a convenient way to read, in any format of your choice
         * @param page : the page that need to show 
         */
            void show(int page);
        /**
         * @brief 
         * 
         */
         bool if_written(int page,int line, int colum, Direction dir, int len_of_string );
            };
}

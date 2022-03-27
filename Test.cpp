/**
 * @file Test.cpp
 * @author Haim Or Hadad
 * @brief 
 * @version 0.1
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "doctest.h"
#include "Notebook.hpp"
using namespace ariel;

#include <string>
#include <algorithm>
using namespace std;


Notebook test_note;
TEST_CASE("read notebook"){
    SUBCASE("Correct reading"){
        CHECK(test_note.read(0,0,0,Direction::Horizontal,5) == "_____");
        test_note.write(0,0,0, Direction::Horizontal,"start");
        CHECK(test_note.read(0,0,0,Direction::Horizontal,5) == "start");
        CHECK(test_note.read(0,0,0,Direction::Horizontal,10) == "start______");
        CHECK(test_note.read(0,0,5,Direction::Horizontal,5) == "_____");
        CHECK(test_note.read(0,0,0,Direction::Vertical,1) == "s");
        CHECK(test_note.read(0,0,0,Direction::Vertical,2) == "s_");
        test_note.write(1,3,0, Direction::Horizontal,"start");
        CHECK(test_note.read(1,3,0,Direction::Horizontal,5) == "start");
        CHECK(test_note.read(1,3,5,Direction::Horizontal,5) == "_____");
        CHECK(test_note.read(1,3,0,Direction::Horizontal,6) == "start_");
        CHECK(test_note.read(1,3,6,Direction::Horizontal,1) == "_");
        CHECK(test_note.read(0,0,0,Direction::Vertical,5) == "start");
    }
}

TEST_CASE("write on notebook"){
    SUBCASE("correct writing"){
        test_note.write(4,2,0, Direction::Horizontal,"start");
        CHECK(test_note.read(4,2,0,Direction::Horizontal,5) == "start");
        CHECK(test_note.read(0,0,5,Direction::Horizontal,5) == "_____");
    }
    SUBCASE("writing on the same place"){
        CHECK_THROWS(test_note.write(4,2,0, Direction::Horizontal,"start"));
        CHECK_THROWS(test_note.write(4,2,1,Direction::Horizontal,"tart"));
        CHECK_THROWS(test_note.write(4,2,2, Direction::Horizontal,"start"));
        CHECK_THROWS(test_note.write(4,2,2,Direction::Horizontal,"tart"));
    }
}

TEST_CASE("erase"){
    SUBCASE("good erase"){
        test_note.write(5,2,0, Direction::Horizontal,"erase me");
        test_note.erase(5,2,0, Direction::Horizontal,8);
        CHECK(test_note.read(5,2,0,Direction::Horizontal,8) == "~~~~~~~~");
        CHECK(test_note.read(5,2,1,Direction::Horizontal,7) == "~~~~~~~");
        test_note.write(41,0,0, Direction::Horizontal,"notebook");
        test_note.erase(41,0,0, Direction::Horizontal,7);
        CHECK(test_note.read(41,0,0,Direction::Horizontal,8) == "~~~~~~~_");
        CHECK(test_note.read(41,0,0,Direction::Horizontal,7) == "~~~~~~~");
    }
}


#include "catch.hpp"
#include "../Parser.h"

namespace HLR1{

/*unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}*/

std::string s_goodLineCommentInput = "\
    Yes1; No1                   \n\
    Yes2 ; No2                  \n\
    ;No3                        \n\
    Yes3                          \
";
TEST_CASE( "Correctly successfully parse line comments", "[Parser]") {
    Parser p(s_goodLineCommentInput);
    REQUIRE(p.getStr()=="Yes1");
    REQUIRE(p.getStr()=="Yes2");
    REQUIRE(p.getStr()=="Yes3");
}

std::string s_goodNumberInput = "100 -100 0x100 -0x100 0X134 ";
TEST_CASE( "Correctly successfully get numbers", "[Parser]") {
    Parser p(s_goodNumberInput);
    REQUIRE(p.getValue()==100);
    REQUIRE(p.getValue()==((uint32_t)-100));
    REQUIRE(p.getValue()==0x100);
    REQUIRE(p.getValue()==((uint32_t)-0x100));
    REQUIRE(p.getValue()==0X134);

}

std::string s_badNumberInput = "abc 00x55 x100 0x-100 0x;10 ";
TEST_CASE( "Correctly fail to get numbers", "[Parser]") {
    Parser p(s_badNumberInput);
    SECTION("Non-numeric"){ REQUIRE(p.getValue()==Parser::BAD_NUMBER); REQUIRE(!p); }
    SECTION("Two-leading zeroes on hex"){ p.skip();
        REQUIRE(p.getValue()==Parser::BAD_NUMBER); REQUIRE(!p); }
    SECTION("No leading zero on hex"){ p.skip(); p.skip();
        REQUIRE(p.getValue()==Parser::BAD_NUMBER); REQUIRE(!p);}
    SECTION("Minux after x in hex"){ p.skip(); p.skip(); p.skip();
        REQUIRE(p.getValue()==Parser::BAD_NUMBER); REQUIRE(!p);}
    SECTION("Hex broken by a line comment"){ p.skip(); p.skip(); p.skip(); p.skip();
        REQUIRE(p.getValue()==Parser::BAD_NUMBER); REQUIRE(!p);}



}

}//namespace HLR1

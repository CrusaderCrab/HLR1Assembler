#include "catch.hpp"
#include "../Parser.h"

namespace HLR1{

uint32_t BAD_NUMBER_copy = Parser::BAD_NUMBER;

std::string s_goodLineCommentInput = "\
    Yes1; No1                   \n\
    Yes2 ; No2                  \n\
    ;No3                        \n\
    Yes3                          \
";/*
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
    SECTION("Non-numeric"){ REQUIRE(p.getValue()==BAD_NUMBER_copy); REQUIRE(!p); }
    SECTION("Two-leading zeroes on hex"){ p.skip();
        REQUIRE(p.getValue()==BAD_NUMBER_copy); REQUIRE(!p); }
    SECTION("No leading zero on hex"){ p.skip(); p.skip();
        REQUIRE(p.getValue()==BAD_NUMBER_copy); REQUIRE(!p);}
    SECTION("Minux after x in hex"){ p.skip(); p.skip(); p.skip();
        REQUIRE(p.getValue()==BAD_NUMBER_copy); REQUIRE(!p);}
    SECTION("Hex broken by a line comment"){ p.skip(); p.skip(); p.skip(); p.skip();
        REQUIRE(p.getValue()==BAD_NUMBER_copy); REQUIRE(!p);}
}

std::string s_goodRegisterInput = "R15 r02 R0 r4564 R33 ";
TEST_CASE("Correctly Successfully get registers", "[Registers]"){
    Parser p(s_goodRegisterInput);
    REQUIRE(p.getRegister()==15);
    REQUIRE(p.getRegister()==2);
    REQUIRE(p.getRegister()==0);
    REQUIRE(p.getRegister()==4564);
    REQUIRE(p.getRegister()==33);
}

std::string s_badRegisterInput = "R r0x10 R0x11 rr11 RR22 R-100";
TEST_CASE("Correctly fail to get registers", "[Registers]"){
    Parser p(s_badRegisterInput);
    REQUIRE(Parser::BAD_NUMBER);
    SECTION("No register number"){
        REQUIRE(p.getRegister()==BAD_NUMBER_copy); REQUIRE(!p); }
    SECTION("Hexidecimal register number given - lower r"){ p.skip();
        REQUIRE(p.getRegister()==BAD_NUMBER_copy); REQUIRE(!p);}
    SECTION("Hexidecimal register number given - upper R"){ p.skip(); p.skip();
        REQUIRE(p.getRegister()==BAD_NUMBER_copy); REQUIRE(!p);}
    SECTION("two lower rs used \"rr11\""){ p.skip(); p.skip(); p.skip();
        REQUIRE(p.getRegister()==BAD_NUMBER_copy); REQUIRE(!p);}
    SECTION("two upper Rs used \"RR22\""){ p.skip(); p.skip(); p.skip(); p.skip();
        REQUIRE(p.getRegister()==BAD_NUMBER_copy); REQUIRE(!p);}
    SECTION("Negative register number"){ p.skip(); p.skip(); p.skip(); p.skip(); p.skip();
        REQUIRE(p.getRegister()==BAD_NUMBER_copy); REQUIRE(!p);}
}
*/
}//namespace HLR1

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

std::string s_lineCommentInput = "\
    Yes1; No1                   \n\
    Yes2 ; No2                  \n\
    ;No3                        \n\
    Yes3                          \
";

TEST_CASE( "Correctly Parse Line Comments", "[Parser]") {

    Parser p(s_lineCommentInput);
    REQUIRE(p.getStr()=="Yes1");
    REQUIRE(p.getStr()=="Yes2");
    REQUIRE(p.getStr()=="Yes3");
}

}//namespace HLR1

#include "catch.hpp"
#include "../LineParser.h"

namespace HLR1{
//  Needed as linking error with LineParser::s_BAD_NUMBER if used
//+ more then 6 times in a TEST_CASE
uint32_t BAD_NUMBER_copy = LineParser::s_BAD_NUMBER;

TEST_CASE("Correctly read nothing", "[LineParser]"){
    LineParser p("", "#");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE("" == p.getStr());
    REQUIRE(p.fail());
    REQUIRE(!p.bad());
}

TEST_CASE("Correctly read one word", "[LineParser]"){
    SECTION("No whitespace"){
        LineParser p("Yes", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Leading whitespace"){
        LineParser p("  Yes", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Trailing whitespace"){
        LineParser p("Yes  ", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Leading and trailing whitespace"){
        LineParser p("  Yes  ", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
}

TEST_CASE("Correctly read two words", "[LineParser]"){
    SECTION("Single delimiting whitespace"){
        LineParser p("Yes1 Yes2", "#");
        REQUIRE("Yes1" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("Yes2" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Trailing whitespace"){
        LineParser p("Yes1 Yes2  ", "#");
        REQUIRE("Yes1" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("Yes2" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
}

TEST_CASE("Correctly Handle comments", "[LineParser]"){
    SECTION("Just a comment, no whitespace"){
        LineParser p("#", "#");
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Leading whitespace"){
        LineParser p(" #", "#");
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Trailing whitespace"){
        LineParser p("# ", "#");
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("One word, delimited from whitespace"){
        LineParser p("Yes #", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("One word, touching comment"){
        LineParser p("Yes#", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("One word, one comment word, comment word delimited"){
        LineParser p("Yes# No", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("One word, one comment word, no delimiting"){
        LineParser p("Yes#No", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("One word, two comment words, no delimiting"){
        LineParser p("Yes#No1 no2", "#");
        REQUIRE("Yes" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("two words, two comment words, no delimiting"){
        LineParser p("Yes1 Yes2#No1 no2", "#");
        REQUIRE("Yes1" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("Yes2" == p.getStr());
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE("" == p.getStr());
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
}

std::string s_goodNumberInput = "100 -100 0x100 -0x100 0X134 ";
TEST_CASE( "Correctly successfully get numbers", "[LineParser]") {
    LineParser p(s_goodNumberInput, "#");
    REQUIRE(p.getValue()==100);
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getValue()==((uint32_t)-100));
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getValue()==0x100);
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getValue()==((uint32_t)-0x100));
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getValue()==0X134);
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getValue()==BAD_NUMBER_copy);
    REQUIRE(p.fail());
    REQUIRE(!p.bad());

}

std::string s_badNumberInput = "abc 00x55 x100 0x-100 0x#10 ";
TEST_CASE( "Correctly fail to get numbers", "[LineParser]") {
    LineParser p(s_badNumberInput, "#");
    SECTION("Non-numeric"){
        REQUIRE(p.getValue()==BAD_NUMBER_copy);
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Two-leading zeroes on hex"){
        p.skip();
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE(p.getValue()==BAD_NUMBER_copy);
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("No leading zero on hex"){
        p.skip(); p.skip();
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE(p.getValue()==BAD_NUMBER_copy);
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Minux after x in hex"){
        p.skip(); p.skip(); p.skip();
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE(p.getValue()==BAD_NUMBER_copy);
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
    SECTION("Hex broken by a line comment"){
        p.skip(); p.skip(); p.skip(); p.skip();
        REQUIRE(!p.fail());
        REQUIRE(!p.bad());
        REQUIRE(p.getValue()==BAD_NUMBER_copy);
        REQUIRE(p.fail());
        REQUIRE(!p.bad());
    }
}

std::string s_goodFilePathInput = " \
    yes1Path yes2Path/Yes2.1Path yes3Path\\Yes3.1Path \
    yes4Path\\Yes4.1Path\\Yes4.2Path                  \
    \"yes5Path\" \"\" \" yes6Path\" \"yes7Path \"     \
";
TEST_CASE( "Correctly successfully parse filepaths", "[LineParser]") {
    LineParser p(s_goodFilePathInput, "#");
    REQUIRE(p.getFilePath()=="yes1Path");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getFilePath()=="yes2Path/Yes2.1Path");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getFilePath()=="yes3Path\\Yes3.1Path");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getFilePath()=="yes4Path\\Yes4.1Path\\Yes4.2Path");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getFilePath()=="yes5Path");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getFilePath()=="");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getFilePath()=="yes6Path");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getFilePath()=="yes7Path");
    REQUIRE(!p.fail());
    REQUIRE(!p.bad());
    REQUIRE(p.getFilePath()=="");
    REQUIRE(p.fail());
    REQUIRE(!p.bad());
    LineParser p2("", "#");
    REQUIRE(p.getFilePath()=="");
    REQUIRE(p.fail());
    REQUIRE(!p.bad());

}

}

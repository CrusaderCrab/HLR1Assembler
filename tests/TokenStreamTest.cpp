#include "catch.hpp"
#include "../TokenStream.h"

namespace HLR1{

TEST_CASE("Correctly consumes Whitespace", "[TokenStream]"){
    SECTION("Empty"){ TokenStream ts("");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==2);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
    SECTION("Empty"){ TokenStream ts(" ");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==3);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
}

TEST_CASE( "Correctly successfully read strings from single line", "[TokenStream]") {
    SECTION("No spaces"){ TokenStream ts("Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==5);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.getToken() == "Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==5);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
    SECTION("One leading space"){ TokenStream ts(" Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==6);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==2);
        REQUIRE(ts.getToken() == "Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==6);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
    SECTION("Two leading spaces"){ TokenStream ts("  Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==7);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==3);
        REQUIRE(ts.getToken() == "Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==7);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
    SECTION("No trailing spaces"){ TokenStream ts("   Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==8);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==4);
        REQUIRE(ts.getToken() == "Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==8);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
    SECTION("One trailing space"){ TokenStream ts("   Yes ");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==9);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==4);
        REQUIRE(ts.getToken() == "Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==9);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
    SECTION("Two trailing spaces"){ TokenStream ts("   Yes  ");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==10);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==4);
        REQUIRE(ts.getToken() == "Yes");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==10);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
    SECTION("One space delimiter"){ TokenStream ts("   Yes1 Yes2");
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==4);
        REQUIRE(ts.getToken() == "Yes1");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==14);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==9);
        REQUIRE(ts.getToken() == "Yes2");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==14);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
    SECTION("Two space delimiters"){ TokenStream ts("   Yes1  Yes2");
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==4);
        REQUIRE(ts.getToken() == "Yes1");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==15);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==10);
        REQUIRE(ts.getToken() == "Yes2");
        REQUIRE(ts.getCurrentRowNumber()==1);
        REQUIRE(ts.getCurrentColNumber()==15);
        REQUIRE(ts.getTokenRowNumber()==1);
        REQUIRE(ts.getTokenColNumber()==1);
        REQUIRE(ts.eof());
    }
}

}

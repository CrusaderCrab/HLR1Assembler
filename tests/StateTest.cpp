#include "catch.hpp"
#include "..\state.h"
#include <iostream>

#include <windows.h>
/*bool cat(){
    int c = 3;
    char* args[3];
    args[0] = "...";
    args[1] = "-c";
    args[2] = "../HLR1_Default_Config.txt";
    HLR1::State ss(c, args);
    return ss.m_littleEndian;
}*/

void defaultState(const HLR1::State& s){
    REQUIRE(!s.m_bad);
}

TEST_CASE("Correctly parse good arguments", "[State]"){
    char* args[15];
    args[0] = "PROGRAM NAME";
    args[1] = "-c";
    args[2] = "../../tests/HLR1_Test_Config.txt";
    args[3] = "-oc";
    args[4] = "../../tests/HLR1_Test_Opcodes.txt";
    args[5] = "-i";
    args[6] = "../INPUTFILE";
    args[7] = "-o";
    args[8] = "../OUTPUTFILE";
    args[9] = "-little";
    args[10] = "-m";
    args[11] = "12345";
    args[12] = "-i";
    args[13] = "\" I AM A BANANA\"";

    char buf[1024];
    int bytes = GetModuleFileName(NULL, buf, 1024);
    std::cout<<bytes<<" BANANA: "<<buf<<" END: "<<std::endl;


    SECTION("Correctly Read no arguments"){
        HLR1::State s(5, args);
        std::cout<<s.m_bad<<" ::\n";
        //REQUIRE(!s.m_bad);
        //defaultState(s);
    }

}

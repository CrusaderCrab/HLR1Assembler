#include "catch.hpp"
#include "..\state.h"
#include <iostream>
#define rr REQUIRE

/*  std::string m_inputPath;
    std::string m_outputPath;
    std::string m_configPath;
    std::string m_opcodePath;
    std::vector<uint32_t> m_binary;
    std::vector<uint32_t> m_opcodes;
    std::vector<uint32_t> m_condCodes;
    bool m_littleEndian;
    uint32_t m_trapOVRegister;
    uint32_t m_trapUNRegister;
    uint32_t m_codeStartAddr;
    bool m_bad;
*/

void checkAllDefaultFrom(int x, const HLR1::State& s){
    switch(x){
case 0: rr(s.m_configPath=="./HLR1_Default_Config.txt");
case 1: rr(s.m_opcodePath=="../../tests/HLR1_Test_Opcodes.txt");
case 2: rr(s.m_inputPath=="./in.hlr1s");
case 3: rr(s.m_outputPath=="./out.hlr1b");
case 4: rr(s.m_littleEndian==false);
case 5: rr(s.m_codeStartAddr==614400);
    }
}

TEST_CASE("Correctly parse good arguments", "[State]"){
    char* args[15];
    args[0] = "PROGRAM NAME";
    args[1] = "-c";
    args[2] = "../../tests/HLR1_Test_Config.txt";
    args[3] = "-oc";
    args[4] = "../../tests/HLR1_Test_Opcodes_ALT.txt";
    args[5] = "-i";
    args[6] = "../../tests/INPUTFILE";
    args[7] = "-o";
    args[8] = "../../tests/OUTPUTFILE";
    args[9] = "-little";
    args[10] = "-m";
    args[11] = "12345";
    args[12] = "-i";
    args[13] = "\" I AM A BANANA\"";

    SECTION("Correctly Read new config file argument"){
        HLR1::State s(3, args);
        rr(s.m_configPath=="../../tests/HLR1_Test_Config.txt");
        checkAllDefaultFrom(1, s);
    }
    SECTION("Correctly Read new OpCode File argument"){
        HLR1::State s(5, args);
        rr(s.m_configPath=="../../tests/HLR1_Test_Config.txt");
        rr(s.m_opcodePath=="../../tests/HLR1_Test_Opcodes_ALT.txt");
        checkAllDefaultFrom(2, s);
    }
    SECTION("Correctly Read new Input File argument"){
        HLR1::State s(7, args);
        rr(s.m_configPath=="../../tests/HLR1_Test_Config.txt");
        rr(s.m_opcodePath=="../../tests/HLR1_Test_Opcodes_ALT.txt");
        rr(s.m_inputPath=="../../tests/INPUTFILE");
        checkAllDefaultFrom(3, s);
    }
    SECTION("Correctly Read new Output File argument"){
        HLR1::State s(9, args);
        rr(s.m_configPath=="../../tests/HLR1_Test_Config.txt");
        rr(s.m_opcodePath=="../../tests/HLR1_Test_Opcodes_ALT.txt");
        rr(s.m_inputPath=="../../tests/INPUTFILE");
        rr(s.m_outputPath=="../../tests/OUTPUTFILE");
        checkAllDefaultFrom(4, s);
    }
    SECTION("Correctly Read littleEndian argument"){
        HLR1::State s(10, args);
        rr(s.m_configPath=="../../tests/HLR1_Test_Config.txt");
        rr(s.m_opcodePath=="../../tests/HLR1_Test_Opcodes_ALT.txt");
        rr(s.m_inputPath=="../../tests/INPUTFILE");
        rr(s.m_outputPath=="../../tests/OUTPUTFILE");
        rr(s.m_littleEndian);
        checkAllDefaultFrom(5, s);
    }
    SECTION("Correctly Read Code start argument"){
        HLR1::State s(12, args);
        rr(s.m_configPath=="../../tests/HLR1_Test_Config.txt");
        rr(s.m_opcodePath=="../../tests/HLR1_Test_Opcodes_ALT.txt");
        rr(s.m_inputPath=="../../tests/INPUTFILE");
        rr(s.m_outputPath=="../../tests/OUTPUTFILE");
        rr(s.m_littleEndian);
        rr(s.m_codeStartAddr == 12345);
        checkAllDefaultFrom(6, s);
    }

}

TEST_CASE("Correctly reject bad arguments", "[State]"){
    SECTION("Invalid Flag"){
        char* args[5];
        args[0] = "PROGRAM NAME";
        args[1] = "-c";
        args[2] = "../../tests/HLR1_Test_Config.txt";
        args[3] = "-t";
        args[4] = "../../tests/HLR1_Test_Opcodes_ALT.txt";
        HLR1::State s(5, args);
        REQUIRE(s.m_bad);
    }
    SECTION("Flag with missing file path"){
        char* args[2];
        args[0] = "PROGRAM NAME";
        args[1] = "-c";
        HLR1::State s(2, args);
        REQUIRE(s.m_bad);
    }
}

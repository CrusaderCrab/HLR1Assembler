#include "Codes.h"

namespace HLR1{

const std::string g_opCodeNames[] = {
    "ADD",
    "ADDC",
    "SUB",
    "SUBC",
    "SUBR",
    "SUBCR",
    "AND",
    "OR",
    "XOR",
    "SLL",
    "SRL",
    "SRA",
    "LDL",
    "LDSU",
    "LDSS",
    "LDBU",
    "LDBS",
    "STL",
    "STS",
    "STB",
    "JMP",
    "JMPR",
    "CALL",
    "CALLR",
    "RET",
    "RETINT",
    "CALLINT",
    "LDHI",
    "GTLPC",
    "GETPSW",
    "PUTPSW",
    "RESERVED",
    "HLR1"
};
const uint32_t g_opCodeNamesLength = sizeof(g_opCodeNames)/sizeof(std::string);

const std::string g_condCodeNames[] = {
    "EQ",
    "NE",
    "LT",
    "LE",
    "GT",
    "GE",
    "BL",
    "BE",
    "AB",
    "AE"
};
const size_t g_condCodeNamesLength = sizeof(g_condCodeNames)/sizeof(std::string);

}

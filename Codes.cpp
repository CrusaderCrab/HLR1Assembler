#include "Codes.h"

namespace HLR1{

std::string OpCodeNames[] = {
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

std::string CondCodeNames[] = {
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

}

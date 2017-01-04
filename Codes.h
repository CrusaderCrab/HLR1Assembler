#pragma once
#include <string>
namespace HLR1{
enum class OpCode{
    ADD,
    ADDC,
    SUB,
    SUBC,
    SUBR,
    SUBCR,
    AND,
    OR,
    XOR,
    SLL,
    SRL,
    SRA,
    LDL,
    LDSU,
    LDSS,
    LDBU,
    LDBS,
    STL,
    STS,
    STB,
    JMP,
    JMPR,
    CALL,
    CALLR,
    RET,
    RETINT,
    CALLINT,
    LDHI,
    GTLPC,
    GETPSW,
    PUTPSW,
    RESERVED,
    HLR1,
    END,
    FIRST=ADD
};

inline OpCode operator++( OpCode& x ) { return x = (OpCode)((uint32_t)(x) + 1); }

extern const std::string g_opCodeNames[];
extern const size_t g_opCodeNamesLength;

enum class CondCode{
    EQ,
    NE,
    LT,
    LE,
    GT,
    GE,
    BL,
    BE,
    AB,
    AE,
    END,
    FIRST=EQ
};

inline CondCode operator++( CondCode& x ) { return x = (CondCode)((uint32_t)(x) + 1); }

extern const std::string g_condCodeNames[];
extern const size_t g_condCodeNamesLength;

}


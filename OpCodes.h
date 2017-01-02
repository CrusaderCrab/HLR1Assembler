
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


}

#pragma once
#include <stdint.h>
#include "Codes.h"
#include "state.h"
/** InstructionGen
Used to generate the actual 32-bit machine instructions which will
be read by the RISC-1 simulator. Also used to check if immediate
values are within value ranges.
*/
namespace HLR1{
/*
generateALU(OpCode, r1, s2, rd, i, c)	: A
generateLD(OpCode, r1, i, rd, c)	: A
generateST(OpCode, r1, i, rs, c)	: A
generateJMP(CondCode, ri, i)		: A
generateJMPR(CondCode, label, PC)	: B
patch(OpCode, addr)			: -
generateCall(r1, i, rd)			: A
generateCALLR(rd, label, PC) //PC+4	: B
generateRET(r1, i)			: A
generateLDHI(rd, i)			: B
*/
class InstructionGen{
#ifdef CATCH_TESTING
public:
#endif
    const State& m_state;
    uint32_t pushIn(uint32_t src, uint32_t dest, size_t n);
    uint32_t generateA(uint32_t opcode, bool cFlag, uint32_t lowR, uint32_t destR, bool iFlag, uint32_t op2);
    uint32_t generateB(uint32_t opcode, bool cFlag, uint32_t r, uint32_t imm);
    uint32_t generatePCOffset(uint32_t pc, uint32_t dest);
public:
    InstructionGen(const State& s);
    uint32_t generateALU(OpCode c, uint32_t r1, uint32_t s2, uint32_t rd, bool cond, bool imm);
    uint32_t generateMEM(OpCode c, uint32_t r1, uint32_t s2, uint32_t rd, bool cond);
    uint32_t generateJMP(CondCode c, uint32_t r1, uint32_t s2);
    uint32_t generateJMPR(CondCode c, uint32_t val);
    uint32_t generateJMPR(CondCode c, uint32_t labelAddr, uint32_t pc);
    uint32_t generateCALL(uint32_t r1, uint32_t s2, uint32_t rd);
    uint32_t generateCALLR(uint32_t rd, uint32_t val);
    uint32_t generateCALLR(uint32_t rd, uint32_t labelAddr, uint32_t pc);
    uint32_t generateRET(uint32_t rs, uint32_t s2);
    uint32_t generateLDHI(uint32_t rd, uint32_t val);
    bool checkJumpOffset(uint32_t pc, uint32_t dest);
    bool checkImmediate(uint32_t imm);
};
}

#include <iostream>
#include "InstructionGen.h"

namespace HLR1{

/*
const State& m_state;
    uint32_t generateA(uint32_t opcode, bool cFlag, uint32_t lowR, uint32_t destR, bool iFlag, uint32_t op2);
    uint32_t generateB(uint32_t opcode, bool cFlag, uint32_t r, uint32_t imm);
public:
    InstructionGen(const State& s);
    uint32_t InstructionGen::generateALU(OpCode c, uint32_t r1, uint32_t s2, uint32_t rd, bool cond, bool imm);
    uint32_t InstructionGen::generateMEM(OpCode c, uint32_t r1, uint32_t s2, uint32_t rd, bool cond);
    uint32_t InstructionGen::generateJMP(CondCode c, uint32_t r1, uint32_t s2);
    uint32_t InstructionGen::generateJMPR(CondCode c, uint32_t val);
    uint32_t InstructionGen::generateJMPR(CondCode c, uint32_t labelAddr, uint32_t pc);
    uint32_t InstructionGen::generateCALL(uint32_t r1, uint32_t s2, uint32_t rd);
    uint32_t InstructionGen::generateCALLR(uint32_t rd, uint32_t val);
    uint32_t InstructionGen::generateCALLR(uint32_t rd, uint32_t labelAddr, uint32_t pc);
    uint32_t InstructionGen::generateRET(uint32_t rs, uint32_t s2);
    uint32_t InstructionGen::generateLDHI(uint32_t rd, uint32_t val);
*/
InstructionGen::InstructionGen(const State& s)
: m_state(s) {}

uint32_t InstructionGen::generateALU(OpCode c, uint32_t r1, uint32_t s2, uint32_t rd, bool cond, bool imm){
    uint32_t code = m_state.getOpCode(c);
    return generateA(code, cond, rd, r1, imm, s2);
}
uint32_t InstructionGen::generateMEM(OpCode c, uint32_t r1, uint32_t s2, uint32_t rd, bool cond){
    uint32_t code = m_state.getOpCode(c);
    return generateA(code, cond, rd, r1, true, s2);
}
uint32_t InstructionGen::generateJMP(CondCode c, uint32_t r1, uint32_t s2){
    uint32_t code = m_state.getOpCode(OpCode::JMP);
    uint32_t ccode = m_state.getCondCode(c);
    return generateA(code, false, ccode, r1, true, s2);
}
uint32_t InstructionGen::generateJMPR(CondCode c, uint32_t labelAddr, uint32_t pc){
    uint32_t code = m_state.getOpCode(OpCode::JMPR);
    uint32_t ccode = m_state.getCondCode(c);
    uint32_t offset = generatePCOffset(pc, labelAddr);
    return generateB(code, false, ccode, offset);
}
uint32_t InstructionGen::generateCALL(uint32_t r1, uint32_t s2, uint32_t rd){
    uint32_t code = m_state.getOpCode(OpCode::CALL);
    return generateA(code, false, rd, r1, true, s2);
}
uint32_t InstructionGen::generateCALLR(uint32_t rd, uint32_t labelAddr, uint32_t pc){
    uint32_t code = m_state.getOpCode(OpCode::CALLR);
    uint32_t offset = generatePCOffset(pc, labelAddr);
    return generateB(code, false, rd, offset);
}
uint32_t InstructionGen::generateRET(uint32_t rs, uint32_t s2){
    uint32_t code = m_state.getOpCode(OpCode::RET);
    return generateB(code, false, rs, s2);
}
uint32_t InstructionGen::generateLDHI(uint32_t rd, uint32_t val){
    uint32_t code = m_state.getOpCode(OpCode::LDHI);
    uint32_t v = (val >> 13);
    return generateB(code, false, rd, v);
}
uint32_t InstructionGen::generateA(uint32_t opcode, bool cFlag, uint32_t destR,
                                   uint32_t lowR, bool iFlag, uint32_t op2){
    uint32_t bin = 0;
    bin = pushIn(opcode, bin, 7);
    //push in flag flag
    bin <<= 1;
    if(cFlag) bin++;
    //push in destR
    bin = pushIn(destR, bin, 5);
    //push in lowR
    bin = pushIn(lowR, bin, 5);
    //push in imm flag
    bin <<= 1;
    if(iFlag) bin++;
    //push in src2
    bin = pushIn(op2, bin, 13);
    return bin;

}
uint32_t InstructionGen::generateB(uint32_t opcode, bool cFlag, uint32_t r, uint32_t imm){
    uint32_t bin = 0;
    bin = pushIn(opcode, bin, 7);
    //push in flag flag
    bin <<= 1;
    if(cFlag) bin++;
    //push in lowR
    bin = pushIn(r, bin, 5);
    //push in imm
    bin = pushIn(imm, bin, 19);
    return bin;
}

uint32_t InstructionGen::pushIn(uint32_t src, uint32_t dest, size_t n){
    for(size_t i = 0; i < n; i++){
        uint32_t m = 1 << (n - (i+1));
        //std::cout<<"Beige: "<<src<<" "<<dest<<" "<<m<<" "<<(src & m)<<" "<<(m ? 1 : 0)<<std::endl;
        m = src & m;
        dest <<= 1;
        dest += (m ? 1 : 0);
    }
    return dest;
}

uint32_t InstructionGen::generatePCOffset(uint32_t pc, uint32_t dest){
    uint32_t f = dest - pc;
    return f;
}
bool checkJumpOffset(uint32_t pc, uint32_t dest){
    return (dest - pc) < 524288;
}
bool InstructionGen::checkImmediate(uint32_t imm){
    return imm < 524288;
}

}

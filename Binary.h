#pragma once
#include <stdint.h>
#include <vector>
namespace HLR1{

class Binary{
    const uint32_t m_codeStartAddr;
    const bool m_littleEndian;
    std::vector<uint8_t> m_bin;
    uint32_t m_offset;

    static uint32_t reverseBytes32(uint32_t word);
    static uint32_t reverseBytes16(uint32_t hword);
    void insertByteAt(uint32_t b, uint32_t offset);
public:
    Binary(uint32_t codeStart, bool littleEnd);
    void pushByte(uint32_t b);
    void pushHWord(uint32_t h);
    void pushWord(uint32_t w);
    uint32_t getOffset();
    void insertWordAt(uint32_t w, uint32_t offset);
    uint32_t getWordAt(uint32_t offset);
    void align();
};

}

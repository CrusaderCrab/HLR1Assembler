#include "Binary.h"
#include <iostream>

namespace HLR1{
/*
    const uint32_t m_codeStartAddr;
    const bool m_littleEndian;
    std::vector<uint8_t> m_bin;
    uint32_t m_offset;
*/
    Binary::Binary(uint32_t codeStart, bool littleEnd)
    : m_codeStartAddr(codeStart), m_littleEndian(littleEnd),
      m_offset(false) {}

    uint32_t Binary::getWordAt(uint32_t offset){
        uint32_t b0 = m_bin[offset]; b0 <<= 24;
        uint32_t b1 = m_bin[offset+1]; b1 <<= 16;
        uint32_t b2 = m_bin[offset+2]; b2 <<= 8;
        uint32_t b3 = m_bin[offset+3];
        uint32_t w = b0 | b1 | b2 | b3;
        if(m_littleEndian){
            w = reverseBytes32(w);
        }
        return w;
    }


    void Binary::insertWordAt(uint32_t w, uint32_t offset){
        if(m_littleEndian){
            w = reverseBytes32(w);
        }
        insertByteAt((w & 0xFF000000) >> 24, offset);
        insertByteAt((w & 0x00FF0000) >> 16, offset+1);
        insertByteAt((w & 0x0000FF00) >> 8, offset+2);
        insertByteAt((w & 0x000000FF), offset+3);
    }

    void Binary::insertByteAt(uint32_t b, uint32_t offset){
        uint8_t b8 = static_cast<uint8_t>(b & 0x000000FF);
        m_bin[offset] = b8;
    }

    void Binary::pushByte(uint32_t b){
        uint8_t b8 = static_cast<uint8_t>(b & 0x000000FF);
        m_bin.push_back(b8);
        m_offset++;
    }

    void Binary::pushHWord(uint32_t hw){
        if(m_littleEndian){
            hw = reverseBytes16(hw);
        }
        pushByte((hw & 0x0000FF00) >> 8);
        pushByte(hw & 0x000000FF);
    }

    void Binary::pushWord(uint32_t w){
        if(m_littleEndian){
            w = reverseBytes32(w);
        }
        pushByte((w & 0xFF000000) >> 24);
        pushByte((w & 0x00FF0000) >> 16);
        pushByte((w & 0x0000FF00) >> 8);
        pushByte((w & 0x000000FF));
    }

    uint32_t Binary::reverseBytes32(uint32_t word){
        uint32_t b1 = (word & 0x000000FF) << 24;
        uint32_t b2 = (word & 0x0000FF00) << 8;
        uint32_t b3 = (word & 0x00FF0000) >> 8;
        uint32_t b4 = (word & 0xFF000000) >> 24;
        return (b1 | b2 | b3 | b4);
    }

    uint32_t Binary::reverseBytes16(uint32_t hword){
        uint32_t b1 = (hword & 0x000000FF) << 8;
        uint32_t b2 = (hword & 0x0000FF00) >> 8;
        return (b1 | b2);
    }

    uint32_t Binary::getOffset(){
        return m_offset;
    }

    void Binary::align(){
        while(m_offset%4!=0){
            pushByte(0);
        }
    }


}

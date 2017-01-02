#pragma once
#include <sstream>
#include <iostream>
namespace HLR1{

class TokenStream{
private:
    std::istringstream m_stream;
    std::string m_nextToken;
    std::string m_errorMsg;
    uint32_t m_rowNum;
    uint32_t m_colNum;
    uint32_t m_oldRowColNum;
    uint32_t m_tokStartRow;
    uint32_t m_tokStartCol;
    void getNext();
    void consumeWhitespace();
    inline char getChar(){
        char ch;
        m_stream.get(ch);
        m_colNum++;
        if(ch=='\n'){
            m_oldRowColNum = m_colNum;
            m_colNum = 1;
            m_rowNum++;
        }
        return ch;
    }
    void putBack(char ch);
    std::string getString();
public:
    static const uint32_t s_NO_POSITION = 0;
    TokenStream(const std::string& in);
    inline explicit operator bool(){ return m_stream.fail() || m_nextToken.length()!=0; }
    inline bool fail(){ return m_stream.fail(); }
    inline std::string errorMsg(){ return m_errorMsg; }
    inline bool eof() { return m_stream.eof() && m_nextToken.length()==0; }
    inline uint32_t getCurrentRowNumber(){ return m_rowNum; }
    inline uint32_t getCurrentColNumber(){ return m_colNum; }
    inline uint32_t getTokenRowNumber(){ return m_tokStartRow; }
    inline uint32_t getTokenColNumber(){ return m_tokStartCol; }

    std::string getToken();
};


}

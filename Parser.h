#pragma once
#include <sstream>
#include "TokenStream.h"
namespace HLR1{

class Parser{
private:
    TokenStream m_stream;
    std::string m_lineComment;
    bool m_bad;
    std::string m_errorMsg;
    uint32_t m_currentTokenRow;
    uint32_t m_currentTokenCol;
    //void putback(size_t n);
    void appendError(const std::string& str);
    inline bool good(){ return m_stream && !m_bad; }
public:
    static const uint32_t BAD_NUMBER = ((uint32_t)-1);
    Parser(std::string str, std::string lineComment=";");
    std::string getStr();
    uint32_t getValue();
    uint32_t parseValue(const std::string& str);
    uint32_t getRegister();
    uint32_t parseRegister(const std::string& str);
    void skip();

    inline explicit operator bool(){ return good(); }
    inline std::string errorMsg(){ return m_errorMsg; }
    inline bool eof() { return m_stream.eof(); }
};
}


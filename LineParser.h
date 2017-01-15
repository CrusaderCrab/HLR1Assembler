#pragma once
#include <sstream>
namespace HLR1{
/** LineParser
    Used to read a single line of text and parse values (e.g. numbers,
    registers, opcodes) out of it. Can also handle line comments.
*/
class LineParser{
private:
    std::istringstream m_stream;
    bool m_bad;
    std::string m_errorMsg;
    void appendError(const std::string& str);
    static std::string removeComments(const std::string& line, const std::string& comment);
public:
    static const uint32_t s_BAD_NUMBER = ((uint32_t)-1);
    LineParser(std::string str, std::string lineComment=";");
    std::string getStr();
    std::string getFilePath();
    uint32_t getValue();
    uint32_t parseValue(const std::string& str);
    uint32_t getRegister();
    uint32_t parseRegister(const std::string& str);
    void skip();

    //inline explicit operator bool(){ return good(); }
    inline std::string errorMsg(){ return m_errorMsg; }
    inline bool eof() { return m_stream.eof(); }
    inline bool fail(){ return m_stream.fail() || m_bad; }
    inline bool bad(){ return m_stream.bad(); }
};
}


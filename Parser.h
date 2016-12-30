#pragma once
#include <sstream>
namespace HLR1{

    class Parser{
    private:
        std::istringstream m_stream;
        std::string m_lineComment;
        bool m_bad;
        std::string m_errorMsg;
        void putback(size_t n);
    public:
        Parser(std::string str, std::string lineComment=";");
        std::string getStr();
        uint32_t getValue();

        inline explicit operator bool(){ return m_stream && !m_bad; }
        inline std::string errorMsg(){ return m_errorMsg; }
        inline bool eof() { return m_stream.eof(); }
    };
}


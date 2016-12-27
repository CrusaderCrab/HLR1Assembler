#pragma once
#include <sstream>
namespace HLR1{

    class Parser{
    private:
        std::istringstream m_stream;
        std::string m_errorMsg;
    public:
        Parser(std::string str);
        std::string getStr();
        uint32_t getValue();

    };
}


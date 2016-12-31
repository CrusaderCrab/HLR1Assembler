#include <limits>
#include "Parser.h"
namespace HLR1{

/*class Parser{
    std::istringstream m_stream;
    std::string m_errorMsg;
    inline explicit operator bool(){ return m_stream; }
    inline std::string errorMsg(){ return m_errorMsg; }
};*/

/***    --ASSUMPTIONS--
        1) A empty string will never be returned by getStr(), unless we are at eof or an error occurred
***/

/***    --BUGS--
        1) If input ends with whitespace, m_stream will not be at EOF but if call any getXXX method will
           return empty string and set m_stream to bad state (as well as eof state)
            -Solution--> Take next string preemptively and unset fail bit on last read, but keep eof set
***/

Parser::Parser(std::string str, std::string lineComment)
: m_stream(str), m_lineComment(lineComment), m_bad(false){}

std::string Parser::getStr(){
    if(m_stream.eof()){
        return std::string();
    }else if(m_stream){
        std::string in;
        m_stream >> in;
        size_t lineComPos = in.find(m_lineComment);
        //if there is a line comment
        if(lineComPos != std::string::npos){
            m_stream.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
            if(lineComPos == 0){
                return getStr();
            }else{
                return in.substr(0, lineComPos);
            }
        }else{
            return in;
        }
    }else{ //stream in a bad state
        return std::string();
    }
}

uint32_t Parser::getValue(){
    if(m_stream.eof()){
        return 0;
    }
    if(m_stream){
        std::string str = getStr();
        if(!m_stream){
            appendError(" : Issue reading value/number");
            return 0;
        }
        return parseValue(str);
    }else{
        return 0;
    }
}

uint32_t Parser::parseValue(const std::string& str){
    std::istringstream nin(str);
    uint32_t res = 0;
    if(str.find("0x")!=std::string::npos){
        nin >> std::hex >> res;
    }else{
        nin >> res;
    }
    if(!nin){
        appendError("Could not parse as number: \""+str+"\"");
    }
    return res;
}

uint32_t Parser::getRegister(){
    if(m_stream.eof()){
        return 0;
    }
    if(m_stream){
        std::string str = getStr();
        if(!m_stream){
            appendError(" : Issue reading register");
            return 0;
        }
        return parseRegister(str);

    }else{
        return -1;
    }
}

uint32_t Parser::parseRegister(const std::string& str){
    if(str.length() <= 0 || (str[0] != 'r' && str[0] != 'R')){
        appendError(" : Expected a register. \""+str+"\"");
        return 0;
    }else{
        return parseValue(str.substr(1, str.length()));
    }
}

void Parser::putback(size_t n){
    for(size_t i = 0; i < n; i++){
        m_stream.unget();
    }
}


//size_t s_commentStartLength = 2;
//size_t s_commentEndLength = 2;
//std::string s_commentStart = "/*";
//std::string s_commentEnd = "*/";
/*
std::string Parser::getStr(){
    if(m_stream.eof()){
        return std::string();
    }
    if(m_stream){
        std::string in;
        m_stream >> in;
        //check if starts with/contains a comment
        size_t commentPos = in.find(s_commentStart);
        //starts with a comment started
        if(commentPos != std::string::npos && commentPos == 0){
            in = in.substr(s_commentStart.length()); //remove comment starter
            if(in.length() == 0){
                if(!m_stream){
                    m_errorMsg = m_errorMsg.append(" : Something went wrong reading a comment");
                    return m_errorMsg;
                }
                m_stream >> in;
            }
            //eat up comment then get next word following it
            while(true){
                commentPos = in.find(s_commentEnd);
                //is just a comment end
                if(commentPos != std::string::npos && commentPos == 0 && in.length()==s_commentEnd.length()){
                    return getStr();
                //starts with a comment end
                }else if(commentPos != std::string::npos && commentPos == 0){
                    in = in.substr(s_commentEnd.length());
                    if(in.length()!= 0){
                        putback(in.length());
                    }
                    return getStr();
                //has a comment end somewhere in it
                }else if(commentPos != std::string::npos){
                    //handle if word after the comment end
                    if(in.length() > commentPos+s_commentEnd.length()){
                        in = in.substr(commentPos+s_commentEnd.length());
                        putback(in.length());
                    }
                    return getStr();
                }
                //haven't found the end comment yet
                if(!m_stream){
                    m_errorMsg = m_errorMsg.append(" : Something went wrong reading a comment");
                    return m_errorMsg;
                }
                m_stream >> in;
            }
        //some word appended with a comment started
        }else if(commentPos != std::string::npos){
            std::string word = in.substr(0, commentPos);
            std::string comment = in.substr(commentPos);
            putback(comment.length());
            return word;
        //No comment
        }else{
            return in;
        }
    }else{
        return m_errorMsg;
    }
}*/
}

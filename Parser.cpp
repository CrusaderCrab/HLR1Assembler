#include "Parser.h"
namespace HLR1{

    /*class Parser{
        std::istringstream m_stream;
        std::string m_errorMsg;
        inline explicit operator bool(){ return m_stream; }
        inline std::string errorMsg(){ return m_errorMsg; }
    };*/

    Parser::Parser(std::string str)
    : m_stream(str){}

    std::string Parser::getStr(){
        if(m_stream.eof()){
            return std::string();
        }
        if(m_stream){
            std::string in;
            m_stream >> in;
            //check if starts with/contains a comment
            size_t commentPos = in.find("/*");
            //starts with a comment started
            if(commentPos != std::string::npos && commentPos == 0){
                in = in.substr(2); //remove comment starter
                if(in.length() == 0){
                    if(!m_stream){
                        m_errorMsg = "Something went wrong reading a comment.";
                        return m_errorMsg;
                    }
                    m_stream >> in;
                }
                //eat up comment then get next word following it
                while(true){
                    commentPos = in.find("*/");
                    //is just a comment end
                    if(commentPos != std::string::npos && commentPos == 0 && in.length()==2){
                        return getStr();
                    //starts with a comment end
                    }else if(commentPos != std::string::npos && commentPos == 0){
                        in = in.substr(2);
                        if(in.length()!= 0){
                            putback(in.length());
                        }
                        return getStr();
                    //has a comment end somewhere in it
                    }else if(commentPos != std::string::npos){
                        //handle if word after the comment end
                        if(in.length() > commentPos+2){
                            in = in.substr(commentPos+2);
                            putback(in.length());
                        }
                        return getStr();
                    }
                    //haven't found the end comment yet
                    if(!m_stream){
                        m_errorMsg = "Something went wrong reading a comment.";
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
    }

    uint32_t Parser::getValue(){
        return 0;
    }

    void Parser::putback(size_t n){
        for(int i = 0; i < n; i++){
            m_stream.unget();
        }
    }


}

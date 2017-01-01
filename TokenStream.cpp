#include "TokenStream.h"
#include <iostream>
namespace HLR1{

TokenStream::TokenStream(const std::string& in)
: m_stream(in), m_bad(false), m_rowNum(1), m_colNum(1),
  m_oldRowColNum(1), m_tokStartRow(1), m_tokStartCol(1) {
    getNext();
}

std::string TokenStream::getString(){
    std::string token;
    if(!eof() && remain()){
        char ch = getChar(); //std::cout<<"GetString1: "<<ch<<" Col: "<<m_colNum<<std::endl;
        while(remain() && (ch!='\n' && ch!='\t' && ch != ' ' && ch!='\r')){
            token.push_back(ch);
            ch = getChar();  //std::cout<<"GetString2: "<<ch<<" Col: "<<m_colNum<<std::endl;
        }
        if(remain()){
            putBack(ch);  //std::cout<<"GetString3: "<<ch<<" Col: "<<m_colNum<<std::endl;
        }
    }
    return token;
}

void TokenStream::getNext(){
    //std::cout<<"GetNext1: "<<m_colNum<<std::endl;
    consumeWhitespace();
    //std::cout<<"GetNext2: "<<m_colNum<<std::endl;
    if(!remain()){
        m_nextToken = std::string();
        m_bad = true;
        m_tokStartRow = 1;
        m_tokStartCol = 1;
    }else{
        m_tokStartRow = m_rowNum;
        m_tokStartCol = m_colNum;
        m_nextToken = getString();
        //std::cout<<"GetNext3: "<<m_colNum<<std::endl;
        consumeWhitespace();
        //std::cout<<"GetNext4: "<<m_colNum<<std::endl;
    }
}

void TokenStream::consumeWhitespace(){
    if(remain()){
        char ch = getChar(); //std::cout<<"White1: "<<ch<<" Col: "<<m_colNum<<std::endl;
        while(remain() && (ch=='\n' || ch=='\t' || ch == ' ' || ch=='\r')){
            ch = getChar(); //std::cout<<"White2: "<<ch<<" Col: "<<m_colNum<<std::endl;
        }
        if(remain()){
            putBack(ch); //std::cout<<"White3: "<<ch<<" Col: "<<m_colNum<<std::endl;
        }
    }
}
void TokenStream::skipTilNewLine(){
    if(remain()){
        char ch = getChar();
        while(remain() && ch!='\n'){
            ch = getChar();
        }
        if(remain()){
            getNext();
        }
    }
}
std::string TokenStream::getToken(){
    std::string n = m_nextToken;
    getNext();
    return n;
}

void TokenStream::putBack(char ch){
    m_stream.putback(ch);
    m_colNum--;
    //std::cout<<"PutBack: \""<<ch<<"\" Col: "<<m_colNum<<std::endl;
    if(ch=='\n'){
        m_colNum = m_oldRowColNum;
        m_oldRowColNum = 1;
        m_rowNum--;
    }
}

}

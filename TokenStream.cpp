#include "TokenStream.h"
#include <iostream>
namespace HLR1{

TokenStream::TokenStream(const std::string& in)
: m_stream(in), m_rowNum(1), m_colNum(1),
  m_oldRowColNum(1), m_tokStartRow(1), m_tokStartCol(1) {
    getNext();
}

std::string TokenStream::getString(){
    std::string token;
    if(!(eof() || m_stream.fail())){
        char ch = getChar();
        while(!(eof() || m_stream.fail()) && (ch!='\n' && ch!='\t' && ch != ' ' && ch!='\r')){
            token.push_back(ch);
            ch = getChar();
        }
        if(!(eof() || m_stream.fail())){
            putBack(ch);
        }
    }
    return token;
}

void TokenStream::getNext(){
    consumeWhitespace();
    if((eof() || m_stream.fail())){
        m_nextToken = std::string();
        m_tokStartRow = s_NO_POSITION;
        m_tokStartCol = s_NO_POSITION;
    }else{
        m_tokStartRow = m_rowNum;
        m_tokStartCol = m_colNum;
        m_nextToken = getString();
        consumeWhitespace();
    }
}

void TokenStream::consumeWhitespace(){
    if(!(eof() || m_stream.fail())){
        char ch = getChar();
        while(!(eof() || m_stream.fail()) && (ch=='\n' || ch=='\t' || ch == ' ' || ch=='\r')){
            ch = getChar();
        }
        if(!(eof() || m_stream.fail())){
            putBack(ch);
        }
    }
}
/*void TokenStream::skipTilNewLine(){
    if(remain()){
        char ch = getChar();
        while(remain() && ch!='\n'){
            ch = getChar();
        }
        if(remain()){
            getNext();
        }
    }
}*/
std::string TokenStream::getToken(){
    std::string n = m_nextToken;
    getNext();
    return n;
}

void TokenStream::putBack(char ch){
    m_stream.putback(ch);
    m_colNum--;
    if(ch=='\n'){
        m_colNum = m_oldRowColNum;
        m_oldRowColNum = 1;
        m_rowNum--;
    }
}

}

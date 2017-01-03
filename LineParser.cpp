#include <limits>
#include <iostream>
#include "LineParser.h"
namespace HLR1{

/***    --ASSUMPTIONS--
        1) A empty string will never be returned by getStr(), unless we have used up the entire input string
***/

/***    --BUGS--
        1) Allows many types of incorrect register definitions.
        2) Poor error messages
        3) Unfound Filepath bugs nearly certainly
***/

LineParser::LineParser(std::string str, std::string lineComment)
: m_stream(removeComments(str, lineComment)), m_bad(false){}

std::string LineParser::removeComments(const std::string& line, const std::string& comment){
    size_t cp = line.find(comment);
    if(cp!=std::string::npos){
        return line.substr(0, cp);
    }else{
        return line;
    }
}

std::string LineParser::getStr(){
    if(!fail()){
        std::string in;
        m_stream >> in;
        if(bad()){
            appendError(" : Something went wrong with the stream.");
        }
        return in;
    }else{ //stream in a bad/eof state
        return std::string();
    }
}

std::string LineParser::getFilePath(){
    if(!fail()){
        std::string firstSeg = getStr();
        size_t quotePos = firstSeg.find('\"');
        if(quotePos==std::string::npos){
            return firstSeg;
        }else if(quotePos==0){ //first position
            if(firstSeg.length() == 1 || firstSeg[firstSeg.length() - 1] != '\"'){
                std::string nextSection = getStr();
                while( !fail() && nextSection[nextSection.length() - 1] != '\"'){
                    firstSeg.append(nextSection);
                    nextSection = getStr();
                }
                if(nextSection[nextSection.length() - 1] != '\"'){
                    appendError(" : Unable to read file Path. Couldn't find close quote.");
                    return std::string();
                }
                firstSeg.append(nextSection);
            }
            return firstSeg.substr(1, firstSeg.length()-2);
        }else{
            appendError(" : Unable to read file Path. Double quote embedded in filepath.");
            return std::string();
        }
    }
    return std::string();
}

uint32_t LineParser::getValue(){
    if(m_stream){
        std::string str = getStr();
        return parseValue(str);
    }else{ //stream in a bad/eof state
        return s_BAD_NUMBER;
    }
}

uint32_t LineParser::parseValue(const std::string& str){
    std::istringstream nin(str);
    uint32_t res = s_BAD_NUMBER;
    if(str.find("0x")!=std::string::npos || str.find("0X")!=std::string::npos){
        nin >> std::hex >> res;
    }else{
        nin >> res;
    }
    if(!nin || !nin.eof()){
        appendError("Could not parse as number: \""+str+"\"");
        res = s_BAD_NUMBER;
    }
    return res;
}

uint32_t LineParser::getRegister(){
    if(m_stream){
        std::string str = getStr();
        return parseRegister(str);

    }else{
        return s_BAD_NUMBER;
    }
}

uint32_t LineParser::parseRegister(const std::string& str){
    if(str.length() <= 0 || (str[0] != 'r' && str[0] != 'R')){
        appendError(" : Expected a register. \""+str+"\"");
        return s_BAD_NUMBER;
    }else{
        return parseValue(str.substr(1, str.length()));
    }
}

void LineParser::appendError(const std::string& str){
    m_bad = true;
    std::ostringstream ost;
    ost << str;
    m_errorMsg.append(ost.str());
}

void LineParser::skip(){
    if(!fail()){
        std::string s;
        m_stream >> s;
    }
}

}

#include <iostream>
#include <fstream>
#include <sstream>
#include "Codes.h"
#include "State.h"
#include "LineParser.h"

namespace HLR1{

    int ribble;
    /*
    std::string m_inputPath;
    std::string m_outputPath;
    std::string m_configPath;
    std::string m_opcodePath;
    std::vector<uint32_t> m_binary;
    std::vector<uint32_t> m_opcodes;
    std::vector<uint32_t> m_condCodes;
    bool m_littleEndian;
    uint32_t m_trapOVRegister;
    uint32_t m_trapUNRegister;
    uint32_t m_codeStartAddr;
    */

    /***
        BUGS:
        1) Allows arguments to pass in empty file path like: " " or "\t" where \t is the literal tab character
           e.g. > HLR1_Assembler.exe -i " "
           Sets the input path to " "
    ***/

State::State(size_t argc, char* argv[])
: m_configPath("./HLR1_Default_Config.txt"), m_littleEndian(false),
  m_trapOVRegister(2), m_trapUNRegister(2), m_codeStartAddr(0),
  m_bad(false){
    size_t i = 1;
    while(i < argc){
        std::string flag(argv[i]);
        i++;
        if(flag == "-little"){
            m_littleEndian = true;
        }else if(i < argc){
            std::string value(argv[i]);
            i++;
            if(flag == "-i" && !m_bad){
                m_inputPath = value;
            }else if(flag == "-o" && !m_bad){
                m_outputPath = value;
            }else if(flag == "-oc" && !m_bad){
                m_opcodePath = value;
            }else if(flag == "-c" && !m_bad){
                m_configPath = value;
            }else if(flag == "-m"){
                LineParser np(value);
                uint32_t startAddr = np.getValue();
                if(np.bad() || startAddr == LineParser::s_BAD_NUMBER){
                    std::ostringstream ess;
                    ess<<"Could not parse "<<value<<" as a number for "<<flag;
                    setError(ess.str());
                }
                m_codeStartAddr = startAddr;
            }else{
                setError(flag.append(" is not a valid argument."));
            }
        }else{
            setError(std::string(flag.append(" passed but no value given to use with")));
        }
    }//end while for reading arguments
    if(!m_bad){
        readConfig();
        if(!m_bad){
            readOpcodesAndCondCodes();
        }
    }
    /*std::cout<<"in: "<<m_inputPath<<std::endl;
    std::cout<<"out: "<<m_outputPath<<std::endl;
    std::cout<<"con: "<<m_configPath<<std::endl;
    std::cout<<"Opc: "<<m_opcodePath<<std::endl;
    std::cout<<"Lit: "<<m_littleEndian<<std::endl;
    std::cout<<"Cstart: "<<m_codeStartAddr<<std::endl;
    std::cout<<"XopVec: "<<m_opcodes.size()<<std::endl;
    std::cout<<"DcondVec: "<<m_condCodes.size()<<std::endl;
    for(uint32_t i : m_opcodes){
        std::cout<<" "<<i;
    }
    std::cout<<std::endl;
    for(uint32_t i : m_condCodes){
        std::cout<<" "<<i;
    }*/

}

void State::readPath(std::string& dest, const std::string& pathName, std::ifstream& ss,
                     const std::string& comment, const std::string& path){
    std::string line;
    bool goodSS = true;
    bool goodLP = true;
    std::string gotPath = "";
    do{
        goodSS = std::getline(ss, line);
        LineParser lp(line, comment);
        gotPath = lp.getFilePath();
        goodLP = !lp.fail();
    }while(goodSS && !goodLP);
    if(goodSS && goodLP){
        dest = gotPath;
        if(!goodLP){
            std::ostringstream ost;
            ost <<"Couldn't parse: "<<line<<" Failed to parse "<<pathName<<" given in file: "<<path;
            setError(ost.str());
        }
    }else{
        std::ostringstream ost;
        ost <<"Failed to get line of file containing "<<pathName<<". file: "<<path;
        setError(ost.str());
    }
}

uint32_t State::readIntFromConfig(const std::string& intName, std::ifstream& ss, const std::string& comment){
    std::string line;
    bool goodSS = true;
    bool goodLP = true;
    uint32_t gotValue = 0;
    do{
        goodSS = std::getline(ss, line);
        LineParser lp(line, comment);
        gotValue = lp.getValue();
        goodLP = !lp.fail();
    }while(goodSS && !goodLP);
    if(!goodSS){
        std::ostringstream ost;
        ost <<"Failed to get line of file containing the "<<intName<<". Config File: "<<m_configPath;
        setError(ost.str());
    }else if(!goodLP){
        std::ostringstream ost;
        ost <<"Couldn't parse \""<<line<<"\" as the "<<intName<<". Used Config File: "<<m_configPath;
        setError(ost.str());
    }
    return gotValue;
}

void State::readConfig(){
    std::ifstream ss;
    openFileStream(ss, m_configPath,  "Config Path");
    if(!m_bad){
        std::string line, comment="#";
        //get input path
        if(!ss.fail() && !m_bad){
            readPath(line, "input file path", ss, comment, m_configPath);
            if(m_inputPath.empty()){
                m_inputPath = line;
            }
        }
        //get output path
        if(!ss.fail() && !m_bad){
            readPath(line, "output file path", ss, comment, m_configPath);
            if(m_outputPath.empty()){
                m_outputPath = line;
            }
        }
        //get opcode path
        if(!ss.fail() && !m_bad && m_opcodePath.empty()){
            readPath(line, "opcode file path", ss, comment, m_configPath);
            if(m_opcodePath.empty()){
                m_opcodePath = line;
            }
        }
        //get if little endian
        if(!ss.fail() && !m_bad){
            uint32_t dest = readIntFromConfig("little endian flag", ss, comment);
            if(dest != 0 && dest != 1){
                std::ostringstream ost;
                ost << "Little Endian flag must be 0/1. Parsed as: "<<dest<<" from file: "<<m_configPath;
                setError(ost.str());
            }
            m_littleEndian = m_littleEndian | static_cast<bool>(dest);
        }
        //get code start address
        if(!ss.fail() && !m_bad){
            uint32_t dest = readIntFromConfig("code start address", ss, comment);
            if(m_codeStartAddr == 0){
                m_codeStartAddr = dest;
            }
        }
    }
    ss.close();
}

void State::readOpcodesAndCondCodes(){
    std::ifstream ss;
    openFileStream(ss, m_opcodePath, "OpCode Path");
    if(!m_bad){
        std::string line, comment="#";
        //read opcodes
        for(OpCode code = OpCode::FIRST; code < OpCode::END; ++code){
            std::string longBits;
            readPath(longBits, "some opcode", ss, comment, m_opcodePath);
            if(m_bad){
                return;
            }
            uint32_t bits = stringToBits(longBits);
            if(m_bad){
                std::ostringstream ost;
                ost << "\"" << longBits << "\" is not a valid binary value. OpCode File: "<< m_opcodePath;
                setError(ost.str());
            }else if(bits > 127){
                std::ostringstream ost;
                ost << "\"" << longBits << "\" is more than 7 bits longs, so it can not be an OpCode. OpCode File: "<< m_opcodePath;
                setError(ost.str());
            }
            m_opcodes.push_back(bits);
        }
        //read CondCodes
        for(CondCode code = CondCode::FIRST; code < CondCode::END; ++code){
            std::string longBits;
            readPath(longBits, "some condcode", ss, comment, m_opcodePath);
            if(m_bad){
                return;
            }
            uint32_t bits = stringToBits(longBits);
            m_condCodes.push_back(bits);
            if(m_bad){
                std::ostringstream ost;
                ost << "\"" << longBits << "\" is not a valid binary value. CondCode File: "<< m_opcodePath;
                setError(ost.str());
            }else if(bits > 32){
                std::ostringstream ost;
                ost << "\"" << longBits << "\" is more than 5 bits longs, so it can not be an CondCode. CondCode File: "<< m_opcodePath;
                setError(ost.str());
            }
        }
    }
    ss.close();
}

void State::openFileStream(std::ifstream& ss, const std::string& path, const std::string& pathName){
    ss.open(path.c_str());
    if(!ss.is_open()){
        std::ostringstream ost;
        ost <<"Couldn't open path to "<<pathName<<" Given Path: "<<path;
        setError(ost.str());
        return;
    }
    if(ss.bad()){
        setError(std::string("Bad bit set when opening file: ").append(path));
        return;
    }
    if(ss.fail()){
        setError(std::string("Fail bit set when opening file: ").append(path));
        return;
    }
}

uint32_t State::getOpCode(OpCode code) const{
    size_t ic = static_cast<size_t>(code);
    return m_opcodes[ic];
}
uint32_t State::getCondCode(CondCode cond) const{
    size_t ic = static_cast<size_t>(cond);
    return m_condCodes[ic];
}

uint32_t State::stringToBits(const std::string& str){
    uint32_t bits = 0;
    for(char ch : str){
        if(ch=='1'){
            bits += 1;
        }else if(ch != '0'){
            m_bad = true;
        }
        bits <<= 1;
    }
    bits >>= 1; //undo last shift right
    return bits;
}

void State::setError(std::string s){
    perror(s.c_str());
    m_bad = true;
}


}

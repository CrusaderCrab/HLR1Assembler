#include "State.h"
#include "LineParser.h"
#include "OpCodes.h"
#include "CondCodes.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace HLR1{

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

State::State(size_t argc, char* argv[])
: m_configPath("./HLR1_Default_Config.txt"), m_littleEndian(false),
  m_trapOVRegister(2), m_trapUNRegister(2), m_codeStartAddr(0),
  m_bad(false){
    bool noErrors = true;
    size_t i = 1;
    while(i < argc){
        std::string flag(argv[i]);
        i++;
        if(flag == "-little"){
            m_littleEndian = true;
        }else if(i < argc){
            std::string value(argv[i]);
            i++;
            LineParser fp(value);
            std::string path = fp.getFilePath();
            if(flag == "-i" || flag == "-o" || flag == "-oc" || flag == "-c"){
                    std::ostringstream ess;
                    ess<<"Could not parse "<<value<<" as a filepath for "<<flag;
                    setError(ess.str());
                    noErrors = false;
            }
            if(flag == "-i" && !fp.bad() && noErrors){
                m_inputPath = path;
            }else if(flag == "-o" && !fp.bad() && noErrors){
                m_outputPath = path;
            }else if(flag == "-oc" && !fp.bad() && noErrors){
                m_opcodePath = path;
            }else if(flag == "-c" && !fp.bad() && noErrors){
                m_configPath = path;
            }else if(flag == "m"){
                LineParser np(value);
                uint32_t startAddr = np.getValue();
                if(np.bad() || startAddr == LineParser::s_BAD_NUMBER){
                    std::ostringstream ess;
                    ess<<"Could not parse "<<value<<" as a number for "<<flag;
                    setError(ess.str());
                    noErrors = false;
                }else{
                    m_codeStartAddr = startAddr;
                }
            }
        }else{
            setError(std::string(flag.append(" passed but no value given to use with")));
            noErrors = false;
        }
    }//end while for reading arguments
    if(noErrors){
        readConfig();
        if(!m_bad){
            readOpcodesAndCondCodes();
        }
    }
    std::cout<<"i: "<<m_inputPath<<std::endl;
    std::cout<<"o: "<<m_outputPath<<std::endl;
    std::cout<<"c: "<<m_configPath<<std::endl;
    std::cout<<"O: "<<m_opcodePath<<std::endl;
    std::cout<<"L: "<<m_littleEndian<<std::endl;
    std::cout<<"C: "<<m_codeStartAddr<<std::endl;
    std::cout<<"X: "<<m_opcodes.size()<<std::endl;
    std::cout<<"D: "<<m_condCodes.size()<<std::endl;
    for(uint32_t i : m_opcodes){
        std::cout<<" "<<i;
    }
    std::cout<<std::endl;
    for(uint32_t i : m_condCodes){
        std::cout<<" "<<i;
    }

}

void State::readPathFromConfig(std::string& dest, const std::string& pathName, std::ifstream& ss, const std::string& comment){
    std::string line;
    bool goodSS = true;
    bool goodLP = true;
    std::string gotPath = "";
    do{
        goodSS = std::getline(ss, line);
        LineParser lp(line, comment);
        gotPath = lp.getFilePath();
        goodLP = !lp.bad();
    }while(goodSS && gotPath.empty());
    if(goodSS && !gotPath.empty()){
        if(dest.empty()){ //only do if no flag has already set it
            dest = gotPath;
            if(!goodLP){
                std::ostringstream ost;
                ost <<"Couldn't parse: "<<line<<" Failed to parse "<<pathName<<" file path given in Config File: "<<m_configPath;
                setError(ost.str());
            }
        }
    }else{
        std::ostringstream ost;
        ost <<"Failed to get line of file containing "<<pathName<<" file path. Config File: "<<m_configPath;
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
        goodLP = !lp.bad();
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
    openFileStream(ss, m_configPath);
    if(!m_bad){
        std::string line, comment="#";
        std::getline(ss, line);
        /**TODO: read comment symbol wanted, for now just ignore**/
        //get input path
        if(!ss.fail() && !m_bad){
            readPathFromConfig(m_inputPath, "input", ss, comment);
        }
        //get output path
        if(!ss.fail() && !m_bad){
            readPathFromConfig(m_outputPath, "output", ss, comment);
        }
        //get opcode path
        if(!ss.fail() && !m_bad){
            readPathFromConfig(m_opcodePath, "opcode", ss, comment);
        }
        //get if little endian
        if(!ss.fail() && !m_bad){
            uint32_t dest = readIntFromConfig("little endian flag", ss, comment);
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
    std::cout<<"End config: "<<m_bad<<std::endl;
    ss.close();
}

void State::readOpcodesAndCondCodes(){
    std::ifstream ss;
    openFileStream(ss, m_opcodePath);
    std::cout<<"Opened opcode: "<<m_bad<<std::endl;
    if(!m_bad){
        std::string line, comment="#";
        std::getline(ss, line);
        /**TODO: read comment symbol wanted, for now just ignore**/
        //read opcodes
        for(OpCode code = OpCode::FIRST; code < OpCode::END; ++code){
            std::string longBits;
            readPathFromConfig(longBits, "some opcode", ss, comment);
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
            readPathFromConfig(longBits, "some condcode", ss, comment);
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

void State::openFileStream(std::ifstream& ss, const std::string& path){
    ss.open(path.c_str());
    if(!ss.is_open()){
        setError(std::string("Couldn't open file: ").append(path));
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

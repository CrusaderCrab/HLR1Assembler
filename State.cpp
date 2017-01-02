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
  m_trapOVRegister(2), m_trapUNRegister(2){
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
            setError(std::string(flag.append(" passed but no value given to use with");
            noErrors = false;
        }
    }//end while for reading arguments
    if(noErrors){
        readConfig();
    }
}

void State::readConfig(){
    std::ifstream ss;
    openFileStream(ss, m_configPath);
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

void State::setError(std::string s){
    perror(s.c_str());
    m_bad = true;
}


}

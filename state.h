#pragma once
#include <stdint.h>
#include <string>
namespace HLR1{

    class State{
    private:
        std::string m_inputPath;
        std::string m_outputPath;
        std::string m_configPath;
        std::string m_opcodePath;
        std::arraylist<uint32_t> m_binary;
        std::arraylist<uint32_t> m_opcodes;
        std::arraylist<uint32_t> m_condCodes;
        bool m_littleEndian;
        uint32_t m_trapOVRegister;
        uint32_t m_trapUNRegister;
        uint32_t m_codeStartAddr;
    public:
        State(int argc, char* argv[]);
        uint32_t getWord(uint32_t addr);
        void putWord(uint32_t addr, uint32_t v);
        void putHalfWord(uint32_t addr, uint32_t v);
        uint32_t getOpcode(std::string name);
        uint32_t getCondCode(std::string cond);

        inline std::string inputPath(){  return m_inputPath; }
        inline std::string outputPath(){ return m_outputPath; }
        inline std::string configPath(){ return m_configPath; }
        inline std::string opcodePath(){ return m_opcodePath; }
        inline bool littleEndian(){ return m_littleEndian; }
        inline uint32_t trapOVRegister(){ return m_trapOVRegister; }
        inline uint32_t trapUNRegister(){ return m_trapUNRegister; }
        inline uint32_t codeStartAddr(){  return m_codeStartAddr; }
    };
}


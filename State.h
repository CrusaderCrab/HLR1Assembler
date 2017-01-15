#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include "Codes.h"

namespace HLR1{
class State{
private:
#ifdef CATCH_TESTING
public:
#endif
    std::string m_inputPath;
    std::string m_outputPath;
    std::string m_configPath;
    std::string m_opcodePath;
    std::vector<uint32_t> m_opcodes;
    std::vector<uint32_t> m_condCodes;
    bool m_littleEndian;
    uint32_t m_trapOVRegister;
    uint32_t m_trapUNRegister;
    uint32_t m_codeStartAddr;
    bool m_bad;
    std::string m_errorMsg;

    void readConfig();
    void readOpcodesAndCondCodes();
    void openFileStream(std::ifstream& ss, const std::string& path, const std::string& pathName);
    void setError(std::string s);
    void readPath(std::string& dest, const std::string& pathName, std::ifstream& ss,
                  const std::string& comment, const std::string& path);
    uint32_t readIntFromConfig(const std::string& intName, std::ifstream& ss, const std::string& comment);
    uint32_t stringToBits(const std::string& longbits);
public:
    State(size_t argc=0, char* argv[]=0);
    uint32_t getWord(uint32_t addr);
    void putWord(uint32_t addr, uint32_t v);
    void putHalfWord(uint32_t addr, uint32_t v);
    uint32_t getOpCode(OpCode code) const;
    uint32_t getCondCode(CondCode cond) const;

    inline std::string inputPath() const {  return m_inputPath; }
    inline std::string outputPath() const { return m_outputPath; }
    inline std::string configPath() const { return m_configPath; }
    inline std::string opcodePath() const { return m_opcodePath; }
    inline bool littleEndian() const { return m_littleEndian; }
    inline uint32_t trapOVRegister() const { return m_trapOVRegister; }
    inline uint32_t trapUNRegister() const { return m_trapUNRegister; }
    inline uint32_t codeStartAddr() const {  return m_codeStartAddr; }
};
}



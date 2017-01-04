#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Codes.h"
namespace HLR1{
struct LabelUsage{
    OpCode ins;
    uint32_t addr;
};
struct Label{
    uint32_t addr;
    bool valid;
    std::vector<LabelUsage> toPatch;
};
class SymbolTable{
    bool m_bad;
    std::string m_errorMsg;
    std::unordered_map<std::string, Label> m_labels;
    void addLabel(const std::string& l, uint32_t a, bool v);
    void addLabel(const std::string& label);
    void setError(const std::string& s);
public:
    SymbolTable();
    void addLabel(const std::string& label, uint32_t addr);
    void setLabelAddr(const std::string& label, uint32_t addr);
    Label getLabel(const std::string& label);
    void addLabelUsage(const std::string& label, OpCode ins, uint32_t addr);
    void removeLabelUsages(const std::string& label);
    void setAddress(const std::string& label, uint32_t addr);
    inline bool fail(){ return m_bad; }
    inline void unsetFail(){
        m_bad = false;
        m_errorMsg = std::string();
    }
    inline const std::string& getErrorMsg(){
        return m_errorMsg;
    }

};
}

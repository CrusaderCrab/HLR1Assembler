#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Codes.h"
/** SymbolTable (15/01/2017)
Keeps track of the labels used in the code being assembled.
Tracks the location of every encountered label and the instructions
that need to be backpatched later.
*/
namespace HLR1{
struct LabelUsage{ //an instruction that needs to be back-patched later
    OpCode ins;
    uint32_t addr;
};
struct Label{ //all table information on a given label
    uint32_t addr; //it's location in the code
    bool valid; //Do we know the address of the label
    std::vector<LabelUsage> toPatch; //instructions using this label that must be updated
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

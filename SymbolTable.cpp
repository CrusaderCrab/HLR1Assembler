#include <sstream>
#include <iostream>
#include "SymbolTable.h"

namespace HLR1{

SymbolTable::SymbolTable()
: m_bad(false) {}

/** SymbolTable::getLabel(const std::string& l)
    returns the label info about the Label 'l'
    Sets the bad bit if the label 'l' has not been already seen,
    either as a label or used in an instruction
    l - Label Name
*/
Label SymbolTable::getLabel(const std::string& l){
    if(m_labels.find(l) != m_labels.end()){
        return m_labels[l];
    }else{
        std::ostringstream oss;
        oss << "Couldn't find label: "<<l;
        setError(oss.str());
        Label la;
        return la;
    }
}
/** SymbolTable::addLabel(const std::string& l, uint32_t a, bool v)
    Adds a label 'l' with address 'a'. Use 'v' to denote if 'a' is
    a valid address or not.
    Sets the bad bit if label 'l' already exists in the table.
    l - Label Name
    a - location address of the label 'l'
    v - Does 'l' have a valid address. i.e. should 'a' be ignored
*/
void SymbolTable::addLabel(const std::string& l, uint32_t a, bool v){
    std::unordered_map<std::string, Label>::const_iterator it = m_labels.find(l);
    if(it == m_labels.end()){
        Label la;
        la.addr = a;
        la.valid = v;
        m_labels[l] = la;
    }else{
        std::ostringstream oss;
        oss << "The label: "<<l<<" has already been defined.";
        setError(oss.str());
    }
}
/** SymbolTable::addLabelUsage(const std::string& label, OpCode ins, uint32_t addr)
    Adds a label usage of the label 'l' at address 'addr'. If no label 'l' exists
    then it is added to the table with no valid location address.
    Can not set the bad bit
    label - label name
    ins - Type of instruction referencing 'label'
    addr - Address of instruction referencing 'label'
*/
void SymbolTable::addLabelUsage(const std::string& label, OpCode ins, uint32_t addr){
    Label la = getLabel(label);
    if(m_bad){
        unsetFail();
        addLabel(label);
        la = getLabel(label);
    }
    LabelUsage u;
    u.ins = ins;
    u.addr = addr;
    la.toPatch.push_back(u);
    m_labels[label] = la;
}
/** SymbolTable::removeLabelUsages(const std::string& label)
    removes all label usages of label 'label' from the tabel.
    Sets the bad bit if 'label' is not in the table already.
    label - Label name
*/
void SymbolTable::removeLabelUsages(const std::string& label){
    Label la = getLabel(label);
    if(!m_bad){
        la.toPatch.clear();
        m_labels[label] = la;
    }
}
/** SymbolTable::setAddress(const std::string& label, uint32_t addr)
    Sets the address of a label 'label' to 'addr'.
    Sets the bad bit if 'label' does not already exist in the table,
    or if 'label' does exist and already has a valid address.
    label - label name
    addr - The address 'label' will be located at.
*/
void SymbolTable::setAddress(const std::string& label, uint32_t addr){
    Label la = getLabel(label);
    if(!m_bad){
        if(!la.valid){
            la.addr = addr;
            la.valid = true;
            m_labels[label] = la;
        }else{
            std::ostringstream oss;
            oss << "The label: "<<label<<" has already been defined.";
            setError(oss.str());
        }
    }
}

void SymbolTable::addLabel(const std::string& label, uint32_t addr){
    addLabel(label, addr, true);
}

void SymbolTable::addLabel(const std::string& label){
    addLabel(label, 0, false);
}

void SymbolTable::setError(const std::string& s){
    m_bad = true;
    m_errorMsg = s;
}

}

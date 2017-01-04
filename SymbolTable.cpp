#include <sstream>
#include <iostream>
#include "SymbolTable.h"

namespace HLR1{

    SymbolTable::SymbolTable()
    : m_bad(false) {}

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

    void SymbolTable::removeLabelUsages(const std::string& label){
        Label la = getLabel(label);
        if(!m_bad){
            la.toPatch.clear();
            m_labels[label] = la;
        }
    }

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

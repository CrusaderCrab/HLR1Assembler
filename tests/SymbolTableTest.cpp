#include <iostream>
#include "catch.hpp"
#include "../SymbolTable.h"
#define rr REQUIRE
#define tt TEST_CASE
#define ss SECTION

namespace HLR1{


tt(" Smackering of correct (and unfailing) usage of Label Symbol Tables.", "[SymbolTable]"){
    SymbolTable st;
    //valid on construction
    rr(!st.fail());
    //add a label that has not been added
    st.addLabel("Yes1", 1234);
    rr(!st.fail());
    //get a label that was added only with no patches
    Label l1 = st.getLabel("Yes1");
    rr(!st.fail());
    rr(l1.addr == 1234);
    rr(l1.valid);
    rr(l1.toPatch.size() == 0);
    //add a label with no addr
    st.addLabelUsage("Yes2", OpCode::JMP, 2345);
    rr(!st.fail());
    Label l2 = st.getLabel("Yes2");
    st.getLabel("Yes2");
    rr(!l2.valid);
    rr(l2.toPatch.size() == 1);
    rr(l2.toPatch[0].ins == OpCode::JMP);
    rr(l2.toPatch[0].addr == 2345);
    //add a second usage to Yes2
    st.addLabelUsage("Yes2", OpCode::CALL, 3456);
    rr(!st.fail());
    Label l5 = st.getLabel("Yes2");
    rr(!l5.valid);
    rr(l5.toPatch.size() == 2);
    rr(l5.toPatch[0].ins == OpCode::JMP);
    rr(l5.toPatch[0].addr == 2345);
    rr(l5.toPatch[1].ins == OpCode::CALL);
    rr(l5.toPatch[1].addr == 3456);
    //set addr of unset label
    st.setAddress("Yes2", 4567);
    rr(st.getErrorMsg()=="");
    rr(!st.fail());
    Label l3 = st.getLabel("Yes2");
    rr(l3.valid);
    rr(l3.addr == 4567);
    rr(l3.toPatch.size() == 2);
    rr(l3.toPatch[0].ins == OpCode::JMP);
    rr(l3.toPatch[0].addr == 2345);
    rr(l3.toPatch[1].ins == OpCode::CALL);
    rr(l3.toPatch[1].addr == 3456);
    //clear usages of a label
    st.removeLabelUsages("Yes2");
    rr(!st.fail());
    Label l4 = st.getLabel("Yes2");
    rr(l4.valid);
    rr(l4.addr == 4567);
    rr(l4.toPatch.size() == 0);

}
tt(" A smackering of correct (and failing) usages of Labels SymbolTable", "[SymbolTable]"){
    SymbolTable st;
    //valid on construction
    rr(!st.fail());
    //fails on getting non-entered label
    st.getLabel("No1");
    rr(st.fail());
    rr(st.getErrorMsg()=="Couldn't find label: No1");
    //unset failure
    st.unsetFail();
    rr(!st.fail());
    rr(st.getErrorMsg()==std::string());
    //double add a label
    st.addLabel("Yes1", 1234);
    rr(!st.fail());
    st.addLabel("Yes1", 2345);
    rr(st.fail());
    st.unsetFail();
    //set the address of a label that already has one
    st.setAddress("Yes1", 3456);
    rr(st.fail());
    st.unsetFail();
    //remove label usages on unentered label
    st.removeLabelUsages("No1");
    rr(st.fail());
    st.unsetFail();
}

}

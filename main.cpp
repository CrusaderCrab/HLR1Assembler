#include <iostream>
#include "state.h"
#include "Parser.h"
using namespace std;

int main(int argc, char *argv[])
{
    std::string input = "Yes1\nYes2 /* No1 */ /**/ Yes3 /*No2*//*No3*//**/Yes4/*No5*/                 \
                          in.hlr1s      /* The default input file. Can be relative or absolute. */    \
out.hlr1b     /* The default output file. Can be relative or absolute. */                             \
defaultopcodes.txt /* The default opcode bindings for the instructions */                             \
false         /* Is Little-Endian. Either 'true' or 'false'. */                                       \
/*2             /* Register to store ret address from trap Overflow function */                       \
/*2             /* Register to store ret address from trap underflow function */                      \
614400        /* Start address of code section in memory. Given as decimal. Default is 600Kbytes */   \
END           /* the end of the file */ ";
    //std::string input = "Yes4/*No5*/";
    HLR1::Parser parser(input);
    while(parser && !parser.eof()){
        if(!parser) std::cout<<"ERR2: "<<parser.errorMsg()<<"\n";
        std::string str = parser.getStr();
        if(str.length()==0) std::cout << "Empty String.\n";
        else std::cout<<str<<"\n";
        if(parser.eof()) std::cout <<"EOF\n";
        if(!parser) std::cout<<"ERR2: "<<parser.errorMsg()<<"\n";
    }

    std::string input2 = "100 -100 0x100 0x01 0x 0x/*6*/";
    //std::string input2 = "100 -100 0x100 0x01 /*6*/";
    HLR1::Parser parser2(input2);
    while(parser2 && !parser2.eof()){
        if(!parser2) std::cout<<"ERR2: "<<parser2.errorMsg()<<"\n";
        uint32_t val = parser2.getValue();
        std::cout<<val<<"\n";
        if(parser2.eof()) std::cout <<"EOF\n";
        if(!parser2) std::cout<<"ERR2: "<<parser2.errorMsg()<<"\n";
    }
}

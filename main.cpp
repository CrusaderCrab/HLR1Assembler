#include <iostream>
#include "state.h"
#include "LineParser.h"
#include "CondCodes.h"
using namespace std;

int main(int argc, char *argv[])
{
    for(int i =0; i < argc; i++){
        std::cout<<"\""<<argv[i]<<"\""<<std::endl;
    }
    HLR1::State s(argc, argv);
    return 0;
}

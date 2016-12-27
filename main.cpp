#include <iostream>
#include "state.h"
using namespace std;

int main(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++){
        std::string arg(argv[i]);
        std::cout<< arg << "\n";

    }
    return 0;
}

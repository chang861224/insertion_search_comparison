#include "utils.h"

int ArgPos(char* str, int argc, char** argv){
    int a;

    for(a = 1 ; a < argc ; a++) if (!strcmp(str, argv[a])){
        if(a == argc - 1){
            std::cout << "Argument missing for " << str << std::endl;
            exit(1);
        }

        return a;
    }

    return -1;
}

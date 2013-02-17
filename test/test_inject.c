#include <stdio.h>
#include "inject.h"

void funcA(){
    printf("in %s\n", __FUNCTION__);
}

void funcB(){
    printf("in %s\n", __FUNCTION__);
}


int main() 
{

    funcA();

    //modify first instruction of funcA to: jmp funcB
    encode_jmp(&funcA, &funcB);

    //now call funcA again
    funcA();

    return 0;
}

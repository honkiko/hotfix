#include <stdio.h>
#include "hotfix.h"

extern int funcA(int);
int funcA_1(int x) {
    printf("It's in funcA_1\n");
    return funcB(x) * funcC(x);
}

HOTFIX_BEGIN
HOTFIX(funcA, funcA_1)
HOTFIX_END


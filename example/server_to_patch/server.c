#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "hotfix.h"


int funcB(int x) {
    //printf("It's in funcB\n");
    return x+1;
}

extern int funcC(int x);

int funcA(int x) {
    //printf("It's in funcA\n");
    return funcB(x) + funcC(x);
}


/*
void SignHandler(int iSignNo)
{
    printf("\nsignal:%d\n",iSignNo);
    hotfix("./patch.so");
}
*/

int main(int argc, char **argv) 
{
    int x;
    char buf[1024];
    char *p;

    hotfix_init();

    while (1) {
        p = fgets(buf, sizeof(buf), stdin);
        if (p == NULL)
            continue;

        if (strncmp(buf, "exit", 4) == 0)
            break;

        errno = 0;
        x = strtol(buf, NULL, 0);
        if (errno)
            continue;
        printf("funcA(%d) = %d\n", x, funcA(x));
    }

    return 0;
}

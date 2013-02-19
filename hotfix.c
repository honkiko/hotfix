#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <dlfcn.h>
#include "inject.h" 
#include "hotfix.h" 

#define HOTFIX_SIG SIGUSR2

static int load_hotfix(char *soname);
void hotfix_sighdl(int iSignNo)
{
    load_hotfix("./patch.so");
}

//void __attribute__((constructor)) hotfix_init(void){
void hotfix_init(void){
   signal(HOTFIX_SIG, hotfix_sighdl);
}


#define HOTFIX_TABLE_SYMBOL "hotfix_table"
static int load_hotfix(char *soname) 
{
    void *handle;
    int (*patch_func)(int);
    //int (*orig_func)(int);
    struct patch_descriptor *patches;
    
    char *error;
    int ret;

    if (soname == NULL) {
        return -1;
    }

    handle = dlopen(soname, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror();    /* Clear any existing error */

    /* Writing: cosine = (double (*)(double)) dlsym(handle, "cos");
       would seem more natural, but the C99 standard leaves
       casting from "void *" to a function pointer undefined.
       The assignment used below is the POSIX.1-2003 (Technical
       Corrigendum 1) workaround; see the Rationale for the
       POSIX specification of dlsym(). */

    //*(void **) (&patch_func) = dlsym(handle, patch_func_name);
    *(void **) (&patches) = dlsym(handle, HOTFIX_TABLE_SYMBOL);

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    /*
    fprintf(stderr, "orig_func=%p, patch_func=%p\n", 
            patches->orig_func, patches->patch_func);
    */
    
    //now inject jmp to original func
    ret = encode_jmp(patches->orig_func, patches->patch_func);
    if (ret) {
        fprintf(stderr, "code injection failed\n");
    }

    //dlclose(handle);  
}

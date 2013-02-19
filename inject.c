#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#define PAGE_MASK(page_size) (~((uintptr_t)(page_size)-1))
#define PAGE_ALIGN(x, page_size) ( ((uintptr_t)(x)) \
            & PAGE_MASK(page_size) )


#define OPCODE_JMP_NEAR_RELATIVE 0xE9
/* this works for both 32 and 64 bit*/
struct jmp_near_relative {
    unsigned char opcode; //0xE9
    unsigned char disp32[4];
};

/* only for 64bit*/
struct jmp_abs_indirect {
    unsigned char opcode; //0xFF
    unsigned char mod; //0x25
    unsigned char disp32[4]; //0
    unsigned char abs_addr[8];
};

int encode_jmp(void *addr_to_write, void *jmp_target) {
    int page_size = sysconf(_SC_PAGESIZE);
    void *write_page = (void *)PAGE_ALIGN(addr_to_write, page_size);
    int ret = mprotect(write_page, page_size, 
            PROT_READ|PROT_WRITE|PROT_EXEC);
    if (ret != 0) {
        printf("Error: mprotect failed. addr:%p, page:%p\n",
                addr_to_write, write_page);
        return ret;
    }

   intptr_t relative_addr = (char *)jmp_target 
       - ((char *)addr_to_write + sizeof(struct jmp_near_relative)); 
   if (labs(relative_addr) > (uint32_t)0xffffffff) {
        //printf("jmp more than 32 bits offset: %ld\n", relative_addr);
        struct jmp_abs_indirect *jmp_abs = 
            (struct jmp_abs_indirect *)addr_to_write;
        jmp_abs->opcode = 0xff;
        jmp_abs->mod = 0x25;
        jmp_abs->disp32[0] = 0;
        jmp_abs->disp32[1] = 0;
        jmp_abs->disp32[2] = 0;
        jmp_abs->disp32[3] = 0;
        memcpy(jmp_abs->abs_addr, &jmp_target, 8);
        return 0;
   }

   int32_t relative_addr_32 = (int32_t)relative_addr;
   struct jmp_near_relative *p = (struct jmp_near_relative *)addr_to_write;
   p->opcode = OPCODE_JMP_NEAR_RELATIVE;
   memcpy(p->disp32, &relative_addr_32, 4);  
   return 0;
}



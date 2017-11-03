#include <stdio.h>
#include"lib_enclave.h"
#include"lib_untrusted.h"
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>

/*
format
 use 0fff extension 
eeax: op code (operand-1): 
   EINIT(3), EENTER(4), EEXIT(5),
 ebx: start memory address of enclave 
 ecx: end memory address of enclave 
*/

void resume(void* loaded_so_handle) {
/*
    __asm__ __volatile__("movl $0x3, %%eax\n\t"
                         ".byte 0x0f,0x01,0xd7\n\t"
                         : //output: put current value in reg-ebx to var-ebx.
                         : "b"(loaded_so_handle) //input: initialize a random register with pointer to var-data.
                         : "memory"//what is changed by the assembly code: memory is changed.
                         );
*/
}

void e_return(void* exit_point) {
printf("                     \n");
//printf("TT: inside e_return()\n");
    __asm__ __volatile__ ("mov %0, %%rbx\n\t"
                  "movl $0x04, %%eax\n\t" // EEXIT
                  ".byte 0x0f,0x01,0xd7" 
                  : //output: put current value in reg-ebx to var-ebx.
                  : "r" (exit_point)
                         //input: initialize a random register with pointer to var-data.
                         //when no operand, just two ::! the following line needs to be commented out
                         //: //what is changed by the assembly code: memory is changed.
                  );
printf("TT: by end of e_return()\n");
}

#ifdef DLL_APP
extern "C" {
#endif

void _entry_point(void){
//don't put the following DEBUG statement before user_entry_point(), because that would OVERWRITE the value in RDX...!!! why?
    void * ptr_rt_args;
    void * ptr_exit;
    __asm__ __volatile__ (
                         "mov %%rcx, %0\n\t" 
                         "mov %%rdx, %1"  //__volatile__ is needed, otherwise, ptr_enclave does not get updated in memory!
                         : "=r" (ptr_exit), "=m" (ptr_rt_args) //somehow ptr_rt_arg may end up with the same reg with ptr_exit
                         :
                         );

//#ifdef DEBUG
//printf("TT: inside _entry_point: user_entry_point:%p, exit:%p, rt_args:%p\n", user_entry_point, ptr_exit, ptr_rt_args);
//#endif
//keep in mind at this point of time, malloc is already "resolved" to glibc; a later dlopen() will NOT override malloc symbol. Thus, here, to redirect malloc symbol (away from malloc@glibc) to malloc@lib_enclave.c in user_entry_point(), we need to dlsym and manually override the malloc symbol.
    //static void* (*malloc)(size_t) = (void* (*)(size_t)) dlsym(ptr_enclave->handle_so, "malloc"); //again, malloc@lib_enclave.c can not be found in rt symbol table.
    //static void (*free)(void *) = (void (*)(void *))dlsym(ptr_enclave->handle_so, "free");
    //free(malloc(10));
    user_entry_point(ptr_rt_args);
//#ifdef DEBUG
//printf("TT: inside _entry_point %d\n", 10);
//#endif
    e_return(ptr_exit);
}


void* lib_malloc(size_t sz)  __THROW
{
    //printf("TT: hooked lib_malloc()\n");
    //return glibc_malloc(sz);
}

void lib_free(void *p)  __THROW
{
    //printf("TT: hooked lib_free()\n");
    //glibc_free(*p);
}


#ifdef DLL_APP
}
#endif


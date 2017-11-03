#include <stdio.h>
#include"lib_untrusted.h"
#include <stdlib.h>
#ifdef DLL_APP
#include <dlfcn.h>
#endif
#include <fcntl.h>
#include <unistd.h>

#include "../../emulator/emulator/sgx.h"

void * static_alloc_enclave_mem(){
  void * enclave_heap = malloc(1024);
  return enclave_heap;
}

void einit(){
  //do nothing for now.
}

#ifdef DLL_APP

struct enclave_mem_image * dload_enclave_so(const char * filename) {
  struct enclave_mem_image * enclave_handle = (struct enclave_mem_image *)malloc(sizeof(struct enclave_mem_image));
  char* error;

  enclave_handle->handle_so = dlopen(filename, RTLD_LAZY);
  if (!enclave_handle->handle_so) {
     fprintf(stderr, "%s\n", dlerror());
     exit(1);
  }

  if ((error = dlerror()) != NULL) {
     fprintf(stderr, "%s\n", error);
     exit(1);
  }

  enclave_handle->heap = static_alloc_enclave_mem();
  // einit() to lock and sign the initialized enclave 
  einit();
  return enclave_handle;
}

void dunload_enclave_so(enclave_mem_image* which_enclave) {
  if (dlclose(which_enclave->handle_so) < 0) {
     fprintf(stderr, "%s\n", dlerror());
     exit(1);
  }
}

#endif
unsigned long old_rsp;

void e_enter(void (* entry_point)(void*), struct enclave_mem_image * which_enclave) {
//enter enclave
  long rip_enter = 0;
  which_enclave->tcs = (TCS *)malloc(sizeof(TCS));
  ((TCS*)which_enclave->tcs)->oentry = (long unsigned int)entry_point;

  __asm__ __volatile__ (
          "lea (%%rip), %0" //save current instruction pointer
          : "=r" (rip_enter));

//printf("TT: begin of e_enter: which_enclave: %p; entry_point: %p, rip_enter:%lx, rt_args: %p\n", which_enclave, entry_point, rip_enter, which_enclave->rt_args);
__asm__ __volatile__ ("mov %%rsp, %0\n\t"
											: "=r"(old_rsp)
											:
											:);
    //followed the SGX reference here: chapter 5: software.intel.com/sites/default/files/329298-002.pdf
    //wrapping foo
    __asm__ __volatile__ (
          "mov %1, %%rbx\n\t" // address of tcs
          "mov %2, %%rdx\n\t" // App-level argument to enter Enclave.
          "movl $0x02, %%eax\n\t" // EENTER, instruction type
          ".byte 0x0f,0x01,0xd7\n\t" // call opcode 01d7
          "mov %%rbx, %0"
          : "=r" (which_enclave->tcs)  //output
          : "r" (which_enclave->tcs), "r" (which_enclave->rt_args) //input: initialize a random register with pointer to var-data.
          : "eax", "rbx", "rdx"//"memory"//what is changed by the assembly code: memory is changed.
            //we need two pass BOTH arguments, because one is visible to kernel, rt_args visible to user-space
          );
//printf("TT: end of e_enter()\n");
__asm__ __volatile__ ("mov %0, %%rsp\n\t"
											:
											: "r"(old_rsp)
											:);
}

//which_enclave is handle of loaded shared object
void call_enclave(enclave_mem_image* which_enclave, void* args) {
  void (* local_entry_point)(void*) = (void (*)(void*))dlsym(which_enclave->handle_so, "_entry_point");

  Dl_info info;
  dladdr((void *)local_entry_point, &info); //local_entry_point is itself a pointer!!!
  void * baseaddr = info.dli_fbase;
  long static_address_offset = (long)local_entry_point - (long)baseaddr;
  //char a[4];

#ifdef DEBUG
  printf("TT: base:%p, _entry_point:%p, diff: %ld, args: %p\n", baseaddr, local_entry_point,  (long)local_entry_point - (long)baseaddr, args);
  const int LINE_SIZE = 17;
  char * aline = (char*)malloc(LINE_SIZE * sizeof(char)); 
  //the following throws stack_smashing detected
  //char aline[LINE_SIZE];
  for(int i = 0; i < LINE_SIZE; i++) aline[i]=0; //needed for heap array.
  int fd = open("/proc/self/maps", O_RDONLY);
  int bytes_read;
  while ( (bytes_read = read(fd, aline, LINE_SIZE - 1)) > 0 ){
    if(bytes_read < LINE_SIZE - 1) {
      aline[bytes_read]='\0';
    }
    printf("%s", aline);
    //printf("||%d||", bytes_read);
  }
  printf("note: sections in order: .text, .rodata, .bss \n");
  free(aline);
#endif
  which_enclave->rt_args = args;
  e_enter(local_entry_point, which_enclave);
  printf("end of call_enclave()\n");
}


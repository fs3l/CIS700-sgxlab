#ifndef LIB_UNTRUSTED_H
#define LIB_UNTRUSTED_H

#include "user_sharedargs.h"

enclave_mem_image* dload_enclave_so(const char * filename); 
void call_enclave(enclave_mem_image* which_enclave, void* args);
void dunload_enclave_so(enclave_mem_image* which_enclave);

#endif

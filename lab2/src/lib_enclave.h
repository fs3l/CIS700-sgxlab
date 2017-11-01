#ifndef LIB_ENCLAVE_H
#define LIB_ENCLAVE_H

//this extern C is needed, because user_entry_point() is called in a C environment (i.e. _entry_point function); if lib_enclave.h is compiled (linked) as a c++ file, then it will be treated as a c++ function, which can not be automatically called in a C function.
#ifdef __cplusplus 
extern "C" {
#endif

//user expected to impl. this function
void user_entry_point(const void*);

void* lib_malloc(size_t sz)  __THROW;

void lib_free(void *p)  __THROW;

#ifdef __cplusplus
}
#endif

#endif

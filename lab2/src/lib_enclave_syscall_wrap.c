#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

extern "C" { //needed for C style mangling

/* create pointers for real glibc functions */
ssize_t __real_write(int fd, const void *buf, size_t count);
ssize_t __wrap_write(int fd, const void *buf, size_t count)
{
  /* printing out the number of characters */
  printf("  Hooked! write:chars#:%lu\n", count);
  /* call the real glibc function and return the result */
  ssize_t result = __real_write(fd, buf, count);
  return result;
}

//puts is not syscall!
int __real_puts(const char* str);
int __wrap_puts(const char* str)
{
  // printing out the number of characters 
  printf("  Hooked! puts:chars#:%lu\n", strlen(str));
  // call the real glibc function and return the result 
  int result = __real_puts(str);
  return result;
}
/*
*/

int __real_brk(void *addr);
int __wrap_brk(void *addr){
  printf("  Hooked! brk:addr:%p\n", addr);
  return __real_brk(addr);
}

//e.g: access("/etc/ld.so.nohwcap", F_OK)
int __real_access(const char *pathname, int mode);
int __wrap_access(const char *pathname, int mode){
  printf("  Hooked! access:pathname:%s, mode:%d\n", pathname, mode);
  return  __real_access(pathname, mode);
}

//e.g.: mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) 
void * __real_mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);
void * __wrap_mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset){
  printf("  Hooked! mmap:start:%p, length:%lu, prot:%d, flags:%d, fd:%d, offset:%ld\n", start, length, prot, flags, fd, offset);
  return __real_mmap(start, length, prot, flags, fd, offset);
}



}

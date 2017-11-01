#include <string.h>
#include <stdio.h>

#include "../Enclave.h"
#include "Enclave_t.h"

/* ecall_function_calling_convs:
 *   memccpy is defined in system C library.
 */
void ecall_function_calling_convs(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    char s1[] = "1234567890";
    char s2[] = "0987654321";

    char buf[BUFSIZ] = {'\0'};
    memcpy(buf, s1, strlen(s1));

    ret = memccpy(NULL, s1, s2, '\0', strlen(s1));
    
    if (ret != SGX_SUCCESS)
        abort();
    assert(memcmp(s1, s2, strlen(s1)) == 0);

    return;
}



#include "../App.h"
#include "Enclave_u.h"

/* edger8r_function_attributes:
 *   Invokes ECALL declared with calling convention attributes.
 *   Invokes ECALL declared with [public].
 */
void edger8r_function_attributes(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;

    ret = ecall_function_calling_convs(global_eid);
    if (ret != SGX_SUCCESS)
        abort();
}


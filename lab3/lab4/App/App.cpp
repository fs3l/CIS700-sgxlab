// App.cpp : Defines the entry point for the console application.
#include <stdio.h>
#include <map>
#include "../Enclave1/Enclave1_u.h"
#include "../Enclave2/Enclave2_u.h"
#include "sgx_eid.h"
#include "sgx_urts.h"
#define __STDC_FORMAT_MACROS
#include <inttypes.h>


#define UNUSED(val) (void)(val)
#define TCHAR   char
#define _TCHAR  char
#define _T(str) str
#define scanf_s scanf
#define _tmain  main

extern std::map<sgx_enclave_id_t, uint32_t> enclave_id;


sgx_enclave_id_t enclave_1_id = 0;
sgx_enclave_id_t enclave_2_id = 0;

#define ENCLAVE1_PATH "libenclave1.so"
#define ENCLAVE2_PATH "libenclave2.so"

void ocall_suprint(const char *str, int ret[1])
{
    printf("%s", str);
}


uint32_t load_enclaves()
{
    uint32_t enclave_temp;
    int ret, launch_token_updated;
    sgx_launch_token_t launch_token;

    enclave_temp = 0;

    ret = sgx_create_enclave(ENCLAVE1_PATH, SGX_DEBUG_FLAG, &launch_token, &launch_token_updated, &enclave_1_id, NULL);
    if (ret != SGX_SUCCESS) {
                return ret;
    }

    enclave_temp++;
    enclave_id.insert(std::pair<sgx_enclave_id_t, uint32_t>(enclave_1_id, enclave_temp));

    ret = sgx_create_enclave(ENCLAVE2_PATH, SGX_DEBUG_FLAG, &launch_token, &launch_token_updated, &enclave_2_id, NULL);
    if (ret != SGX_SUCCESS) {
                return ret;
    }

    enclave_temp++;
    enclave_id.insert(std::pair<sgx_enclave_id_t, uint32_t>(enclave_2_id, enclave_temp));

   
    return SGX_SUCCESS;
}

int _tmain(int argc, _TCHAR* argv[])
{
    uint32_t ret_status;
    sgx_status_t status;
    uint32_t arg1 = 5, arg2 = 4;

    UNUSED(argc);
    UNUSED(argv);

    if(load_enclaves() != SGX_SUCCESS)
    {
        printf("\nLoad Failure");
    }

    do
    {
        //Test Create session between Enclave1(Source) and Enclave2(Destination)
        status = Enclave1_start_create_session(enclave_1_id, &ret_status, enclave_1_id, enclave_2_id);
        if (status!=SGX_SUCCESS)
        {
            printf("create session failed: Error code is %x", status);
            break;
        }

        // in class task
        printf("\n\nLab Task\nEnclave 1 will send message 0x12345678 to Enclave 2\n");
        //Test message exchange between Enclave1(Source) and Enclave2(Destination)
        status = Enclave1_exchange_message(enclave_1_id, &ret_status, enclave_1_id, enclave_2_id);
        if (status!=SGX_SUCCESS)
        {
            printf("message exchange failed: Error code is %x", status);
            break;
        }


        // homework task
        printf("\n\nHomework Task\n");
        printf("Input 2 variables. For example, 5 4 :\n");
        scanf("%u%u",&arg1,&arg2);

        //Test Enclave to Enclave call between Enclave1(Source) and Enclave2(Destination)
        status = Enclave1_enclave_to_enclave_call(enclave_1_id, &ret_status, enclave_1_id, enclave_2_id,arg1,arg2);
        if (status!=SGX_SUCCESS)
        {
            printf("enclave_to_enclave_call failed: Error code is %x", status);
            break;
        }
 
        //Test Closing Session between Enclave1(Source) and Enclave2(Destination)
        status = Enclave1_start_close_session(enclave_1_id, &ret_status, enclave_1_id, enclave_2_id);
        if (status!=SGX_SUCCESS)
        {
            printf("close session failed: Error code is %x", status);
            break;
        }

#pragma warning (push)
#pragma warning (disable : 4127)    
    }while(0);
#pragma warning (pop)

    sgx_destroy_enclave(enclave_1_id);
    sgx_destroy_enclave(enclave_2_id);

    return 0;
}

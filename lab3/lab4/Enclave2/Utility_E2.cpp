#include "sgx_eid.h"
#include "EnclaveMessageExchange.h"
#include "error_codes.h"
#include "Utility_E2.h"
#include "stdlib.h"
#include "string.h"

uint32_t unmarshal_input_parameters_e2(uint32_t* var1, uint32_t* var2, ms_in_msg_exchange_t* ms)
{
    char* buff;
    size_t len;
    if(!var1 || !var2 || !ms)
        return INVALID_PARAMETER_ERROR;

    buff = ms->inparam_buff;
    len = ms->inparam_buff_len;

    if(len != (sizeof(*var1) + sizeof(*var2)))
        return ATTESTATION_ERROR;

    memcpy(var1, buff, sizeof(*var1));
    memcpy(var2, buff + sizeof(*var1), sizeof(*var2));

    return SUCCESS;
}

uint32_t marshal_retval_and_output_parameters_e2(char** resp_buffer, size_t* resp_length, uint32_t retval)
{
    ms_out_msg_exchange_t *ms;
    size_t ret_param_len, ms_len;
    char *temp_buff;
    size_t retval_len;
    if(!resp_length)
        return INVALID_PARAMETER_ERROR;
    retval_len = sizeof(retval);
    ret_param_len = retval_len; //no out parameters
    temp_buff = (char*)malloc(ret_param_len);
    if(!temp_buff)
        return MALLOC_ERROR;

    memcpy(temp_buff, &retval, sizeof(retval)); 
    ms_len = sizeof(ms_out_msg_exchange_t) + ret_param_len;
    ms = (ms_out_msg_exchange_t *)malloc(ms_len);
    if(!ms)
    {
        SAFE_FREE(temp_buff);
        return MALLOC_ERROR;
    }
    ms->retval_len = (uint32_t)retval_len;
    ms->ret_outparam_buff_len = (uint32_t)ret_param_len;
    memcpy(&ms->ret_outparam_buff, temp_buff, ret_param_len);
    *resp_buffer = (char*)ms;
    *resp_length = ms_len;
    SAFE_FREE(temp_buff);
    return SUCCESS;
}

uint32_t marshal_message_exchange_request(uint32_t target_fn_id, uint32_t msg_type, uint32_t secret_data, char** marshalled_buff, size_t* marshalled_buff_len)
{
    ms_in_msg_exchange_t *ms;
    size_t secret_data_len, ms_len;
    if(!marshalled_buff_len)
        return INVALID_PARAMETER_ERROR;    
    secret_data_len = sizeof(secret_data);
    ms_len = sizeof(ms_in_msg_exchange_t) + secret_data_len;
    ms = (ms_in_msg_exchange_t *)malloc(ms_len);
    if(!ms)
        return MALLOC_ERROR;

    ms->msg_type = msg_type;
    ms->target_fn_id = target_fn_id;
    ms->inparam_buff_len = (uint32_t)secret_data_len;
    memcpy(&ms->inparam_buff, &secret_data, secret_data_len);
    *marshalled_buff = (char*)ms;
    *marshalled_buff_len = ms_len;
    return SUCCESS;
}

uint32_t umarshal_message_exchange_request(uint32_t* inp_secret_data, ms_in_msg_exchange_t* ms)
{
    char* buff;
    size_t len;
    if(!inp_secret_data || !ms)
        return INVALID_PARAMETER_ERROR;    
    buff = ms->inparam_buff;
    len = ms->inparam_buff_len;
    if(len != sizeof(uint32_t))
        return ATTESTATION_ERROR;

    memcpy(inp_secret_data, buff, sizeof(uint32_t));

    return SUCCESS;
}


uint32_t marshal_message_exchange_response(char** resp_buffer, size_t* resp_length, uint32_t secret_response)
{
    ms_out_msg_exchange_t *ms;
    size_t secret_response_len, ms_len;
    size_t retval_len, ret_param_len;
    if(!resp_length)
        return INVALID_PARAMETER_ERROR;    
    secret_response_len = sizeof(secret_response);
    retval_len = secret_response_len;
    ret_param_len = secret_response_len;
    ms_len = sizeof(ms_out_msg_exchange_t) + ret_param_len;
    ms = (ms_out_msg_exchange_t *)malloc(ms_len);
    if(!ms)
        return MALLOC_ERROR;
    ms->retval_len = (uint32_t)retval_len;
    ms->ret_outparam_buff_len = (uint32_t)ret_param_len;
    memcpy(&ms->ret_outparam_buff, &secret_response, secret_response_len);
    *resp_buffer = (char*)ms;
    *resp_length = ms_len;
     return SUCCESS;
}

uint32_t umarshal_message_exchange_response(char* out_buff, char** secret_response)
{
    size_t retval_len;
    ms_out_msg_exchange_t *ms;
    if(!out_buff)
        return INVALID_PARAMETER_ERROR;    
    ms = (ms_out_msg_exchange_t *)out_buff;
    retval_len = ms->retval_len;
    *secret_response = (char*)malloc(retval_len);
    if(!*secret_response)
    {
        return MALLOC_ERROR;
    }
    memcpy(*secret_response, ms->ret_outparam_buff, retval_len);
    return SUCCESS;
}

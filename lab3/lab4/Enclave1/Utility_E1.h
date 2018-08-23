#ifndef UTILITY_E1_H__
#define UTILITY_E1_H__

#include "stdint.h"

typedef struct _internal_param_struct_t
{
    uint32_t ivar1;
    uint32_t ivar2;
}internal_param_struct_t;

typedef struct _external_param_struct_t
{
    uint32_t var1;
    uint32_t var2;
    internal_param_struct_t *p_internal_struct;
}external_param_struct_t;

#ifdef __cplusplus
extern "C" {
#endif

uint32_t marshal_input_parameters_e2(uint32_t target_fn_id, uint32_t msg_type, uint32_t var1, uint32_t var2, char** marshalled_buff, size_t* marshalled_buff_len);
uint32_t unmarshal_retval_and_output_parameters_e2(char* out_buff, char** retval);
uint32_t marshal_message_exchange_request(uint32_t target_fn_id, uint32_t msg_type, uint32_t secret_data, char** marshalled_buff, size_t* marshalled_buff_len);
uint32_t umarshal_message_exchange_request(uint32_t* inp_secret_data, ms_in_msg_exchange_t* ms);
uint32_t marshal_message_exchange_response(char** resp_buffer, size_t* resp_length, uint32_t secret_response);
uint32_t umarshal_message_exchange_response(char* out_buff, char** secret_response);
#ifdef __cplusplus
 }
#endif
#endif

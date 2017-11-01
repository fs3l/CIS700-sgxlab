
/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
int suprint(const char *fmt, ...)
{
    int ret[1];
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_suprint(buf, ret);
    return ret[0];
}

long call_sum(int * list, long size){
    long ret = 0;
    for(int j=0;j<16;j++) {
      for(int i = j; i < size; i+=16){
        ret += list[i];
      }
    }
    suprint(" The sum result is %ld \n", ret);
    return ret;
}

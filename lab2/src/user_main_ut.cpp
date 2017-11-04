#include <stdio.h>
#include <stdlib.h>

#include "lib_untrusted.h"
#include "user_sharedargs.h"

void bar(int * ptr_int){
  printf("outside enclave: %d\n", *ptr_int);
}

int main(){
    struct sort_args_enclave args;

        int task=1;
    printf("Choose the task to run:\n1 Merge sort\n2 Bubble sort\n3 Quick sort\n");
    scanf("%d",&task);

    /* Lab 2 list input*/
    int list[8];
    printf("\nInput 8 numbers to be sorted:\n");
    for(int i=0;i<8;i++){
        scanf("%d",&list[i]);
    }

    List listc;
    listc.array = list;
    listc.size = 8;
    
    if(task == 1){
        /*Merge Sort*/
        args.plist = &listc;
        args.size = 8;

        enclave_mem_image* enclave_handle_msort;
        enclave_handle_msort = dload_enclave_so("./bin/enclave_msort.so");
        call_enclave(enclave_handle_msort, &args);
        dunload_enclave_so(enclave_handle_msort);
    }
    else if(task == 2){
        /*Bubble Sort*/
        args.plist = &listc;
        args.size = 8;
    
        enclave_mem_image* enclave_handle_bsort;
        enclave_handle_bsort = dload_enclave_so("./bin/enclave_bsort.so");
        call_enclave(enclave_handle_bsort, &args);
        dunload_enclave_so(enclave_handle_bsort);
    }
    else if(task == 3){
        /*Quick Sort*/

        args.plist = &listc;
        args.size = 8;

        enclave_mem_image* enclave_handle_qsort;
        enclave_handle_qsort = dload_enclave_so("./bin/enclave_qsort.so");
        call_enclave(enclave_handle_qsort, & args);
        dunload_enclave_so(enclave_handle_qsort);

    }
}



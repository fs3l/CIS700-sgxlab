#include<stdio.h>
#include<unistd.h>
#include"lib_enclave.h"
#include"user_sharedargs.h"

#define malloc lib_malloc
#define free lib_free


void mergeSort(List list, int l, int r){
    /* TODO: task 1 code here */
}



void user_entry_point(const void* args){
	printf("\nMERGE SORT\n");
	List* list = ((struct sort_args_enclave*) args)->plist;
	int size = ((struct sort_args_enclave*) args)->size;
	printf("Origin List: [index is show as: (index)]");
	list->printList(list, size);
	
	mergeSort(*list, 0, size-1);

	printf("\nSorted List:");
	list->printList(list, size);
}

#undef malloc
#undef free

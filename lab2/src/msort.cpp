#include<stdio.h>
#include<unistd.h>
#include"lib_enclave.h"
#include"user_sharedargs.h"

#define malloc lib_malloc
#define free lib_free


void merge(/* TODO: task 2*/){
    /* TODO: task 2 code here*/

}

void divide(List* list, int l, int r){
    /* TODO: task 2 code here */
}



void user_entry_point(const void* args){
	printf("\n\n\nMERGE SORT\n");
	List* list = ((struct sort_args_enclave*) args)->plist;
	int size = ((struct sort_args_enclave*) args)->size;
	printf("Origin List:");
	list->printList(list, size);
	
	printf("\n\n");
	divide(list, 0, size-1);
	printf("\n\n");	

	printf("Sorted List:");
	list->printList(list, size);
	printf("\n\n\n\n");
}

#undef malloc
#undef free

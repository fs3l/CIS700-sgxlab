#include<stdio.h>
#include<unistd.h>

#include"lib_enclave.h"
#include"user_sharedargs.h"

/* TODO: task 3: homework lab code here */

void printList(List* list, int size){
	for(int i=0; i<size; i++){
		printf("%d ", (*list)[i]);
	}
	printf("\n");
}

void user_entry_point(const void* args){
	printf("\n\n\nQUICK SORT\n");
	List* list = ((struct sort_args_enclave*)args)->plist;
	int size = ((struct sort_args_enclave*)args)->size;

	printf("Origin List:");
	list->printList(list, size);
	
	printf("\n\n");
        // TODO: your sorting function call here
	// for example: quickSort(list, 0, size-1);
	printf("\n\n");	

	printf("Sorted List:");
	list->printList(list, size);

	printf("\n\n\n\n");
}

#include<stdio.h>
#include<unistd.h>
#include"lib_enclave.h"
#include"user_sharedargs.h"

/* This is task 1 for the Lab 2
 * This file contains implementation of bubble sort
 */

void bubbleSort(List* list, int size){
	/* TODO: task 1 code here */
}

void user_entry_point(const void* args){
	printf("\n\n\nBUBBLE SORT:\n");
//	int* list = ((struct sort_args_enclave*) args)->plist->value;
	List* list = ((struct sort_args_enclave*) args)->plist;
	int size = ((struct sort_args_enclave*) args)->size;
	printf("Origin List:");
	list->printList(list, size);
	
	printf("\n\n");
	bubbleSort(list, size);
	printf("\n\n");
	printf("Sorted List:");
	list->printList(list, size);
	
	printf("\n\n\n\n");
}





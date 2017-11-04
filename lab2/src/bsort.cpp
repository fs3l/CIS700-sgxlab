#include<stdio.h>
#include<unistd.h>
#include"lib_enclave.h"
#include"user_sharedargs.h"

/* This is task 2 for the Lab 2
 * This file contains implementation of bubble sort
 */

void bubbleSort(TrackedList list, int size){
	/* TODO: task 2 code here */
}

void user_entry_point(const void* args){
	printf("\nBUBBLE SORT:\n");
//	int* list = ((struct sort_args_enclave*) args)->plist->value;
	TrackedList* list = ((struct sort_args_enclave*) args)->plist;
	int size = ((struct sort_args_enclave*) args)->size;
	printf("Origin TrackedList: [index is show as: (index)]");
	list->printTrackedList(list, size);
	
	bubbleSort(*list, size);
	printf("\nSorted TrackedList:");
	list->printTrackedList(list, size);
}


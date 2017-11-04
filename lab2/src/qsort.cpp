#include<stdio.h>
#include<unistd.h>

#include"lib_enclave.h"
#include"user_sharedargs.h"

/* TODO: task 3: homework lab code here */


void quickSort(TrackedList *list, int left, int right){
    /* TODO: task 3 code here */
    // Remove printf below when you fill your code
    printf("Quick sort does not finish\n");
}


void user_entry_point(const void* args){
	printf("\nQUICK SORT\n");
	TrackedList* list = ((struct sort_args_enclave*)args)->plist;
	int size = ((struct sort_args_enclave*)args)->size;

	printf("Origin TrackedList: [index is show as: (index)]");
	list->printTrackedList(list, size);
	
	quickSort(list, 0, size-1);

	printf("\nSorted TrackedList:");
	list->printTrackedList(list, size);

}

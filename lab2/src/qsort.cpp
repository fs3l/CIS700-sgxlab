#include<stdio.h>
#include<unistd.h>

#include"lib_enclave.h"
#include"user_sharedargs.h"

/* TODO: task 3: homework lab code here */


void quickSort(List *list, int left, int right){
    /* TODO: task 3 code here */
    // Remove printf below when you fill your code
    printf("Quick sort does not finish\n");
}


void user_entry_point(const void* args){
	printf("\nQUICK SORT\n");
	List* list = ((struct sort_args_enclave*)args)->plist;
	int size = ((struct sort_args_enclave*)args)->size;

	printf("Origin List: [index is show as: (index)]");
	list->printList(list, size);
	
	quickSort(list, 0, size-1);

	printf("\nSorted List:");
	list->printList(list, size);

}

#ifndef USER_SHAREDARGS_H
#define USER_SHAREDARGS_H
#include<stdexcept>
//shared between untrusted code and enclave code
class List {
public:
	int* value;
	int size;

	List(){
		value = NULL;

	}

	int& operator[](int k){
		if(k<0 || k>=size)
		  throw std::out_of_range("invalid index"); 
	        printf("(%d) ",k);
		return value[k];
	}
		
    void printList(List* list, int size){
	printf("\n");
	for(int i=0; i<size; i++){
		printf("%d  ", (*list)[i]);
	}
	printf("\n");
}
};

struct args_enclave {
	int val_int;
	void * misc;
};

struct sort_args_enclave{
	int size;
	//	int* plist;
	List *plist;
};

struct enclave_mem_image {
	//static or einit time
	void* handle_so; //.text and .data
	void* heap;
	void* tcs;
	//eenter time
	void* rt_args; 
} ;


#endif

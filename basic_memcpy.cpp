#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <assert.h>

using namespace std;

void mymemcpy(void* dest, const void* src, size_t len){
	assert(dest!=NULL && src!=NULL);

	if(src > dest){
		int i=0;
		while(i < len){
			*((char*)dest+i) = *((char*)src+i);		
			i++;
		}
	}else{		
		while(len -- > 0){
			*((char*)dest+len) = *((char*)src+len);		
		}
	}
}

int main(){
	char arr[20] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t'};
	int len = 20;
	
	mymemcpy(arr, arr+5, 8);
	
	int i=0;
	for(i=0; i<len; i++){
		printf("%c,",arr[i]);
	}
	printf("\n");
	scanf("%d",&i);
	
	return 0;
} 

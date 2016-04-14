#include <iostream>
#include <assert.h>
using namespace std;

void* memmove(void* dst, const void* src, size_t len){
	assert(NULL != dst);
	assert(NULL != src);
	
	char* pDst = (char*)dst;
	const char* pSrc = (char*)src;
	
	if(pDst <= pSrc || pDst >= pSrc+len){
		while(len--){
			*pDst++ = *pSrc++;
		}
	}else{ //cpy from high to low
		char* pDstEnd = pDst + len-1;
		const char* pSrcEnd = pSrc + len-1;
		while(len--){
			*pDstEnd-- = *pSrcEnd--;
		}
	}
	
	return pDst;
}

int main(){
	char* src = new char[3];
	src[0] = '3';
	src[1] = '2';
	src[2] = '9';
	
	char* dst = new char[3];
	
	memmove(dst, src, 3);
	
	for(int i=0; i<3; i++){
		cout << dst[i] << ",";
	}
	cout << endl;
		
	
	return 0;
}

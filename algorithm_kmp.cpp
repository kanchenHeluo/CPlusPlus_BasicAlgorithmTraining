#include <iostream>
#include <string.h>
using namespace std;

void makenext(int* next, char* substr){
	int sublen = strlen(substr);
	for(int i=1; i<sublen; i++){
		int idx = i-1;
		while(idx!=0 && substr[i-1] != substr[next[idx]]){
			idx = next[idx];
		}
		
		next[i] = next[idx]+1;
	}
	cout << "next:" << endl;
	for(int i=0; i<sublen; i++){
		cout << next[i] << ",";
	}
	cout << endl;
}

int kmp(char* substr, char* str){
	int sublen = strlen(substr);
	int len = strlen(str);
	int* next =new int[sublen];
	next[0] = -1;
	
	makenext(next, substr);
	
	int i=0,j=0;
	for(i=0; i<len; i++){
		if(substr[j] == str[i]){
			j++;		
			if(j==sublen){
				break;
			}
		}else{
			i--;
			j = next[j];
			if(-1 == j){
				i++;
				j++;
			}
		}
	}
	if(j==sublen){
		return i-j+1;
	}
	return -1;
	


}

int main(){
	char* str = "aa";
	char* substr = "aa";
	
	cout << kmp(substr, str) << endl;
	
	return 0;
}

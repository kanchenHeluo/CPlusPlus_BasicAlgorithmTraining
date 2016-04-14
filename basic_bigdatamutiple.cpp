#include <iostream>
#include <string.h>
using namespace std;

int* arr(char* a, int* len, int* negative){
	int alen = strlen(a), i=0;
	*len = alen;
	*negative = 1;
	if(alen>0 && a[0]=='-'){
		*len = alen-1;
		
		i=1;
		*negative = -1;
	}
	
	int* re = new int[*len], ridx=0;
	for(; i<alen; i++){
		re[ridx++] = a[i]-'0';
	}
		
	return re;
}

int* multipleBigData(char* a, char* b, int* len){	
	int alen, blen, anegative, bnegative;
	int* a1 = arr(a, &alen, &anegative);
	int* b1 = arr(b, &blen, &bnegative);
	*len = alen+blen+1;
	int* result = new int[*len];
	memset(result, 0, sizeof(int)*(*len));
	
	int kk = 0;	
	for(int i=alen-1; i>-1; i--){
		for(int j=blen-1; j>-1; j--){
			int k = alen-kk+j+1;
			result[k] += a1[i]*b1[j];
			int up = k;
			while(result[up]/10>0){
				result[up-1]+=result[up]/10;
				result[up] = result[up]%10;
				up = up-1;
			}
			
		}
		kk++;
	}
	
	delete a1;
	delete b1;
	
	if(anegative*bnegative == 1){
		result[0] = 1;
	}else{
		result[0] = 0;
	}	
	return result;
}

int main(){
	char* a = "-9111";
	char* b = "45";
	
	int relen = 0;
	int* re = multipleBigData(a,b,&relen);
	
	if(!re[0]){
		cout << '-';
	}
	int i=1;
	while(i<relen && re[i]==0){
		i++;
	}
	if(i>=relen){
		cout << "0";
	}
	for(; i<relen; i++){
		cout << re[i];
	}
	cout << endl;
	delete re;
	
	return 0;
}

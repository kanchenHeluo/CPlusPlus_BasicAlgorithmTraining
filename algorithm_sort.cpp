#include <iostream>

using namespace std;

int partition(int* arr, int low, int high){
	int tmp = arr[low];
	while(low<high){
		while( high>low && arr[high]>tmp ){
			high--;
		}
		if(high>low){
			arr[low] = arr[high];
		}
		while(low<high && arr[low]<tmp){
			low++;
		}
		if(low<high){
			arr[high] = arr[low];
		}		
	}
	arr[low] = tmp;
	return low;
}

void quicksort(int* arr, int low, int high){
	
	if(low < high){
		int idx = partition(arr, low, high);
		quicksort(arr, low, idx-1);
		quicksort(arr, idx+1, high);
	}
}

void merge(int* arr, int s, int m, int e){
	int len = e-s+1, k=s;
	
	int leftlen = m-s+1;
	int* left = new int[leftlen];
	for(int i=0; i<leftlen; i++){
		left[i] = arr[s++];
	}
	int rightlen = e-m;
	int* right = new int[rightlen];
	m++;
	for(int i=0; i<rightlen; i++){
		right[i] = arr[m++];
	}
	
	int i=0, j=0;
	while(i<leftlen && j<rightlen){
		if(left[i]<right[j]){
			arr[k++] = left[i++];
		}else{
			arr[k++] = right[j++];
		}
	}	
	while(i<leftlen){
		arr[k++] = left[i++];
	}
	while(j<rightlen){
		arr[k++] = right[j++];
	}
	delete left;
	delete right;
}

void mergesort(int* arr, int low, int high){
	if(low<high){
		int mid = (low+high)/2;
		mergesort(arr, low, mid);
		mergesort(arr, mid+1, high);
		merge(arr, low, mid, high);
	}
}

void adjustheap(int* arr, int idx, int len){
	int tmp = arr[idx];
	int left = 2*idx+1, right=left+2;
	
	while(left<len){
		int min_val = arr[left], min_idx = left;
		if(right < len && arr[right]<min_val){
			min_val = arr[right];
			min_idx = right;
		}
		
		if( tmp < min_val){
			break;
		}
		
		arr[idx] = min_val;
		idx = min_idx;
		left = 2*idx+1;
		right = left+2; 
	}
	arr[idx]=tmp;
}

void makeheap(int* arr, int len){
	for(int i=len/2; i>=0; i--){
		adjustheap(arr, i, len);
	}	
}

void heapsort(int* arr, int len){
	makeheap(arr, len);
	
	
	
	while(len>0){
		cout << arr[0] << endl;
		arr[0] = arr[len-1];
		len--;
		adjustheap(arr, 0, len);
	}
}

int main(){
	int* arr =new int[6];
	arr[0] = 3;
	arr[1] = 0;
	arr[2] = 9;
	arr[3] = -2;
	arr[4] = 7;
	arr[5] = 1;
	
	heapsort(arr, 6);
	
	/*
	for(int i=0; i<6; i++){
		cout << arr[i] << ",";
	}
	cout << endl;
	*/
	return 0;
}

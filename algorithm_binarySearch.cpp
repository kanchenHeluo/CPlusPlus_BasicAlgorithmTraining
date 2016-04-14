#include <iostream>

using namespace std;

int binarySearch(int* arr, int len, int data){
	int low=0, high=len-1;
	while(low<=high){
		int mid = (low+high)/2;
		if(arr[mid] == data)
			return mid;
		else if(arr[mid] > data){
			high = mid-1;
		}else{
			low = mid+1;
		}
	}
	return -1;
}

int main(){
	int* arr =new int[2];
	arr[0] = 3;
	arr[1] = 3;
	/*
	arr[1] = 6;
	arr[2] = 9;
	arr[3] = 12;
	arr[4] = 17;
	arr[5] = 21;*/

	cout << binarySearch(arr, 2, 3); 
	cout << binarySearch(arr, 2, 4); 
	/*
	cout << binarySearch(arr, 6, 6);
	cout << binarySearch(arr, 6, 9);
	cout << binarySearch(arr, 6, 12);
	cout << binarySearch(arr, 6, 17);
	cout << binarySearch(arr, 6, 21);
	cout << binarySearch(arr, 6, 22);
	cout << binarySearch(arr, 6, 2);
	cout << binarySearch(arr, 6, 10);*/
	return 0;
}

#include <iostream>
#include <vector>

using namespace std;

void combination(const int* arr, int len, vector<int>& result){
	if(len < 0){
		for(int i=0; i<result.size(); i++){
			cout << result[i] << ",";
		}
		cout << endl;
	}else{
		result.push_back(arr[len]);
		combination(arr, len-1, result);
		result.pop_back();	
		combination(arr, len-1, result);
	}
}

void permutation(int *arr, int s, int e){
	if(e == s+1){
		for(int i=0; i<e; i++){
			cout << arr[i] << ",";
		}
		cout << endl;
	}else{
		for(int i=s; i<e; i++){
			int tmp = arr[s];
			arr[s] = arr[i];
			arr[i] = tmp;
			
			permutation(arr,s+1,e);
			
			tmp = arr[i];
			arr[i] = arr[s];	
			arr[s] = tmp;
		}
	}
	
}


int main(){
	int arr[] = {1,2,3,4};
	cout << "permuation:" << endl;
	permutation(arr,0,4);
	cout << "combination:" << endl;
	vector<int> result;
	combination(arr,3, result);
	return 0;
}

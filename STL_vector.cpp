#include <iostream>
#include <cstring>

using namespace std;

template<T>
class vector{
	private:
		T* arr = null;
		size_t size, buffersize;
		
	public:
		vector(){
			buffersize = 100;
			size = -1; 
			arr = new T[buffersize];
			if(!arr){
				; //?
			}
		}
		
		~vector(){
			delete arr;
		}
		
		void push_back(T data){
			T* arr2 = null;
			if(size == buffersize-1){
				buffersize += 100;
				arr2 = new T[buffersize];
			}
			if(arr2){
				memmove(arr2, arr, sizeof(T)*size);
				//delete arr; ?
				arr = arr2;
				size++;
				arr[size] = data;
			}else{
				;// ?
			}
		}
		
		T pop(){
			if(size > 0){
				size--;
				return arr[size+1];
			}
		}
}

int main(){
	
	return 0;
}

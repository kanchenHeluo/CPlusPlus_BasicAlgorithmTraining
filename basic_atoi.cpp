#include <iostream>
#include <string>
#define INT_MAX 2147483647LL 
#define INT_MIN -2147483648LL

using namespace std;

void trim(string& text){
	if(!text.empty()){
		text.erase(0, text.find_first_not_of(" \n\r\t"));
		text.erase(text.find_last_not_of(" \n\r\t")+1);
	}
}

long long myAtoi(string str) {
	long long result = 0;
    bool positive = true;
	int index = 0, len=str.length();
	
	trim(str);
    if(str[0] == '+' || str[0] == '-'){
    	index ++;
    	positive = str[0] == '-' ? false:true;
	}
    
    while(index < len){
    	int asc = str[index] - '0';
		if(asc < 0 || asc > 9){
    		break;
		}
		if(positive){
			result = (result*10 + asc);	
		}else{
			result = (result*10 - asc);
		}
		if(result > INT_MAX){
			return INT_MAX;
		}else if(result < INT_MIN){
			return INT_MIN;
		}
		
		index++;
	}
	return result;
}

int main(){
	
	string a = "92345AB	";

	cout << myAtoi(a) << endl;
	a="2147483648";
	
	cout << myAtoi(a) << endl;
	
	a="9223372036854775809";
	cout << myAtoi(a) << endl;
	return 0;
}

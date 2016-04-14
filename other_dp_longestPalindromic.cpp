#include <iostream> 
#include <string>
#include <cstring>
//https://leetcode.com/problems/longest-palindromic-substring/
using namespace std;

int dp[1000][1000];

string longestPalindrome(string s) {	
	int slen = s.length();
	memset(dp,0,sizeof(int)*1000000);
		
	//dp
	int max_i = 0, max = 1;	
	for(int len=1; len < slen+1; len++){
		for(int i=0; i<slen-len+1; i++){
			int j = i+len-1;
			
			if (s[i] == s[j] && (i+1>=j-1 || dp[i+1][j-1] == 1)){
				dp[i][j] = 1;
				if(j-i+1 > max){
					max = j-i+1;
					max_i = i;
				}
			}			
		}
	}
	
	return s.substr(max_i, max);
}

int main(){
	string s = "dfsadav";
	
	cout << longestPalindrome(s) << endl;
	
	return 0;
} 

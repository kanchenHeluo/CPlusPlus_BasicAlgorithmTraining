#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#define N 100
using namespace std;

int s[N], p[N], na[N], arr[N][N], row[N];
vector<vector<string> > result;
void queen(int r, int n){
	if(r == n){
		vector<string> re;
		for(int i=0; i<n; i++){
			string str(n,'.');
			str[row[i]] = 'Q';	
			re.push_back(str);
		}
		result.push_back(re);
	}else{
		for(int i=0; i<n; i++){
			if(s[i]==0 && p[r+i]==0 && na[n+r-i-1]==0){
				s[i] = 1;
				p[r+i] = 1;
				na[n+r-i-1] = 1;
				arr[r][i] = 1;
				row[r] = i;
				queen(r+1,n);
				arr[r][i]= 0;
				s[i] = 0;
				p[r+i] = 0;
				na[n+r-i-1] = 0;
			}
		}
	}
}

vector<vector<string> > solveNQueens(int n) {
	memset(s,0,sizeof(int)*n);
	memset(p,0,sizeof(int)*n);
	memset(na,0,sizeof(int)*n);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			arr[i][j] = 0;
		}
	}
	queen(0,n);
	return result;
}

int main(){
	int n=2;
	solveNQueens(n);
	
	for(int i=0; i<result.size(); i++){
		for(int j=0; j<n; j++){
			cout << result[i][j];
		}
		cout << endl;
	}
	
	return 0;
}

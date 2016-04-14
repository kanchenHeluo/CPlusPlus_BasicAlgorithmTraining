#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

struct POSS{
	int x;
	int y;
	vector<int> posses;
	POSS(int x1, int y1):x(x1), y(y1){}
};

bool cmp(POSS a, POSS b){
	return a.posses.size()< b.posses.size();
}

bool checkCubic(int x, int y, vector<vector<char> >& board){
	int si = x/3, sj = y/3;
	int flag[10] = {0};
	
	for(int i=0; i<9; i++){
		if(i!=x && board[i][y] == board[x][y]){
			return false;
		}
	}
	
	for(int j=0; j<9; j++){
		if(j!=y && board[x][j] == board[x][y]){
			return false;
		}
	}
	
	for(int i=si*3+0; i<si*3+3; i++){
		for(int j=sj*3+0; j<sj*3+3; j++){
			if((i!=x || j!=y) && board[i][j] == board[x][y]){
				return false;
			}
		}
	}
	return true;
}

bool trySudoku(int idx, vector<POSS>& possibility, vector<vector<char> >& board){	
	if(idx == possibility.size()){
		return true;
	}
	else{
		POSS p = possibility[idx];
		for(int i=0; i<p.posses.size(); i++){ // traverse every sub-possiblity			
			board[p.x][p.y] = '0'+p.posses[i];
			//if (idx == 0)
			//	cout << "try: x=" << p.x << ",y=" << p.y <<",val=" << board[p.x][p.y] << endl; 
			if(checkCubic(p.x, p.y, board)){
				if(trySudoku(idx+1, possibility, board)){
					return true;
				}
			}
			board[p.x][p.y] = '.';
		}
		return false;
	}
}

void calc(vector<POSS>& possibility, vector<vector<char> >&board){
	vector<int> row[9];
	vector<int> col[9];
	int flag[10];
	
	for(int i=0; i<9; i++){
		memset(flag, 0, sizeof(int)*10);
		for(int j=0; j<9; j++){
			if(board[i][j]!= '.'){
				flag[board[i][j] - '0'] = 1;
			}
		}
		for(int j=1; j<10; j++){
			if(!flag[j]){
				row[i].push_back(j);		
			}
		}
	}	
	for(int i=0; i<9; i++){
		memset(flag, 0, sizeof(int)*10);
		for(int j=0; j<9; j++){
			if(board[j][i]!= '.')
				flag[board[j][i] - '0'] = 1;
		}
		for(int j=1; j<10; j++){
			if(!flag[j]){
				col[i].push_back(j);		
			}
		}
	}
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			if(board[i][j]=='.'){
				POSS p(i,j);
				int flag[10] = {0};
				for(int k=0; k<row[i].size(); k++){
					flag[row[i][k]]++;
				}
				for(int k=0; k<col[j].size(); k++){	
					flag[col[j][k]]++;
				}
				for(int k=0; k<10;k++){
					if(flag[k]==2){
						p.posses.push_back(k);
					}
				}
				possibility.push_back(p);
			}
		}
	}
}

void solveSudoku(vector<vector<char> >& board) {
	vector<POSS> possibility; 
	calc(possibility, board);
	sort(possibility.begin(), possibility.end(), cmp);
	trySudoku(0, possibility, board);
}

void inputSudoku(vector<vector<char> >& board){
	for(int i=0;i<9;i++){
		vector<char> row;
		for(int j=0;j<9;j++){
			char a;
			cin >> a; 
			row.push_back(a);
		}
		board.push_back(row);
	}
}

void printSudoku(vector<vector<char> >board){
	int ilen = board.size();
	int jlen = board[0].size();
	
	for(int i=0; i<ilen; i++){
		for(int j=0; j<jlen; j++){
			cout << board[i][j];
		}
		cout << endl;
	}
}

int main(){
	vector<vector<char> >board;
	
	inputSudoku(board);
	solveSudoku(board);
	printSudoku(board);
	
	return 0;
}

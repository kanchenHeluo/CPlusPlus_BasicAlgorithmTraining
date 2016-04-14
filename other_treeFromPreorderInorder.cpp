#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void vectorCpy(vector<int>& dest, vector<int> src, int s, int e){
	for(int i=s; i<e; i++){
		dest.push_back(src[i]);
	}
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	if(preorder.size() == 0){
		return NULL;
	}
	
	TreeNode* root = new TreeNode(preorder[0]);
	if(preorder.size() == 1 && inorder.size() == 1){
		return root;
	}else{
		vector<int>::iterator iter = find(inorder.begin(), inorder.end(), preorder[0]);	
		int index = iter-inorder.begin();
		
		vector<int> ino_l;
		vectorCpy(ino_l, inorder, 0, index);
		
		vector<int> ino_r;
		vectorCpy(ino_r, inorder, index+1, inorder.size());
		
		vector<int> pre_l;
		vectorCpy(pre_l, preorder, 1, index+1);
		
		vector<int> pre_r;
		vectorCpy(pre_r, preorder, index+1, preorder.size());
		
		root -> left = buildTree(pre_l, ino_l);	
		root -> right = buildTree(pre_r, ino_r);
		
		return root;
	}    
}



int main(){
	
	vector<int> preorder;
	vector<int> inorder;
	
	preorder.push_back();
	
	inorder.push_back();
	
	
	TreeNode* root = buildTree(preorder, inorder);
	
	
	
	return 0;
}

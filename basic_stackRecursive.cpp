#include <iostream>
#include <stack>

using namespace std;

struct Node{
	int val;
	struct Node* left;
	struct Node* right;
};

/*
Node* root;

void preorder(Node* root){
	if(root!=null){
		cout << root->val << ",";
	    
		preorder(root->left);
		
		
		preorder(root->right);
	
	}
}*/

enum Status {
	StatusFirstTime,
	StatusLeftBack,
	StatusRightBack
};

struct stackNode{
	Status status;
	Node* node;
};





void preorder_norecursive(Node* root){
	stackNode snode;
	snode.node = root;
	snode.status = StatusFirstTime;
	stack<stackNode> s;
	s.push(snode);
	
	while(s.size() > 0){
		stackNode& r = s.top();
		/*
		cout << r.node->val << ", " << r.node->left << "-" << r.node->right << ", " << r.status << endl;
		system("PAUSE");*/
		if (r.status == StatusFirstTime) {
			stackNode snode;
			cout << r.node->val << endl;
			r.status = StatusLeftBack;
			if (r.node->left) {
				snode.status = StatusFirstTime;
				snode.node = r.node->left;
				s.push(snode);	
				
			}
			
		} else if (r.status == StatusLeftBack) {
			r.status = StatusRightBack;
			if (r.node->right) {
				snode.status = StatusFirstTime;
				snode.node = r.node->right;
				s.push(snode);	
			
			}
			
		} else if (r.status == StatusRightBack) {
			s.pop();
		}
	}
}


struct Node2 {
	int val;
	struct Node2* left;
	struct Node2* right;
	
	Status status;
	Node2* parent;
};

void preorder_nostack(Node2* root){
	Node* current = node;	
	while(current != NULL){
		if (current->status == StatusFirstTime) {
			cout << current->val << endl;
			current->status = StatusLeftBack;
			if (current->left) {
				current = current->left;
			}			
		} else if (current->status == StatusLeftBack) {
			current->status = StatusRightBack;
			if (current->right) {
				current = current->right;
			}			
		} else if (current->status == StatusRightBack) {
			current = current->parent;
		}
	}
}

int main(){
	Node tree;
	tree.left = new Node;
	tree.right = new Node;
	tree.left->right = new Node;
	tree.left->left = NULL;
	tree.right->left = new Node;
	tree.right->right = NULL;
	tree.left->right->left = NULL;
	tree.left->right->right = NULL;
	tree.right->left->left = NULL;
	tree.right->left->right = NULL;
	
	tree.val = 0;
	tree.left->val = 1;
	tree.right->val = 2;
	tree.left->right->val = 3;
	tree.right->left->val = 4;

	preorder_norecursive(&tree);

	return 0;
}

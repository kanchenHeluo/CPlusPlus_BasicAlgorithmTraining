#include <iostream>
#include <stack>
#include <queue>
#include <math.h>

#define max(a, b)  (a>b ? a:b)

using namespace std;

enum Direction{
	Left,
	Right
};

class TreeNode{
public:
	int m_val;
	int m_height;
	TreeNode* m_left;
	TreeNode* m_right;
	TreeNode(int v){
		m_val = v;
		m_height = 0;
		m_left = NULL;
		m_right = NULL;
	}
};

struct StackNode{
	TreeNode* m_tn;
	Direction m_dir;
	StackNode(){}
	StackNode(TreeNode* tn, Direction dir): m_tn(tn), m_dir(dir) {}
};

TreeNode* root = new TreeNode(10);
stack<StackNode> s;

void printTree(TreeNode* r){ //BFS
	if(r == NULL)
		return;
	queue<TreeNode*> q;
	q.push(r);
	while(!q.empty()){
		TreeNode* t = q.front();
		q.pop();
		if(t==NULL){
			cout << "NIL" << ",";
		}else{
			cout << "[" << t->m_val << ":" << t->m_height << "],";
			q.push(t->m_left);
			q.push(t->m_right);
		}
	}
	cout << endl;
}

int updateHeight(TreeNode* r){
	int lh = -1;
	int rh = -1;
	if(r->m_left != NULL){
		lh = r->m_left->m_height;
	}
	if(r->m_right != NULL){
		rh = r->m_right->m_height;
	}
	return max(rh,lh)+1;
}

TreeNode* rotateAvl(TreeNode* y, TreeNode* yp, Direction ypDir, Direction dir){
	cout << "rotate:" << y->m_val << endl;
	if(dir == Left){
		TreeNode* x = y->m_left;
		y->m_left = x->m_right;
		x->m_right = y;
		y->m_height = updateHeight(y);
		x->m_height = updateHeight(x);
		if(yp!=NULL){
			if(ypDir == Left){
				yp -> m_left = x;
			}else{
				yp -> m_right = x;
			}
			yp->m_height = updateHeight(yp);
		}
		
		return x;
	}else{
		TreeNode* x = y->m_right;
		y->m_right = x->m_left;
		x->m_left = y;
		y->m_height = updateHeight(y);
		x->m_height = updateHeight(x);
		if(yp!=NULL){
			if(ypDir == Left){
				yp -> m_left = x;
			}else{
				yp -> m_right = x;
			}
			yp->m_height = updateHeight(yp);
		}
		return x;
	}
}

TreeNode* insertAvl(TreeNode* root, TreeNode* tn){
	int left = 0;
	if(root == NULL){
		root = tn;
	}
	TreeNode* tmp = root;
	TreeNode* p = NULL;
	while(tmp!=NULL){		
		p = tmp;
		if(tmp->m_val > tn->m_val){
			StackNode sn(tmp, Left);
			s.push(sn);
			tmp = tmp->m_left;
			left = 1;
		}else{
			StackNode sn(tmp, Right);
			s.push(sn);
			tmp = tmp->m_right;
			left = 0;
		}
	}
	
	if(1 == left){
		p->m_left = tn;
		StackNode sn(tn, Left);
		s.push(sn);		
	}else{
		p->m_right = tn;
		StackNode sn(tn, Right);
		s.push(sn);		
	}
	
	// check if need rotate
	StackNode child = s.top();
	StackNode current(NULL, Left);
	StackNode parent(NULL, Left);
	
	s.pop();
	StackNode stackTop;
	int bf = 1;
	while(!s.empty()){
		stackTop = s.top();
		//update height
		stackTop.m_tn->m_height = max(child.m_tn->m_height+1,stackTop.m_tn->m_height);
		
		current = stackTop;
		TreeNode* t = stackTop.m_tn;
		int leftheight, rightheight;
		if(t->m_left == NULL){
			leftheight = -1;
		}else{
			leftheight = t->m_left->m_height;
		}
		if(t->m_right == NULL){
			rightheight = -1;
		}else{
			rightheight = t->m_right->m_height;
		}
		
		if(abs(leftheight - rightheight) > 1){
			cout << "current node:" << stackTop.m_tn->m_val << ", left h:" << leftheight << ",right h:" << rightheight << endl; 
			bf = 0;
			s.pop();
			break;
		}		
		child = stackTop;
		s.pop();
	}
	
	if(!s.empty()){		
		parent = s.top(); 
		parent.m_tn->m_height = max(current.m_tn->m_height+1,parent.m_tn->m_height);
		s.pop();
	}
	
	// need rotate
	if(0 == bf){
		TreeNode* p = root;
		if(current.m_dir == Left){
			if(child.m_dir == Left){			
				p = rotateAvl(current.m_tn, parent.m_tn, parent.m_dir, Left);
			}else{
				p = rotateAvl(child.m_tn, current.m_tn, current.m_dir, Right);
				p = rotateAvl(current.m_tn, parent.m_tn, parent.m_dir, Left);
				
			}
		}else{
			if(child.m_dir == Left){
				p = rotateAvl(child.m_tn, current.m_tn, current.m_dir, Left);
				printTree(root);
				p = rotateAvl(current.m_tn, parent.m_tn, parent.m_dir, Right);
			}else{
				p = rotateAvl(current.m_tn, parent.m_tn, parent.m_dir, Right);
			}
		}
		if(parent.m_tn == NULL){
			root = p;
		}
	}	
	
	child = parent;
	while(!s.empty()){
		parent = s.top();
		s.pop();		
		parent.m_tn->m_height = max(child.m_tn->m_height+1,parent.m_tn->m_height);
		child = parent;
	}
	return root;
}

int main(){
	printTree(root);
	TreeNode* t1 = new TreeNode(6);
	TreeNode* t2 = new TreeNode(4);
	TreeNode* t3 = new TreeNode(12);
	TreeNode* t4 = new TreeNode(11);
	root = insertAvl(root, t1);
	root = insertAvl(root, t2);
	root = insertAvl(root, t3);
	root = insertAvl(root, t4);
	return 0;
}

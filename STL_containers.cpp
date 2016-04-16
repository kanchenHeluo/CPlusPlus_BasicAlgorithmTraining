#include <iostream>
#include <vector>
#include <deque> 
#include <queue>
#include <map>
#include <ext/hash_map> 
#include <algorithm>
#include <cstring>
using namespace std;
using namespace __gnu_cxx;

//cmp
bool cmp(const int a, const int b){
	return a < b;
}

//internal as array, copy&reallocate
void vectorDemo(){
	cout << "vector demo:" << endl;
	vector<int> v(5,0);
	v.push_back(1);
	cout << "vector size & element:" << v.size() << "," << v[v.size()-1] << endl;
	v.pop_back();
	cout << "vector size & element:" << v.size() << "," << v[v.size()-1] << endl;	
	
	string str = "hello world";
	vector<char> s;
	s.resize(str.length());
	s.assign(str.begin(), str.end());
	cout << "iter result:" << endl;
	for(vector<char>::iterator iter = s.begin(); iter != s.end(); iter++){
		cout << *iter << ",";
	}
	cout << endl;

}

//front-end queue, similar with vector, but not successive in memory; index fetch slower than vector, but front-end insert faster than vector--no need copy 
void dequeDemo(){
	cout << "deque demo:" << endl;
	deque<int> dq1(5,0);
	dq1.push_back(1);
	dq1.push_back(2);
	dq1.push_front(-1);
	dq1.push_front(-2);
	dq1.pop_back();
	dq1.pop_front();
	
	dq1.insert(dq1.begin()+1, 999);
	for(deque<int>::iterator iter=dq1.begin(); iter!=dq1.end(); iter++){
		cout << *iter << ",";
	}
	cout << endl;
	cout << "front:" << dq1.front() << endl;
	cout << "back:" << dq1.back() << endl;
}

struct Node{
	int val;
	Node(int v):val(v) {}
	friend bool operator< (Node n1, Node n2){
		return n1.val < n2.val;
	}
};
//internal as heap
void priorityQueueDemo(){
	cout << "priority queue demo:" << endl;
	priority_queue<Node> q;
	Node n1(3);
	Node n2(2);
	Node n3(1);
	Node n4(4);
	q.push(n1);
	q.push(n2);
	q.push(n3);
	q.push(n4);
	while(q.size() != 0){
		cout << q.top().val << ",";
		q.pop();
	}
	cout << endl;
}

//map: RBTree, O(log(n))


//hash_map: hash_table, O(1) 
class MapNode{
public:
	int val;
	MapNode(){} //default
	MapNode(int v){
		val = v;
	}
	
	bool operator == (const MapNode& o) const {
		return val == o.val;
	}
};

class Key_t {
	public:
	size_t operator () (const MapNode& t) const {
		return t.val;
	}
};
void mapDemo(){
	cout << "map:" << endl;
	map<string, int> m;
	m["a"] = 1;
	m.insert(make_pair<string, int>("b",2));
	cout << m.size() << endl;
	map<string, int>::iterator iter;
	iter = m.find("b");
	if(iter!=m.end()){
		cout << iter->first << ":" << iter->second << endl;
	}
}

void hashmapDemo(){
	cout << "hash map:" << endl;
	hash_map<MapNode, int, Key_t> m;
	MapNode n1(1), n2(2);
	m.insert(make_pair(n1,1));
	typedef pair<MapNode, int> MapPair;
	m.insert(MapPair(n2,2));
	hash_map<MapNode, int, Key_t>::iterator iter;
	cout << m.size() << endl;
	for(iter=m.begin(); iter!=m.end(); iter++){
		cout << iter->first.val << "," << iter->second << endl;
	}

	iter = m.find(n1);
	if(iter!=m.end()){
		cout << iter->first.val << ":" << iter->second << endl;
	}
}

int main(){	
	int arr[4] = {2,1,5,4};
	sort(arr, arr+4, cmp);
	for(int i=0; i<4; i++){
		cout << arr[i] << ",";
	}
	cout << endl;
	mapDemo();
	hashmapDemo();
	vectorDemo();
	dequeDemo();
	priorityQueueDemo();

	return 0;
}

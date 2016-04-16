#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#define MAX 2100000000
using namespace std;

struct Edge{
	int x;
	int y;
	int weight;
	Edge(int xx, int yy, int w): x(xx), y(yy), weight(w){}
};

struct Graph{
	vector<Edge> edges;
	int vertex;
	Graph(vector<Edge> es, int v): edges(es), vertex(v) {}
};

//no negative weight, O(ElogV)
struct Node{
	int y;
	int dist;
	friend bool operator< (Node n1, Node n2){
		return n1.dist > n2.dist;
	}
};

//no negative weight, O(v^2)
int* djs(int** G, int len, int idx){
	int* path = new int[len];
	int* visited = new int[len];
	for(int i=0; i<len; i++){
		path[i] = G[idx][i];
		visited[i] = 0;
	}
	path[idx] = 0;
	visited[idx] = 1;
	
	int i=idx;
	while(i!=-1){
		//update
		for(int j=0; j<len; j++){
			if(!visited[j] && path[j] > path[i]+G[i][j]){
				path[j] = path[i]+G[i][j];
			}
		}
		//min
		int min = MAX+1000000, min_idx = -1;
		for(int j=0; j<len; j++){
			if(!visited[j] && min > path[j]){
				min = path[j];
				min_idx = j; 
			}
		}
		visited[min_idx] = 1;
		i = min_idx;
	}
	
	return path;
}

//no negative weight, O(ElogV)
int* djs_min_heap(int** G, int len, int idx){
	priority_queue<Node> h;
	Node nodes[len];

	int* path = new int[len];
	int* visited = new int[len];
	memset(visited, 0, sizeof(int)*len);
	
	path[idx] = 0;
	visited[idx] = 1;

	for(int i=0; i<len; i++){
		if(i!=idx){
			nodes[i].dist = G[idx][i];
			nodes[i].y = i;
			h.push(nodes[i]);	
		}
	}

	while(h.size()>0){
		Node n = h.top();	
		while(h.size()!=0 && visited[n.y]){
			h.pop();
			n = h.top();
		}
		if(h.size()==0){
			break;
		}
		path[n.y] = n.dist;
		visited[n.y] = 1;
		int k = n.y;
		h.pop();
		
		//update
		for(int j=0; j<len; j++){
			if(!visited[j] && nodes[j].dist > nodes[k].dist + G[k][j]){
				nodes[j].dist = nodes[k].dist + G[k][j];
				h.push(nodes[j]);
			}
		}
	}
	return path;
}

//no negative weight, O(v^3)
int** floyd(int** G, int len){
	int** path = new int*[len];
	for(int i=0; i<len; i++){
		path[i] = new int[len];
		for(int j=0; j<len; j++){
			path[i][j] = G[i][j];
		}
	}
	
	for(int k=0; k<len; k++){
		for(int i=0; i<len; i++){
			for(int j=0; j<len; j++){
				if( path[i][j]> path[i][k] + path[k][j]){
					path[i][j] = path[i][k] + path[k][j];
				}
			}
		}
	}
	
	return path;
}

//negative weight, O(E*V)
int* bellman_ford(Graph nG, int idx){
	int* path = new int[nG.vertex];
	for(int i=0; i<nG.vertex; i++){
		path[i] = MAX;
	}
	
	for(int i=0; i<nG.edges.size(); i++){
		if(nG.edges[i].x == idx){
			path[nG.edges[i].y] = nG.edges[i].weight;
		}
	}
	path[idx] = 0;
	
	bool flag;
	for(int i=0; i<nG.vertex; i++){
		flag = false;
		for(int j=0; j<nG.edges.size(); j++){
			int u = nG.edges[j].x, v = nG.edges[j].y;	
			//cout << "compare u="<<u << " with v=" << v << ", with weight=" << nG.edges[j].weight << ",path[u]=" << path[u] << ",path[v]" << path[v] << endl;
			if( path[v] > path[u] + nG.edges[j].weight){
				path[v] = path[u] + nG.edges[j].weight;
				flag = true;
			}
		
		}
		if(!flag){
			break;
		}
	}
	
	if(flag){
		cout << "negative loop existed!" << endl;
		return NULL; 
	}
	
	return path;
}

int* spfa(Graph nG, int idx){
	deque<int> que;
	que.push_back(idx);
	
	int* cnt = new int[nG.vertex];
	int* flag = new int[nG.vertex];
	memset(cnt, 0, sizeof(int)*nG.vertex);
	memset(flag, 0, sizeof(int)*nG.vertex);
	
	int* path = new int[nG.vertex];
	for(int i=0; i<nG.vertex; i++){
		path[i] = MAX;
		
	}
	flag[idx] = 1;
	cnt[idx]++;
	path[idx] = 0;
	
	for(int i=0; i<nG.edges.size(); i++){
		if(nG.edges[i].x == idx){
			path[nG.edges[i].y] = nG.edges[i].weight;
			que.push_back(nG.edges[i].y);
			cnt[nG.edges[i].y]++;
			flag[nG.edges[i].y] = 1;
		}
	}

	
	while(que.size()>0){
		int n = que.front();
		flag[n] = 0;
		que.pop_front();
		//update
		for(int i=0; i<nG.edges.size(); i++){
			int u=nG.edges[i].x, v = nG.edges[i].y;
			if(u==n && path[v] > path[u] + nG.edges[i].weight ){
				path[v] = path[u] + nG.edges[i].weight;
				cnt[v] ++;
				flag[v] = 1;
				if(cnt[v] > nG.vertex){
					cout << "negative loop existed." << endl;
					return NULL;
				}
				if(!flag[v]){
					if(que.size() > 0 && path[v] < path[que.front()]){
						que.push_front(v);					
					}else{
						que.push_back(v);					
					}
					
				}
			}
		}
		
	}
	return path;
}

int main(){
	vector<Edge> edges;
	Edge e1(0,1,2);
	Edge e2(0,2,3);
	Edge e3(1,2,-1);
	Edge e4(2,1,1);
	Edge e5(2,3,1);
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	edges.push_back(e4);
	edges.push_back(e5);
	
	Graph nG(edges, 4);
	
	int* sp = spfa(nG, 0);
	cout << "spfa:"<< endl;
	if(sp!=NULL){
		for(int i=0; i<4; i++){
			cout << sp[i] << ",";
		}
	}
	cout << endl;
	
	
	
	int* bp = bellman_ford(nG, 0);
	cout << "bellman-ford:"<< endl;
	if(bp!=NULL){
		for(int i=0; i<4; i++){
			cout << bp[i] << ",";
		}
	}
	cout << endl;
	
	int** G;
	G = new int*[4];
	for(int i=0; i<4; i++){
		G[i] = new int[4];
		for(int j=0; j<4; j++){
			if(i==j){
				G[i][j] = 0;
			}else{
				G[i][j] = MAX;
			}
		}
	}
	G[0][1] = 3;
	G[0][2] = 7;
	G[0][3] = 1;
	G[1][2] = 2;
	G[1][3] = 1;
	G[2][0] = 3;
	G[2][3] = 8;
	G[3][0] = 1;
	G[3][1] = 1;
	G[3][2] = 1;
	
	cout << "simple djs:" << endl;
	int* sdp = djs(G, 4, 0);
	for(int i=0; i<4; i++){
		cout << sdp[i] << ",";
	}
	cout << endl;
	
	cout << "djs with min heap:" << endl;
	int* dp = djs_min_heap(G, 4, 0);
	for(int i=0; i<4; i++){
		cout << dp[i] << ",";
	}
	cout << endl;
	
	cout << "floyd:" << endl;
	int** fp = floyd(G, 4);
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			cout << fp[i][j] << ",";
		}
		cout << endl;
	}
	
	return 0;

}

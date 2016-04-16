#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#define MAX 2100000000
using namespace std;

struct Edge{
    int x;
    int y;
    int weight;
    Edge(int i, int j, int w):x(i), y(j), weight(w){}
};
struct Graph{
    int vertex;
    vector<Edge> edges;
    Graph(int v, vector<Edge> es): vertex(v), edges(es){}
};

//prim
int prim(Graph g){
    int result = 0;
    int* visited = new int[g.vertex];
    memset(visited, 0, g.vertex*sizeof(int));
    int* p = new int[g.vertex];
    for(int i=0; i<g.vertex; i++){
        p[i] = MAX;
    }
    
    int min=0, min_idx=0, cnt=0;
    while(min_idx!=-1){
        visited[min_idx] = 1;
        result += min;
        cnt++;
        
        for(int i=0; i<g.edges.size(); i++){
            if(!visited[g.edges[i].y] && g.edges[i].x == min_idx && p[g.edges[i].y] > g.edges[i].weight){
                p[g.edges[i].y] = g.edges[i].weight;
            }
        }
        min_idx = -1;
        min = MAX;
       for(int i=0; i<g.vertex; i++){
            if(!visited[i] && min > p[i]){
                min = p[i];
                min_idx = i;
            }
        }
   
    }
    if(cnt < g.vertex){
        result = 0;
    }
    return result; 
}

//kruskal
int* p = NULL;
bool cmp(const Edge e1, const Edge e2){
    return e1.weight < e2.weight;
}

int find(int u){
    if(u == p[u]){
        return u;
    }
    p[u] = find(p[u]);
    return p[u];
}

int kruskal(Graph g){
    int result = 0;
    p = new int[g.vertex];
    for(int i=0; i<g.vertex; i++){
        p[i] = i;
    }
    
    //sort edges
    sort(g.edges.begin(), g.edges.end(), cmp);
    
    int cnt = 0;
    for(int i=0; i<g.edges.size(); i++){
        int u=g.edges[i].x, v = g.edges[i].y;
        int up = find(u), vp = find(v);
        if(up != vp){
            p[up] = vp;
            result += g.edges[i].weight;
            cnt++;
        }
    }
    if(cnt < g.vertex-1){
        result = 0;
    }
    delete p;
    return result;
}

int main(){
    Edge e1(0,1,1);
//    Edge e2(0,2,2);
    Edge e3(0,3,5);
 //   Edge e4(1,2,4);
    Edge e5(1,3,3);
   // Edge e6(2,3,1);

    vector<Edge> edges;
    edges.push_back(e1);
    //edges.push_back(e2);
    edges.push_back(e3);
    //edges.push_back(e4);
    edges.push_back(e5);
    //edges.push_back(e6);
    
    Graph g(4, edges);

    cout << kruskal(g) << endl;
    cout << prim(g) << endl;
    return 0;
}

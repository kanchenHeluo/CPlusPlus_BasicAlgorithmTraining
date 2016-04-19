#include <iostream>
#include <queue>
#include <string.h>
#define INF 0x7FFFFFFF
using namespace std;

int G[6][6] = {{0,1,0,0,0,0},
                   {1,0,1,0,0,0},
                   {0,1,0,1,0,0},
                   {0,0,1,0,1,0},
                   {0,0,0,1,0,1},
                   {0,0,0,0,1,0}};

//Warshall: O(n^3)
int warshall(){
    int f[6][6];
    memset(f,0,sizeof(int)*36);

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            f[i][j] = G[i][j];
        }
    }
    for(int i=0; i<6; i++){
        f[i][i] = 1;
    }
    for(int k=0; k<6;k++){
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                if(f[i][j] == 0 && f[i][k] > 0 && f[k][j] > 0){
                    f[i][j] = 1;
                }
            }
        }
    }

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(f[i][j]==0){
                return 0;
            }
        }
    }
    return 1;
}

//union-find
int* p = new int[6];
int union_find(int x){
    if(x == p[x]){
        return x;
    }
    p[x] = union_find(p[x]);
    return p[x];
}

int union_f(){
    for(int i=0; i<6; i++){
        p[i] = i;
    }

    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            if(G[i][j] > 0){
                int u = union_find(i), v = union_find(j);
                if(u!=v){
                    p[u] = v;
                }
            }
        }
    }

    int par = union_find(0);
    for(int i=1; i<6; i++){
        if(par != union_find(i)){
            return 0;
        }
    }
    return 1;
}


//maximum network flow: Edmonds-karp
/*
int G[6][6] = {{0,1,0,0,1,0},
                   {0,0,1,0,0,1},
                   {0,0,0,1,0,0},
                   {0,0,0,0,0,0},
                   {0,0,1,0,0,0},
                   {0,0,0,1,0,0}};
*/
int bfs(int len, int s, int e, int* &path){
    queue<int> q;
    int* flow = new int[len];
    memset(flow, 0, sizeof(int)*len);
    flow[s] = INF;
    q.push(s);
    while(!q.empty()){
        int idx = q.front();
        q.pop();
        if(idx == e){
            break;
        }
        for(int i=0; i<len; i++){
            if(i!=s && path[i]==-1 && G[idx][i]> 0){
                q.push(i);
                path[i] = idx;
                flow[i] = G[idx][i] > flow[idx] ? flow[idx] : G[idx][i];
            }
        }
    }
    if(path[e] == -1){return -1;}
    return flow[e];
}

//edmonds-karp
int Edmonds_Karp(int len, int s, int e){
    int result = 0;
    int* path = new int[len];

    memset(path, -1, sizeof(int)*len);
    int f = bfs(len, s, e, path);
    
    while(f != -1 ){
        result += f;
        int next = e;
        while(next!=s){
            int pre = path[next];
            G[next][pre] += f;
            G[pre][next] -= f;
            next = pre;
        }
        memset(path, -1, sizeof(int)*len);
        f = bfs(len, s, e, path);
    }
    return result;
}

//Xiongyali Edmonds: O(VE)
int used[3], linked[3];
/*
int G[3][3]  = {{1,1,0},{1,0,1},{0,0,1}};  
*/

int find(int pos){
    for(int i=0; i<3; i++){
        if(G[pos][i] && !used[i]){
            used[i] = 1;
            if(linked[i]==-1 || find(linked[i])){
                linked[i] = pos;
                return 1;
            }
        }
    }
    return 0;
}

int xylEdmonds(){
    int result = 0;
    memset(linked, -1, sizeof(int)*3);
    for(int i=0; i<3; i++){
        memset(used, 0, sizeof(int)*3);
        result += find(i);
    }
    return result;
}

int main(){
    /*
    cout << "Xiong Ya Li Algorithm, maximum match:" << endl;
    cout << xylEdmonds()<<endl;
    
    cout << "Maximum network flow:" << endl;
    cout << Edmonds_Karp(6,0,3) << endl;
    */
    cout << "judge graph connectivity:" << endl;
    cout << warshall() << endl;
    cout << union_f() << endl;
    return 0;
}

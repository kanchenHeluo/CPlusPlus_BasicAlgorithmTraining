#include <iostream>
#include <string.h>
#define NEG_INF 0xFFFFFFFE
using namespace std;


int V = 10;
int goods_weight[4] = {2,3,4,6};
int goods_value[4] = {1,5,3,9};
int n = 4;

int pack_maximum(){
    int* f = new int[V+1];
    int result = 0;
    
    memset(f,0,sizeof(int)*(V+1));

    for(int i=0; i<n; i++){
        for(int v = V; v>=goods_weight[i]; v--){
            f[v] = f[v] > f[v-goods_weight[i]] + goods_value[i] ? f[v] : f[v-goods_weight[i]] + goods_value[i];
        }
    }

    result = f[V];
    delete[] f;
    return result;
}

int fullpack_maximum(){
    int* f = new int[V];
    int result = 0;
 
    for(int i=0; i<=V; i++){
        f[i] = NEG_INF;
    }
    f[0] = 0;
    for(int i=0; i<n; i++){
        for(int v = V; v>=goods_weight[i]; v--){
            if(f[v-goods_weight[i]]!=NEG_INF){
                f[v] = f[v] > f[v-goods_weight[i]] + goods_value[i] ? f[v] : f[v-goods_weight[i]] + goods_value[i];
            }
        }
    }

    result = f[V];
    delete[] f;
    return result;
}

int multipack_maximum(){
     int* f = new int[V+1];
    int result = 0;
 
    memset(f,0,sizeof(int)*(V+1));

    for(int i=0; i<n; i++){
        for(int v = goods_weight[i]; v<=V; v++){
            f[v] = f[v] > f[v-goods_weight[i]] + goods_value[i] ? f[v] : f[v-goods_weight[i]] + goods_value[i];
        }
    }

    result = f[V];
    delete[] f;
    return result;
}

int main(){
    cout << "pack:" << endl;
    cout << pack_maximum() << endl;

    cout << "full pack:" << endl;
    cout << fullpack_maximum() << endl;

    cout << "multi pack:" << endl;
    cout << multipack_maximum() << endl;

    return 0;
}

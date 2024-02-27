#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <stdio.h>
using namespace std;
#define INF 0x3f3f3f3f

struct edge{
    public:
    int x, y, w;
    edge(int x, int y, int w){
        this->x = x;
        this->y = y;
        this->w = w;
    }
};

struct Graph{
    public:
    int V;//number of vertex
    long long sum;
    vector<int> adj;//vertex
    vector<int> cost;
    vector<edge> spec;//special offers
    Graph(int V){
        this->V = V;
        // adj.resize(V);
        for(int i = 0 ; i < V ; i++){
            adj.push_back(i);
        }
        
        cost = vector<int> (V, 0);
        sum = 0;
    }
    int find(int x) {
        if (x != adj[x]) {
            return adj[x] = find(adj[x]);
        }
        else return x;
    }

    void merge(int x, int y){
        adj[find(x)] = find(y);
    }

    static bool cmp(edge& a, edge& b) {
        return (a.w != b.w) ? (a.w < b.w) : (a.x < b.x);
    }



    void Kruskal(){
        sort(spec.begin(), spec.end(), cmp);
        // for(int i=0; i<spec.size();i++){
        //     printf("%d", spec[i]);//spec[i];
        // }
        for (int i = 0, j = 0; i < V-1 && j < spec.size(); ++j){
            if (find(spec[j].x) == find(spec[j].y)) continue;
            merge(spec[j].x, spec[j].y);
            sum += spec[j].w;
            // cout<<sum;
            i++;    
        }

        cout << sum << endl;
    }
};


    // void Kruskal() {


    //     sort(spec.begin(), spec.end(), [](const edge &a, const edge &b) {
    //         if(a.w!=b.w) return a.w < b.w;
    //         else return a.x<b.x;
    //     });

    //     for (int i = 0, j = 0; i < V-1 && j < spec.size(); ++j){
    //         if (find(spec[j].x) == find(spec[j].x)) continue;
    //         merge(spec[j].x, spec[j].x);
    //         sum += spec[j].w;
    //         i++;    
    //     }


int main(){

    int Q; 
    cin >> Q;
    for(int i=0; i<Q; i++){
        int n, m; 
        cin >> n >> m;
        Graph g(n);
        int min = INT_MAX;
        int min_index = -1;
        for(int i = 0 ; i < n ; i++){
            // cout<<"n";
            int tmp;
            cin >> tmp;
            g.cost[i] = tmp;
            if(min > g.cost[i]) {
                min = g.cost[i];
                min_index = i;
            }
        }

        while(m--){

            // cout<<m;
            int x, y, pay;
            cin >> x >> y >> pay;
            x--; y--;
            if(pay > g.cost[x] + g.cost[y] ) continue;
            g.spec.push_back(edge(x, y, pay));
        }
        for(int i = 0 ; i < n ; i++){
            // cout<<n;
            if(min_index == i) continue;
            g.spec.push_back(edge(min_index, i, min + g.cost[i]));
        }
        g.Kruskal();
    }
    return 0;
}
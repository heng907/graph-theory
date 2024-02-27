#include <bits/stdc++.h>
using namespace std;

void addedge(vector<int> adj[], int u, int v){
   adj[u].push_back(v);
   adj[v].push_back(u);
}
bool isBipartite(vector<int> adj[], int v, vector<bool>& visited, vector<int>& color){
   for (int u : adj[v]) {
      if (visited[u] == false) {
         visited[u] = true;
         color[u] = !color[v];
         if (!isBipartite(adj, u, visited, color))
            return false;
      }
      else if (color[u] == color[v])
      return false;
   }
   return true;
}
int main() {
   int n,m;
   cin>>n>>m;
   if(n<=1||m<=1||n>200000||m>200000)
   {
       return 0;
   }
   else
   {
        vector<int> adj_list[n+1];
        vector<bool> visited(n+1);
        vector<int> color(n+1);

        for(int i=0;i<m;i++)
        {
            int a,b;
            cin>>a>>b;
            addedge(adj_list,a,b);
        }

        visited[1] = true;
        color[1] = 0;
        if(isBipartite(adj_list, 1, visited, color))
        {
            cout<<"Yes";
        }
        else
            cout<<"No";
   }
}

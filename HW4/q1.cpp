#include <bits/stdc++.h>
using namespace std;
void APUtil(vector<int> adj[], int u, bool visited[],
			int disc[], int low[], int& time, int parent,
			bool isAP[])
{
	// Count of children in DFS Tree
	int children = 0;

	// Mark the current node as visited
	visited[u] = true;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;

	// Go through all vertices adjacent to this
	for (auto v : adj[u]) {
		// If v is not visited yet, then make it a child of u
		// in DFS tree and recur for it
		if (!visited[v]) {
			children++;
			APUtil(adj, v, visited, disc, low, time, u, isAP);

			// Check if the subtree rooted with v has
			// a connection to one of the ancestors of u
			low[u] = min(low[u], low[v]);

			// If u is not root and low value of one of
			// its child is more than discovery value of u.
			if (parent != -1 && low[v] >= disc[u])
				isAP[u] = true;
		}

		// Update low value of u for parent function calls.
		else if (v != parent)
			low[u] = min(low[u], disc[v]);
	}

	// If u is root of DFS tree and has two or more children.
	if (parent == -1 && children > 1)
		isAP[u] = true;
}

void AP(vector<int> adj[], int V)
{
	int disc[V+1] = { 0 };
	int low[V+1];
	bool visited[V+1] = { false };
	bool isAP[V+1] = { false };
	int time = 0, par = -1;
	// Adding this loop so that the
	// code works even if we are given
	// disconnected graph
	for (int u = 0; u <= V; u++)
	{	
		if (!visited[u])
		{
			APUtil(adj, u, visited, disc, low, time, par, isAP);
		}
		// cout<<"test"<<endl;
	}
	// Printing the number and APs
	int cnt = 0;
  for (int u = 0; u <= V; u++){
    if (isAP[u] == true){
      cnt=cnt+1;
    }
		// cout<<"test"<<endl;
  }
  cout<<cnt<<endl;
  for (int u = 0; u <= V; u++){
		if (isAP[u] == true){
			cout << u << " ";
		}
		// cout<<"test"<<endl;
	}
}

// Utility function to add an edge
void addEdge(vector<int> adj[], int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

int main()
{

  int n, m;
  cin>>n>>m;//n is the vertices, m is the edge

  if(n<1||n>100000||m<1||m>100000){
    return 0;
  }
  else{
    vector<int> adj[n+1];
    for(int i=0; i<m; i++){
      int u, v;
      cin>>u>>v;
      addEdge(adj, u, v);
    }

    AP(adj,n);
	  return 0;
  }

}

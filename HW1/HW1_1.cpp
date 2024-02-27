#include<bits/stdc++.h>

using namespace std;

int main()
{
    int n,m;
    cin>>n>>m;
    if(n>1000||(m<0&&m<=n*n))
    {
           return 0;
    }

    int adj[n+1][n+1];
    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<n+1;j++)
        {
            adj[i][j]=0;
        }

    }
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        if(u<1||v<1||u>n||v>n||(w>1e+9)||w<-(1e+9))
        {
            return 0;
        }
        adj[u][v]=1*w;
    }


    int temp_out[n+1]={0};
    for(int i=1;i<n+1;i++)
    {
        int count=0;
        for(int j=1;j<n+1;j++)
        {
            if (adj[i][j]!=0)
            {
                count++;
            }
            temp_out[i]=count;
        }
    }

    int temp_in[n+1]={0};
    for(int i=1;i<n+1;i++)
    {
        int count_=0;
        for(int j=1;j<n+1;j++)
        {
            if(adj[j][i]!=0)
            {
                count_++;
            }
            temp_in[i]=count_;
        }
    }

    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<n+1;j++)
        {
            cout<<adj[i][j]<<" ";
        }
        cout<<"\n";
    }

    for(int i=1;i<n+1;i++)
    {
        cout<<temp_in[i]<<" "<<temp_out[i]<<"\n";
    }

}

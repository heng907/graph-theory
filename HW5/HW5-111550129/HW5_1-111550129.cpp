#include <bits/stdc++.h>

using namespace std;

bool ans = true;
bool e[18][18];
int deg[18];
int n,m;
bool k33(){
    vector<int> is_end;
    for(int i = 1 ;i<=n;i++){
        if(deg[i]==3)is_end.push_back(i);
    }
    if(is_end.size()!=6)return false;
    while(1){
        bool flag = true;
        for(int i =1;i<=n;i++){
            if(deg[i]==2){
                flag = false;
                deg[i]=0;
                int a = -1,b;
                for(int j =1;j<=n;j++){
                    if(e[i][j]){
                        if(a==-1)a = j;
                        else b = j;
                    }
                }
                e[i][b] = false;e[i][a] = false;e[a][i] = false;e[b][i] = false;
                e[a][b] = true;e[b][a]  =true;
            }
        }
        if(flag)break;
    }
    vector<int> is_down;
    vector<int> is_up;
    is_up.push_back(is_end[0]);
    for(int i = 1 ;i<=5;i++){
        if(e[is_end[0]][is_end[i]])is_down.push_back(is_end[i]);
        else is_up.push_back(is_end[i]);
    }
    if(is_up.size()!=3||is_down.size()!=3)return false;
    int temp = 0;
    for(int i :is_up){
        for(int j:is_down){
            if(e[i][j])temp++;
        }
    }
    if(temp==9)return true;
    return false;
}
bool k5(){
    vector<int> is_end;
    for(int i = 1 ;i<=n;i++){
        if(deg[i]==4)is_end.push_back(i);
    }
    if(is_end.size()!=5)return false;
    while(1){
        bool flag = true;
        for(int i =1;i<=n;i++){
            if(deg[i]==2){
                flag = false;
                deg[i]=0;
                int a = -1,b;
                for(int j =1;j<=n;j++){
                    if(e[i][j]){
                        if(a==-1)a = j;
                        else b = j;
                    }
                }
                e[i][b] = false;e[i][a] = false;e[a][i] = false;e[b][i] = false;
                e[a][b] = true;e[b][a]  =true;
            }
        }
        if(flag)break;
    }
    int temp = 0;
    for(int i =0;i<5;i++){
        for(int j =0;j<5;j++){
            if(e[is_end[i]][is_end[j]]){
                temp++;
            }
        }
    }
    if(temp==20)return true;
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int p = 1;
    cin >> p;
    for(int i=0; i<p; i++)
    {
		ans = true;
		cin >> n >> m;
		vector<vector<int>> edge(m);
		for (int i = 0; i < m; i++)
		{
			int a, b;
			cin >> edge[i].first >> edge[i].second;
		}
		
		for(int i =1;i<(1<<m);i++){
			memset(e,false,sizeof(e));
			memset(deg,0,sizeof(deg));
				for(int j = 0; j < m; j++){
					if((i>> j) & 1){
						int a= edge[j].first;
						int b= edge[j].second;
						e[a][b] = true;
						deg[a]++;
						e[b][a] = true;
						deg[b]++;
					}
				}
				if(k5()||k33()){
					cout <<"No\n";
				}
		
		}
		cout << "Yes\n";
		}
}
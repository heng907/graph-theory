#include <bits/stdc++.h>

using namespace std;
using std::cout;
using std::endl;
using std::string;

bool length_cmp(string&a, string&b){
    if(a.length() == b.length()){
        for(int i = 0 ; i < a.length() ; i++){
            if(a[i] != b[i]) return a[i] > b[i];
        }
    }
    return a.length() > b.length();
}

string string_cmp(string &a, string &b){
    if(a.size() < b.size() ) return a;
    if(b.size() < a.size() ) return b;
    for(int i = 0 ; i < a.size() ;i++){
        if(a[i] < b[i]) return a;
        if(b[i] < a[i]) return b;
    }
    return a;//if the strings are the same
}

string string_vec_cmp(vector<string> &A){
    string smallest = A[0];
    for(int i = 1 ; i < A.size() ;i++){
        smallest = string_cmp(smallest, A[i]);
    }
    return smallest;
}

void Print(vector<vector<int>> v){
    for(int i = 0 ; i < v.size() ; i++){
        for(int j = 0 ; j < v[i].size() ; j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}
void Preprocess(vector<vector<int>> &cost, vector<string> &A, int n){
    for(int i = 0 ; i < n ; i++){// preprocess the cost of each word when string a is followed by string b.
        for(int j = 0 ; j < n ; j++){
            cost[i][j] = A[j].length();//cost[i][j] means i + j needs how many additional words.
            for(int k = 1 ; k <= min(A[i].length(), A[j].length()) ; k++){
                if(A[i].substr(A[i].size() - k) == A[j].substr(0, k)){
                    cost[i][j] = A[j].length() - k;
                }
            }
        }
    }
    return;
}

void init(vector<vector<int>> &dp, vector<string> &A, int n){
    for(int i = 0 ; i < n ; i++){//initialize
        dp[1 << i][i] = A[i].length();//use 2^i to store the status, dp[1 << i][i] means node that is start in 2^i position, and stop at i.
    }
}

string findSolution1(vector<string> &A, vector<vector<int>> &cost, vector<vector<int>> &dp, vector<vector<int>> &path, int n){
    init(dp, A, n);
    //dp[status][end] means the length of the string from status to node "end". like status "1111, 1" means no visited node, and the end node is 1, status"1011, 1" means node 2 has been visited, and end node is 1.
    for(int status = 1; status < (1 << n); status++){//every status
        for(int end = 0 ; end < n; end++){//every end node
            if(!(status & (1 << end))) continue;//if 2^end postition of status is not 1, means the status has been used, so we skip it.
            int prev = status - (1 << end);//make 2^end position of status become 0, means we get the previous status.

            for(int mid = 0; mid < n ; mid++){
                if(dp[prev][mid] + cost[mid][end] < dp[status][end]){//if the cost is lower.
                    dp[status][end] = dp[prev][mid] + cost[mid][end];
                    path[status][end] = mid;//save the path
                }
                if(dp[prev][mid] + cost[mid][end] == dp[status][end])
                    path[status][end] = mid;
            }

        }
    }

    vector<int> possible_ans_node;
    auto it = min_element(begin(dp.back()), end(dp.back()));//find the smallest length when the status is 11111(if n = 5).
    for(int i = 0 ; i < n ; i++){//find the same smallest length of the end node.
        if(dp[(1 << n) - 1][i] == *it){
            possible_ans_node.push_back(i);
        }
    }

    vector<string> possible_ans_string;
    //cout << "possible_ans_string.size(): " << possible_ans_string.size() << endl;
    for(int i = 0 ; i < possible_ans_node.size() ;i++){
        int status = (1 << n) - 1;
        string ans;
        while(status){
            int prev = path[status][possible_ans_node[i]];
            if(prev < 0) ans = A[possible_ans_node[i]] + ans;
            else ans = A[possible_ans_node[i]].substr(A[possible_ans_node[i]].length() - cost[prev][possible_ans_node[i]]) + ans;
            status &= ~(1 << possible_ans_node[i]); //get the previous status
            possible_ans_node[i] = prev;
        }
        possible_ans_string.push_back(ans);
    }
    return string_vec_cmp(possible_ans_string);
}

string shortestSuperstring(vector<string> &A){
    const int n = A.size();
    vector<vector<int>> cost = vector<vector<int>>(n, vector<int>(n));

    Preprocess(cost, A, n);
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX / 2));
    vector<vector<int>> path(1 << n, vector<int>(n, -1));

    string ans = findSolution1(A, cost, dp, path, n);
    return ans;
}

bool string_mergable(string &a, string &b){//a.size() >= b.size()
    if(a.find(b) != std::string::npos) return true;
    return false;
}


int main(){
    std :: ios :: sync_with_stdio ( false );
    std :: cin . tie ( 0 );
    //
    int n;
    cin >> n;
    if(n<1||n>18) return 0;
    vector<string> s(n, "");
    vector<bool> erasable(n, false);
    vector<string> processed_string;
    //
    for(int i = 0 ; i < n ; i++)
    {
        cin>>s[i];
    }
    sort(s.begin(), s.end(), length_cmp);

    for(int i = n - 1 ; i > 0 ; i--){
        for(int j = i - 1; j >= 0; j--){
            if(string_mergable(s[j], s[i])){
                erasable[i] = true;
                break;
            }
        }
    }
    for(int i = 0 ; i < erasable.size() ; i++)
    {
        if(erasable[i] == false) processed_string.push_back(s[i]);
    }
    std::sort(processed_string.begin(), processed_string.end());
    string ans = shortestSuperstring(processed_string);

    if(ans.size()>50) return 0;
    cout<<ans;
    return 0;
}


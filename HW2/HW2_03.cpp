#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> adja;//record adjacent

pair<int, int> findLengthOnLeaf(int current_node, vector<int> deg, int length){
    int pre_node = -1;
    while(deg[current_node] != 3)
    {
        int next_node;
        for(int i = 0 ; i < adja[current_node].size(); i++)
        {
            if(adja[current_node][i] == pre_node) continue;
            next_node = adja[current_node][i];
        }
        pre_node = current_node;
        current_node = next_node;
        length++;
    }
    for(int i = 0 ; i < adja[current_node].size() ; i++)
    {
        if(adja[current_node][i] == pre_node)
        {
            adja[current_node].erase(adja[current_node].begin() + i);
        }
    }
    return pair<int, int>(length, current_node);
}

bool find_key(vector<int> s, vector<int> e, deque<int> bone, vector<deque<int>> possible_key, vector<int> key){
    bool flg = false;
    for(int i = 0 ; i < 2 ; i++)
    {
        for(int j = 0 ; j < 2 ; j++)
        {
            possible_key[2 * i + j].push_front(s[i]);
            possible_key[2 * i + j].push_back(e[j]);
        }
    }
    for(int rev = 0 ; rev < 2 ; rev++)
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            if(rev == 1) reverse(possible_key[i].begin(), possible_key[i].end());
            if(possible_key[i].size() != key.size()) break;
            for(int j = 0 ; j < possible_key[i].size() ; j++)
            {
                if(possible_key[i][j] != key[j]) break;//find another possible key
                if(possible_key[i][j] == key[j] && j == possible_key[i].size() - 1) flg = true;//find the possible key
            }
        }
    }
    return flg;
}

int main(){
    int n;
    cin >> n;
    n -= 1;
    adja.resize(n + 1);
    vector<int> joint;
    vector<int> deg(n + 1, 0);
    while(n--){
        int tmp1, tmp2;
        cin >> tmp1 >> tmp2;

        adja[tmp1].push_back(tmp2);
        deg[tmp1]++;

        if(adja[tmp1].size() == 3)
        {
            joint.push_back(tmp1);
        }
        adja[tmp2].push_back(tmp1);
        deg[tmp2]++;
        if(adja[tmp2].size() == 3)
        {
            joint.push_back(tmp2);
        }

    }

    int m;
    cin >> m;
    vector<int> key;

    while(m--){
        int tmp;
        cin >> tmp;
        key.push_back(tmp);
    }
    //get all the length from the leaves to their nearest joint.

    vector<pair<int, int>> leaf;//first is length, second is the node that is along the leaf, first touched joint.
    for(int i = 0 ; i < deg.size() ; i++)
    {
        if(deg[i] == 1) leaf.push_back(findLengthOnLeaf(i, deg, 0));
    }

    //find start and end node, and their 2 leaves' length.

    int start_node = -1, end_node = -1;
    vector<int> start_length;
    vector<int>end_length;

    for(int i = 0 ; i < leaf.size() ;i++){
        for(int j = i + 1; j < leaf.size() ;j++){
            if(leaf[i].second == leaf[j].second) {
                if (start_node == -1) {
                    start_node = leaf[i].second;
                    start_length.push_back(leaf[i].first);
                    start_length.push_back(leaf[j].first);
                }
                else {
                    end_node = leaf[i].second;
                    end_length.push_back(leaf[i].first);
                    end_length.push_back(leaf[j].first);
                }
            }
        }
    }


    //find the bone key that is start from the start node and end with end node.

    bool flg = false;

    deque<int> bone;
    int cur_node = start_node;
    int pre_node = -1;
    while(cur_node != end_node){
        int next_node;

        for(int i = 0 ; i < adja[cur_node].size() ; i++){
            if(adja[cur_node][i] == pre_node) continue;
            next_node = adja[cur_node][i];
        }
        for(int i = 0 ; i < leaf.size() ; i++){
            if(leaf[i].second == cur_node && cur_node != start_node)
            {
                // don't pushback the start node
                bone.push_back(leaf[i].first);
            }
        }
        pre_node = cur_node;
        cur_node = next_node;
    }

    vector<deque<int>> possible_key(4, bone);
    flg = find_key(start_length, end_length, bone, possible_key, key);


    if(flg == true) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}

#include <bits/stdc++.h>

using namespace std;

int main(){
    int length;
    cin >> length;
    vector<int> arr(100000, 0);
    int temp;
    for(int i=0;i<length;i++){
        cin >> temp;
        arr[temp]++;
    }
    int num = 0;
    int ans = -1;
    for(int i=0;i<length;i++){
        if(arr[i] >= num){
            num = arr[i];
            ans = i;
        }
    }
    cout << ans << " " << num << endl;
}

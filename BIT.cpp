//https://codeforces.com/contest/961/problem/E
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int arr[N];
bool d[N];
int ep[N];
void add(int x, int val, int n){
    for(; x < N; x += x&-x) arr[x] += val;
}

int sum(int x){
    int ans = 0;
    for(; x > 0; x -= x&-x) ans += arr[x];
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<pair<int, int>> v;
    ll ans = 0;
    for(int i = 1; i <= n; ++i){
        cin >> ep[i];
        v.push_back({ep[i], i});
    }
    sort(v.begin(), v.end());
    int cur = 0;
    for(int i = 1; i <= n; ++i){
        if(!d[i]) ans += sum(i), d[i] = 1;
        add(1, 1, n);
        add(ep[i] + 1, -1, n);
        while(v[cur].first == i && cur < n){
            if(!d[v[cur].second]) ans += sum(v[cur].second), d[v[cur].second] = 1;
            //cout << cur << ' ' << sum(v[cur].second) << ' ' << v[cur].second << '\n';
            cur++;
        }
    }
    cout << ans << '\n';
}


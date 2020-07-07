#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> adj[N];
int ans[N];
int s[N];

void dfs(int x, int p){
    s[x] = 1;
    for(int y: adj[x]){
        if(y == p || ans[y]) continue;
        dfs(y, x);
        s[x] += s[y];
    }
}

int get(int x, int p, int sz){
    int mx = sz - s[x];
    for(int y: adj[x]){
        if(y == p || ans[y]) continue;
        int ctr = get(y, x, sz);
        if(ctr != -1) return ctr;
        mx = max(mx, s[y]);
    }
    if(mx <= sz / 2) return x;
    return -1;
}

void dcmp(int x, int id){
    dfs(x, -1);
    x = get(x, -1, s[x]);
    ans[x] = id;
    for(auto y: adj[x]){
        if(ans[y]) continue;
        dcmp(y, id + 1);
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int i = 1;i < n; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dcmp(1, 1);
    for(int i = 1; i <= n; ++i){
        cout << char('A' + ans[i] - 1) << ' ';
    }
}

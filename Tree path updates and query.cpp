//https://cses.fi/problemset/task/1136

#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
vector<int> g[N];
int in[N], out[N], _time, pa[N][18], dep[N];
int bit[2*N];
int ans[N];

void dfs(int x, int p){
    in[x] = ++_time;
    dep[x] = dep[p] + 1;
    pa[x][0] = p;
    for(int y: g[x]){
        if(y == p) continue;
        dfs(y, x);
    }
    out[x] = ++_time;
}

void build(int n){
    for(int i = 1; i < 18; ++i){
        for(int j = 1; j <= n; ++j){
            pa[j][i] = pa[pa[j][i-1]][i-1];
        }
    }
}

int lca(int x, int y, bool tmp){// tmp 1 -> dist
    if(dep[x] > dep[y]) swap(x, y);
    int ds = 0;
    for(int i = 17; i >= 0; --i){
        if(dep[x] <= dep[pa[y][i]]){
            y = pa[y][i];
            ds += (1<<i);
        }
    }
    if(x == y && !tmp) return x;
    else if(x == y && tmp) return ds;
    for(int i = 17; i >= 0; --i){
        if(pa[x][i] != pa[y][i]){
            x = pa[x][i];
            y = pa[y][i];
            ds += (1<<(i+1));
        }
    }
    if(!tmp) return pa[x][0];
    else return ds+2;
}

void upd(int x, int val){
    for(; x < 2*N; x += x&-x) bit[x] += val ;
}

int sum(int x){
    int ret = 0;
    for(; x > 0; x -= x&-x) ret += bit[x];
    return ret;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;

    for(int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    build(n);
    for(int i = 0; i < m; ++i){
        int x, y; cin >> x >> y;
        if(in[x] > in[y]) swap(x, y);
        int lc = lca(x, y, 0);
        if(lc == x){
            upd(in[x], 1);
            upd(in[y] + 1, -1);
        }
        else{
            upd(in[lc], 1);
            upd(in[x] + 1, -1);
            upd(in[lc], 1);
            upd(in[y] + 1, -1);
            ans[lc]++;
        }
    }
    for(int i = 1; i <= n; ++i){
        int t = sum(in[i]) - sum(out[i]);
        cout << t - ans[i] << ' ';
    }
}

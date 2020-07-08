#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int a[N];
int in[N], out[N], dep[N];
vector<int> g[N];
int _time;
struct bit{
    int tr[N];
    void add(int x, int val){
        for(; x < N; x += x&-x) tr[x] += val;
    }
    int sum(int x){
        int ret = 0;
        for(; x > 0; x -= x&-x) ret += tr[x];
        return ret;
    }
}bitree[3];

void dfs(int x, int p){
    dep[x] = dep[p] + 1;
    in[x] = ++_time;
    for(auto y: g[x]){
        if(y == p) continue;
        dfs(y, x);
    }
    out[x] = _time;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    for(int i = 1; i<= n; ++i) cin >> a[i];
    for(int i = 1; i < n; ++i){
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    while(m--){
        int q; cin >> q;
        if(q == 1){
            int nod, val; cin >> nod >> val;

            bitree[(dep[nod]&1)].add(in[nod], val);
            bitree[(dep[nod]&1)].add(out[nod] + 1, -val);
            bitree[(dep[nod]&1)^1].add(in[nod], -val);
            bitree[(dep[nod]&1)^1].add(out[nod] + 1, val);
            //*/
        }else{
            int nod; cin >> nod;
            cout << bitree[dep[nod]&1].sum(in[nod]) + a[nod] << '\n';
        }
    }
}

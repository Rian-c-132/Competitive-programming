#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
const int mxlift = 18;
int LCA_Tree[4*N];
pair<int, int> mintree[4*N], maxtree[4*N];
vector<int> adj[N];
int depth[N], in[N], out[N];
int table[N][mxlift]; // for binary lifting
int _time;

int dfs(int u, int fa){
    in[u] = ++_time;
    depth[u] = depth[fa] + 1;
    table[u][0] = fa;
    for(auto v: adj[u]){
        if(v != fa)
            dfs(v, u);
    }
    out[u] = _time;
}

void buildTable(int n){
    for(int i = 1; i < mxlift; ++i)
        for(int j = 1; j <= n; ++j)
            table[j][i] = table[table[j][i-1]][i-1];
}
int lca(int u, int v){
    if(depth[u] > depth[v]) swap(u, v);
    for(int i = mxlift - 1; i >= 0; --i){
        if(depth[table[v][i]] >= depth[u]){
            v = table[v][i];
        }
    }
    if(v == u) return v;
    for(int i = mxlift - 1; i >= 0; --i){
        if(table[v][i] != table[u][i]){
            v = table[v][i], u = table[u][i];
        }
    }
    return table[u][0];
}

void buildTreeLca(int node, int l, int r){
    if(l == r){
        LCA_Tree[node] = l;
        return;
    }
    int mid = l + (r - l) / 2;
    buildTreeLca(2*node, l, mid);
    buildTreeLca(2*node + 1, mid + 1, r);
    LCA_Tree[node] = lca(LCA_Tree[2*node], LCA_Tree[2*node + 1]);
    return;
}


void buildminmax(int node, int l, int r){
    if(l == r){
        mintree[node] = {in[l], l};
        maxtree[node] = {in[l], l};
        return;
    }
    int mid = l + (r - l) / 2;
    buildminmax(2*node, l, mid);
    buildminmax(2*node + 1, mid + 1, r);
    mintree[node] = min(mintree[2*node], mintree[2*node + 1]);
    maxtree[node] = max(maxtree[2*node], maxtree[2*node + 1]);
}

pair<int, int> querymm(int node, int l, int r, int st, int en, bool flag){
    if(l > en || r < st){
        if(flag){
            return {0, 0} ;
        }else
            return {1e9, 1e9};
    }
    int mid = l + (r - l) / 2;
    if(st <= l && r <= en){
        if(flag){
            return maxtree[node];
        }else
            return mintree[node];
    }
    pair<int, int> a = querymm(2*node, l, mid, st, en, flag);
    pair<int, int> b = querymm(2*node + 1, mid + 1, r, st, en, flag);
    if(flag) return max(a, b);
    else return min(a, b);
}
int query_lca(int node, int l, int r, int st, int en){
    if(l > en || r < st){
        return -1;
    }
    if(st <= l && r <= en){
        return LCA_Tree[node];
    }
    int mid = l + (r - l) / 2;
    int a = query_lca(2*node, l, mid, st, en);
    int b = query_lca(2*node + 1, mid + 1, r, st, en);
    if(a == -1) return b;
    else if(b == -1) return a;
    else return lca(a, b);
}

int solve(int u, int l, int r, int n){
    if(l == u){
        return query_lca(1, 1, n, l + 1, r);
    }
    if(r == u){
        return query_lca(1, 1, n, l, r - 1);
    }
    return lca(query_lca(1, 1, n, l, u - 1), query_lca(1, 1, n, u + 1, r));
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    for(int i = 0; i < 4*N; ++i){
        mintree[i] = {1e9, 1e9};
    }
    int n, q; cin >> n >> q;
    for(int i = 2; i <= n; ++i){
        int p; cin >> p;
        adj[p].push_back(i);
        adj[i].push_back(p);
    }
    dfs(1, 0);
    buildTable(n);
    buildTreeLca(1, 1, n);
    buildminmax(1, 1, n);
    while(q--){
        int st, en; cin >> st >> en;
        pair<int, int> _mn = querymm(1, 1, n, st, en, 0);
        pair<int, int> _mx = querymm(1, 1, n, st, en, 1);
        int a = solve(_mn.second, st, en, n);
        int b = solve(_mx.second, st, en, n);
        if(depth[a] > depth[b]){
            cout << _mn.second << ' ' << depth[a] - 1 << '\n';
        }else{
            cout << _mx.second << ' ' << depth[b] - 1 << '\n';
        }
    }
    return 0;
}

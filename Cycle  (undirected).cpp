//https://codeforces.com/contest/1364/problem/D
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> adj[N], ans[2], cycle;
bool vis[N], kd;
int n, m, k;
int cnt, pa[N], col[N];
void dfs(int u){
    vis[u] = true;
    cnt++;
    if(cnt == k){
        kd = true;
        return;
    }
    for(auto v: adj[u]){
        if(!vis[v] && !kd){
            dfs(v);
        }
    }
}

void dfs2(int u, int fa){
    ans[col[u]].push_back(u);
    for(auto v: adj[u]){
        if(!vis[v] || v == fa) continue;
        if(col[v] == -1){
            col[v] = 1 - col[u];
            pa[v] = u;
            dfs2(v, u);
        }
        else if(col[v] != 1 - col[u]){
            int t = u;
            while(t != v){
                cycle.push_back(t);
                t = pa[t];
            }
            cycle.push_back(v);
            cout << 2 << '\n';
			cout << cycle.size() << '\n';
			for (int g: cycle) {
				cout << g << ' ';
			}
			exit(0);
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m >> k;
    for(int i = 0; i < m; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    for(int i = 1; i <= n; ++i) col[i] = -1;
    col[1] = 0;
    dfs2(1, 1);
    if(ans[0].size() < ans[1].size()){
        swap(ans[0], ans[1]);
    }
    cout << 1 << '\n';
    for(int i = 1; i <= (k+1)/2; ++i){
        cout << ans[0][i-1] << ' ';
    }
}

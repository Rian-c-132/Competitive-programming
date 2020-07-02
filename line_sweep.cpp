#include<bits/stdc++.h>
using namespace std;
const int N = 5e5+10;
vector<int> adj[N];
bool vis[N];

int ver;
void dfs(int x = 0, int pa = -1){
    vis[x] = 1;
    ver++;
    for(auto y: adj[x]){
        if(pa != y && !vis[y]){
            dfs(y);
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> v(n);
    for(int i = 0; i < n; ++i){
        cin >> v[i].first >> v[i].second;
    }
    vector<pair<int, int>> ev;
    for(int i = 0; i < n; ++i){
        ev.push_back({v[i].first, i});
        ev.push_back({v[i].second, i});
    }
    sort(ev.begin(), ev.end());
    set<pair<int, int>> st;
    bool k = true;
    int cnt = 0;
    for(auto it: ev){
        if(cnt >= n){
            k = false;
            break;
        }
        if(st.count(it)) {
            st.erase(it);
            continue;
        }
        int i = it.second;
        int r = v[i].second;
        for(auto jt: st){
            int j = jt.second;
            int r1 = jt.first;
            if(r1 > r){
                break;
            }
            adj[i].push_back(j);
            adj[j].push_back(i);
            cnt++;
            if(cnt >= n) break;
        }
        st.insert({v[i].second, i});
    }
    if(cnt >= n || !k){
        cout << "NO\n";
        return 0;
    }
    dfs();
    if(ver == n){
        cout << "YES\n";
    }else cout << "NO\n";
}

#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
const int MXLOG = 22;
int _log[N];
int a[N];
int table[MXLOG][N];
void compute_log(){
    _log[1] = 0;
    for(int i = 2; i < N; ++i)
        _log[i] = _log[i/2] + 1;
}
void build(int n){// for minimum, works for idempotent functions. (GCD, LCM, maximum)
    for(int i = 0; i <= _log[n]; ++i){
        int curlen = 1<<i ;
        for(int j = 0; j + curlen <= n; ++j){
            if(curlen == 1) table[i][j] = a[j];
            else{
                table[i][j] = min(table[i - 1][j], table[i - 1][j + curlen/2]);
            }
        }
    }
}
int query(int l, int r){
    int len = r - l + 1;
    len = _log[len];
    return min(table[len][l], table[len][r - (1<<len) + 1]);
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
    for(int i = 0; i < n; ++i) cin >> a[i];
    compute_log();
    build(n);
}
//

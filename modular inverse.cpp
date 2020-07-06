#include<bits/stdc++.h>

#define pii pair<int, int>
const int mod = 1e9 + 7;
const int N = 2e3 + 5;
const int M = 2e5 + 5;
typedef long long ll;
int D[N];
using namespace std;

int fact[M];
int ifac[M];

int pwm(ll x, int y){
    ll ans = 1;
    while(y){
        if(y&1){
            ans = (ans * x) % mod;
            ans = (ans + mod) % mod;
        }
        x = (x * x) % mod;
        x = (x + mod) % mod;
        y >>= 1;
    }
    if(ans < 0) ans += mod;
    return ans;
}

int ncr(int n, int r){
    if(r > n || r < 0 || n < 0) return 0;
    return (((1LL * fact[n] * ifac[r] ) % mod ) * ifac[n - r]) % mod;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int h, w;
    int n;
    cin >> h >> w >> n;
    vector<pii> a(n + 1);
    for(int i = 0; i < n; ++i){
        cin >> a[i].first >> a[i].second;
    }
    a[n].first = h;
    a[n].second = w;
    sort(a.begin(), a.end());
    fact[0] = fact[1] = 1;
    for(int i = 2; i < M; ++i) {
        fact[i] = (1LL * fact[i-1] * i) % mod;
        fact[i] = (fact[i] + mod) % mod;
    }

    ifac[200000] = pwm(1LL * fact[200000], mod - 2);
    for(int i = 200000 - 1; i >= 0; --i){
        ifac[i] = (1LL * ifac[i + 1] * (i + 1) ) % mod;
        ifac[i] = (ifac[i] + mod) % mod;
    }
    for(int i = 0; i <= n; ++i){
        D[i] = ncr(a[i].first + a[i].second - 2, a[i].first - 1);
        for(int j = 0; j < i; ++j){
            D[i] = (D[i] - ( 1LL * D[j] * ncr(a[i].first + a[i].second - a[j].first - a[j].second, a[i].first - a[j].first) ) % mod)% mod;
        }
    }


    cout << (D[n] + mod) % mod;
}

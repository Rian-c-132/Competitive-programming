//prefix sum palindrome
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int pref[2 * N];
string prefix(string);
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    for(int i = 0; i < n; ++i){
        string s; cin >> s;
        int len = 0;
        int left = 0, right = s.size() - 1;
        int cnt = 0;
        vector<char> uwu;

        while(left <= right){
            if(s[left] == s[right]){
                uwu.push_back(s[left]);
                cnt++;
            }
            else break;
            left++, right--;
        }
        left = s.size() - 2 * uwu.size();
        if(left <= 0){
            cout << s << '\n';
            continue;
        }
        string tmp = s.substr(cnt, left);
        string tmp2 = tmp;
        reverse(tmp2.begin(), tmp2.end());
        tmp = prefix(tmp);
        tmp2 = prefix(tmp2);
        if(tmp.size() < tmp2.size()){
            swap(tmp, tmp2);
        }
        for(auto c: uwu) cout << c;
        cout << tmp;
        reverse(uwu.begin(), uwu.end());
        for(auto c: uwu) cout << c;
        cout << '\n';
    }
}

string prefix(string s){
    string t = s;
    reverse(t.begin(), t.end());
    t = s + "#" + t;
    int len = 0;
    for(int i = 1; i < t.size(); ++i){
        while(len != 0 && t[len] != t[i]) len = pref[len - 1];
        if(t[len] == t[i]) len++;
        pref[i] = len;
    }
    return s.substr(0, len);
}

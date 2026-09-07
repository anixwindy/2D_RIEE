// ══ 字串雜湊(雙模數)═══════════════════════════════════
//  用途   : O(1) 比較任意兩個子字串是否相同
//  複雜度 : 前處理 O(n),每次比較 O(1)
//  等級   : 藍 (1600-1899)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : ★★ 1. 單模數會被卡(anti-hash test)-> 一律用雙模數
//           2. base 要隨機,不要寫死 31/131,Codeforces 上會被 hack
//           3. 字元不要減 'a' 減到變 0,用 s[i] - 'a' + 1
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Hashing {
    static const ll M1 = 1000000007, M2 = 998244353;
    ll B1, B2;
    vector<ll> h1, h2, p1, p2;

    explicit Hashing(const string& s) {
        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        B1 = 131 + rng() % 100;                 // 隨機 base,防 hack
        B2 = 137 + rng() % 100;
        int n = s.size();
        h1.assign(n + 1, 0); h2.assign(n + 1, 0);
        p1.assign(n + 1, 1); p2.assign(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            ll c = s[i];
            h1[i+1] = (h1[i] * B1 + c) % M1;
            h2[i+1] = (h2[i] * B2 + c) % M2;
            p1[i+1] = p1[i] * B1 % M1;
            p2[i+1] = p2[i] * B2 % M2;
        }
    }
    // 取 s[l..r] 的雜湊(0-indexed 閉區間)
    pair<ll,ll> get(int l, int r) const {
        ll a = ((h1[r+1] - h1[l] * p1[r-l+1]) % M1 + M1) % M1;
        ll b = ((h2[r+1] - h2[l] * p2[r-l+1]) % M2 + M2) % M2;
        return {a, b};
    }
    bool equal(int l1, int r1, int l2, int r2) const {
        if (r1 - l1 != r2 - l2) return false;
        return get(l1, r1) == get(l2, r2);
    }
};

int main() {
    string s = "abcabc";
    Hashing h(s);
    cout << "s[0..2] == s[3..5] ? " << h.equal(0, 2, 3, 5) << "\n";   // 1
    cout << "s[0..1] == s[1..2] ? " << h.equal(0, 1, 1, 2) << "\n";   // 0
    return 0;
}

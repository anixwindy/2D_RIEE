// ══ 快速冪 / 模逆元 / 組合數 ════════════════════════════
//  用途   : 幾乎每一題「答案對 1e9+7 取模」都會用到
//  複雜度 : 快速冪 O(log n);組合數預處理 O(n) 後查詢 O(1)
//  等級   : 青 (1400-1599)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : ★★ 1. 乘法一定要先轉 long long 再乘,不然爆 int
//           2. 減法之後可能變負 -> (a - b % MOD + MOD) % MOD
//           3. 費馬小定理求逆元「只有 MOD 是質數」才能用
//           4. 除法不能直接除,要乘上逆元
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

ll mpow(ll b, ll e, ll m = MOD) {
    b %= m;
    if (b < 0) b += m;
    ll r = 1;
    while (e > 0) {
        if (e & 1) r = r * b % m;
        b = b * b % m;
        e >>= 1;
    }
    return r;
}
ll minv(ll a, ll m = MOD) { return mpow(a, m - 2, m); }   // ★ m 必須是質數
ll madd(ll a, ll b) { return (a + b) % MOD; }
ll msub(ll a, ll b) { return (a - b % MOD + MOD) % MOD; }
ll mmul(ll a, ll b) { return a % MOD * (b % MOD) % MOD; }
ll mdiv(ll a, ll b) { return mmul(a, minv(b)); }

// ── 組合數:預處理階乘與階乘逆元 ─────────────────
struct Comb {
    vector<ll> f, fi;
    explicit Comb(int n) : f(n + 1), fi(n + 1) {
        f[0] = 1;
        for (int i = 1; i <= n; ++i) f[i] = f[i-1] * i % MOD;
        fi[n] = minv(f[n]);
        for (int i = n; i > 0; --i) fi[i-1] = fi[i] * i % MOD;
    }
    ll C(int n, int k) const {
        if (k < 0 || k > n || n < 0) return 0;
        return f[n] * fi[k] % MOD * fi[n-k] % MOD;
    }
    ll P(int n, int k) const {
        if (k < 0 || k > n || n < 0) return 0;
        return f[n] * fi[n-k] % MOD;
    }
};

int main() {
    cout << "2^10 mod p     = " << mpow(2, 10)  << "\n";      // 1024
    cout << "inverse of 3   = " << minv(3)      << "\n";
    cout << "3 * inv(3)     = " << mmul(3, minv(3)) << "\n";  // 1
    Comb c(1000);
    cout << "C(10,3) = " << c.C(10, 3) << "\n";               // 120
    cout << "P(10,3) = " << c.P(10, 3) << "\n";               // 720
    return 0;
}

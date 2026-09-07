// ══ 質數篩 + 質因數分解 ═════════════════════════════════
//  用途   : 大量質數判定、快速分解質因數、算歐拉函數
//  複雜度 : 線性篩 O(n);單次分解 O(log n)
//  等級   : 青 (1400-1599)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 0 和 1 都不是質數
//           2. n 大到 1e7 以上時 vector<int> 會吃 40MB,考慮用 vector<char>
//           3. 單一個大數要分解就用試除法到 sqrt(n),不用篩
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Sieve {
    int n;
    vector<int> spf;                            // spf[x] = x 的最小質因數
    vector<int> primes;
    explicit Sieve(int n) : n(n), spf(n + 1, 0) {
        for (int i = 2; i <= n; ++i) {
            if (!spf[i]) { spf[i] = i; primes.push_back(i); }
            for (int p : primes) {
                if (p > spf[i] || (ll)p * i > n) break;
                spf[p * i] = p;
            }
        }
    }
    bool is_prime(int x) const { return x >= 2 && spf[x] == x; }

    // 用 spf 分解,O(log x)
    vector<pair<int,int>> factor(int x) const {
        vector<pair<int,int>> f;
        while (x > 1) {
            int p = spf[x], c = 0;
            while (x % p == 0) { x /= p; ++c; }
            f.push_back({p, c});
        }
        return f;
    }
};

// ── 單一個大數的分解(不用篩)────────────────────
vector<pair<ll,int>> factor_big(ll x) {
    vector<pair<ll,int>> f;
    for (ll p = 2; p * p <= x; ++p)
        if (x % p == 0) {
            int c = 0;
            while (x % p == 0) { x /= p; ++c; }
            f.push_back({p, c});
        }
    if (x > 1) f.push_back({x, 1});             // ★ 剩下的那個一定是質數
    return f;
}

int main() {
    Sieve s(100);
    cout << "primes under 30 : ";
    for (int p : s.primes) { if (p >= 30) break; cout << p << ' '; }
    cout << "\n";
    cout << "is_prime(97) = " << s.is_prime(97) << "\n";        // 1
    cout << "factor(60) = ";
    for (auto [p, c] : s.factor(60)) cout << p << "^" << c << ' ';   // 2^2 3^1 5^1
    cout << "\n";
    cout << "factor_big(1000000007) = ";
    for (auto [p, c] : factor_big(1000000007)) cout << p << "^" << c << ' ';
    cout << "\n";
    return 0;
}

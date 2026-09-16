
// ══════════════════════════════════════════════════════════════
//  ★ 這一題(AC 之後,連 code 一起存進 solved/<rating>/)
//  CF_____  題目名            rating _____
//  https://codeforces.com/problemset/problem/_____/_
//  用時 ___min
// ──────────────────────────────────────────────────────────────
//  題目一句話 :
//  卡在哪     :除法  ceil 是 整數除法無條件捨去
//  關鍵想法   :  如果要 n /a 無條件進位--> (n + a - 1) / a
//  線索       : ★★ 下次看到「  無條件進位      」就要想到
// ══════════════════════════════════════════════════════════════
#if defined(__GNUC__) && !defined(__clang__)
    #include <bits/stdc++.h>          // GCC / MinGW(CLion 走這條)
#else
    #include <algorithm>              // MSVC 沒有 bits/stdc++.h
    #include <array>
    #include <bitset>
    #include <cmath>
    #include <cstring>
    #include <deque>
    #include <functional>
    #include <iostream>
    #include <map>
    #include <numeric>
    #include <queue>
    #include <set>
    #include <string>
    #include <tuple>
    #include <unordered_map>
    #include <unordered_set>
    #include <vector>
#endif
using namespace std;

using ll  = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (int)(x).size()

const ll  INF = LLONG_MAX / 4;
const int MOD = 1000000007;

// ── debug:交出去之前不用刪,它只在本機有作用 ──────────
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(x)
#endif
// ────────────────────────────────────────────────
void solve() {
    ll n,m,a=0;
    cin>>n>>m>>a;
    ll num =0;
    if (a>n && a>m) {
        num=1;

    }else if (a>n || a>m) {
        if (m>n) {
           num=  ((m + a - 1) / a);

        }else {
            num=  ((n + a - 1) / a);

        }

    }else{
        num= ((m + a - 1) / a)*  ((n + a - 1) / a);

    }cout<<num<<'\n';
}




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;                 // ← 單筆測資的題目,把這行註解掉
    while (T--) solve();
    return 0;
}

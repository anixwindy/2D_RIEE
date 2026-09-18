
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

// ---- 型別:全部用 using ----
using ll  = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;
using vll = vector<ll>;
template<class T> using vec = vector<T>;            // macro 做不到的
template<class T> using vec2 = vector<vector<T>>;

// ---- 非型別:只能用 macro ----
#define pb push_back
#define fi first
#define se second
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






}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;                 // ← 單筆測資的題目,把這行註解掉
    while (T--) solve();
    return 0;
}

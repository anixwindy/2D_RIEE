// ══════════════════════════════════════════════════════════════
//  ★ 解題工作檔 —— 每一題都在這裡寫
//
//  流程:
//    1. 題目測資貼進 src/_solve/in.txt
//    2. CLion 右上 target 選 _solve -> 按 ▶(綠三角)
//       (Run Configuration 裡設 "Redirect input from" 指到 in.txt)
//    3. AC 之後把這個檔複製到 cp/solved/YYYY-MM-DD_題號.cpp
//       並照 cp/SOLVED_FORMAT.md 寫一份 .md
//
//  ⚠ 這個檔案會被一直覆蓋。重要的東西記得先存走。
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

// ══════════════════════════════════════════════════════════════
//  這裡貼 codebook 的東西(把它的 main() 去掉)
// ══════════════════════════════════════════════════════════════


// ══════════════════════════════════════════════════════════════
//  ★ 想法(寫給自己看,AC 之後直接搬進 cp/solved/*.md)
//    題目一句話 :
//    卡在哪     :
//    關鍵想法   :
// ══════════════════════════════════════════════════════════════
void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;

    dbg(n);
    cout << accumulate(all(a), 0LL) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;                 // ← 單筆測資的題目,把這行註解掉
    while (T--) solve();
    return 0;
}

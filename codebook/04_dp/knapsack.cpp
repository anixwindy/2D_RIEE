// ══ 背包 DP(01 / 完全 / 多重)═════════════════════════
//  用途   : 「選或不選」型的最佳化。DP 的第一課
//  複雜度 : 01/完全 O(nW);多重(二進位拆分)O(n W log k)
//  等級   : 青 (1400-1599)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : ★★ 一維滾動時,迴圈方向決定是哪一種背包:
//             01 背包   -> 容量「由大到小」(每個物品只能拿一次)
//             完全背包 -> 容量「由小到大」(可以拿無限次)
//           方向寫反是最經典的 WA,而且不會噴錯
//           2. 「恰好裝滿」要把 dp 初始化成 -INF,只有 dp[0]=0
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ── 01 背包:每個物品最多拿 1 次,求最大價值 ────────
ll knap01(int W, const vector<int>& w, const vector<ll>& v) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); ++i)
        for (int c = W; c >= w[i]; --c)                 // ★ 由大到小
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

// ── 完全背包:每個物品可拿無限次 ────────────────
ll knapUnbounded(int W, const vector<int>& w, const vector<ll>& v) {
    vector<ll> dp(W + 1, 0);
    for (size_t i = 0; i < w.size(); ++i)
        for (int c = w[i]; c <= W; ++c)                 // ★ 由小到大
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W];
}

// ── 多重背包:第 i 種最多拿 k[i] 次(二進位拆分)──
ll knapBounded(int W, const vector<int>& w, const vector<ll>& v, const vector<int>& k) {
    vector<int> nw;
    vector<ll>  nv;
    for (size_t i = 0; i < w.size(); ++i) {
        int cnt = k[i];
        for (int b = 1; cnt > 0; b <<= 1) {             // 1,2,4,8... 拆成 log 個
            int take = min(b, cnt);
            nw.push_back(w[i] * take);
            nv.push_back(v[i] * take);
            cnt -= take;
        }
    }
    return knap01(W, nw, nv);
}

// ── 恰好裝滿版本(裝不滿回 -1)────────────────────
ll knapExact(int W, const vector<int>& w, const vector<ll>& v) {
    const ll NEG = LLONG_MIN / 4;
    vector<ll> dp(W + 1, NEG);
    dp[0] = 0;
    for (size_t i = 0; i < w.size(); ++i)
        for (int c = W; c >= w[i]; --c)
            if (dp[c - w[i]] > NEG) dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
    return dp[W] <= NEG ? -1 : dp[W];
}

int main() {
    vector<int> w = {2, 3, 4};
    vector<ll>  v = {3, 4, 5};
    cout << "01 knapsack  W=5 : " << knap01(5, w, v)        << "\n";   // 7
    cout << "unbounded    W=5 : " << knapUnbounded(5, w, v) << "\n";   // 7
    cout << "bounded k=2  W=6 : " << knapBounded(6, w, v, {2,2,2}) << "\n";  // 8
    cout << "exact fill   W=5 : " << knapExact(5, w, v)     << "\n";   // 7
    cout << "exact fill   W=1 : " << knapExact(1, w, v)     << "\n";   // -1
    return 0;
}

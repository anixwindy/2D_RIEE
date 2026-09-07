// ══ 狀壓 DP(Bitmask DP)═══════════════════════════════
//  用途   : n <= 20 左右、要記「哪些已經用過」的題目
//  複雜度 : O(2^n * n) 或 O(2^n * n^2)
//  等級   : 紫 (1900-2099)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : ★★ 看到 n <= 20 就該想到狀壓,這是最強的訊號
//           2. 1 << n 在 n >= 31 會溢位 -> 用 1LL << n
//           3. dp 陣列大小是 2^n,n=20 就是 100 萬,乘以 n 要算清楚記憶體
//           4. 位元運算優先權很低,該加括號就加
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = LLONG_MAX / 4;

// ── TSP:從 0 出發走完所有點回到 0 的最短距離 ──────
ll tsp(const vector<vector<ll>>& d) {
    int n = d.size();
    int FULL = 1 << n;
    vector<vector<ll>> dp(FULL, vector<ll>(n, INF));
    dp[1][0] = 0;                                   // 只走過 0,人在 0
    for (int mask = 1; mask < FULL; ++mask)
        for (int u = 0; u < n; ++u) {
            if (dp[mask][u] == INF)  continue;
            if (!(mask >> u & 1))    continue;
            for (int v = 0; v < n; ++v) {
                if (mask >> v & 1) continue;        // v 已經走過
                int nm = mask | (1 << v);
                dp[nm][v] = min(dp[nm][v], dp[mask][u] + d[u][v]);
            }
        }
    ll best = INF;
    for (int u = 0; u < n; ++u) best = min(best, dp[FULL - 1][u] + d[u][0]);
    return best;
}

// ── 常用位元技巧 ────────────────────────────────
void bit_tricks() {
    int m = 0b1011;
    cout << "popcount      : " << __builtin_popcount(m) << "\n";       // 3
    cout << "lowest bit    : " << (m & -m)              << "\n";       // 1
    cout << "trailing zero : " << __builtin_ctz(m)      << "\n";       // 0
    cout << "sub masks     : ";
    for (int s = m; s; s = (s - 1) & m) cout << s << ' ';               // 列舉子集
    cout << "\n";
}

int main() {
    vector<vector<ll>> d = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    cout << "TSP min tour = " << tsp(d) << "\n";      // 80
    bit_tricks();
    return 0;
}

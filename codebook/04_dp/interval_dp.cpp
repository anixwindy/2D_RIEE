// ══ 區間 DP ═════════════════════════════════════════════
//  用途   : 石子合併、最少插入成迴文、括號匹配、矩陣鏈乘
//  複雜度 : 通常 O(n^3)
//  等級   : 藍 (1600-1899)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : ★★ 迴圈順序一定是「先枚舉長度,再枚舉左端點」
//             因為 dp[l][r] 依賴比它「短」的區間
//           2. 分割點 k 的範圍別寫錯(通常 l <= k < r)
//           3. n=1 的邊界要先填好
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = LLONG_MAX / 4;

// ── 石子合併:相鄰兩堆合併,代價是兩堆總和,求最小總代價 ──
ll stone_merge(const vector<ll>& a) {
    int n = a.size();
    if (n <= 1) return 0;
    vector<ll> pre(n + 1, 0);
    for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + a[i];
    auto sum = [&](int l, int r){ return pre[r + 1] - pre[l]; };

    vector<vector<ll>> dp(n, vector<ll>(n, 0));
    for (int len = 2; len <= n; ++len)                 // ★ 先枚舉長度
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            dp[l][r] = INF;
            for (int k = l; k < r; ++k)                // 分割點
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + sum(l, r));
        }
    return dp[0][n - 1];
}

// ── 最少插入幾個字元讓字串變迴文 ────────────────
int min_insert_palindrome(const string& s) {
    int n = s.size();
    if (n <= 1) return 0;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len <= n; ++len)
        for (int l = 0; l + len - 1 < n; ++l) {
            int r = l + len - 1;
            if (s[l] == s[r]) dp[l][r] = dp[l + 1][r - 1];
            else              dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1;
        }
    return dp[0][n - 1];
}

int main() {
    vector<ll> a = {1, 2, 3, 4};
    cout << "stone merge min cost = " << stone_merge(a) << "\n";       // 19
    cout << "min insert for zzazz = " << min_insert_palindrome("zzazz") << "\n";  // 0
    cout << "min insert for mbadm = " << min_insert_palindrome("mbadm") << "\n";  // 2
    return 0;
}

// ══ 雙指標 / 滑動視窗 ═══════════════════════════════════
//  用途   : 找「滿足某條件的最長/最短連續區間」
//  複雜度 : O(n) —— 每個指標各只往前走 n 次
//  等級   : 綠 (1200-1399)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. 只有「條件單調」才能用(右端右移後,左端不會需要往回退)
//           2. 先 while 縮左,再更新答案,順序反了就錯
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ── 最長:和 <= K 的最長連續區間長度 ──────────────
int longest_sum_at_most(const vector<ll>& a, ll K) {
    int n = a.size(), best = 0, l = 0;
    ll cur = 0;
    for (int r = 0; r < n; ++r) {
        cur += a[r];
        while (l <= r && cur > K) cur -= a[l++];   // 先縮到合法
        best = max(best, r - l + 1);               // 再更新答案
    }
    return best;
}

// ── 最短:和 >= K 的最短連續區間長度(沒有回 -1)───
int shortest_sum_at_least(const vector<ll>& a, ll K) {
    int n = a.size(), best = INT_MAX, l = 0;
    ll cur = 0;
    for (int r = 0; r < n; ++r) {
        cur += a[r];
        while (l <= r && cur - a[l] >= K) cur -= a[l++];
        if (cur >= K) best = min(best, r - l + 1);
    }
    return best == INT_MAX ? -1 : best;
}

// ── 最長:不含重複元素的最長連續區間 ───────────────
int longest_no_repeat(const vector<int>& a) {
    unordered_map<int,int> cnt;
    int best = 0, l = 0;
    for (int r = 0; r < (int)a.size(); ++r) {
        cnt[a[r]]++;
        while (cnt[a[r]] > 1) cnt[a[l++]]--;
        best = max(best, r - l + 1);
    }
    return best;
}

int main() {
    vector<ll> a = {2, 1, 5, 1, 3, 2};
    cout << "longest sum<=8  : " << longest_sum_at_most(a, 8)    << '\n';  // 3
    cout << "shortest sum>=7 : " << shortest_sum_at_least(a, 7)  << '\n';  // 3
    vector<int> b = {1, 2, 3, 2, 4};
    cout << "longest no repeat : " << longest_no_repeat(b)       << '\n';  // 3
    return 0;
}

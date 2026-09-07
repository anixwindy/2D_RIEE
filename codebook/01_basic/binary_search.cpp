// ══ 二分搜 / 二分答案 ═══════════════════════════════════
//  用途   : (1) 在排好序的陣列找位置 (2) 對「答案」二分
//  複雜度 : O(log n) x 一次 check 的成本
//  等級   : 綠 (1200-1399)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. lo/hi 用 ll,不然 mid 會溢位
//           2. 邊界寫錯會無限迴圈 -> 記住「迴圈內一定要縮小區間」
//           3. check 必須是單調的,不單調就不能二分
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ── 模板 1:找「第一個滿足 check 的位置」──────────────
// check 長這樣: false false false true true true
//                                 ^ 回傳這裡
ll lower_bound_first_true(ll lo, ll hi, function<bool(ll)> check) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;     // 這樣寫不會溢位
        if (check(mid)) hi = mid;
        else            lo = mid + 1;
    }
    return lo;                           // 都不滿足時會回傳原本的 hi
}

// ── 模板 2:找「最後一個滿足 check 的位置」────────────
// check 長這樣: true true true false false
//                          ^ 回傳這裡
ll upper_bound_last_true(ll lo, ll hi, function<bool(ll)> check) {
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2; // 注意 +1,不然會無限迴圈
        if (check(mid)) lo = mid;
        else            hi = mid - 1;
    }
    return lo;
}

// ── 實數二分(答案是小數時)────────────────────────
double bs_real(double lo, double hi, function<bool(double)> check) {
    for (int it = 0; it < 100; ++it) {   // 固定跑 100 次,不要用 while(hi-lo>eps)
        double mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else            lo = mid;
    }
    return lo;
}

int main() {
    // 例:在 a 裡找第一個 >= 5 的位置
    vector<int> a = {1, 3, 5, 7, 9};
    ll pos = lower_bound_first_true(0, a.size(), [&](ll i){ return a[i] >= 5; });
    cout << "first >= 5 at index " << pos << '\n';        // 2

    // 例:二分答案 —— 求最大的 x 使得 x*x <= 50
    ll best = upper_bound_last_true(0, 1000000, [&](ll x){ return x * x <= 50; });
    cout << "max x with x*x <= 50 : " << best << '\n';    // 7

    // STL 內建的兩個(排好序才能用)
    cout << "stl lower_bound : " << (lower_bound(a.begin(), a.end(), 5) - a.begin()) << '\n';
    cout << "stl upper_bound : " << (upper_bound(a.begin(), a.end(), 5) - a.begin()) << '\n';
    return 0;
}

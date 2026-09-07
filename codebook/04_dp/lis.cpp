// ══ 最長遞增子序列 LIS ══════════════════════════════════
//  用途   : LIS 本身,以及一大票能轉成 LIS 的題目
//  複雜度 : O(n log n)
//  等級   : 青 (1400-1599)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : ★★ 嚴格遞增用 lower_bound,非嚴格(可等於)用 upper_bound
//           2. tail 陣列裡放的「不是」LIS 本身,只有長度是對的
//              要還原序列必須另外記 par
//           3. 最長遞減 = 把陣列反過來再做 LIS
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;

// 嚴格遞增的 LIS 長度
int lis_strict(const vector<int>& a) {
    vector<int> tail;
    for (int x : a) {
        auto it = lower_bound(tail.begin(), tail.end(), x);   // ★ 嚴格 -> lower
        if (it == tail.end()) tail.push_back(x);
        else                  *it = x;
    }
    return tail.size();
}

// 非嚴格(允許相等)的 LIS 長度
int lis_nondecreasing(const vector<int>& a) {
    vector<int> tail;
    for (int x : a) {
        auto it = upper_bound(tail.begin(), tail.end(), x);   // ★ 非嚴格 -> upper
        if (it == tail.end()) tail.push_back(x);
        else                  *it = x;
    }
    return tail.size();
}

// 連序列本身一起還原
vector<int> lis_restore(const vector<int>& a) {
    int n = a.size();
    vector<int> tail, tailIdx, par(n, -1);
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(tail.begin(), tail.end(), a[i]);
        int pos = it - tail.begin();
        if (pos > 0) par[i] = tailIdx[pos - 1];
        if (it == tail.end()) { tail.push_back(a[i]); tailIdx.push_back(i); }
        else                  { tail[pos] = a[i];     tailIdx[pos] = i;     }
    }
    vector<int> res;
    if (tailIdx.empty()) return res;
    for (int i = tailIdx.back(); i != -1; i = par[i]) res.push_back(a[i]);
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS strict         = " << lis_strict(a)         << "\n";   // 4
    vector<int> b = {1, 3, 3, 5};
    cout << "LIS strict  (dup)  = " << lis_strict(b)         << "\n";   // 3
    cout << "LIS nondecr (dup)  = " << lis_nondecreasing(b)  << "\n";   // 4
    cout << "one LIS : ";
    for (int x : lis_restore(a)) cout << x << ' ';                      // 2 3 7 18
    cout << "\n";
    return 0;
}

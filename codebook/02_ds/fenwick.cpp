// ══ 樹狀陣列 BIT / Fenwick Tree ═════════════════════════
//  用途   : 單點修改 + 前綴和查詢。比線段樹短很多,能用就用它
//  複雜度 : 修改 O(log n),查詢 O(log n)
//  等級   : 藍 (1600-1899)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 內部一律 1-indexed。外面 0-indexed 要 +1
//           2. 值會爆 int -> 用 long long
//           3. 只能做「可逆」的運算(和、xor)。最大值不行,那要線段樹
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<ll> t;
    explicit Fenwick(int n) : n(n), t(n + 1, 0) {}

    void add(int i, ll v) {                     // 0-indexed:a[i] += v
        for (++i; i <= n; i += i & -i) t[i] += v;
    }
    ll pre(int i) {                             // 0-indexed:a[0..i] 的和
        ll s = 0;
        for (++i; i > 0; i -= i & -i) s += t[i];
        return s;
    }
    ll range(int l, int r) { return pre(r) - (l ? pre(l - 1) : 0); }

    // 找最小的 i 使得 pre(i) >= target(要求所有值非負)
    int lower_bound(ll target) {
        int pos = 0;
        ll cur = 0;
        for (int pw = 1 << (31 - __builtin_clz(max(n, 1))); pw > 0; pw >>= 1) {
            if (pos + pw <= n && cur + t[pos + pw] < target) {
                pos += pw;
                cur += t[pos];
            }
        }
        return pos;                             // 回傳 0-indexed 的位置
    }
};

int main() {
    vector<ll> a = {1, 2, 3, 4, 5};
    Fenwick f(a.size());
    for (int i = 0; i < (int)a.size(); ++i) f.add(i, a[i]);

    cout << "sum a[0..2] = " << f.range(0, 2) << '\n';   // 6
    f.add(1, 10);                                        // a[1] 變成 12
    cout << "after a[1]+=10, sum a[0..2] = " << f.range(0, 2) << '\n';  // 16
    cout << "first idx with pre >= 14 : " << f.lower_bound(14) << '\n'; // 2
    return 0;
}

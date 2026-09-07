// ══ 線段樹(區間加 + 區間和,懶標)═══════════════════
//  用途   : 區間修改 + 區間查詢。BIT 做不到的都找它
//  複雜度 : 建樹 O(n),修改/查詢各 O(log n)
//  等級   : 紫 (1900-2099)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 每次往下走之前一定要 push(),忘了就 WA
//           2. 陣列開 4*n,開 2*n 會越界
//           3. lazy 也要用 long long
//           4. 換成「區間覆蓋」時 apply/push 都要改,不能只改一半
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SegTree {
    int n;
    vector<ll> sum, lazy;
    explicit SegTree(int n) : n(n), sum(4 * n, 0), lazy(4 * n, 0) {}
    SegTree(const vector<ll>& a) : SegTree((int)a.size()) { build(1, 0, n - 1, a); }

    void build(int p, int l, int r, const vector<ll>& a) {
        if (l == r) { sum[p] = a[l]; return; }
        int m = (l + r) / 2;
        build(p*2, l, m, a);
        build(p*2+1, m+1, r, a);
        sum[p] = sum[p*2] + sum[p*2+1];
    }
    void apply(int p, int l, int r, ll v) {     // 整段加 v
        sum[p]  += v * (r - l + 1);
        lazy[p] += v;
    }
    void push(int p, int l, int r) {            // 把懶標推給兩個小孩
        if (!lazy[p]) return;
        int m = (l + r) / 2;
        apply(p*2, l, m, lazy[p]);
        apply(p*2+1, m+1, r, lazy[p]);
        lazy[p] = 0;
    }
    void update(int p, int l, int r, int ql, int qr, ll v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply(p, l, r, v); return; }
        push(p, l, r);
        int m = (l + r) / 2;
        update(p*2, l, m, ql, qr, v);
        update(p*2+1, m+1, r, ql, qr, v);
        sum[p] = sum[p*2] + sum[p*2+1];
    }
    ll query(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return sum[p];
        push(p, l, r);
        int m = (l + r) / 2;
        return query(p*2, l, m, ql, qr) + query(p*2+1, m+1, r, ql, qr);
    }
    // ── 外面用這兩個就好(0-indexed 閉區間)──
    void update(int l, int r, ll v) { update(1, 0, n - 1, l, r, v); }
    ll   query (int l, int r)       { return query(1, 0, n - 1, l, r); }
};

int main() {
    vector<ll> a = {1, 2, 3, 4, 5};
    SegTree t(a);
    cout << "sum [0..4] = " << t.query(0, 4) << '\n';    // 15
    t.update(1, 3, 10);                                  // a[1..3] 各 +10
    cout << "after +10 on [1..3], sum [0..4] = " << t.query(0, 4) << '\n';  // 45
    cout << "sum [2..2] = " << t.query(2, 2) << '\n';    // 13
    return 0;
}

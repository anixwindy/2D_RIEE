// ══ 前綴和 / 差分(1D + 2D)═══════════════════════════
//  用途   : 前綴和 = 快速查「區間和」;差分 = 快速做「區間加」
//  複雜度 : 前處理 O(n),每次查詢/修改 O(1)
//  等級   : 綠 (1200-1399)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. 一律開 1-indexed,pre[0]=0,可以少寫一堆 if
//           2. 值會爆 int -> 用 long long
//           3. 二維容斥的正負號寫反是最常見的 WA
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ── 1D 前綴和:查 a[l..r] 的和 ─────────────────────
struct Prefix1D {
    vector<ll> pre;
    explicit Prefix1D(const vector<ll>& a) : pre(a.size() + 1, 0) {
        for (size_t i = 0; i < a.size(); ++i) pre[i + 1] = pre[i] + a[i];
    }
    ll query(int l, int r) const { return pre[r + 1] - pre[l]; }   // 0-indexed, 閉區間
};

// ── 1D 差分:對 a[l..r] 全部加 v,最後還原 ──────────
struct Diff1D {
    vector<ll> d;
    explicit Diff1D(int n) : d(n + 2, 0) {}
    void add(int l, int r, ll v) { d[l] += v; d[r + 1] -= v; }
    vector<ll> build(int n) {
        vector<ll> a(n);
        ll cur = 0;
        for (int i = 0; i < n; ++i) { cur += d[i]; a[i] = cur; }
        return a;
    }
};

// ── 2D 前綴和:查左上(r1,c1) 到 右下(r2,c2) 的和 ───
struct Prefix2D {
    vector<vector<ll>> pre;
    Prefix2D(const vector<vector<ll>>& g) {
        int n = g.size(), m = n ? g[0].size() : 0;
        pre.assign(n + 1, vector<ll>(m + 1, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                pre[i+1][j+1] = g[i][j] + pre[i][j+1] + pre[i+1][j] - pre[i][j];
    }
    ll query(int r1, int c1, int r2, int c2) const {   // 0-indexed, 閉區間
        return pre[r2+1][c2+1] - pre[r1][c2+1] - pre[r2+1][c1] + pre[r1][c1];
    }
};

int main() {
    vector<ll> a = {1, 2, 3, 4, 5};
    Prefix1D p(a);
    cout << "sum a[1..3] = " << p.query(1, 3) << '\n';           // 2+3+4 = 9

    Diff1D d(5);
    d.add(1, 3, 10);
    auto b = d.build(5);
    cout << "after +10 on [1..3] : ";
    for (ll x : b) cout << x << ' ';                             // 0 10 10 10 0
    cout << '\n';

    vector<vector<ll>> g = {{1,2,3},{4,5,6},{7,8,9}};
    Prefix2D q(g);
    cout << "sum rect (0,0)-(1,1) = " << q.query(0, 0, 1, 1) << '\n';  // 1+2+4+5 = 12
    return 0;
}

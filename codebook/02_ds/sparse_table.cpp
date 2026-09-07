// ══ ST 表 Sparse Table(靜態 RMQ)═══════════════════════
//  用途   : 陣列不會變動時,O(1) 查區間最小/最大/gcd
//  複雜度 : 前處理 O(n log n),查詢 O(1)
//  等級   : 藍 (1600-1899)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 只能用在「不會修改」的陣列。要改就用線段樹
//           2. 只適用「可重複計算」的運算(min/max/gcd/and/or),和不行
//           3. LOG 表要先建,不然 log2 浮點誤差會出事
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;

template <class T, class F = function<T(T,T)>>
struct SparseTable {
    int n, K;
    vector<vector<T>> st;
    vector<int> lg;
    F op;
    SparseTable(const vector<T>& a, F op) : n(a.size()), op(op) {
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;
        K = lg[max(n, 1)] + 1;
        st.assign(K, vector<T>(n));
        st[0] = a;
        for (int k = 1; k < K; ++k)
            for (int i = 0; i + (1 << k) <= n; ++i)
                st[k][i] = op(st[k-1][i], st[k-1][i + (1 << (k-1))]);
    }
    T query(int l, int r) {                     // 0-indexed 閉區間
        int k = lg[r - l + 1];
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};

int main() {
    vector<int> a = {5, 2, 8, 1, 9, 3};
    SparseTable<int> mn(a, [](int x, int y){ return min(x, y); });
    SparseTable<int> mx(a, [](int x, int y){ return max(x, y); });
    cout << "min [1..4] = " << mn.query(1, 4) << '\n';   // 1
    cout << "max [1..4] = " << mx.query(1, 4) << '\n';   // 9
    return 0;
}

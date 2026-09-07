// ══ 並查集 DSU / Union-Find ═════════════════════════════
//  用途   : 判「這兩個點連通嗎」、算連通塊數、Kruskal 的零件
//  複雜度 : 幾乎 O(1)(路徑壓縮 + 按大小合併)
//  等級   : 青 (1400-1599)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. 比較兩點是否同組要用 find(a)==find(b),不能直接比 par
//           2. 忘記路徑壓縮會退化成 O(n)
//           3. 多筆測資要重新 init,不然殘留舊資料
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, sz;
    int comp;                                   // 目前的連通塊數
    explicit DSU(int n) : par(n), sz(n, 1), comp(n) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) {                           // 路徑壓縮
        while (par[x] != x) x = par[x] = par[par[x]];
        return x;
    }
    bool same(int a, int b) { return find(a) == find(b); }
    bool unite(int a, int b) {                  // 已經同組回 false
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);          // 小的掛到大的下面
        par[b] = a;
        sz[a] += sz[b];
        --comp;
        return true;
    }
    int size(int x) { return sz[find(x)]; }     // x 所在連通塊的大小
};

int main() {
    DSU d(6);
    d.unite(0, 1);
    d.unite(1, 2);
    d.unite(4, 5);
    cout << "same(0,2) = " << d.same(0, 2) << '\n';   // 1
    cout << "same(0,3) = " << d.same(0, 3) << '\n';   // 0
    cout << "components = " << d.comp      << '\n';   // 3  -> {0,1,2} {3} {4,5}
    cout << "size of 0's group = " << d.size(0) << '\n'; // 3
    return 0;
}

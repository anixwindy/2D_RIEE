// ══ 最小生成樹 Kruskal(配 DSU)═════════════════════════
//  用途   : 用最小總權重把所有點連起來
//  複雜度 : O(E log E)(瓶頸在排序)
//  等級   : 藍 (1600-1899)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 圖不連通時 MST 不存在(選到的邊數 < n-1)
//           2. 權重和要用 long long
//           3. 「最大生成樹」就把排序反過來,其他一模一樣
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct DSU {
    vector<int> par, sz;
    explicit DSU(int n) : par(n), sz(n, 1) { iota(par.begin(), par.end(), 0); }
    int find(int x) { while (par[x] != x) x = par[x] = par[par[x]]; return x; }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
        return true;
    }
};

struct Edge { int u, v; ll w; };

// 回傳 pair{總權重, 選到的邊}。不連通時總權重回 -1
pair<ll, vector<Edge>> kruskal(int n, vector<Edge> es) {
    sort(es.begin(), es.end(), [](const Edge& a, const Edge& b){ return a.w < b.w; });
    DSU d(n);
    ll total = 0;
    vector<Edge> used;
    for (auto& e : es)
        if (d.unite(e.u, e.v)) { total += e.w; used.push_back(e); }
    if ((int)used.size() != n - 1) return {-1, {}};
    return {total, used};
}

int main() {
    int n = 4;
    vector<Edge> es = {{0,1,1},{1,2,2},{0,2,4},{2,3,3}};
    auto [total, used] = kruskal(n, es);
    cout << "MST weight = " << total << "\n";           // 6
    cout << "edges : ";
    for (auto& e : used) cout << e.u << "-" << e.v << ":" << e.w << "  ";
    cout << "\n";
    return 0;
}

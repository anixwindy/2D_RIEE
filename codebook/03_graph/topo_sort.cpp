// ══ 拓撲排序(Kahn / BFS 版)═══════════════════════════
//  用途   : DAG 的排序;也用來「判斷有沒有環」
//  複雜度 : O(V + E)
//  等級   : 藍 (1600-1899)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 結果長度 < n 就代表有環
//           2. 要「字典序最小的拓撲序」就把 queue 換成 priority_queue
//           3. DAG 上的 DP 常常就是照拓撲序遞推
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;

// 回傳拓撲序;有環則回傳空 vector
vector<int> topo_sort(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> indeg(n, 0), order;
    for (int u = 0; u < n; ++u) for (int v : g[u]) ++indeg[v];

    queue<int> q;                 // 要字典序最小就換成 priority_queue<int, vector<int>, greater<int>>
    for (int i = 0; i < n; ++i) if (!indeg[i]) q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }
    return (int)order.size() == n ? order : vector<int>{};
}

// ── DAG 上的最長路(照拓撲序遞推)──────────────────
vector<int> longest_path_dag(const vector<vector<int>>& g) {
    auto order = topo_sort(g);
    vector<int> dp(g.size(), 0);
    for (int u : order) for (int v : g[u]) dp[v] = max(dp[v], dp[u] + 1);
    return dp;
}

int main() {
    int n = 6;
    vector<vector<int>> g(n);
    auto add = [&](int a, int b){ g[a].push_back(b); };   // 有向邊 a 指向 b
    add(5,2); add(5,0); add(4,0); add(4,1); add(2,3); add(3,1);

    auto ord = topo_sort(g);
    cout << "topo order : ";
    if (ord.empty()) cout << "has cycle";
    else for (int x : ord) cout << x << ' ';
    cout << "\n";

    auto dp = longest_path_dag(g);
    cout << "longest path ending at each node : ";
    for (int x : dp) cout << x << ' ';
    cout << "\n";
    return 0;
}

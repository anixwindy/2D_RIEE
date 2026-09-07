// ══ 樹形 DP ═════════════════════════════════════════════
//  用途   : 在樹上做 DP。最大獨立集、樹直徑、子樹統計
//  複雜度 : O(n)
//  等級   : 藍 (1600-1899)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : ★★ n=1e5 以上遞迴會爆堆疊 -> 這裡全部用「拓撲式」迭代
//             做法:先 BFS 出一個順序,再反過來由葉往根推
//           2. 無根樹要先指定 root,並記住 parent 避免走回去
//           3. 換根 DP 是另一個題型,要跑第二遍由根往葉推
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 先算出「由根往下的 BFS 順序」與每個點的父親
pair<vector<int>, vector<int>> bfs_order(const vector<vector<int>>& g, int root) {
    int n = g.size();
    vector<int> order, par(n, -1), vis(n, 0);
    queue<int> q;
    vis[root] = 1; q.push(root);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : g[u]) if (!vis[v]) { vis[v] = 1; par[v] = u; q.push(v); }
    }
    return {order, par};
}

// ── 子樹大小 ────────────────────────────────────
vector<int> subtree_size(const vector<vector<int>>& g, int root) {
    auto [order, par] = bfs_order(g, root);
    vector<int> sz(g.size(), 1);
    for (int i = (int)order.size() - 1; i >= 0; --i) {   // ★ 反過來 = 由葉往根
        int u = order[i];
        if (par[u] != -1) sz[par[u]] += sz[u];
    }
    return sz;
}

// ── 最大權獨立集:相鄰兩點不能同時選,求最大總權重 ──
ll max_independent_set(const vector<vector<int>>& g, const vector<ll>& w, int root) {
    auto [order, par] = bfs_order(g, root);
    int n = g.size();
    vector<ll> take(n), skip(n, 0);
    for (int i = 0; i < n; ++i) take[i] = w[i];
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i], p = par[u];
        if (p == -1) continue;
        take[p] += skip[u];                       // 選了 p,小孩就不能選
        skip[p] += max(take[u], skip[u]);         // 不選 p,小孩隨意
    }
    return max(take[root], skip[root]);
}

// ── 樹的直徑(兩次 BFS)────────────────────────
int tree_diameter(const vector<vector<int>>& g) {
    int n = g.size();
    auto far = [&](int s) {
        vector<int> d(n, -1);
        queue<int> q; d[s] = 0; q.push(s);
        int best = s;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (d[u] > d[best]) best = u;
            for (int v : g[u]) if (d[v] == -1) { d[v] = d[u] + 1; q.push(v); }
        }
        return pair<int,int>{best, d[best]};
    };
    auto [a, _]  = far(0);
    auto [b, len] = far(a);
    (void)b;
    return len;
}

int main() {
    //      0
    //     / \
    //    1   2
    //   / \
    //  3   4
    int n = 5;
    vector<vector<int>> g(n);
    auto add = [&](int a, int b){ g[a].push_back(b); g[b].push_back(a); };
    add(0,1); add(0,2); add(1,3); add(1,4);

    auto sz = subtree_size(g, 0);
    cout << "subtree sizes : ";
    for (int x : sz) cout << x << ' ';                       // 5 3 1 1 1
    cout << "\n";
    vector<ll> w = {1, 10, 1, 1, 1};
    cout << "max independent set = " << max_independent_set(g, w, 0) << "\n";  // 11
    cout << "tree diameter = " << tree_diameter(g) << "\n";  // 3
    return 0;
}

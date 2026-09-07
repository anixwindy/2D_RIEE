// ══ LCA 最近公共祖先(倍增法)═══════════════════════════
//  用途   : 樹上兩點的最近公共祖先、樹上兩點距離
//  複雜度 : 前處理 O(n log n),查詢 O(log n)
//  等級   : 紫 (1900-2099)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 先把深的那個往上跳到同深度,再兩個一起跳
//           2. up[0][root] 要設成 root 自己
//           3. n=1 時 LOG 要至少 1,不然會開 0 維陣列
//           4. 遞迴建表在深鏈上會爆堆疊 -> 這裡用 BFS 建
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;

struct LCA {
    int n, LOG;
    vector<vector<int>> up;                     // up[k][v] = v 往上跳 2 的 k 次方步
    vector<int> dep;

    LCA(const vector<vector<int>>& g, int root) : n(g.size()) {
        LOG = 1;
        while ((1 << LOG) < max(n, 2)) ++LOG;
        up.assign(LOG + 1, vector<int>(n, root));
        dep.assign(n, 0);

        vector<int> vis(n, 0);                  // BFS 建父節點與深度,不會爆堆疊
        queue<int> q;
        vis[root] = 1; up[0][root] = root;
        q.push(root);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) if (!vis[v]) {
                vis[v] = 1;
                up[0][v] = u;
                dep[v] = dep[u] + 1;
                q.push(v);
            }
        }
        for (int k = 1; k <= LOG; ++k)
            for (int v = 0; v < n; ++v)
                up[k][v] = up[k-1][ up[k-1][v] ];
    }

    int jump(int v, int k) {                    // v 往上跳 k 步
        for (int i = 0; i <= LOG; ++i)
            if (k >> i & 1) v = up[i][v];
        return v;
    }
    int lca(int a, int b) {
        if (dep[a] < dep[b]) swap(a, b);
        a = jump(a, dep[a] - dep[b]);           // 先跳到同深度
        if (a == b) return a;
        for (int k = LOG; k >= 0; --k)
            if (up[k][a] != up[k][b]) { a = up[k][a]; b = up[k][b]; }
        return up[0][a];
    }
    int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }
};

int main() {
    //        0
    //       / \
    //      1   2
    //     / \   \
    //    3   4   5
    int n = 6;
    vector<vector<int>> g(n);
    auto add = [&](int a, int b){ g[a].push_back(b); g[b].push_back(a); };
    add(0,1); add(0,2); add(1,3); add(1,4); add(2,5);

    LCA t(g, 0);
    cout << "lca(3,4)  = " << t.lca(3, 4)  << "\n";   // 1
    cout << "lca(3,5)  = " << t.lca(3, 5)  << "\n";   // 0
    cout << "dist(3,5) = " << t.dist(3, 5) << "\n";   // 4
    return 0;
}

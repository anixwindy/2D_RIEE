// ══ 圖的走訪:BFS / DFS / 連通塊 / 網格 BFS ═════════════
//  用途   : 最基本的圖論。無權圖最短路 = BFS
//  複雜度 : O(V + E)
//  等級   : 青 (1400-1599)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ BFS 要在「入隊時」標記 visited,不是出隊時,不然會重複入隊
//           2. 遞迴 DFS 在 n=1e5 以上可能爆堆疊 -> 改成手動堆疊
//           3. 網格題的方向陣列別打錯
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;

// ── 無權圖最短路(層數)────────────────────────────
vector<int> bfs(const vector<vector<int>>& g, int s) {
    vector<int> dist(g.size(), -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u])
            if (dist[v] == -1) {                // 入隊時就標記
                dist[v] = dist[u] + 1;
                q.push(v);
            }
    }
    return dist;
}

// ── 迭代式 DFS(不會爆堆疊)────────────────────────
vector<int> dfs_order(const vector<vector<int>>& g, int s) {
    vector<int> order, vis(g.size(), 0);
    vector<int> stk{s};
    vis[s] = 1;
    while (!stk.empty()) {
        int u = stk.back(); stk.pop_back();
        order.push_back(u);
        for (int v : g[u])
            if (!vis[v]) { vis[v] = 1; stk.push_back(v); }
    }
    return order;
}

// ── 連通塊數量 ──────────────────────────────────
int count_components(const vector<vector<int>>& g) {
    int n = g.size(), cnt = 0;
    vector<int> vis(n, 0);
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        ++cnt;
        vector<int> stk{i};
        vis[i] = 1;
        while (!stk.empty()) {
            int u = stk.back(); stk.pop_back();
            for (int v : g[u]) if (!vis[v]) { vis[v] = 1; stk.push_back(v); }
        }
    }
    return cnt;
}

// ── 網格 BFS(井字號是牆)──────────────────────────
const int DR[4] = {-1, 1, 0, 0};
const int DC[4] = { 0, 0,-1, 1};

vector<vector<int>> grid_bfs(const vector<string>& g, int sr, int sc) {
    int n = g.size(), m = g[0].size();
    vector<vector<int>> d(n, vector<int>(m, -1));
    queue<pair<int,int>> q;
    d[sr][sc] = 0;
    q.push({sr, sc});
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int k = 0; k < 4; ++k) {
            int nr = r + DR[k], nc = c + DC[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (g[nr][nc] == 35 || d[nr][nc] != -1)    continue;   // 35 = 井字號
            d[nr][nc] = d[r][c] + 1;
            q.push({nr, nc});
        }
    }
    return d;
}

int main() {
    // 0-1-2  3-4   (兩個連通塊)
    vector<vector<int>> g(5);
    auto add = [&](int a, int b){ g[a].push_back(b); g[b].push_back(a); };
    add(0,1); add(1,2); add(3,4);

    auto d = bfs(g, 0);
    cout << "dist from 0 : ";
    for (int x : d) cout << x << ' ';                    // 0 1 2 -1 -1
    cout << "\n";
    cout << "components = " << count_components(g) << "\n";  // 2

    vector<string> mp = {"...#", ".#..", "...."};
    auto gd = grid_bfs(mp, 0, 0);
    cout << "grid dist to (2,3) = " << gd[2][3] << "\n";  // 5
    return 0;
}

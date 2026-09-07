// ══ Dijkstra 最短路(非負權)═══════════════════════════
//  用途   : 有權圖的單源最短路
//  複雜度 : O((V + E) log V)
//  等級   : 藍 (1600-1899)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 有負邊不能用 Dijkstra,要用 Bellman-Ford
//           2. dist 用 long long;INF 設 4e18 會加爆 -> 用 LLONG_MAX/4
//           3. priority_queue 預設大的先出,要 greater 反過來
//           4. 出隊時要檢查 d > dist[u] 就跳過(懶惰刪除)
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll  = long long;
using pli = pair<ll,int>;
const ll INF = LLONG_MAX / 4;

vector<ll> dijkstra(const vector<vector<pair<int,ll>>>& g, int s, vector<int>* par = nullptr) {
    vector<ll> dist(g.size(), INF);
    if (par) par->assign(g.size(), -1);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;              // 過期的,丟掉
        for (auto [v, w] : g[u])
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (par) (*par)[v] = u;
                pq.push({dist[v], v});
            }
    }
    return dist;
}

// ── 還原路徑(要傳 par 進去 dijkstra)──────────────
vector<int> restore_path(const vector<int>& par, int s, int t) {
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) {
        path.push_back(v);
        if (v == s) break;
    }
    reverse(path.begin(), path.end());
    return path.empty() || path[0] != s ? vector<int>{} : path;
}

int main() {
    int n = 5;
    vector<vector<pair<int,ll>>> g(n);
    auto add = [&](int a, int b, ll w){ g[a].push_back({b,w}); g[b].push_back({a,w}); };
    add(0,1,4); add(0,2,1); add(2,1,2); add(1,3,5); add(2,3,8); add(3,4,3);

    vector<int> par;
    auto d = dijkstra(g, 0, &par);
    cout << "dist from 0 : ";
    for (ll x : d) cout << (x == INF ? -1 : x) << ' ';   // 0 3 1 8 11
    cout << "\n";
    cout << "path 0 -> 4 : ";
    for (int v : restore_path(par, 0, 4)) cout << v << ' ';
    cout << "\n";
    return 0;
}

// ══ 快速輸入輸出 + 常用縮寫 ═════════════════════════════
//  用途   : 每一題都貼這一段。cin/cout 不解綁會慢 5-10 倍
//  複雜度 : —
//  等級   : 灰 (<1200)
//  驗證   : [OK] 每題都在用
//  坑     : 解綁之後不能再混用 scanf/printf,會亂序
//  用法   : main() 第一行放 fastio();
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll  = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
#define all(x) (x).begin(), (x).end()
#define sz(x)  (int)(x).size()

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// ── 多筆測資的標準骨架 ────────────────────────────────
void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for (auto &x : a) cin >> x;
    cout << accumulate(all(a), 0LL) << '\n';
}

int main() {
    fastio();
    int T = 1;
    cin >> T;              // 單筆測資的題目就把這行註解掉
    while (T--) solve();
    return 0;
}

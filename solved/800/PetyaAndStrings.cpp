//
// Created by user on 2026/9/11.
//
// const ll  INF = LLONG_MAX / 4;
// const int MOD = 1000000007;
//
// Yes / No 常數（配合 string solve() 用）
// const string yes = "Yes", no = "No";
// string solve() {
//     int n; cin >> n;
//     // 要輸出數字：return std::format("{}", ans);
//     //
//     // 要輸出判斷：return "Yes";
//     //
//     // 要輸出無解：return "-1";
// }

#include <bits/stdc++.h>
using namespace std;

using ll  = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vi  = vector<int>;
using vll = vector<ll>;

#define pb      push_back
#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (int)(x).size()
#define fi first
#define se second

// ══════════════════════════════════════════════════════════════
//  CF 112A - Petya and Strings
//  兩個等長字串，忽略大小寫比字典序，輸出 -1 / 1 / 0
// ══════════════════════════════════════════════════════════════

// ──────────────────────────────────────────────────────────────
//  ▼▼▼ 你的第 4 版（保留，不刪）▼▼▼
//
//  void solve() {
//      string a;
//      string b;
//
//      cin>>a>>b;
//      for (auto x :a) {              // (C) range-for 拿不到 index，i 沒宣告
//          if (a[i]==b[i]) {
//              i++;                   // (C) 手動改 i 影響不到 range-for
//          }
//          else if (a[i]!=b[i]){
//              int a1 = a[i]-'a';
//              int b1 = b[i]-'a';
//              if (a1>b1) {
//                  cout<<1<<'\n';     // (D) 印完沒結束 -> 會印很多次
//              }else if (a1<b1) {
//                  cout<<-1<<'\n';
//              }else {
//                  cout<<0<<'\n';     // (F) dead code，永遠到不了
//              }
//          }
//      }
//                                     // (E) 兩串全同 -> 一個字都沒印
//  }                                  // (B) tolower 不見了
//
//  ▲▲▲ 你的第 4 版 ▲▲▲
// ──────────────────────────────────────────────────────────────

void solve() {
    string a, b;
    cin >> a >> b;

    // ── 塊 A：統一大小寫（這段是你自己寫的，原封不動搬回來）──
    transform(a.begin(), a.end(), a.begin(),
              [](unsigned char c) { return tolower(c); });
    transform(b.begin(), b.end(), b.begin(),
              [](unsigned char c) { return tolower(c); });

    // ── 塊 B：從左往右找第一個不同的位置 ──
    for (int i = 0; i < sz(a); i++) {
        if (a[i] == b[i]) continue;              // 這一位相同 -> 看下一位
        cout << (a[i] > b[i] ? 1 : -1) << '\n';  // 不同 -> 當場決定
        return;                                  // ★ 立刻結束，後面不看
    }
    cout << 0 << '\n';                           // ★ 掃完都沒不同 = 相等
}

// ──────────────────────────────────────────────────────────────
//  ★ 第二種寫法：string 內建就是字典序，連迴圈都不用
//    （AC 之後再回來把上面那版換成這個，體會一下差別）
//
//  void solve() {
//      string a, b;
//      cin >> a >> b;
//      transform(all(a), a.begin(), [](unsigned char c){ return tolower(c); });
//      transform(all(b), b.begin(), [](unsigned char c){ return tolower(c); });
//      if      (a < b) cout << -1 << '\n';
//      else if (a > b) cout <<  1 << '\n';
//      else            cout <<  0 << '\n';
//  }
// ──────────────────────────────────────────────────────────────

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;              //  單筆測資的題目，把這行註解掉
    while(t--) {
        solve();
    }
    return 0;
}

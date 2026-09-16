
//https://codeforces.com/problemset/problem/96/A
// A Football
// ══════════════════════════════════════════════════════════════
//  ★ 這一題(AC 之後,連 code 一起存進 solved/<rating>/)
// ──────────────────────────────────────────────────────────────
//  卡在哪     : 11 00   不同 ，3種  ifelse
//  關鍵想法   :更好是 長度 1  讀下一個跟時 +跟上一個 一樣 長度+1 or 歸0
//  線索       : ★★ 下次看到「        」就要想到「        」
//
//
//   「連續」這個概念在程式裡的通用形狀就是這兩行：一樣就加、不一樣就重設。你以後會在「最長連
//   續子陣列」「最長不下降段」「連續簽到天數」看到一模一樣的骨架。這個 pattern
//   比這一題本身值錢。
//══════════════════════════════════════════════════════════════
#if defined(__GNUC__) && !defined(__clang__)
    #include <bits/stdc++.h>          // GCC / MinGW(CLion 走這條)
#else
    #include <algorithm>              // MSVC 沒有 bits/stdc++.h
    #include <array>
    #include <bitset>
    #include <cmath>
    #include <cstring>
    #include <deque>
    #include <functional>
    #include <iostream>
    #include <map>
    #include <numeric>
    #include <queue>
    #include <set>
    #include <string>
    #include <tuple>
    #include <unordered_map>
    #include <unordered_set>
    #include <vector>
#endif
using namespace std;

using ll  = long long;
using ull = unsigned long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
#define all(x)  (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x)   (int)(x).size()

const ll  INF = LLONG_MAX / 4;
const int MOD = 1000000007;

// ── debug:交出去之前不用刪,它只在本機有作用 ──────────
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << endl
#else
#define dbg(x)
#endif

void solve() {
    string s;
    cin>>s;
    int count1 =0;//1
    int count2 =0;//0
    for (int i=1;i<sz(s);i++) {
        if (s[i-1]=='1' && s[i]=='1') {
            count1++;
            count2=0;
        }else if(s[i-1]=='0' && s[i]=='0'){
            count2 +=1;
            count1=0;

        }else {
            count1 =0;
            count2 =0;
        }if (count1>=6  || count2>=6) {
            cout<<"YES"<<'\n';
            return;
        }
    }
    cout<<"NO"<<'\n';


}
// ___------------------------------------------------------------------__
// void solve() {
//     string s;
//     cin >> s;
//     int run = 1;                     // 目前這一段連續多長。第 0 個字元自己就是長度 1
//     for (int i = 1; i < sz(s); i++) {
//     //以下精華
//         if (s[i] == s[i-1]) run++;   // 跟前一個一樣 -> 這段變長
//         else                 run = 1; // 不一樣 -> 從這個字元重新起算,長度是 1
//         if (run >= 7) {              // ★ 門檻就是題目給的 7,不用換算
//             cout << "YES" << '\n';
//             return;
//         }
//     }
//     cout << "NO" << '\n';
// }
// ___------------------------------------------------------------------__
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;                 // ← 單筆測資的題目,把這行註解掉
    while (T--) solve();
    return 0;
}


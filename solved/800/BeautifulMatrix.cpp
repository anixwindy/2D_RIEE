//
// Created by user on 2026/9/11.
//
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

void solve() {

//二維陣列
    vector<vi> a(5, vi(5,0));

    int ans =0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> a[i][j];

            if (a[i][j] == 1) {
                ans+= abs(i-2)+abs(j-2);
            }

        }
    }cout<<ans<<'\n';






}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;              //  單筆測資的題目,把這行註解掉
    while(t--) {
        solve();
    }
    return 0;
}











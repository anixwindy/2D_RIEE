// ══ 數位 DP ═════════════════════════════════════════════
//  用途   : 「1 到 N 之間有幾個數字滿足某條件」
//  複雜度 : O(位數 * 狀態數 * 10)
//  等級   : 紫 (1900-2099)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : ★★ 三個旗標一定要想清楚:
//             tight   : 前面都貼著上界 -> 這一位不能超過上界那位
//             started : 前面是不是還在前導零
//           2. 記憶化只能存 tight=false 的狀態,tight=true 的路徑唯一
//           3. 區間 [L,R] 的答案 = f(R) - f(L-1)
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 例題:求 0..N 之間,有多少個數字「不含相鄰重複數字」
struct DigitDP {
    string s;
    vector<vector<ll>> memo;                    // memo[pos][last+1]
    vector<vector<bool>> done;

    ll solve(ll N) {
        if (N < 0) return 0;
        s = to_string(N);
        int n = s.size();
        memo.assign(n, vector<ll>(11, 0));
        done.assign(n, vector<bool>(11, false));
        return go(0, 10, true, false);          // last=10 代表「還沒放過數字」
    }
    ll go(int pos, int last, bool tight, bool started) {
        if (pos == (int)s.size()) return 1;
        if (!tight && started && done[pos][last]) return memo[pos][last];

        int hi = tight ? s[pos] - '0' : 9;
        ll res = 0;
        for (int d = 0; d <= hi; ++d) {
            bool nstarted = started || d > 0;
            if (nstarted && started && d == last) continue;   // 相鄰不能一樣
            res += go(pos + 1, nstarted ? d : 10, tight && d == hi, nstarted);
        }
        if (!tight && started) { done[pos][last] = true; memo[pos][last] = res; }
        return res;
    }
};

int main() {
    DigitDP dp;
    cout << "count in [0,100] without adjacent equal digits = "
         << dp.solve(100) << "\n";
    // 區間 [L,R] 這樣算
    ll L = 10, R = 50;
    DigitDP a, b;
    cout << "count in [10,50] = " << a.solve(R) - b.solve(L - 1) << "\n";
    return 0;
}

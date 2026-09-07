// ══ KMP + Z 函數(字串匹配)═══════════════════════════
//  用途   : 在文字裡找模式串的所有出現位置;找最長 border
//  複雜度 : O(n + m)
//  等級   : 紫 (1900-2099)
//  驗證   : [  ] 還沒用它 AC 過
//  坑     : 1. ★ 分隔字元要選一個「不會出現在兩個串裡」的
//           2. failure/z 陣列的定義要記牢:
//                fail[i] = s[0..i] 的最長「真前綴 = 真後綴」長度
//                z[i]    = s[i..] 與 s 的最長共同前綴長度
//           3. z[0] 通常直接設成 n
// ═══════════════════════════════════════════════════════
#include <bits/stdc++.h>
using namespace std;

// ── KMP 的 failure function ──────────────────────
vector<int> kmp_fail(const string& s) {
    int n = s.size();
    vector<int> f(n, 0);
    for (int i = 1; i < n; ++i) {
        int j = f[i - 1];
        while (j > 0 && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) ++j;
        f[i] = j;
    }
    return f;
}

// 找 pat 在 txt 裡的所有起始位置
vector<int> kmp_search(const string& txt, const string& pat) {
    vector<int> res;
    if (pat.empty()) return res;
    string s = pat + char(1) + txt;             // char(1) 當分隔符
    auto f = kmp_fail(s);
    int m = pat.size();
    for (int i = m + 1; i < (int)s.size(); ++i)
        if (f[i] == m) res.push_back(i - 2 * m);
    return res;
}

// ── Z 函數 ─────────────────────────────────────
vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    if (n) z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

int main() {
    string txt = "ababcabab", pat = "abab";
    cout << "matches at : ";
    for (int p : kmp_search(txt, pat)) cout << p << ' ';       // 0 5
    cout << "\n";

    auto f = kmp_fail("aabaaab");
    cout << "fail : ";
    for (int x : f) cout << x << ' ';                          // 0 1 0 1 2 2 3
    cout << "\n";

    auto z = z_function("aabxaab");
    cout << "z    : ";
    for (int x : z) cout << x << ' ';                          // 7 1 0 0 3 1 0
    cout << "\n";
    return 0;
}

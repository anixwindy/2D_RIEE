

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define F first
#define S second


#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    if (!(cin >> n >> k)) return;


    vi a(n);

    // 2. 讀取所有人的分數
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // 3. 抓出「第 k 名的分數」作為門檻
    // 注意：陣列索引從 0 開始，所以第 k 名是 a[k - 1]
    int threshold = a[k - 1];

    int count = 0;

    // 4. 計算有幾個人達標
    for (int i = 0; i < n; ++i) {
        // 條件：大於等於門檻，且必須大於 0 分
        if (a[i] >= threshold && a[i] > 0) {
            count++;
        }
    }

    // 5. 輸出晉級人數
    cout << count << "\n";
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;

    while(t--) {
        solve();
    }

    return 0;
}
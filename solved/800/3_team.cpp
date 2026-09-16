

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define F first
#define S second

int  solve() {
    // ============ 在這裡寫你的解題code ============

    int total=0,your_input;

    for (int i = 0; i < 3; ++i) {
        cin>>your_input;
        total+=your_input;
    }
    return (total>=2);//if (sum >= 2) return 1; else return 0;



    // ============================================
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int final_ans = 0;
    int t = 1;
    cin >> t;  // 如果題目只有一組測試,就把這行註解掉

    while(t--) {
        final_ans += solve();

    }cout << final_ans << endl;

    return 0;
}
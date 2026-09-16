
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define F first
#define S second
int solve() {
    int sum = 0;
    int m,n;
    cin>>m>>n;
    int k = n / 2;   // 水平方向可以配對的欄數
    int y = m / 2;   // 垂直方向可以配對的列數




    if (n % 2 == 0) {
        sum += k * m;
    } else {
        sum += k * m;
        sum += y;
    }

    return sum;
}









int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;


    while(t--) {
        cout << solve() << "\n";

    }

    return 0;
}

//https://codeforces.com/problemset/problem/4/A
// // #include <iostream>
#include <format>
#include <bits/stdc++.h>
using namespace std;

#define all(x) (x).begin(), (x).end()
#define fastIO do { ios::sync_with_stdio(0); cin.tie(0); } while (0)

void solve() {
    // 這裡寫邏輯
    int n;
    if (!(cin >> n)) return;
    if (n>2 && n%2==0) {
        cout<<"YES"<< "\n";

    }else cout<<"NO"<< "\n";


}



int main() {
    fastIO; // 呼叫加速代碼

    int t = 1;//<--看情況

    while (t--) {
        solve();
    }
    return 0;
}

/*
* #include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define F first
#define S second

void solve() {
    // ============ 解題區 ===== */
//
// Created by user on 2026/1/27.
//
#include<bits/stdc++.h>
#include<string>
#include<format>

//https://codeforces.com/problemset/problem/71/A
#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define F first
#define S second
using namespace std;

void solve() {
    string a;
    cin>>a;
    int len = a.size();
    char llast=a[len-1];
    char ffirst=a[0];
    if (len>10) {
        int k = (len-2);
        string b =to_string(k);
        cout<<format("{}{}{}",ffirst,b,llast)<<"\n";
    }else cout<<a<<endl;
}


int main() {




    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    cin>>t;
    while (t--) {
        solve();
    }


    return 0;
}
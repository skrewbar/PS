#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 10'007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    
    vector<vector<int>> palindromeCnt(s.size(), vector<int>(s.size()));
    for (int i = 0; i < s.size(); i++) palindromeCnt[i][i] = 1;
    for (int i = 0; i < s.size() - 1; i++) {
        palindromeCnt[i][i+1] = 2;
        if (s[i] == s[i+1]) palindromeCnt[i][i+1]++;
    }

    for (int k = 2; k < s.size(); k++) {
        for (int i = 0; i + k < s.size(); i++) {
            if (s[i] == s[i+k]) {
                palindromeCnt[i][i+k] = (palindromeCnt[i+1][i+k] + palindromeCnt[i][i+k-1] + 1) % MOD;
            } else {
                palindromeCnt[i][i+k] = (palindromeCnt[i+1][i+k] + palindromeCnt[i][i+k-1] - palindromeCnt[i+1][i+k-1] + MOD) % MOD;
            }
        }
    }

    cout << palindromeCnt[0][s.size()-1];
}
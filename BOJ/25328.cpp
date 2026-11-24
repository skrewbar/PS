#include <bits/stdc++.h>
using namespace std;

int k;
map<string, int> cnt;
string temp;

void backtracking(string s, int index) {
    if (temp.length() == k) {
        cnt[temp]++;
        return;
    }

    if (index == s.length()) return;

    temp += s[index];
    backtracking(s, index+1);
    temp.pop_back();
    backtracking(s, index+1);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    string x, y, z;
    cin >> x >> y >> z;
    cin >> k;

    backtracking(x, 0);
    backtracking(y, 0);
    backtracking(z, 0);


    bool isAnswerE = false;
    for (pair<string, int> p : cnt) {
        if (p.second > 1) {
            cout << p.first << '\n';
            isAnswerE = true;
        }
    }

    if (not isAnswerE) cout << -1;


    return 0;
}
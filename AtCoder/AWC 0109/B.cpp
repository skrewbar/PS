#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    vector<char> stk;
    for (int i = 0; i < S.length(); i++) {
        stk.push_back(S[i]);

        if (stk.size() >= 2 and stk[stk.size() - 2] == stk.back()) {
            stk.pop_back();
            stk.pop_back();
        }
    }

    cout << stk.size();

    return 0;
}

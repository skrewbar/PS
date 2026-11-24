#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> stk;

    for (int i = 0; i < N; i++) {
        int a;
        cin >> a;

        if (stk.empty()) {
            stk.push_back(a);
            continue;
        }

        if (stk.back() + a == 3) stk.pop_back();
        else stk.push_back(a);
    }

    for (int i = 0; i < stk.size(); i++) {
        if (stk[i] == 2) {
            cout << "No";
            return 0;
        }
    }

    cout << (stk.size() % 3 == 0 ? "Yes" : "No");

    return 0;
}

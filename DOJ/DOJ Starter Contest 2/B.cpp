#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];

    vector<int> B(N + 1);
    for (int i = 1; i <= N; i++) cin >> B[i];

    bool consistent = true;
    for (int i = 1; i <= N; i++) {
        if (A[i] < B[i]) consistent = false;
    }

    if (consistent) cout << "YES";
    else cout << "NO";

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int sumA = 0;
    int sumB = 0;

    for (int i = 1; i <= N; i++) {
        int A;
        cin >> A;
        sumA += A;
    }
    for (int i = 1; i <= M; i++) {
        int B;
        cin >> B;
        sumB += B;
    }

    if (sumA > sumB) cout << "YES";
    else cout << "NO";

    return 0;
}
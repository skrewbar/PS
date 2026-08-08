#include <bits/stdc++.h>
using namespace std;

int query(int a, int b) {
    cout << "? " << a << ' ' << b << endl;

    int res;
    cin >> res;

    return res;
}

void answer(int x) { cout << "! " << x << endl; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i + 2 <= N; i += 2) {
        int res = query(i, i + 1);

        if (res) {
            res = query(i, N);

            if (res) answer(i);
            else answer(i + 1);
            return 0;
        }
    }

    int res = query(1, N - 1);
    if (res) answer(N - 1);
    else answer(N);

    return 0;
}
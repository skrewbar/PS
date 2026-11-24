#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

map<int, int> answer;

int matrix[2222][2222];

void dnc(int r1, int c1, int sz) {
    bool same = true;

    for (int i = r1; i < r1 + sz; i++) {
        if (not same)
            break;

        for (int j = c1; j < c1 + sz; j++) {
            if (matrix[i][j] != matrix[r1][c1]) {
                same = false;
                break;
            }
        }
    }

    if (same) {
        answer[matrix[r1][c1]]++;
        return;
    }

    sz /= 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            dnc(r1 + i * sz, c1 + j * sz, sz);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> matrix[i][j];
        }
    }

    dnc(0, 0, N);

    println("{}\n{}\n{}", answer[-1], answer[0], answer[1]);

    return 0;
}
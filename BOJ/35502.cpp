#include <bits/stdc++.h>
using namespace std;

using ldouble = long double;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

constexpr int delta[] = {1, -1, 0, 0};

ldouble expects[555][555][10];
ldouble minEx[555][555];
int A[10];

int N, M, D;

bool isInvalid(int r, int c) {
    return r <= 0 or r > N or c <= 0 or c > M;
}

bool renewExpect(int r, int c) {
    ldouble sortedEx[10];
    for (int i = 0; i < D; i++)
        sortedEx[i] = expects[r][c][i];

    sort(sortedEx, sortedEx + D);
    bool renewed = false;
    ldouble sum = 0;
    for (int i = 0; i < D; i++) {
        if (isinf(sortedEx[i]))
            break;

        sum += sortedEx[i];
        if (minimize(minEx[r][c], (D + sum) / (i + 1)))
            renewed = true;
    }

    return renewed;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> D;
    for (int i = 0; i < D; i++)
        cin >> A[i];

    fill(&expects[0][0][0], &expects[N + 1][M][D], INFINITY);
    fill(&minEx[0][0], &minEx[N + 1][M], INFINITY);

    MinHeap<tuple<ldouble, int, int>> pq;
    fill(expects[N][M], expects[N][M] + D, 0);
    pq.emplace(minEx[N][M] = 0, N, M);

    while (not pq.empty()) {
        auto [ex, r, c] = pq.top();
        pq.pop();

        if (ex > minEx[r][c])
            continue;

        for (int i = 0; i < D; i++) {
            for (int k = 0; k < 4; k++) {
                int nr = r + delta[k] * A[i];
                int nc = c + delta[3 - k] * A[i];

                if (isInvalid(nr, nc))
                    continue;

                if (not minimize(expects[nr][nc][i], ex))
                    continue;

                if (renewExpect(nr, nc))
                    pq.emplace(minEx[nr][nc], nr, nc);
            }
        }
    }

    if (isinf(minEx[1][1]))
        println("-1");
    else
        println("{:.12f}", minEx[1][1]);

    return 0;
}
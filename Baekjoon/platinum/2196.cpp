#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

int xorCount[111][1 << 18];
int nums[111];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int B, E;
    cin >> B >> E;

    string targetStr;
    cin >> targetStr;
    int target = stoi(targetStr, nullptr, 2);

    for (int i = 0; i < E; i++) {
        string numStr;
        cin >> numStr;
        nums[i] = stoi(numStr, nullptr, 2);
    }

    fill(&xorCount[0][0], &xorCount[E][1 << B], INF);
    xorCount[0][0] = 1;
    xorCount[0][nums[0]] = 2;

    for (int i = 1; i < E; i++) {
        xorCount[i][nums[i]] = 2;
        for (int j = 0; j < i; j++)
            xorCount[i][nums[i] ^ nums[j]] = 1;

        for (int j = 0; j < (1 << B); j++) {
            int k = j ^ nums[i];

            xorCount[i][j] = min(
                {xorCount[i][j], xorCount[i - 1][j], xorCount[i - 1][k] + 1});
        }
    }

    int answer = 0;
    int ansDiffCnt = INF;
    for (int k = 0; k < (1 << B); k++) {
        if (xorCount[E - 1][k] == INF)
            continue;

        int diffCount = 0;
        for (int i = 0; i < B; i++) {
            if ((k & (1 << i)) != (target & (1 << i)))
                diffCount++;
        }

        if (diffCount < ansDiffCnt or
            (diffCount == ansDiffCnt and
             xorCount[E - 1][k] < xorCount[E - 1][answer])) {
            answer = k;
            ansDiffCnt = diffCount;
        }
    }

    println("{}", xorCount[E - 1][answer]);
    for (int i = B - 1; i >= 0; i--) {
        if (answer & (1 << i))
            print("1");
        else
            print("0");
    }

    return 0;
}
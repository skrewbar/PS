#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

unordered_map<int, int> grundy;

int getGrundy(int bit) {
    if (grundy.contains(bit))
        return grundy[bit];

    int& ret = grundy[bit];

    vector<bool> possible(30);
    for (int i = 0; i < 30; i++) {
        if (~bit & (1 << i))
            continue;

        int nextBit = bit;
        for (int j = 0; j <= i; j++) {
            if (~bit & (1 << j))
                continue;

            if ((i + 1) % (j + 1) == 0)
                nextBit ^= 1 << j;
        }
        possible[getGrundy(nextBit)] = true;
    }

    while (possible[ret])
        ret++;

    return ret;
}

vector<int> getBestPlays(int bit) {
    vector<int> ret;

    for (int i = 0; i < 30; i++) {
        if (~bit & (1 << i))
            continue;

        int nextBit = bit;
        for (int j = 0; j <= i; j++) {
            if (~bit & (1 << j))
                continue;

            if ((i + 1) % (j + 1) == 0)
                nextBit ^= 1 << j;
        }
        int nextGrundy = getGrundy(nextBit);
        if (nextGrundy == 0)
            ret.push_back(i + 1);
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> X(N);
    int bit = 0;
    for (int i = 0; i < N; i++) {
        cin >> X[i];
        bit |= 1 << (X[i] - 1);
    }

    for (int i = 0; i < N; i++) {
        print("({}) ", X[i]);

        int nextBit = bit;
        for (int j = 0; j < X[i]; j++) {
            if (~bit & (1 << j))
                continue;

            if (X[i] % (j + 1) == 0)
                nextBit ^= 1 << j;
        }

        vector<int> best = getBestPlays(nextBit);

        if (best.size() == 0) {
            print("A\n");
        } else {
            for (int num : best)
                print("{} ", num);
            println();
        }
    }

    return 0;
}
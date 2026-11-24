#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

enum Category : uint8_t {
    ONES = 0,
    TWOS = 1,
    THREES = 2,
    FOURS = 3,
    FIVES = 4,
    SIXES = 5,

    CHANCE = 6,
    THREE_KIND = 7,
    FOUR_KIND = 8,
    SHORT_STRAIGHT = 9,
    LONG_STRAIGHT = 10,
    FULL_HOUSE = 11,
    YAHTZEE = 12,
};

int dice[15][10], dp[15][1 << 13], scoreCache[15][15];

int getScore(int i, Category category) {
    int& score = scoreCache[i][category];
    if (score != -1)
        return score;

    score = 0;

    switch (category) {
        default: {
            for (int j = 0; j < 5; j++)
                if (dice[i][j] == category + 1)
                    score += category + 1;
            break;
        }
        case CHANCE: {
            for (int j = 0; j < 5; j++)
                score += dice[i][j];
            break;
        }
        case THREE_KIND: {
            int sum = 0;
            for (int j = 0; j < 5; j++)
                sum += dice[i][j];

            for (int k = 1; k <= 6; k++) {
                int count = 0;
                for (int j = 0; j < 5; j++)
                    if (dice[i][j] == k)
                        count++;
                if (count >= 3) {
                    score = sum;
                    break;
                }
            }
            break;
        }
        case FOUR_KIND: {
            int sum = 0;
            for (int j = 0; j < 5; j++)
                sum += dice[i][j];

            for (int k = 1; k <= 6; k++) {
                int count = 0;
                for (int j = 0; j < 5; j++)
                    if (dice[i][j] == k)
                        count++;
                if (count >= 4) {
                    score = sum;
                    break;
                }
            }
            break;
        }
        case SHORT_STRAIGHT: {
            int count[7] = {};
            for (int j = 0; j < 5; j++)
                count[dice[i][j]]++;

            if ((count[1] and count[2] and count[3] and count[4]) or
                (count[2] and count[3] and count[4] and count[5]) or
                (count[3] and count[4] and count[5] and count[6]))
                score += 25;

            break;
        }
        case LONG_STRAIGHT: {
            int count[7] = {};
            for (int j = 0; j < 5; j++)
                count[dice[i][j]]++;

            if ((count[1] and count[2] and count[3] and count[4] and
                 count[5]) or
                (count[2] and count[3] and count[4] and count[5] and count[6]))
                score += 35;

            break;
        }
        case FULL_HOUSE: {
            if (dice[i][0] == dice[i][1] and dice[i][2] == dice[i][3] and
                dice[i][3] == dice[i][4])
                score = 40;
            if (dice[i][0] == dice[i][1] and dice[i][1] == dice[i][2] and
                dice[i][3] == dice[i][4])
                score = 40;
            break;
        }
        case YAHTZEE: {
            bool same = true;
            for (int j = 0; j < 4; j++)
                if (dice[i][j] != dice[i][j + 1])
                    same = false;

            if (same)
                score = 50;
            break;
        }
    }

    return score;
}

int getMaxScore(int category, int state) {
    if (category < 0)
        return 0;

    int& ret = dp[category][state];
    if (ret != -1)
        return ret;

    for (int i = 0; i < 13; i++) {
        if (state & (1 << i))
            continue;
        ret = max(ret, getMaxScore(category - 1, state | (1 << i)) +
                           getScore(i, Category(category)));
    }

    if (category == SIXES and ret >= 63)
        ret += 35;
    return ret;
}

void solve(int tc) {
    fill(&dp[0][0], &dp[13][1 << 13], -1);
    fill(&scoreCache[0][0], &scoreCache[14][15], -1);

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 5; j++) {
            cin >> dice[i][j];
        }
        sort(dice[i], dice[i] + 5);
    }

    print("Case {}: {}\n", tc, getMaxScore(YAHTZEE, 0));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++)
        solve(tc);

    return 0;
}
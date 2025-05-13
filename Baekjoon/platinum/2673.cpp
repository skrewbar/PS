#include <bits/stdc++.h>
using namespace std;

class Chord {
   public:
    int start, end;
    Chord(int _start, int _end) : start(_start), end(_end) {
        if (end < start)
            swap(start, end);
    }

    bool operator==(const Chord& c) const {
        return start == c.start and end == c.end;
    }
};

namespace std {
template <>
struct hash<Chord> {
    size_t operator()(const Chord& c) const { return c.start + c.end * 100; }
};
}  // namespace std

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unordered_set<Chord> chords;
    vector<vector<int>> dp(101, vector<int>(101));

    int n;
    cin >> n;
    while (n--) {
        int s, e;
        cin >> s >> e;
        chords.insert(Chord(s, e));
    }

    for (int size = 1; size <= 100; size++) {
        for (int i = 1; i <= 100; i++) {
            int j = i + size - 1;
            if (j > 100)
                continue;
            for (int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
            dp[i][j] += chords.contains(Chord(i, j));
        }
    }

    cout << dp[1][100];
}
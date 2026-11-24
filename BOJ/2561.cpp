#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct Range {
    int l, r;
};

/**
 * use 1-based index
 */
template <typename T>
struct Flipper {
    stack<Range> flipRanges;
    vector<T>& v;

    Flipper(vector<T>& v) : v(v) {}

    void flip(int l, int r) {
        reverse(v.begin() + l, v.begin() + r + 1);
        flipRanges.emplace(l, r);
    }

    Range popflip() {
        Range range = flipRanges.top();
        flipRanges.pop();

        auto [l, r] = range;
        reverse(v.begin() + l, v.begin() + r + 1);
        return range;
    }

    void rollBackNTimes(int n) {
        while (n-- and not flipRanges.empty()) {
            auto [l, r] = flipRanges.top();
            flipRanges.pop();
            reverse(v.begin() + l, v.begin() + r + 1);
        }
    }

    bool sorted() const {
        for (int i = 1; i < (int)v.size(); i++)
            if (v[i] != i)
                return false;
        return true;
    }

    bool empty() const { return flipRanges.empty(); }
};

int n;

template <typename T>
bool flipTwice(Flipper<T>& flipper) {
    vector<T>& v = flipper.v;
    int l, r;

    l = 1;
    while (l < n and v[l] == l)
        l++;
    r = l;
    while (r < n and v[r] != l)
        r++;
    flipper.flip(l, r);

    l = 1;
    while (l < n and v[l] == l)
        l++;
    r = l;
    while (r < n and v[r] != l)
        r++;
    flipper.flip(l, r);

    if (flipper.sorted())
        return true;

    flipper.rollBackNTimes(2);

    r = n;
    while (r > 0 and v[r] == r)
        r--;
    l = r;
    while (l > 0 and v[l] != r)
        l--;
    flipper.flip(l, r);

    l = 1;
    while (l < n and v[l] == l)
        l++;
    r = l;
    while (r < n and v[r] != l)
        r++;
    flipper.flip(l, r);

    return flipper.sorted();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    vector<int> board(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> board[i];

    Flipper flipper(board);
    if (flipper.sorted()) {
        print("1 1\n1 1\n1 1\n");
        return 0;
    }

    vector<int> endpoints;
    if (board[1] != 1)
        endpoints.push_back(1);
    for (int i = 2; i <= n; i++) {
        if (abs(board[i] - board[i - 1]) != 1) {
            endpoints.push_back(i - 1);
            endpoints.push_back(i);
        }
    }
    if (board[n] != n)
        endpoints.push_back(n);

    int intervalCnt = endpoints.size();
    for (int i = 0; i < intervalCnt; i++) {
        for (int j = i; j < intervalCnt; j++) {
            flipper.flip(endpoints[i], endpoints[j]);
            if (flipTwice(flipper)) {
                stack<Range> rev_ranges;
                while (not flipper.empty())
                    rev_ranges.push(flipper.popflip());
                while (not rev_ranges.empty()) {
                    auto [l, r] = rev_ranges.top();
                    rev_ranges.pop();
                    print("{} {}\n", l, r);
                }
                return 0;
            }
            flipper.rollBackNTimes(3);
        }
    }

    assert(false);
}
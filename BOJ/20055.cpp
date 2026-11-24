#include <bits/stdc++.h>
using namespace std;

struct ConveyorBelt {
    int n;
    list<int> robots;
    deque<int> durability;

    ConveyorBelt(int n) : n(n), durability(2*n) {}

    int broken = 0;

    void rotate() {
        durability.push_front(durability.back());
        durability.pop_back();

        for (auto it = robots.rbegin(); it != robots.rend(); it++)
            (*it)++;
        if (not robots.empty() and robots.back() == n - 1)
            robots.pop_back();
    }

    void move() {
        for (auto it = robots.rbegin(); it != robots.rend(); it++) {
            if (it != robots.rbegin() and *prev(it) == *it + 1)
                continue;
            if (durability[*it + 1] == 0)
                continue;

            (*it)++;
            if (--durability[*it] == 0)
                broken++;
        }
        if (not robots.empty() and robots.back() == n - 1)
            robots.pop_back();
    }

    void putRobot() {
        if (durability[0] == 0)
            return;

        robots.push_front(0);
        if (--durability[0] == 0)
            broken++;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    ConveyorBelt belt(N);
    for (int i = 0; i < 2*N; i++)
        cin >> belt.durability[i];

    int answer = 0;
    while (belt.broken < K) {
        answer++;
        belt.rotate();
        belt.move();
        belt.putRobot();
    }

    cout << answer;

    return 0;
}
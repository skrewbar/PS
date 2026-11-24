#include <bits/stdc++.h>
using namespace std;

struct Shark {
    int size, speed, intelli;

    bool operator==(const Shark& shark) const = default;

    bool eatable(const Shark& shark) const {
        return size >= shark.size and speed >= shark.speed and
               intelli >= shark.intelli;
    }
};

vector<bool> matched;
vector<int> matching;
vector<vector<int>> eatableList;

bool canBeMatched(int shark) {
    for (int prey : eatableList[shark]) {
        if (matched[prey])
            continue;
        matched[prey] = true;

        if (matching[prey] == -1 or canBeMatched(matching[prey])) {
            matching[prey] = shark;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Shark> sharks(n);
    matched = vector(n, false);
    matching = vector(n, -1);
    eatableList = vector<vector<int>>(n);

    for (auto& [size, speed, intelli] : sharks)
        cin >> size >> speed >> intelli;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (sharks[i].eatable(sharks[j])) {
                if (sharks[i] == sharks[j] and
                    i <= j)  // 인덱스가 큰 상어가 작은 상어를 왕
                    continue;
                eatableList[i].push_back(j);
            }
        }
    }

    int eatenCnt = 0;
    for (int i = 0; i < n; i++) {
        ranges::fill(matched, false);
        eatenCnt += canBeMatched(i);
        ranges::fill(matched, false);
        eatenCnt += canBeMatched(i);
    }

    cout << n - eatenCnt;
}
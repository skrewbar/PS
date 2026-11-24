#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }
#define by_desc(x) [](const auto& a, const auto& b) { return a.x > b.x; }

template <typename T>
bool minimize(T& target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T>
bool maximize(T& target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

constexpr ll INF = 1e16;

struct Book {
    int id;
    ll W, V, T;
} books[202020];

int N, K;
ll fatigue = INF;
vector<int> answerPerm;

void findAnswer(bool traceback = false) {
    priority_queue<pair<ll, int>> pq;
    map<ll, int> TCnt;
    ll minW = INF, idW, minWT = INF, idWT;
    ll S = 0;

    for (int i = 1; i <= K - 1; i++) {
        S += books[i].W;
        pq.emplace(books[i].W, i);
        TCnt[books[i].T]++;
    }
    auto [_, p] = pq.top();
    pq.pop();

    auto [id, W, V, T] = books[p];
    S -= W;
    if (--TCnt[T] == 0)
        TCnt.erase(T);
    TCnt[books[K].T]++;

    if (minimize(minW, W))
        idW = id;
    if (minimize(minWT, W + T))
        idWT = id;

    for (int i = K; i <= N; i++) {
        S += books[i].W;
        ll minT = TCnt.begin()->first;

        // find answer
        ll f = S + books[i].V + minT + min(minW, minWT - minT);
        if (traceback and f == fatigue) {
            answerPerm.push_back(books[i].id);
            answerPerm.push_back(minW < minWT - minT ? idW : idWT);

            while (not pq.empty()) {
                tie(_, p) = pq.top();
                pq.pop();
                answerPerm.push_back(books[p].id);
            }

            return;
        } else
            minimize(fatigue, f);
        if (i == N)
            break;

        // update
        pq.emplace(books[i].W, i);
        tie(_, p) = pq.top();
        pq.pop();

        id = books[p].id;
        W = books[p].W;
        T = books[p].T;
        S -= W;

        if (--TCnt[T] == 0)
            TCnt.erase(T);
        TCnt[books[i + 1].T]++;

        if (minimize(minW, W))
            idW = id;
        if (minimize(minWT, W + T))
            idWT = id;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    for (int i = 1; i <= N; i++) {
        auto& [idx, W, V, T] = books[i];
        idx = i;
        cin >> W >> V >> T;
    }
    if (K == 1) {
        int answerId = 0;

        for (int i = 1; i <= N; i++) {
            auto [_, W, V, T] = books[i];
            if (minimize(fatigue, W + V + T))
                answerId = i;
        }

        answerPerm.push_back(answerId);
    } else {
        sort(books + 1, books + N + 1, by(V));
        findAnswer();
        findAnswer(true);
    }

    println("{}", fatigue);
    for (int i : answerPerm)
        print("{} ", i);

    return 0;
}


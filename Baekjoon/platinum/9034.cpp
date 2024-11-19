#include <bits/stdc++.h>
using namespace std;

vector<int> tree;

void add(int i, int value) {
    i += tree.size()/2;
    for (tree[i] += value; i > 1; i >>= 1) {
        tree[i >> 1] = tree[i] + tree[i^1];
    }
}

int get_range_sum(int l, int r) {
    l += tree.size()/2;
    r += tree.size()/2;
    int sum = 0;
    for (;l <= r; l >>= 1, r >>= 1) {
        if (l & 1) sum += tree[l++];
        if (~r & 1) sum += tree[r--];
    }
    return sum;
}

vector<int> score;
vector<int> unique_score;

struct Query {
    char type;
    int j;
    int k;
};
vector<Query> queries;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        score.resize(n);
        score.assign(score.size(), 0);
        unique_score.clear();
        unique_score.push_back(0);

        int m;
        cin >> m;
        queries.resize(m);

        for (int i = 0; i < m; i++) {
            char type;
            cin >> type;
            int j;
            cin >> j;
            j--;
            if (type == 'R') {
                int k;
                cin >> k;
                queries[i] = {type, j, k};
                score[j] += k;
                unique_score.push_back(score[j]);
            } else queries[i] = {type, j};
        }

        sort(unique_score.begin(), unique_score.end());
        unique_score.erase(unique(unique_score.begin(), unique_score.end()), unique_score.end());

        tree.resize(unique_score.size() * 2);
        tree.assign(tree.size(), 0);
        score.assign(score.size(), 0);
        for (auto q : queries) {
            if (q.type == 'R') {
                add(lower_bound(unique_score.begin(), unique_score.end(), score[q.j]) - unique_score.begin(), -1);
                score[q.j] += q.k;
                add(lower_bound(unique_score.begin(), unique_score.end(), score[q.j]) - unique_score.begin(), 1);
            } else {
                cout << get_range_sum(lower_bound(unique_score.begin(), unique_score.end(), score[q.j]) - unique_score.begin() + 1, unique_score.size() - 1) + 1 << '\n';
            }
        }
    }
}
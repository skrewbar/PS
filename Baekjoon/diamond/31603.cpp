#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

using ll = long long;

struct PSTNode {
    PSTNode *left = nullptr, *right = nullptr;
    ll value = 0;

    void modify(PSTNode* prev, int s, int e, int i, int v) {
        if (s == e) {
            this->value = v;
            return;
        }

        int m = (s + e) / 2;
        if (i <= m) {
            this->left = new PSTNode;
            this->right = prev->right;
            this->left->modify(prev->left, s, m, i, v);
        } else {
            this->left = prev->left;
            this->right = new PSTNode;
            this->right->modify(prev->right, m + 1, e, i, v);
        }

        this->value = this->left->value + this->right->value;
    }

    void modifyInPlace(int s, int e, int i, int v) {
        if (s == e) {
            this->value = v;
            return;
        }

        int m = (s + e) / 2;
        PSTNode* newNode = new PSTNode;
        if (i <= m) {
            newNode->left = this->left->left;
            newNode->right = this->left->right;
            this->left = newNode;
            this->left->modifyInPlace(s, m, i, v);
        } else {
            newNode->left = this->right->left;
            newNode->right = this->right->right;
            this->right = newNode;
            this->right->modifyInPlace(m + 1, e, i, v);
        }

        this->value = this->left->value + this->right->value;
    }

    int getKth(PSTNode* prev, int s, int e, int& k) {
        if (s == e)
            return s;

        int m = (s + e) / 2;
        int leftValue = this->left->value - prev->left->value;

        if (leftValue >= k) {
            return this->left->getKth(prev->left, s, m, k);
        } else {
            k -= leftValue;
            return this->right->getKth(prev->right, m + 1, e, k);
        }
    }
};

PSTNode* yCountTree[101010];
PSTNode* eulerTourTree[101010];

void initSegmentTree(PSTNode* node, int s, int e) {
    if (s == e)
        return;

    node->left = new PSTNode;
    node->right = new PSTNode;

    int m = (s + e) / 2;
    initSegmentTree(node->left, s, m);
    initSegmentTree(node->right, m + 1, e);
}

int n, q, root;
int sz[101010], in[101010], out[101010];
vector<int> childs[101010];

void eulerTour(int cur) {
    sz[cur] = 1;
    out[cur] = in[cur];

    eulerTourTree[in[cur]] = new PSTNode;
    eulerTourTree[in[cur]]->modify(eulerTourTree[in[cur] - 1], 1, n, cur, 1);

    for (int child : childs[cur]) {
        in[child] = out[cur] + 1;
        eulerTour(child);
        out[cur] = out[child];
        sz[cur] += sz[child];
    }
}

void preprocessPST(int cur) {
    for (int child : childs[cur]) {
        yCountTree[child] = new PSTNode;
        yCountTree[child]->modify(yCountTree[cur], 1, n, cur,
                                  sz[cur] - sz[child]);
        preprocessPST(child);
    }

    yCountTree[cur]->modifyInPlace(1, n, cur, sz[cur]);
}

void preprocess() {
    eulerTourTree[0] = new PSTNode;
    initSegmentTree(eulerTourTree[0], 1, n);
    in[root] = 1;
    eulerTour(root);

    yCountTree[root] = new PSTNode;
    initSegmentTree(yCountTree[root], 1, n);
    preprocessPST(root);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;

        if (p == 0)
            root = i;
        else
            childs[p].push_back(i);
    }
    preprocess();

    while (q--) {
        ll k;
        cin >> k;

        int x = (k - 1) / n + 1;
        k = (k - 1) % n + 1;

        PSTNode* node = yCountTree[x];
        int s = 1, e = n;
        while (s != e) {
            int m = (s + e) / 2;

            if (node->left->value >= k) {
                node = node->left;
                e = m;
            } else {
                k -= node->left->value;
                node = node->right;
                s = m + 1;
            }
        }
        int lca = s;

        PSTNode* lcaLo = eulerTourTree[in[lca] - 1];
        PSTNode* lcaHi = eulerTourTree[out[lca]];
        PSTNode *exLo, *exHi;
        exLo = exHi = eulerTourTree[0];

        if (lca != x) {
            int lo = 0, hi = childs[lca].size();
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                int c = childs[lca][mid];

                if (in[c] <= in[x])
                    lo = mid + 1;
                else
                    hi = mid;
            }
            int exclude = childs[lca][lo - 1];

            exLo = eulerTourTree[in[exclude] - 1];
            exHi = eulerTourTree[out[exclude]];
        }
        s = 1, e = n;
        while (s != e) {
            int m = (s + e) / 2;

            int leftValue = lcaHi->left->value - lcaLo->left->value -
                            (exHi->left->value - exLo->left->value);

            if (leftValue >= k) {
                lcaLo = lcaLo->left;
                lcaHi = lcaHi->left;
                exLo = exLo->left;
                exHi = exHi->left;

                e = m;
            } else {
                k -= leftValue;

                lcaLo = lcaLo->right;
                lcaHi = lcaHi->right;
                exLo = exLo->right;
                exHi = exHi->right;

                s = m + 1;
            }
        }

        int y = s;

        ll ans = 0;
        ans += (ll)(x - 1) * n * n;
        ans += (ll)(lca - 1) * n;
        ans += y - 1;
        println("{}", ans);
    }

    return 0;
}
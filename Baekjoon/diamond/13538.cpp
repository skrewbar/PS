#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct PSTSegmentTree {
    struct Node {
        Node *prev = nullptr, *left = nullptr, *right = nullptr;
        int cnt = 0;

        ~Node() {
            if (prev) {
                if (left != prev->left)
                    delete left;
                if (right != prev->right)
                    delete right;
            }
        }
    };

    vector<Node*> roots;
    int height, maxValue;

    PSTSegmentTree(int n) {
        roots.push_back(new Node());

        height = ceil(log2(n)) + 1;
        maxValue = (1 << height) - 1;

        init(roots.back(), 0, maxValue);
    }
    void init(Node* now, int start, int end) {
        if (start == end)
            return;

        now->left = new Node();
        now->right = new Node();

        int mid = (start + end) >> 1;

        init(now->left, start, mid);
        init(now->right, mid + 1, end);
    }

    void add(int value) {
        Node* newRoot = new Node();
        newRoot->prev = roots.back();
        roots.push_back(newRoot);

        add(newRoot, 0, maxValue, value);
    }
    void add(Node* now, int start, int end, int value) {
        if (start == end) {
            now->cnt = now->prev->cnt + 1;
            return;
        }

        int mid = (start + end) >> 1;
        if (value <= mid) {
            now->left = new Node();
            now->right = now->prev->right;

            now->left->prev = now->prev->left;
            add(now->left, start, mid, value);
        } else {
            now->left = now->prev->left;
            now->right = new Node();

            now->right->prev = now->prev->right;
            add(now->right, mid + 1, end, value);
        }

        now->cnt = now->left->cnt + now->right->cnt;
    }

    int maxXOR(int left, int right, int value) {
        return maxXOR(roots[left - 1], roots[right], 0, maxValue, value,
                      height - 1);
    }
    int maxXOR(Node* left, Node* right, int start, int end, int value, int h) {
        if (start == end)
            return start;

        int mid = (start + end) >> 1;

        int lcnt = right->left->cnt - left->left->cnt;
        int rcnt = right->right->cnt - left->right->cnt;

        if (value & (1 << h) and lcnt)
            return maxXOR(left->left, right->left, start, mid, value, h - 1);
        if (~value & (1 << h) and rcnt)
            return maxXOR(left->right, right->right, mid + 1, end, value,
                          h - 1);

        if (lcnt)
            return maxXOR(left->left, right->left, start, mid, value, h - 1);
        // else if (rcnt)
        return maxXOR(left->right, right->right, mid + 1, end, value, h - 1);
    }

    void remove(int cnt) { roots.resize(roots.size() - cnt); }

    int cntLessThan(int left, int right, int value) {
        return cntLessThan(roots[right], 0, maxValue, value) -
               cntLessThan(roots[left - 1], 0, maxValue, value);
    }
    int cntLessThan(Node* now, int start, int end, int value) {
        if (start > value)
            return 0;

        if (end <= value)
            return now->cnt;

        int mid = (start + end) >> 1;
        int lcnt = cntLessThan(now->left, start, mid, value);
        int rcnt = cntLessThan(now->right, mid + 1, end, value);
        return lcnt + rcnt;
    }

    int kth(int left, int right, int k) {
        return kth(roots[left - 1], roots[right], 0, maxValue, k);
    }
    int kth(Node* left, Node* right, int start, int end, int k) {
        if (start == end)
            return start;

        int mid = (start + end) >> 1;

        if (right->left->cnt - left->left->cnt >= k)
            return kth(left->left, right->left, start, mid, k);
        return kth(left->right, right->right, mid + 1, end,
                   k - (right->left->cnt - left->left->cnt));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    PSTSegmentTree seg(500'000);

    int M;
    cin >> M;

    while (M--) {
        int type;
        cin >> type;

        switch (type) {
            case 1: {
                int x;
                cin >> x;
                seg.add(x);
                break;
            }
            case 2: {
                int L, R, x;
                cin >> L >> R >> x;
                cout << seg.maxXOR(L, R, x) << '\n';
                break;
            }
            case 3: {
                int k;
                cin >> k;
                seg.remove(k);
                break;
            }
            case 4: {
                int L, R, x;
                cin >> L >> R >> x;
                cout << seg.cntLessThan(L, R, x) << '\n';
                break;
            }
            case 5: {
                int L, R, k;
                cin >> L >> R >> k;
                cout << seg.kth(L, R, k) << '\n';
                break;
            }
        }
    }

    return 0;
}
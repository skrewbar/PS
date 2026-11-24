#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int N, M;

// persistent segment tree
struct Node {
    Node *left, *right;
    int value;
};

Node* roots[101010];

void fillSegTree(Node* node, int start, int end) {
    if (start == end)
        return;

    int mid = (start + end) / 2;

    node->left = new Node();
    node->right = new Node();

    fillSegTree(node->left, start, mid);
    fillSegTree(node->right, mid + 1, end);
}

void modify(Node* cur, Node* prev, int start, int end, int index, int value) {
    if (start == end) {
        cur->value = value;
        return;
    }

    int mid = (start + end) / 2;
    if (index <= mid) {
        cur->left = new Node();
        cur->right = prev->right;
        modify(cur->left, prev->left, start, mid, index, value);
    } else {
        cur->left = prev->left;
        cur->right = new Node();
        modify(cur->right, prev->right, mid + 1, end, index, value);
    }

    cur->value = cur->left->value + cur->right->value;
}

// graph
vector<int> adj[101010];
int weight[101010];
vector<int> compressedWeight;

// lowest common ancestor
constexpr int MAX_LOG = 18;
int depth[101010], parent[101010][20];

void preprocessLCA(int cur) {
    for (int child : adj[cur]) {
        if (child == parent[cur][0])
            continue;

        depth[child] = depth[cur] + 1;
        parent[child][0] = cur;
        for (int i = 1; i <= MAX_LOG; i++)
            parent[child][i] = parent[parent[child][i - 1]][i - 1];

        preprocessLCA(child);
    }
}

int getLCA(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);

    int diff = depth[v] - depth[u];
    for (int i = 0; i <= MAX_LOG; i++) {
        if (diff & (1 << i))
            v = parent[v][i];
    }

    if (u == v)
        return u;

    for (int i = MAX_LOG; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

void dfs(int cur) {
    roots[cur] = new Node();
    modify(roots[cur], roots[parent[cur][0]], 0, N - 1, weight[cur], 1);

    for (int child : adj[cur]) {
        if (child == parent[cur][0])
            continue;

        dfs(child);
    }
}

int findKth(int u, int v, int k) {
    int lca = getLCA(u, v);

    Node *uNode = roots[u], *vNode = roots[v], *lcaNode = roots[lca],
         *lcaParNode = roots[parent[lca][0]];

    int start = 0, end = N - 1;
    while (start != end) {
        int leftSum = uNode->left->value + vNode->left->value -
                      lcaNode->left->value - lcaParNode->left->value;

        int mid = (start + end) / 2;

        if (leftSum >= k) {
            uNode = uNode->left;
            vNode = vNode->left;
            lcaNode = lcaNode->left;
            lcaParNode = lcaParNode->left;

            end = mid;
        } else {
            k -= leftSum;

            uNode = uNode->right;
            vNode = vNode->right;
            lcaNode = lcaNode->right;
            lcaParNode = lcaParNode->right;

            start = mid + 1;
        }
    }

    return start;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    for (int v = 1; v <= N; v++) {
        cin >> weight[v];
        compressedWeight.push_back(weight[v]);
    }

    ranges::sort(compressedWeight);
    for (int v = 1; v <= N; v++)
        weight[v] = ranges::lower_bound(compressedWeight, weight[v]) -
                    compressedWeight.begin();

    for (int i = 0; i < N - 1; i++) {
        int X, Y;
        cin >> X >> Y;

        adj[X].push_back(Y);
        adj[Y].push_back(X);
    }

    preprocessLCA(1);

    roots[0] = new Node();
    fillSegTree(roots[0], 0, N - 1);
    dfs(1);

    while (M--) {
        int X, Y, K;
        cin >> X >> Y >> K;

        println("{}", compressedWeight[findKth(X, Y, K)]);
    }

    return 0;
}
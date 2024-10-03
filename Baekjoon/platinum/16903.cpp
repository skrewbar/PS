#include <bits/stdc++.h>
using namespace std;


struct TrieNode {
    int count;
    TrieNode *childs[2];

    TrieNode() {
        count = 0;
        fill(childs, childs+2, nullptr);
    }


    ~TrieNode() {
        for (int i = 0 ; i < 2 ; i++) {
            if (childs[i] != nullptr) delete childs[i];
        }
    }


    void insert(int n, int digit = 30) {
        count++;
        if (digit == -1) {
            return;
        }

        int cur = (n & (1 << digit)) >> digit;
        if (childs[cur] == nullptr) childs[cur] = new TrieNode();
        childs[cur]->insert(n, digit-1);
    }


    void remove(int n, int digit = 30) {
        count--;
        if (digit == -1) {
            return;
        }

        int cur = (n & (1 << digit)) >> digit;
        childs[cur]->remove(n, digit-1);
        if (childs[cur]->count == 0) {
            delete childs[cur];
            childs[cur] = nullptr;
        }
    }


    int get_max_xor(int x, int digit = 30) {
        if (digit == -1) {
            return 0;
        }

        int cur = (x & (1 << digit)) >> digit;
        if (not (childs[cur ^ 1] == nullptr)) {
            return childs[cur ^ 1]->get_max_xor(x, digit-1) + (1 << digit);
        } else {
            return childs[cur]->get_max_xor(x, digit-1);
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    TrieNode *trie = new TrieNode();
    trie->insert(0);
    
    int m;
    cin >> m;
    while (m--) {
        int cmd, x;
        cin >> cmd >> x;

        if (cmd == 1) {
            trie->insert(x);
        } else if (cmd == 2) {
            trie->remove(x);
        } else {
            cout << trie->get_max_xor(x) << '\n';
        }
    }

    return 0;
}
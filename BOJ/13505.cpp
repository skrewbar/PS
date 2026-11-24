#include <bits/stdc++.h>
using namespace std;


struct TrieNode {
    TrieNode *childs[2];


    TrieNode() {
        fill(childs, childs+2, nullptr);
    }


    void insert(int x, int digit = 30) {
        if (digit == -1) return;

        int cur = (x & (1 << digit)) >> digit;
        if (childs[cur] == nullptr) childs[cur] = new TrieNode();
        childs[cur]->insert(x, digit-1);
    }


    int get_max_xor(int x, int digit = 30) {
        if (digit == -1) return 0;

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

    int n;
    cin >> n;
    int arr[n];

    for (int i = 0 ; i < n ; i++) {
        cin >> arr[i];
        trie->insert(arr[i]);
    }

    int max_xor = 0;

    for (int i = 0 ; i < n ; i++) {
        max_xor = max(max_xor, trie->get_max_xor(arr[i]));
    }

    cout << max_xor;


    return 0;
}
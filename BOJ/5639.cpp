#include <bits/stdc++.h>
using namespace std;


void postorder_traversal(vector<int>::iterator begin, vector<int>::iterator end) {
    if (begin == end) return;
    auto rightsubtree = upper_bound(begin+1, end, *begin);

    postorder_traversal(begin+1, rightsubtree);
    postorder_traversal(rightsubtree, end);
    cout << *begin << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> keys;
    keys.reserve(10001);
    int key;
    while (cin >> key) keys.push_back(key);
    postorder_traversal(keys.begin(), keys.end());

    return 0;
}
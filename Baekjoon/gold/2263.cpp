#include <bits/stdc++.h>
using namespace std;


vector<int> find_inorder;
vector<int> postorder;
void print_preorder(int in_begin, int in_end, int post_begin, int post_end) {
    if (in_end < in_begin or post_end < post_begin) return;

    int root = postorder[post_end];
    cout << root << ' ';
    int inorder_root = find_inorder[root];
    int left_size = inorder_root - in_begin;

    print_preorder(in_begin, inorder_root-1, post_begin, post_begin + left_size - 1);
    print_preorder(inorder_root+1, in_end, post_begin + left_size, post_end - 1);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    find_inorder.resize(n+1);
    for (int i = 1; i <= n; i++) {
        int inorder;
        cin >> inorder;
        find_inorder[inorder] = i;
    }
    postorder.resize(n+1);
    for (int i = 1; i <= n; i++) cin >> postorder[i];

    print_preorder(1, n, 1, n);

    return 0;
}
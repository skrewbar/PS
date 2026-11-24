#include <iostream>
#include <vector>
using namespace std;


void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> basket(n);
    for (int i = 0 ; i < n ; i++) {
        basket[i] = i + 1;
    }

    while (m--) {
        int left, right;
        cin >> left >> right;
        left--;right--;

        for (int i = 0 ; i < (right-left+1)/2 ; i++) {
            swap(basket[left + i], basket[right - i]);
        }
    }

    for (int i = 0 ; i < n ; i++) {
        cout << basket[i] << ' ';
    }
}
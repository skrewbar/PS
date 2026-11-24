#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    vector<int> increasing(n, 1);
    vector<int> decreasing(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                increasing[i] = max(increasing[j] + 1, increasing[i]);
                decreasing[i] = max(increasing[i], decreasing[i]);
            } else if (arr[j] > arr[i]) {
                decreasing[i] = max(decreasing[j] + 1, decreasing[i]);
            }
        }
    }

    cout << *max_element(decreasing.begin(), decreasing.end());
}
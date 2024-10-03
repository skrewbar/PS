#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n; cin >> n;
    vector<int> solutions(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> solutions[i];
    }

    vector<int> ans = {0, 0, 2000000001};
    
    int left = 0;
    int right = n-1;
    while (left < right) {
        int sum = solutions[left] + solutions[right];
        if (abs(sum) < abs(ans[2])) {
            ans[0] = solutions[left];
            ans[1] = solutions[right];
            ans[2] = sum;
        }
        if (sum < 0) left++;
        else right--;
    }
    cout << ans[0] << ' ' << ans[1];

    return 0;
}
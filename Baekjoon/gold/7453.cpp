#include <bits/stdc++.h>
using namespace std;

vector<int> nums[4];
vector<int> cPlusD;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;

    for (int i = 0 ; i < 4 ; i++) nums[i].resize(n);
    cPlusD.reserve(n * n);

    for (int j = 0 ; j < n ; j++) {
        for (int i = 0 ; i < 4 ; i++) {
            cin >> nums[i][j];
        }
    }


    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            cPlusD.push_back(nums[2][i] + nums[3][j]);
        }
    }
    sort(cPlusD.begin(), cPlusD.end());


    long long ans = 0;
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            int aPlusB = nums[0][i] + nums[1][j];
            auto lbound = lower_bound(cPlusD.begin(), cPlusD.end(), -aPlusB);
            auto rbound = upper_bound(cPlusD.begin(), cPlusD.end(), -aPlusB);
            ans += rbound - lbound;
        }
    }

    cout << ans;


    return 0;
}
#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n; cin >> n;
    vector<ll> solutions(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> solutions[i];
    }
    sort(solutions.begin(), solutions.end());


    vector<ll> minAns = {0, 0, 0, 3000000001};

    for (int i = 0 ; i < n - 2 ; i++) {
        int left = i+1;
        int right = n-1;

        while (left < right) {
            ll sum = solutions[i] + solutions[left] + solutions[right];
            if (abs(sum) < abs(minAns[3])) {
                minAns = {solutions[i], solutions[left], solutions[right], sum};
            }

            if (sum < 0) left++;
            else right--;
        }
        
    }

    cout << minAns[0] << ' ' << minAns[1] << ' ' << minAns[2];


    return 0;
}
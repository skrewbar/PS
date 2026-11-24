#include <bits/stdc++.h>
using namespace std;

vector<vector<vector<int>>> DP;
vector<int> arr;

int cost(int from, int to) {
    if (from == to) return 1; // 같은발로 누르기
    else if (from == 0) return 2; // 중앙에서 옮기기
    else if (abs(from - to) == 2) return 4; // 2차이 나는곳(가장먼곳)에서 옮기기
    else return 3; // 나머지
}

int solve(int n, int left, int right) {
    if (n == arr.size()) return 0;

    if (DP[n][left][right] != -1) return DP[n][left][right];
    // if (DP.at(n).at(left).at(right) != -1) return DP[n][left][right];


    int to = arr[n];
    DP[n][left][right] = min(
        solve(n+1, to, right) + cost(left, to),
        solve(n+1, left, to) + cost(right, to)
    );
    return DP[n][left][right];
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    while (n != 0) {
        arr.push_back(n);
        cin >> n;
    }
    DP.resize(arr.size(), vector<vector<int>>(5, vector<int>(5, -1)));

    cout << solve(0, 0, 0);

    return 0;
}
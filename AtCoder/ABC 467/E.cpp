#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

using ll = long long;

ll A[202020], B[202020], C[202020];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N - 1; i++) cin >> B[i];
    for (int i = 2; i <= N; i++) C[i] = B[i - 1] - C[i - 1];

    vector<pair<ll, int>> candidates;

    for (int i = 1; i <= N; i++) {
        ll s = (C[i] - A[i]) * (i & 1 ? -1 : 1);
        s = (s % M + M) % M;
        candidates.emplace_back(s, i);
    }

    sort(all(candidates));

    ll sum = 0;
    for (int i = 1; i <= N; i++) {
        ll cnt = C[i] - A[i] + candidates[0].first * (i & 1 ? 1 : -1);
        cnt = (cnt % M + M) % M;
        sum += cnt;
    }

    ll ans = sum;
    {
        int i = 0;
        while (i < N and candidates[0].first == candidates[i].first) {
            if (~candidates[i].second & 1) sum += M;
            i++;
        }
        while (i < N) {
            if (N & 1) sum += candidates[i].first - candidates[i - 1].first;

            int cnt[2] = {};

            cnt[candidates[i].second & 1]++;
            while (i + 1 < N and candidates[i].first == candidates[i + 1].first)
                cnt[candidates[++i].second & 1]++;

            sum -= M * cnt[1];
            ans = min(ans, sum);
            sum += M * cnt[0];

            i++;
        }
    }

    cout << ans;

    return 0;
}

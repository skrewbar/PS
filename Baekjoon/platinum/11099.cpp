#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

using ll = long long;

constexpr ll EXPLODE_LIMIT = 1e9;

constexpr ll REPEAT_LIMIT = 2e10;

vector<vector<ll>> multiply(const vector<vector<ll>>& A,
                            const vector<vector<ll>>& B) {
    ASSERT(A[0].size() == B.size());
    vector<vector<ll>> ret(A.size(), vector<ll>(B[0].size()));

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < B.size(); k++) {
                ret[i][j] += A[i][k] * B[k][j];

                if (ret[i][j] >= EXPLODE_LIMIT) {
                    ret[i][j] = EXPLODE_LIMIT;
                    break;
                }
            }
        }
    }

    return ret;
}

vector<vector<ll>> power(vector<vector<ll>> base, ll exp) {
    vector<vector<ll>> ret(base.size(), vector<ll>(base.size()));
    for (int i = 0; i < base.size(); i++)
        ret[i][i] = 1;

    while (exp) {
        if (exp & 1)
            ret = multiply(ret, base);
        base = multiply(base, base);
        exp >>= 1;
    }

    return ret;
}

void solve() {
    int N, L;
    cin >> N >> L;

    vector<vector<ll>> mat(N + 1, vector<ll>(N + 1));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++)
            cin >> mat[j][i];
    }
    mat[N][N] = 1;

    vector<vector<ll>> first(N + 1, vector<ll>(1));
    first[0][0] = 1;

    ll lo = 0, hi = 2*REPEAT_LIMIT;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;

        vector<vector<ll>> cnt = multiply(power(mat, mid), first);
        if (cnt[N][0] >= L)
            hi = mid;
        else
            lo = mid + 1;
    }

    if (hi == 2*REPEAT_LIMIT)
        println("lucky");
    else
        println("{}", lo);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}
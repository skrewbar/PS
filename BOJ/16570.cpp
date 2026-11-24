#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> getFail(const vector<int>& s) {
    vector<int> fail(s.size());

    for (int i = 1, j = 0; i < s.size(); i++) {
        while (j > 0 and s[i] != s[j])
            j = fail[j - 1];
        if (s[i] == s[j])
            fail[i] = ++j;
    }

    return fail;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];

    reverse(A.begin(), A.end());
    vector<int> fail = getFail(A);

    int maxLen = *max_element(fail.begin(), fail.end());
    if (maxLen == 0)
        println("-1");
    else
        println("{} {}", maxLen, count(fail.begin(), fail.end(), maxLen));

    return 0;
}
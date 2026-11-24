#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> getFailureFunction(const vector<int>& s) {
    vector<int> fail(s.size());
    for (int i = 1, j = 0; i < (int)s.size(); i++) {
        while (j > 0 and s[i] != s[j])
            j = fail[j - 1];
        if (s[i] == s[j])
            fail[i] = ++j;
    }
    return fail;
}

struct Answer {
    int k, p;
    bool operator<(const Answer& a) const {
        if (k + p == a.k + a.p)
            return p < a.p;
        return k + p < a.k + a.p;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> s(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];

    ranges::reverse(s);

    vector<int> fail = getFailureFunction(s);

    Answer answer(0, n);
    for (int i = 0; i < n; i++) {
        int repeatLen = (i + 1) - fail[i];
        answer = min(answer, Answer(n - (i + 1), repeatLen));
    }

    print("{} {}", answer.k, answer.p);

    return 0;
}
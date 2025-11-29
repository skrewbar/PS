#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

// return gcd of two POSITIVE integers
int gcd(int a, int b) {
    while (b > 0) {
        a %= b;
        swap(a, b);
    }

    return a;
}

vector<int> getFail(const string& s) {
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

    string meat;
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        meat.push_back(c);
    }

    vector<int> fail = getFail(meat);
    int patternLen = meat.size() - fail.back();

    if (meat.size() % patternLen == 0) {
        int cnt = meat.size() / patternLen;

        int g = gcd(cnt, N);
        cout << cnt / g << '/' << N / g;
    } else {
        cout << 1 << '/' << N;
    }

    return 0;
}
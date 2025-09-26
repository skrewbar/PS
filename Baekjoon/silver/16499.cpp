#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

unordered_map<string, int> cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        string word;
        cin >> word;

        sort(word.begin(), word.end());
        cnt.insert(pair(word, 0));
        cnt[word]++;
    }

    cout << cnt.size();

    return 0;
}
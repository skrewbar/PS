#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

string answer;
vector<string> video;

void compress(int r, int c, int sz) {
    bool compressable = true;

    for (int i = r; i < r + sz; i++) {
        if (not compressable)
            break;

        for (int j = c; j < c + sz; j++) {
            if (video[i][j] == video[r][c])
                continue;

            compressable = false;
            break;
        }
    }    

    if (compressable) {
        answer.push_back(video[r][c]);
        return;
    }

    answer.push_back('(');
    sz /= 2;
    compress(r, c, sz);
    compress(r, c + sz, sz);
    compress(r + sz, c, sz);
    compress(r + sz, c + sz, sz);
    answer.push_back(')');
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    video.resize(N);
    for (int i = 0; i < N; i++)
        cin >> video[i];

    compress(0, 0, N);
    println("{}", answer);

    return 0;
}
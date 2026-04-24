#include <bits/stdc++.h>
using namespace std;

int T[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    for (int i = 0; i < N; i++)
        cin >> T[i];
    sort(T, T + N);
    
    for (int i = 0; i < N - 1; i++)
        T[i] = (T[i + 1] - T[i]);
    sort(T, T + N - 1);
    
    int ans = K;
    for (int i = 0; i < N - K; i++)
        ans += T[i];
        
    cout << ans;

    return 0;
}
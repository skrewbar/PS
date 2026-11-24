#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int board[5050][5050];

// void printBoard(int n) {
//     for (int i = 1; i <= n + 2; i++) {
//         for (int j = 1; j <= i + 2; j++) {
//             print("{:2} ", board[i][j]);
//         }
//         print("\n");
//     }
//     print("========\n");
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    while (m--) {
        int a, b, x;
        cin >> a >> b >> x;
        board[a][b] += 1;
        board[a][b + 1] -= 1;
        board[a + x + 1][b] -= 1;
        board[a + x + 1][b + x + 2] += 1;
        board[a + x + 2][b + 1] += 1;
        board[a + x + 2][b + x + 2] -= 1;
    }

    for (int i = 1; i <= n + 2; i++)
        for (int j = 1; j <= i + 2; j++)
            board[i][j] += board[i][j - 1];
    
    for (int j = 1; j <= n + 2; j++)
        for (int i = j; i <= n + 2; i++)
            board[i][j] += board[i - 1][j];
    
    for (int i = 1; i <= n + 2; i++)
        for (int j = 1; j <= n + 2; j++)
            board[i][j] += board[i - 1][j - 1];
    
    int answer = 0;
    for (int i = 1; i <= n + 2; i++)
        for (int j = 1; j <= i + 2; j++)
            if (board[i][j])
                answer++;

    print("{}", answer);
    return 0;
}
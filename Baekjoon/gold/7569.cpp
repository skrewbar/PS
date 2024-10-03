#include <bits/stdc++.h>

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define dout if constexpr (local) cout

#ifdef LOCAL
constexpr bool local = true;
#else
constexpr bool local = false;
#endif

using namespace std;

struct Tomato {
    int x, y, z;
    Tomato(int x, int y, int z) : x(x), y(y), z(z) {}
};

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};


int main() { fastio
    int m, n, h;
    cin >> m >> n >> h;

    int tomatoes[n][m][h];
    queue<Tomato> q;

    for (int k = 0; k < h; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> tomatoes[i][j][k];
                if (tomatoes[i][j][k] == 1) q.push(Tomato(i, j, k));
            }
        }
    }


    while (not q.empty()) {
        Tomato now = q.front();
        q.pop();

        for (int k = 0; k < 6; k++) {
            int nx = now.x + dx[k];
            int ny = now.y + dy[k];
            int nz = now.z + dz[k];

            if ((0 <= nx and nx < n) and (0 <= ny and ny < m) and (0 <= nz and nz < h) and tomatoes[nx][ny][nz] == 0) {
                tomatoes[nx][ny][nz] = tomatoes[now.x][now.y][now.z] + 1;
                q.push(Tomato(nx, ny, nz));
            }
        }
    }

    dout << '\n';
    for (int k = 0; k < h; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (tomatoes[i][j][k] == 0) {
                    cout << -1;
                    return 0;
                }
                dout << tomatoes[i][j][k] << ' ';
            }
            dout << '\n';
        }
        dout << '\n';
    }


    cout << *max_element(&tomatoes[0][0][0], &tomatoes[n-1][m-1][h]) - 1;


    return 0;
}
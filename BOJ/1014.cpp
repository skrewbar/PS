#include <bits/stdc++.h>
using namespace std;


bool canSit(int bit, int width, vector<bool> &sittable) {
    for (int i = 0; i < width; i++) {
        if (bit & (1 << i) and not sittable[i]) return false;
    }
    return true;
}

bool isAdjacent(int bit, int width) {
    for (int i = 0; i < width-1; i++) {
        int adj = 3 << i;
        if ((bit & adj) == adj) return true;
    }
    return false;
}

bool cannotSitOrAdjacent(int bit, int width, vector<bool> &sittable) {
    return not canSit(bit, width, sittable) or isAdjacent(bit, width);
}

bool canCheat(int frontBit, int behindBit, int width) {
    for (int i = 0; i < width; i++) {
        int bit = 1 << i;
        if (not (behindBit & bit)) continue;
        if (frontBit & (bit >> 1)) return true;
        if (frontBit & (bit << 1)) return true;
    }
    return false;
}


int main() {
    int c;
    cin >> c;
    while (c--) {
        int n, m;
        cin >> n >> m;

        vector<vector<bool>> sittable(n, vector<bool>(m));
        for (int i = 0; i < n; i++) {
            string chairs;
            cin >> chairs;
            for (int j = 0; j < m; j++) {
                sittable[i][j] = (chairs[j] == '.');
            }
        }


        vector<vector<int>> maxStudent(n, vector<int>(1 << m));
        for (int k = 0; k < (1 << m); k++) {
            if (cannotSitOrAdjacent(k, m, sittable[0])) continue;
            for (int j = 0; j < m; j++) {
                if (k & (1 << j)) maxStudent[0][k]++;
            }
        }

        for (int row = 0; row < n-1; row++) {
            for (int now = 0; now < (1 << m); now++) {
                if (cannotSitOrAdjacent(now, m, sittable[row])) continue;
                for (int next = 0; next < (1 << m); next++) {
                    if (cannotSitOrAdjacent(next, m, sittable[row+1])) continue;
                    if (canCheat(now, next, m)) continue;
                    
                    int count = 0;
                    for (int col = 0; col < m; col++) if (next & (1 << col)) count++;
                    maxStudent[row+1][next] = max(maxStudent[row][now] + count, maxStudent[row+1][next]);
                }
            }
        }
        cout << *max_element(maxStudent[n-1].begin(), maxStudent[n-1].end()) << '\n';
    }
}
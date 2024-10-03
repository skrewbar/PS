#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

// get failure function of v
vector<int> getFail(vector<int> v) {
    vector<int> fail(v.size());

    for (int i = 1, j = 0; i < v.size(); i++) {
        while (j > 0 and v[i] != v[j]) j = fail[j-1];
        if (v[i] == v[j]) fail[i] = ++j;
    }

    return fail;
}

// returns if container contains v
bool contains(vector<int> container, vector<int> v) {
    vector<int> fail = getFail(v);

    for (int i = 0, j = 0; i < container.size(); i++) {
        while (j > 0 and container[i] != v[j]) j = fail[j-1];

        if (container[i] == v[j]) {
            if (j == v.size() - 1) {
                return true;
            } else j++;
        }
    }

    return false;
}


int main() {
    fastio();

    int n, k;
    cin >> n >> k;

    vector<vector<int>> programs(n);
    vector<vector<int>> reversedPrograms(n);
    for (int i = 0; i < n; i++) {
        int length;
        cin >> length;
        programs[i].resize(length);

        for (int j = 0; j < length; j++) {
            cin >> programs[i][j];
        }

        reversedPrograms[i] = programs[i];
        reverse(reversedPrograms[i].begin(), reversedPrograms[i].end());
    }


    for (int i = 0; i < programs[0].size() - k + 1; i++) {
        vector<int> sub(k);

        for (int j = 0; j < k; j++) {
            sub[j] = programs[0][i+j];
        }
        bool isInfected = true;

        for (int j = 1; j < programs.size(); j++) {
            if (not contains(programs[j], sub) and not contains(reversedPrograms[j], sub)) {
                isInfected = false;
                break;
            }
        }
        if (isInfected) {
            cout << "YES";
            return 0;
        }
    }
    
    cout << "NO";
    return 0;
}
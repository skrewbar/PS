#include <bits/stdc++.h>
using namespace std;

int A[11];
int B[11];

set<char> candidates[11];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i];
        B[i]--;
    }

    int M;
    cin >> M;
    vector<string> s(M);
    for (int i = 0; i < M; i++)
        cin >> s[i];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (s[j].length() != A[i])
                continue;
            candidates[i].insert(s[j][B[i]]);
        }
    }
    
    for (int j = 0; j < M; j++) {
        const string& str = s[j];
        
        if (str.length() != N) {
            cout << "No\n";
            continue;
        }

        bool possible = true;
        for (int i = 0; i < str.length(); i++) {
            if (not candidates[i].contains(str[i])) {
                possible = false;
                break;
            }
        }
        
        cout << (possible ? "Yes" : "No") << '\n';
    }

    return 0;
}
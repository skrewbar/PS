#include "combo.h"
#include <algorithm>
#include <vector>
using namespace std;

#define all(v) (v).begin(), (v).end()

vector<char> chr = {'A', 'B', 'X', 'Y'};

string guess_sequence(int N) {
    string S;

    if (press("AB") == 0) {
        if (press("X"))
            S += 'X';
        else
            S += 'Y';
    } else {
        if (press("A"))
            S += 'A';
        else
            S += 'B';
    }
    chr.erase(remove(all(chr), S[0]), chr.end());

    while ((int)S.size() <= N - 2) {
        string p;

        for (int i = 0; i < 3; i++) {
            p += S;
            p += chr[0];
            p += chr[i];
        }
        p += S;
        p += chr[1];

        int coin = press(p);

        if (coin == S.size() + 2) {
            S += chr[0];
        } else if (coin == S.size() + 1) {
            S += chr[1];
        } else {
            S += chr[2];
        }
    }

    if (S.size() < N) {
        for (int i = 0; i < 2; i++) {
            if (press(S + chr[i]) == N) {
                S.push_back(chr[i]);
                break;
            }
        }
        if (S.size() != N)
            S += chr[2];
    }

    return S;
}

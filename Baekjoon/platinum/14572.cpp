#include <bits/stdc++.h>
using namespace std;

class Student {
   public:
    int ability;
    vector<int> knownAlgorithms;

    bool operator<(const Student& s) const { return ability < s.ability; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, d;
    cin >> n >> k >> d;

    vector<Student> students(n);
    for (Student& student : students) {
        int m;
        cin >> m >> student.ability;
        while (m--) {
            int algo;
            cin >> algo;
            algo--;
            student.knownAlgorithms.push_back(algo);
        }
    }
    sort(students.begin(), students.end());

    vector<int> knownCount(k);
    int lo = 0, hi = 0, answer = 0;  // 범위 [lo, hi]

    while (hi < n) {
        for (int algo : students[hi].knownAlgorithms)
            knownCount[algo]++;

        while (lo < hi and students[hi].ability - students[lo].ability > d) {
            for (int algo : students[lo].knownAlgorithms)
                knownCount[algo]--;
            lo++;
        }

        int algoCount = 0, wellKnownCount = 0;
        for (int i = 0; i < k; i++) {
            algoCount += knownCount[i] > 0;
            wellKnownCount += knownCount[i] == (hi - lo + 1);
        }
        answer = max(answer, (algoCount - wellKnownCount) * (hi - lo + 1));

        hi++;
    }

    cout << answer;
}
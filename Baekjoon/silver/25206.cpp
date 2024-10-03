#include <iostream>
#include <map>
using namespace std;

map<string, double> grade_table;

void setup() {
    grade_table.insert({"A+", 4.5});
    grade_table.insert({"A0", 4.0});
    grade_table.insert({"B+", 3.5});
    grade_table.insert({"B0", 3.0});
    grade_table.insert({"C+", 2.5});
    grade_table.insert({"C0", 2.0});
    grade_table.insert({"D+", 1.5});
    grade_table.insert({"D0", 1.0});
    grade_table.insert({"F0", 0.0});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double rating = 0.0;
    double credit_sum = 0.0;
    setup();

    for (int i = 0 ; i < 20 ; i++) {
        string subject;
        double credit;
        string grade;
        cin >> subject >> credit >> grade;

        if (grade == "P") {
            continue;
        }
        credit_sum += credit;
        rating += credit * grade_table[grade];
    }
    cout << rating / credit_sum;
}
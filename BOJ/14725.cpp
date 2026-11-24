#include <bits/stdc++.h>
using namespace std;


class Node {
public:
    map<string, Node> childs;

    void push_child(vector<string>::iterator iter) {
        if (*iter == "end") return;
        if (childs.find(*iter) == childs.end()) childs[*iter] = Node();
        childs[*iter].push_child(iter+1);
    }

    void print(int depth) {
        for (auto [name, node] : childs) {
            for (int i = 0; i < depth * 2; i++) cout << '-';
            cout << name << '\n';
            node.print(depth+1);
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Node root;

    int n;
    cin >> n;
    while (n--) {
        int food_cnts;
        cin >> food_cnts;
        vector<string> foods(food_cnts+1);
        for (int i = 0; i < food_cnts; i++) cin >> foods[i];
        foods[food_cnts] = "end";
        root.push_child(foods.begin());
    }

    root.print(0);
}
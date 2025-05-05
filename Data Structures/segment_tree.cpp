#include <iostream>
#include <vector>
#include <concepts>
using namespace std;

template <typename T, typename M>
concept Mergable = requires(M merge, T a, T b) {
    { merge(a, b) } -> same_as<T>;
    // T()가 merge()에 대한 항등원이어야 함
};

template <typename T, typename Merge>
requires Mergable<T, Merge>
class SegmentTree {
private:
    size_t n;
    vector<T> tree;
    Merge merge;

    void set(size_t index, T value) {
        for (tree[index += n] = value; index > 1; index >>= 1) {
            tree[index >> 1] = merge(tree[index], tree[index ^ 1]);
        }
    }
public:
    SegmentTree(size_t n): n(n) {
        tree = vector<T>(n << 1);
    }

    SegmentTree(const vector<T> array): n(array.size()) {
        tree = vector<T>(n << 1);

        for (size_t i = 0; i < n; i++) {
            tree[i + n] = array[i];
        }

        for (size_t i = n - 1; i > 0; i--) {
            tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    struct Proxy {
        SegmentTree &tree;
        size_t index;

        Proxy &operator=(T value) {
            tree.set(index, value);
            return *this;
        }

        operator T() {
            return tree.tree[index + tree.n];
        }
    };
    Proxy operator[](size_t index) {
        return Proxy{*this, index};
    }

    T rangeQuery(size_t left, size_t right) {
        T ret = T();
        for (left += n, right += n; left <= right; left >>= 1, right >>= 1) {
            if (left & 1) ret = merge(ret, tree[left++]);
            if (~right & 1) ret = merge(ret, tree[right--]);
        }
        return ret;
    }
};

class Add {
public:
    int operator()(int a, int b) {
        return a + b;
    }
};

int main() {
    SegmentTree<int, Add> tree(vector<int>(10, 1));

    cout << tree.rangeQuery(0, 9) << '\n';
    tree[5] = 2;
    tree[6] = 7;
    cout << tree.rangeQuery(4, 7);
}
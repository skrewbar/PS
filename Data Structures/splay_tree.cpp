#include <cstddef>
#include <iostream>

template <typename T>
class SplayTree {
   public:
    struct Node {
        Node *left = nullptr, *right = nullptr, *parent = nullptr;
        T key;
        size_t sz = 0;

        Node(T _key) : key(_key) {}

        void updateSize() {
            sz = 1;
            if (left)
                sz += left->sz;
            if (right)
                sz += right->sz;
        }
    };

    ~SplayTree() { deconstruct(root); }

    void insert(T x) {
        if (!root) {
            Node* node = new Node(x);
            root = node;
            return;
        }

        Node *cur = root, **newNodePtr;
        while (true) {
            if (x == cur->key)
                return;

            if (x < cur->key) {
                if (!cur->left) {
                    newNodePtr = &cur->left;
                    break;
                }
                cur = cur->left;
            } else {
                if (!cur->right) {
                    newNodePtr = &cur->right;
                    break;
                }
                cur = cur->right;
            }
        }

        *newNodePtr = new Node(x);
        (*newNodePtr)->parent = cur;
        splay(*newNodePtr);
    }

    void erase(T x) {
        if (!find(x))
            return;

        Node* del = root;
        if (del->left) {
            if (del->right) {
                root = del->left;
                root->parent = nullptr;

                Node* node = root;
                while (node->right)
                    node = node->right;
                node->right = del->right;
                del->right->parent = node;
                splay(node);

                delete del;
                return;
            }
            root = del->left;
            root->parent = nullptr;
            delete del;
            return;
        }
        if (del->right) {
            root = del->right;
            root->parent = nullptr;
            delete del;
            return;
        }
        delete del;
        root = nullptr;
    }

    Node* find(T x) {
        if (!root)
            return nullptr;

        Node* cur = root;

        while (true) {
            if (x == cur->key)
                break;

            if (x < cur->key) {
                if (!cur->left)
                    break;
                cur = cur->left;
            } else {
                if (!cur->right)
                    break;
                cur = cur->right;
            }
        }

        splay(cur);
        return cur;
    }

    size_t rank(T x) {
        if (!root)
            return 0;

        size_t ret = 0;
        Node* cur = root;
        while (true) {
            if (x == cur->key) {
                ret++;
                if (cur->left)
                    ret += cur->left->sz;
                break;
            }

            if (x < cur->key) {
                if (!cur->left)
                    break;
                cur = cur->left;
            } else {
                ret++;
                if (cur->left)
                    ret += cur->left->sz;

                if (!cur->right)
                    break;
            }
        }

        splay(cur);
        return ret;
    }

   private:
    Node* root = nullptr;

    void deconstruct(Node* node) {
        if (!node)
            return;

        deconstruct(node->left);
        deconstruct(node->right);
        delete node;
    }

    void rotate(Node* node) {
        Node* parent = node->parent;
        if (!parent)
            return;

        Node* child;
        if (node == parent->left) {
            child = parent->left = node->right;
            node->right = parent;
        } else {
            child = parent->right = node->left;
            node->left = parent;
        }

        node->parent = parent->parent;
        parent->parent = node;

        if (child)
            child->parent = parent;

        if (node->parent) {
            if (parent == node->parent->left)
                node->parent->left = node;
            else
                node->parent->right = node;
        } else {
            root = node;
        }

        parent->updateSize();
        node->updateSize();
    }

    void splay(Node* node) {
        while (node != root) {
            Node* parent = node->parent;
            Node* grandParent = parent->parent;

            if (grandParent) {
                if ((grandParent->left == parent) != (parent->left == node))
                    rotate(node);  // Zig-Zag step
                else
                    rotate(parent);  // Zig-Zig step
            }

            rotate(node);  // Zig step
        }
    }
};

int main() {
    SplayTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.erase(1);
    tree.find(1);
    std::cout << tree.rank(2);
}
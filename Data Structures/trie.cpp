#include <map>
#include <string>

class Trie {
   public:
    Trie() { root = new TrieNode; }

    void insert(const char s[]) { root->insert(s); }
    void insert(const std::string& s) { root->insert(s.c_str()); }

    bool contains(const char s[]) { return root->find(s); }
    bool contains(const std::string& s) { return root->find(s.c_str()); }

   private:
    struct TrieNode {
        std::map<char, TrieNode*> child;
        bool end;

        TrieNode() : end(false) {}
        ~TrieNode() {
            for (auto& [_, ptr] : child)
                delete ptr;
        }

        void insert(const char* str) {
            if (*str == '\0') {
                end = true;
                return;
            }

            char next = *str;
            if (not child.contains(next))
                child[next] = new TrieNode;
            child[next]->insert(str + 1);
        }

        bool find(const char* str) {
            if (*str == '\0')
                return end;

            char next = *str;
            if (not child.contains(next))
                return false;
            return child[next]->find(str + 1);
        }
    };

    TrieNode* root;
};
#include <string>
using namespace std;

class Trie {
public:
    struct node {
        node* children[26];
        bool is_leaf = false;
        node() {
            for (int i = 0; i < 26; i++) {
                children[i] = nullptr;
            }
        }
    };
private:
    node* _root;
    node* _remove_helper(node* root, string input, int depth);
    int _values = 0;;
public:
    Trie();
    ~Trie();
    node* get_root();
    void insert(string input);
    void remove(string input);
    bool find(string input);
    void clear();
    int get_values();
};


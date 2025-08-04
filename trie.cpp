#include "trie.h"

char changecase(char c) {
    if (isupper(c)) {
        return tolower(c);
    }
    return c;
}

bool has_children(Trie::node* root) {
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != nullptr) {
            return true;
        }
    }
    return false;
}

Trie::node* Trie::_remove_helper(node* root, string input, int depth) {
    if (!root->children) {
        return nullptr;
    }
    if (depth == input.size()) {
        if (root->is_leaf) {
            root->is_leaf = false;
        }
        if (!has_children(root)) {
            delete root;
            root = nullptr;
        }
        return root;
    }
    int index = changecase(input[depth]) - 'a';
    root->children[index] = _remove_helper(root->children[index], input, depth + 1);
    if (!has_children(root) && !root->is_leaf) {
        delete root;
        root = nullptr;
    }
    return root;

}

Trie::Trie()
{
    _root = new node;
}

Trie::~Trie() {
    delete _root;
}

void Trie::insert(string input) {
    if (_values == 0) {
        _root = new node;
    }
    if (!this->find(input)) {
        _values++;
    }
    node* current_node = _root;
    for (int i = 0; i < input.size(); i++) {
        int index = changecase(input[i]) - 'a';
        if (current_node->children[index] == nullptr) {
            node* temp = new node;
            current_node->children[index] = temp;
        }
        current_node = current_node->children[index];
    }
    current_node->is_leaf = true;
}

void Trie::remove(string input) {
    if (this->find(input)) {
        _values--;
    }
    node* removed_node = _remove_helper(_root, input, 0);
}

bool Trie::find(string input) {
    if (_values == 0) {
        return false;
    }
    node* current_node = _root;
    for (int i = 0; i < input.size(); i++) {
        int index = changecase(input[i]) - 'a';
        if (current_node->children[index] == nullptr) {
            return false;
        }
        current_node = current_node->children[index];
    }
    return current_node->is_leaf;
}


void Trie::clear() {
    delete _root;
    _root = new node;
    _values = 0;
}


Trie::node* Trie::get_root() {
    return _root;
}

int Trie::get_values() {
    return _values;
}

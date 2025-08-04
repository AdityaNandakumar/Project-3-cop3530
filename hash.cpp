#include "hash.h"

Hash_Table::Hash_Table() {
    _buckets = 27;
    _table.resize(_buckets);
}

Hash_Table::Hash_Table(int buckets) {
    _buckets = buckets;
    _table.resize(_buckets);
}

int Hash_Table::_hash(string input) {
    int sum = 0;
    int base = 27;
    for (int i = 0; i < input.size(); i++) {
        int index = (input[i] - 'a') + 1;
        int base_power = input.size() - (i + 1);
        sum = sum + (index * pow(base, base_power));
    }
    return sum % _buckets;
}

void Hash_Table::_rehash() {
    vector<vector<string>> new_table;
    _buckets *= 2;
    new_table.resize(_buckets);
    for (int i = 0; i < _table.size(); i++) {
        for (int j = 0; j < _table[i].size(); j++) {
            int index = _hash(_table[i][j]);
            new_table[index].push_back(_table[i][j]);
        }
    }
    _table = new_table;
}

void Hash_Table::insert(string input) {
    _size++;
    _load_factor = _size / _buckets;
    if (_load_factor > 0.75f) {
        _rehash();
    }
    int index = _hash(input);
    for (int i = 0; i < _table[index].size(); i++) {
        if (_table[index][i] == input) {
            return;
        }
    }
    _table[index].push_back(input);
}

void Hash_Table::remove(string input) {
    _size--;
    int index;
    index = _hash(input);
    bool found = false;
    int index_location;
    for (int i = 0; i < _table[index].size(); i++) {
        if (_table[index][i] == input) {
            found = true;
            index_location = i;
            break;
        }
    }
    if (found) {
        _table[index].erase(_table[index].begin() + index_location);
    }
}

bool Hash_Table::search(string input) {
    int index = _hash(input);
    bool found = false;
    int index_location;
    for (int i = 0; i < _table[index].size(); i++) {
        if (_table[index][i] == input) {
            found = true;
            index_location = i;
            break;
        }
    }
    if (!found) {
        return false;
    }
    return true;
}

void Hash_Table::clear() {
    for (int i = 0; i < _table.size(); i++) {
        _table[i].clear();
    }
}

vector<vector<string>>& Hash_Table::get_table() {
    return _table;
}

int Hash_Table::get_bucket_count() {
    return _buckets;
}


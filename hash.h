#include <string>
#include <vector>
#include <cmath>
using namespace std;

class Hash_Table {
private:
    int _buckets = 0;
    int _size = 0;
    float _load_factor = 0.0f;
    vector<vector<string>> _table;
    int _hash(string input);
    void _rehash();
public:
    Hash_Table();
    Hash_Table(int buckets);
    void insert(string input);
    void remove(string input);
    bool search(string input);
    int get_bucket_count();
    void clear();
    vector<vector<string>>& get_table();
};

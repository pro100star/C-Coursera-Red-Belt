#include <algorithm>
#include <future>
#include <numeric>
#include <vector>
#include <string>
#include <random>
using namespace std;

template <typename K, typename V>
class ConcurrentMap {
public:
    static_assert(is_integral_v<K>, "ConcurrentMap supports only integer keys");

    struct Access {
        lock_guard<mutex> guard;
        V& ref_to_value;
    };

    explicit ConcurrentMap(size_t bucket_count) : maps(bucket_count) {}

    Access operator[](const K& key) {
        auto& e = maps[key % maps.size()];
        return {lock_guard(e.first), e.second[key]};
    }

    map<K, V> BuildOrdinaryMap() {
        map<K, V> result;
        for (auto& e : maps) {
            for (auto& p : e.second) {
                lock_guard<mutex> guard(e.first);
                result[p.first] = p.second;
            }
        }
        return result;
    }

private:
    vector<pair<mutex, map<K, V>>> maps;
};

#include <set>
#include <unordered_map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
    using Id = int;

    Id Add(T object) {
        auto it = identifiers.insert({0, count}).first;
        items[count] = move(object);
        iterators[count] = it;
        return count++;
    }

    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
             IdOutputIt ids_begin) {
        for (auto it = range_begin; it != range_end; ++it, ++ids_begin) {
            *ids_begin = Add(move(*it));
        }
    }

    bool IsValid(Id id) const {
        return items.count(id) > 0;
    }

    const T& Get(Id id) const {
        return items.at(id);
    }

    void Promote(Id id) {
        auto it = iterators[id];
        iterators[id] = identifiers.insert({it->first + 1, it->second}).first;
        identifiers.erase(it);
    }

    pair<const T&, int> GetMax() const {
        auto it = identifiers.rbegin();
        return {items.at(it->second), it->first};
    }

    pair<T, int> PopMax() {
        auto it = identifiers.end();
        --it;
        Id id = (*identifiers.rbegin()).second;
        pair<T, int> p = make_pair(move(items[it->second]), it->first);
        identifiers.erase(*it);
        iterators.erase(id);
        items.erase(id);
        return p;
    }

private:
    set<pair<int, Id>> identifiers;
    unordered_map<Id, T> items;
    unordered_map<Id, set<pair<int, Id>>::iterator> iterators;
    size_t count = 0;
};

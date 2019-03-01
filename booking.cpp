#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <vector>

class HotelManager {
public:
    HotelManager() = default;

    void Book(long long time, std::string& name, size_t id, size_t count) {
        current_time = time;
        rooms_count[name] += count;
        clients[name].push({time, {id, count}});
        ++used[name][id];

        for (auto& hotel : clients) {
            std::map<size_t, size_t>& hotel_used = used[hotel.first];
            size_t k = 0;
            std::map<size_t, size_t> del;
            while (!hotel.second.empty() && hotel.second.front().first <= current_time - 86400) {
                ++del[hotel.second.front().second.first];
                k += hotel.second.front().second.second;
                hotel.second.pop();
            }
            for (auto& d : del) {
                hotel_used[d.first] -= d.second;
                if (hotel_used[d.first] == 0) {
                    hotel_used.erase(d.first);
                }
            }
            rooms_count[hotel.first] -= k;
        }
    }

    size_t getClients(std::string& name) {
        return used[name].size();
    }

    size_t getRooms(std::string& name) {
        return rooms_count[name];
    };

private:
    std::map<std::string, std::queue<std::pair<long long, std::pair<size_t, size_t>>>> clients;
    std::map<std::string, size_t> rooms_count;
    std::map<std::string, std::map<size_t, size_t>> used;
    long long current_time = -1'000000'000000'000000;
};

void Book(HotelManager& hm) {
    long long time;
    std::cin >> time;
    std::string name;
    std::cin >> name;
    size_t id;
    std::cin >> id;
    size_t count;
    std::cin >> count;
    hm.Book(time, name, id, count);
}

int main() {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(nullptr);

    size_t q;
    std::cin >> q;
    HotelManager hm = {};

    for (size_t i = 0; i < q; ++i) {
        std::string query;
        std::cin >> query;
        if (query == "BOOK") {
            Book(hm);
        } else {
            std::string name;
            std::cin >> name;
            size_t res;
            if (query == "CLIENTS") {
                res = hm.getClients(name);
            } else {
                res = hm.getRooms(name);
            }
            std::cout << res << '\n';
        }
    }
    return 0;
}

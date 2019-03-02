#include <iostream>
#include <map>
#include <queue>

struct Event {
    Event(size_t id_, long long time_, size_t count_) : id(id_), time(time_), count(count_) {}

    size_t id;
    long long time;
    size_t count;
};

class Hotel {
public:
    Hotel() = default;

private:
    void Update(long long time) {
        current_time = time;
        while (!events.empty() && events.front().time <= current_time - 86400) {
            if (clients[events.front().id] == 1) {
                clients.erase(events.front().id);
            } else {
                --clients[events.front().id];
            }

            rooms -= events.front().count;
            events.pop();
        }
    }

public:
    void Book(Event& e) {
        ++clients[e.id];
        events.push(e);
        rooms += e.count;

        Update(e.time);
    }

    size_t getClients(long long time) {
        Update(time);
        return clients.size();
    }

    size_t getRooms(long long time) {
        Update(time);
        return rooms;
    }

private:
    long long current_time = -1'000000'000000'000000;
    std::map<size_t, size_t> clients;
    std::queue<Event> events;
    size_t rooms = 0;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t q;
    std::cin >> q;
    std::map<std::string, Hotel> hotels;
    long long current_time = -1'000000'000000'000000;

    for (size_t i = 0; i < q; ++i) {
        std::string query;
        std::cin >> query;
        if (query == "BOOK") {
            long long time;
            std::cin >> time;
            current_time = time;
            std::string name;
            std::cin >> name;
            size_t id;
            std::cin >> id;
            size_t count;
            std::cin >> count;
            Event e(id, time, count);
            hotels[name].Book(e);
        } else {
            std::string name;
            std::cin >> name;
            size_t res;
            if (query == "CLIENTS") {
                res = hotels[name].getClients(current_time);
            } else {
                res = hotels[name].getRooms(current_time);
            }
            std::cout << res << '\n';
        }
    }
    return 0;
}


#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include <utility>

using namespace std;

class ReadingManager {
public:
    ReadingManager() = default;

    void Read(int user_id, int page_count) {
        if (users.count(user_id) == 0) {
            ++pages[page_count];
        } else {
            int temp = users[user_id];
            if (--pages[temp] == 0) {
                pages.erase(temp);
            }
            ++pages[page_count];
        }
        users[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        if (users.count(user_id) == 0) {
            return 0;
        }
        if (users.size() == 1) {
            return 1;
        }
        size_t count = 0;
        int count_pages = users.at(user_id);
        for (const auto& page : pages) {
            if (page.first < count_pages) {
                count += page.second;
            } else {
                break;
            }
        }
        return count * 1.0 / (users.size() - 1);
    }

private:
    map<int, int> users;
    map<int, int> pages;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}

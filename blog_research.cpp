#include <future>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (auto& e : other.word_frequences) {
            word_frequences[e.first] += e.second;
        }
    }
};

Stats ExploreLine(const set<string>& key_words, const string& line) {
    string tmp = string();
    Stats stats;
    for (const char& c : line) {
        if (c == ' ') {
            if (!tmp.empty() && key_words.find(tmp) != key_words.end()) {
                ++stats.word_frequences[move(tmp)];
            }
            tmp = string();
        } else {
            tmp.push_back(c);
        }
    }
    if (!tmp.empty() && key_words.find(tmp) != key_words.end()) {
        ++stats.word_frequences[move(tmp)];
    }
    return stats;
}

Stats ExploreKeyWordsSingleThread(
        const set<string>& key_words, istream& input
) {
    Stats result;
    for (string line; getline(input, line); ) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    Stats result;
    vector<string> strings;
    string s;
    while (getline(input, s)) {
        strings.push_back(move(s));
    }
    vector<stringstream> streams;
    streams.reserve(4);
    for (size_t i = 0; i < 4; ++i) {
        stringstream ss;
        for (auto it = strings.begin() + strings.size() * i / 4; it != strings.end()
        && it != strings.begin() + strings.size() * (i + 1) / 4; ++it) {
            ss << *it << '\n';
        }
        streams.emplace_back(move(ss));
    }
    vector<future<Stats>> fut;
    fut.reserve(4);
    for (auto& e : streams) {
        fut.emplace_back(async(ExploreKeyWordsSingleThread, ref(key_words), ref(e)));
    }
    for (auto& e : fut) {
        result += e.get();
    }
    return result;
}

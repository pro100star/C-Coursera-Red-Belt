#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        int newWords = 0;
        for (const auto& word : words) {
            if (dict.find(word) == dict.end()) {
                ++newWords;
                dict.insert(word);
            }
        }
        return newWords;
    }

    vector<string> KnownWords() {
        vector<string> res(dict.size());
        size_t i = 0;
        for (const auto& word : dict) {
            res[i++] = word;
        }
        return res;
    }
};

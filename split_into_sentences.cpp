#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector <Token>;

template <typename Token>
vector <Sentence<Token>> SplitIntoSentences (vector <Token> tokens) {
  vector<Sentence<Token>> result;
  Sentence<Token> tmp;
  bool flag = false;
  for (auto& item : tokens) {
    if (item.IsEndSentencePunctuation()) {
      tmp.push_back(move(item));
      flag = true;
    } else if (flag) {
      result.push_back(move(tmp));
      tmp.clear();
      flag = false;
      tmp.push_back(move(item));
    } else {
      tmp.push_back(move(item));
    }
  }
  result.push_back(move(tmp));
  return result;
}

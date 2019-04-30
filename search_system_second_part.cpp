#include "search_server.h"
#include "iterator_range.h"

#include <iostream>
#include <iterator>
#include <sstream>

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

void SyncUpdate(istream& document_input, Synchronized<InvertedIndex>& index) {
    InvertedIndex new_index;
    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
    }
    index.GetAccess().ref_to_value = move(new_index);
}

SearchServer::SearchServer(istream& document_input) {
    SyncUpdate(document_input, index);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    futures.push_back(async(SyncUpdate, ref(document_input), ref(index)));
}

void SyncAdd(istream& query_input, ostream& search_results_output, Synchronized<InvertedIndex>& index) {
    vector<pair<size_t, size_t>> docid_count(index.GetAccess().ref_to_value.GetSize());
    for (string current_query; getline(query_input, current_query);) {
        const auto words = SplitIntoWords(current_query);
        for (size_t i = 0; i < docid_count.size(); ++i) {
            docid_count[i] = {i, 0};
        }
        for (const auto &word : words) {
            for (const auto[docid, hitcount] : index.GetAccess().ref_to_value.Lookup(word)) {
                docid_count[docid].second += hitcount;
            }
        }

        partial_sort(
                begin(docid_count),
                docid_count.size() > 5 ? docid_count.begin() + 5 : docid_count.end(),
                end(docid_count),
                [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
                    int64_t lhs_docid = lhs.first;
                    auto lhs_hit_count = lhs.second;
                    int64_t rhs_docid = rhs.first;
                    auto rhs_hit_count = rhs.second;
                    return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
                }
        );

        search_results_output << current_query << ':';
        size_t k = 0;
        for (auto&[docid, hitcount] : Head(docid_count, 5)) {
            if (k++ == 5) break;
            if (hitcount == 0) break;
            search_results_output << " {"
                                  << "docid: " << docid << ", "
                                  << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
    }
}

void SearchServer::AddQueriesStream(
        istream& query_input, ostream& search_results_output
) {
    this_thread::sleep_for(chrono::microseconds(100000));
    futures.push_back(async(SyncAdd, ref(query_input), ref(search_results_output), ref(index)));
}

void InvertedIndex::Add(const string& document) {
    docs.push_back(document);

    const size_t docid = docs.size() - 1;
    vector<string> words = SplitIntoWords(document);
    for (const auto& word : words) {
        auto& tmp = index[word];
        if (tmp.empty() || tmp.back().first != docid) {
            tmp.push_back({docid, 0});
        }
    }
    for (const auto& word : words) {
        index[word].back().second++;
    }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return empty;
    }
}

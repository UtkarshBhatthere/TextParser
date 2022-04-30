// Helper Class for special operation on word map.
#pragma once
#include <map>
#include <string>
#include <iostream>

namespace wordmap {

    uint64_t addToMap(std::map<std::string, uint64_t> &base_map, std::string word)
    {
        uint64_t curr_count = 0;

        // If word exists in map.
        if (base_map.find(word) != base_map.end()) {
            curr_count = base_map[word];
            base_map[word] = ++curr_count;
            return curr_count;
        }

        base_map.insert({word, ++curr_count});
        return curr_count;
    }

    void mapToSortedArray(std::map<std::string, uint64_t> &map, std::vector<std::pair<std::string, uint64_t>> &vec)
    {
        vec.reserve(map.size());	// Expand vector to be as long as map.
        std::transform(map.begin(), map.end(), std::back_inserter(vec), [](auto &pair) {return pair;});
        std::sort(vec.begin(), vec.end(), [](std::pair<std::string, uint64_t> &a, std::pair<std::string, uint64_t> &b)
            {
                return (a.second > b.second);   // Comparator for Descending Sort of word->count pairs.
            });
        return;
    }
};

namespace sorted_vec {

    void mergeInVector(std::vector<std::pair<std::string, uint64_t>> &final_vec, std::vector<std::pair<std::string, uint64_t>> &to_merge_vec)
    {
        std::vector<std::pair<std::string, uint64_t>> temp_vec(final_vec.size());

        std::move(final_vec.begin(), final_vec.end(), std::back_inserter(temp_vec));
        final_vec.reserve(temp_vec.size() + to_merge_vec.size());
        std::set_union(temp_vec.begin(), temp_vec.end(), to_merge_vec.begin(), to_merge_vec.end(), std::back_inserter(final_vec));
        return;
    }
};

// Helper Class for special operation on word map.
#pragma once
#include <map>
#include <string>
#include <iostream>

#include "common.h"

namespace wordmap {

    /**
     * @brief Add a word to the map of word->count pairs, if already present increase count.
     * 
     * @param base_map
     * @param word
     * @return uint64_t Frequency of the newly added word.
     */
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

    /**
     * @brief Convert a Map with word->count pairs to a vector of such pairs, sorted on the basis of count.
     * 
     * @param map 
     * @param vec 
     */
    void mapToSortedArray(std::map<std::string, uint64_t> &map, std::vector<std::pair<std::string, uint64_t>> &vec)
    {
        vec.reserve(map.size());	// Expand vector to be as long as map.
        std::transform(map.begin(), map.end(), std::back_inserter(vec), [](auto &pair) {return pair;});
        std::sort(vec.begin(), vec.end(), [](std::pair<std::string, uint64_t> &a, std::pair<std::string, uint64_t> &b)
            {
                return (a.second >= b.second);   // Comparator for Descending Sort of word->count pairs.
            });
        return;
    }
};

namespace sorted_vec {

    /**
     * @brief Merge a sorted vector to another inplace, i.e. once done, final_vec will be a sorted union of itself and to_merge_vec.
     * 
     * @param final_vec 
     * @param to_merge_vec 
     */
    void mergeInVector(std::vector<std::pair<std::string, uint64_t>> &final_vec, std::vector<std::pair<std::string, uint64_t>> &to_merge_vec)
    {
        std::vector<std::pair<std::string, uint64_t>> temp_vec(final_vec.size());

        std::move(final_vec.begin(), final_vec.end(), std::back_inserter(temp_vec));
        final_vec.reserve(temp_vec.size() + to_merge_vec.size());
        std::set_union(temp_vec.begin(), temp_vec.end(), to_merge_vec.begin(), to_merge_vec.end(), std::back_inserter(final_vec));
        return;
    }
};

namespace stat_stream {

    /**
     * @brief Populate the Stream with the stats of Most/Least frequent words.
     * 
     * @param stream 
     * @param sorted_vec 
     */
    void fillStatFromSortedVector(std::stringstream &stream, std::vector<std::pair<std::string, uint64_t>> &sorted_vec)
    {
        if (sorted_vec.empty()) {
            return;
        }

        if (sorted_vec.size() <= CONST_TEN) {
            std::for_each(sorted_vec.begin(), sorted_vec.end(), [&stream](auto &pair)
                {
                    stream << "Word: " << pair.first << ", Count: " << pair.second << std::endl; 
                });
            return;
        }

        stream << "\nMost Frequent Words\n===================\n";
        std::for_each(sorted_vec.begin(), sorted_vec.begin()+CONST_FIVE, [&stream](auto &pair)
                {
                    stream << "Word: \"" << pair.first << "\", Count: " << pair.second << std::endl; 
                });
        
        stream << "\nLeast Frequent Words\n====================\n";
        std::for_each(sorted_vec.end()-CONST_FIVE, sorted_vec.end(), [&stream](auto &pair)
                {
                    stream << "Word: \"" << pair.first << "\", Count: " << pair.second << std::endl; 
                });

        stream << "\nNote: The Word is lexically sorted so words not listed here may have same frequency.\n";
        return;
    }
};

#include "memory"
#include "sstream"
#include "algorithm"

#include "include/parser.h"
#include "containerHelper.hpp"

void parser::fix_punc(string& str, std::vector<char> lookup) {
	for (auto& x : lookup) {
		if (str.back() == x) {
			str.erase(str.end() - 1);
			return;
		}
	}

	return;
}


parser::parser(strstream &stream)
{
	// Punctuations.
	punc_lookup = 
	{ '.', ',', '?', '!', ';',
	 ':','-', '(', ')', '{',
	 '}', '[', ']', '\'', '"'
	};

	fill_map(stream);
}

unsigned long parser::fill_map(strstream &stream)
{
	// used in word by word parsing.
	iter begin = iter(stream);
	iter end = iter();
	uint64_t prev_unique_count = this->unique_word_count;
	uint64_t batch_word_count = 0;
	
	// Batch wise parsing of strstream.
	std::map<string, uint64_t> batch_map;
	std::vector<std::pair<string, uint64_t>> curr_vec((this->deduplicated_index.size()));
	std::vector<std::pair<string, uint64_t>> batch_vec;

	// Parse incoming stream.
	while (begin != end) {
		string word(*begin);
		uint64_t word_freq = 0;
		uint64_t batch_word_freq = 0;

		fix_punc(word, punc_lookup);						// Remove trailing punctutaions.

		wordmap::addToMap(this->deduplicated_index, word);
		wordmap::addToMap(batch_map, word);

		batch_word_count++;		// +1 words parsed in this batch.
		begin++;
	}

	// Generate a sorted vector from word_map
	wordmap::mapToSortedArray(batch_map, batch_vec);

	// Merge sorted batch vector to main sorted vector.
	sorted_vec::mergeInVector(this->sorted_vec, batch_vec);

	// Update Class level data
	this->word_count += batch_word_count;
	this->unique_word_count = deduplicated_index.size();	// Total Unique keys in Map
	return unique_word_count - prev_unique_count;
}

std::map<std::string, uint64_t>& parser::export_index(void)
{
	return deduplicated_index;
}

std::string parser::word_stat(void)
{
	std::stringstream stream;

	stream << "Word Map Summary\n================\n";
	stream << "Total Words: " << this->word_count << ", Unique Words: " << this->unique_word_count << " \n";
	stat_stream::fillStatFromSortedVector(stream, this->sorted_vec);
	return stream.str();
}

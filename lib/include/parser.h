#pragma once

#include <map>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>

#include "common.h"

class parser
{
private:
	// -> Data Members <- //
	
	// Code Readability.
	using iter = std::istream_iterator<std::string>;
	using string = std::string;
	using strstream = std::fstream;

	// For overall figures.
	unsigned long word_count = 0;
	unsigned long unique_word_count = 0;

	// Punctuation symbols for word sanitisation.
	std::vector<char> punc_lookup;
	
	// Lexical Word Pool: word is key and count is value.
	std::map<string, uint64_t> deduplicated_index;

	// Countwise Descending Sorted word pairs.
	std::vector<std::pair<string, uint64_t>> sorted_vec;
	

	// -> Member Functions <- //
	void fix_punc(string& str, std::vector<char> lookup);

public:
	parser(strstream &stream);
	unsigned long fill_map(strstream &stream);
	std::map<string, uint64_t>& export_index(void);
	string word_stat(void);
};


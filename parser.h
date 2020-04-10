#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>

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
	// Lexical Word Pool.
	std::map<string, string> deduplicated_index;
	// Punctuation symbols.
	std::vector<char> punc_lookup;

	// -> Member Functions <- //
	char fix_punc(string& str, std::vector<char> lookup);

public:
	parser(strstream &stream);
	unsigned long fill_map(strstream &stream);
	std::map<string, string>& export_index(void);
	string word_stat(void);
};


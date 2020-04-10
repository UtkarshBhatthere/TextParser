#include "parser.h"
#include "memory"

char parser::fix_punc(string& str, std::vector<char> lookup) {
	for (auto& x : lookup) {
		if (str.back() == x) {
			str.erase(str.end() - 1);
			return x;
		}
	}
	return false;
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

	int curr_count = unique_word_count;

	while (begin != end) {
		string word(*begin);
		char punc_symbol = fix_punc(word, punc_lookup);
		deduplicated_index.insert(std::pair<string, string>(word, word));
		word_count++;
		begin++;
	}
	unique_word_count = deduplicated_index.size();
	return unique_word_count - curr_count;
}

std::map<std::string, std::string>& parser::export_index(void)
{
	return deduplicated_index;
}

std::string parser::word_stat(void)
{
	std::unique_ptr<char[]> buffer(new char[100]);
	const char* format = "Total words: %d, Unique words: %d\n";
	int size = snprintf(buffer.get(), 100, format, word_count, unique_word_count);
	return std::string(buffer.get(), buffer.get() + size - 1);
}

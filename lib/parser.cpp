#include "memory"
#include "include/parser.h"

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

	// Parse incoming stream.
	while (begin != end) {
		string word(*begin);
		uint64_t curr_word_count = 0;

		fix_punc(word, punc_lookup);						// Remove trailing punctutaions.
		curr_word_count = deduplicated_index.count(word);	// 0 if not present, curr count if present.

		deduplicated_index.insert(std::pair<string, uint64_t>(word, ++curr_word_count));
		batch_word_count++;		// +1 words parsed in this batch.

		begin++;
	}

	// Update Class level data.
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
	std::unique_ptr<char[]> buffer(new char[100]);
	const char* format = "Total words: %d, Unique words: %d\n";
	int size = snprintf(buffer.get(), 100, format, word_count, unique_word_count);
	return std::string(buffer.get(), buffer.get() + size - 1);
}

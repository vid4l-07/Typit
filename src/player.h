#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

struct FormatedChar{
	char c;
	bool format;
};

class Player{
	public:
	std::string org_str;
	std::string rest_str;
	std::vector<FormatedChar> player_input;
	int words_typed;
	int errors;
	int index;

	Player(): errors(0), words_typed(0), index(0) {
		gen_word(true);
	}

	void type(char c, bool correct);
	void backspace();
	void count_words();
	void gen_word(bool first = false);
	void del_char();
};

#endif

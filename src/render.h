#pragma once
#include <string>
#include "player.h"
#include "term.h"

class Render{
	private:
	Terminal& term;
	int filas;
	int columnas;
	int words_gen;

	public:
	int max_words;
	Render(Terminal& term_param): term(term_param),  words_gen(0) { term.get_center(filas, columnas); }

	void center(int filas, int columnas);
	void new_words(Player& player);
	void stats(int time, int wpm);
	void update(Player& player);
};

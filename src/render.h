#ifndef RENDER_H
#define RENDER_H

#include <termios.h>
#include <string>
#include "player.h"

class Render{
	private:
	int filas;
	int columnas;
	termios oldt;

	public:
	Render(termios term_param): oldt(term_param) { get_center(); }

	void enable_raw_mode();
	void disable_raw_mode();
	void get_center();
	void center(int filas, int columnas);
	void clear();
	void new_words(Player& player);
	void update(Player& player);
};

#endif

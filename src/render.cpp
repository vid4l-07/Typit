#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string>
#include "render.h"

void Render::clear(){
	std::cout << "\033[2J";
}

void Render::get_center() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	filas = w.ws_row / 2;
	columnas = w.ws_col / 2;
}

void Render::center(int filas, int columnas){
	std::cout << "\033[" << filas << ";" << columnas << "H";
}

void Render::new_words(Player& player){
	while (player.rest_str.size() < columnas - 10 && words_gen < max_words){
		player.gen_word();
		words_gen ++;
	}
	if (player.player_input.size() >= columnas - 5){
		player.del_char();
	}
}

void Render::stats(int time, int wpm){
	center(filas - filas / 2, columnas - columnas / 3);
	std::cout << time;
	center(filas - filas / 2, columnas + columnas / 3);
	std::cout << "wpm: " << wpm;
}

void Render::update(Player& player){
	clear();
	center(filas, columnas);
	new_words(player);
	std::string copy_str = player.rest_str;

	if (!player.rest_str.empty()) {
		std::cout << "\033[7m" << player.rest_str.front() << "\033[0m" << player.rest_str.substr(1);
	}
	center(filas, columnas - player.player_input.size());
	
	std::string format_str;
	for (const auto& i:player.player_input){
		std::string s(1,i.c);

		if (i.format){
			format_str += "\033[32m" + s + "\033[0m";
		} else{
			format_str += "\033[31m" + s + "\033[0m";
		}
	}
	std::cout << format_str;
	center(filas, columnas);
}

void Render::enable_raw_mode() {
	termios newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	std::cout << "\033[?25l"; // hide cursor
}

void Render::disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

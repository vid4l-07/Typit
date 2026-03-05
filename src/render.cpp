#include <iostream>
#include <string>
#include "render.h"

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
	center(filas, columnas + player.rest_str.size());
	std::cout << "\033[K";  // clear right of the words
	center(filas, columnas - player.player_input.size() - 1);
	std::cout << "\033[1K";  // clear left of the words
	center(filas, columnas);
}


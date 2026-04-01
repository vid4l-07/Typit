#include <chrono>
#include <iostream>
#include "render.h"
#include "player.h"
#include "game.h"
#include "terms/term.h"

void Game::set_start_time(){
	inicio = std::chrono::high_resolution_clock::now();
}
double Game::get_time() const{
	auto fin = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tiempo = fin - inicio;
	return tiempo.count();
}


double Game::get_wpm(){
	double elapsed_minutes = get_time() / 60.0;

    if (elapsed_minutes <= 0.0001)
        return 0;

    int total_chars = player.player_input.size();
    double words = total_chars / 5.0;
    return words / elapsed_minutes;
}

void Game::handle_input(char c){
	if (c < KEY_MIN) return;
	if (c == ' ') player.words_typed ++;

	if (c == KEY_BACKSPACE){
		player.backspace();
	} else if (!player.rest_str.empty() && c == player.rest_str[0]){
		player.type(c, true);
	} else{
		player.type(c, false);
	}
}

void Game::main_loop_words(){
	set_start_time();
	while (player.index < player.org_str.size()) {
		if (term.key_pressed()){
			char c = term.read_char();
			handle_input(c);
		}
		render.update(player);
		render.stats(get_time(), get_wpm());
	}
	duration = get_time();
}

void Game::main_loop_time(){
	int index = 0;
	set_start_time();
	while (duration < max) {
		duration = get_time();
		if (term.key_pressed()){
			char c = term.read_char();
			handle_input(c);
		}
		render.update(player);
		render.stats(max - get_time(), get_wpm());
	}
	duration = get_time();
}

void Game::start() {
	term.clear();
	if (mode == 'w'){
		render.max_words = max;
		render.update(player);
		main_loop_words();
	} else {
		render.max_words = 999999;
		render.update(player);
		main_loop_time();
	}
}

void Game::end() {
	term.clear();
	double accuracy = (double(player.org_str.size()) - player.errors) / double(player.org_str.size()) * 100;
	render.end(get_time(), player.words_typed, get_wpm(), accuracy, player.errors);
	std::cin.get();
}

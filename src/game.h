#pragma once
#include <iostream>
#include <chrono>
#include "player.h"
#include "render.h"

class Game{
	private:
	Terminal& term;
	Player& player;
	Render& render;
	char mode;
	int max;
	std::chrono::time_point<std::chrono::high_resolution_clock> inicio;

	void main_loop_words();
	void main_loop_time(); 

	public:
	double duration;

	Game(Player& player_param, Render& render_param, Terminal& term_param, char mode_param, int max_param): player(player_param), 
	render(render_param), term(term_param), mode(mode_param), max(max_param) {}

	void handle_input(char c);
	void start(); // w = words, t = time
	void end();
	void set_start_time();
	double get_time() const;
	double get_wpm();
};


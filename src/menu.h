#pragma once
#include <string>
#include <vector>
#include "term.h"
#include "menu_render.h"

class Menu{
	private:
	void select(bool direction);
	int current_selection;
	Terminal& term;
	Menu_render menu_render;

	public:
	std::string title;
	std::vector<Option> options;
	int mode; // 0 options, 1 incrase decrease
	bool handle_input(char c);
	int start();
	void end();

	Menu(std::string title_param, std::vector<std::string>& options_param, Terminal& term_param): title(title_param), 
	term(term_param), menu_render(term){

		if (options_param.size() > 0){
			mode = 0;
			current_selection = 0;
			for (const std::string& i:options_param){
				Option o(i);
				options.push_back(o);
			}
			options.at(0).selected = true;
		} else {
			mode = 1;
			current_selection = 5;
		}
	}
};


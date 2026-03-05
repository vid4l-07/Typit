#include "menu.h"

void Menu::select(bool direction){
	if (direction){
		if (current_selection < options.size() - 1){
			options.at(current_selection).selected = false;
			current_selection ++;
			options.at(current_selection).selected = true;
		}
	} else {
		if (current_selection > 0){
			options.at(current_selection).selected = false;
			current_selection --;
			options.at(current_selection).selected = true;
		}
	}
}

bool Menu::handle_input(char c){
	if (c == '\n'){
		return false;
	}
	if (c == 27) {
		term.read_char();
		char dir = term.read_char();

		if (mode == 0){
			if (dir == KEY_RIGHT) {
				select(true);
			} 
			else if (dir == KEY_LEFT) {
				select(false);
			}
		} else {
			if (dir == KEY_UP) {
				if (current_selection < 60){
					current_selection ++;
				}
			} 
			else if (dir == KEY_DOWN) {
				if (current_selection > 5){
					current_selection --;
				}
			}
		}
	}
	return true;
}


int Menu::start(){
	bool runing = true;
	if (mode == 0){
		menu_render.render_options(title, options);
	} else {
		menu_render.render_number(title, current_selection);
	}

	while (runing){
		char c = term.read_char();
		runing = handle_input(c);
		if (mode == 0){
			menu_render.render_options(title, options);
		} else {
			menu_render.render_number(title, current_selection);
		}
	}

	end();
	return current_selection;
}

void Menu::end(){
	term.clear();
}

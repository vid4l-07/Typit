#include <csignal>
#include <string>
#include <vector>
#include "player.h"
#include "game.h"
#include "render.h"
#include "term.h"
#include "menu.h"

Game* game_point = nullptr;

void ctrlc_handler(int signal) {
	game_point -> end();
	std::_Exit(0);
}

int main(){
	Terminal term;

	std::vector<std::string> lang = {"en", "es"};
	Menu menu_lang("Language", lang, term);

	int lang_selct = menu_lang.start();
	std::string lang_str;
	if (lang_selct == 0){
		lang_str = "en";
	} else {
		lang_str = "es";
	}

	std::vector<std::string> mode = {"time", "words"};
	Menu menu_mode("Mode", mode, term);
	int mode_select = menu_mode.start();
	char mode_str;
	
	int max;
	std::vector<std::string> empty = {};
	if (mode_select == 0){
		mode_str = 't';
		Menu menu_max("time", empty, term);
		max = menu_max.start();
	} else {
		mode_str = 'w';
		Menu menu_max("Words", empty, term);
		max = menu_max.start();
	}
	

	Player player(lang_str);
	Render render(term);

	Game game(player, render, term, mode_str, max);

	game_point = &game;

	std::signal(SIGINT, ctrlc_handler);

	game.start();
    game.end();

    return 0;
}

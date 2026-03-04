#include <csignal>
#include <string>
#include <termios.h>
#include "player.h"
#include "game.h"
#include "render.h"

Game* game_point = nullptr;

void ctrlc_handler(int signal) {
	game_point -> end();
	std::_Exit(0);
}

int main(){
	char mode;
	std::string len;
	std::cout << "Modo: ";
	std::cin >> mode;
	std::cout << "Idioma: ";
	std::cin >> len;

    termios oldt;
	Player player(len);
	Render render(oldt);

	Game game(player, render, mode);

	game_point = &game;

	std::signal(SIGINT, ctrlc_handler);

	game.start();
    game.end();

    return 0;
}

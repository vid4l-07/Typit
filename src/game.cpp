#include <chrono>
#include "render.h"
#include "player.h"
#include "Game.h"

void Game::set_start_time(){
	inicio = std::chrono::high_resolution_clock::now();
}
double Game::get_time() const{
	auto fin = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> tiempo = fin - inicio;
	return tiempo.count();
}

void Game::start() {
	render.enable_raw_mode();
	render.clear();
	render.update(player);
	main_loop();
}

void Game::end() {
	render.disable_raw_mode();
	double accuracy = (double(player.org_str.size()) - player.errors) / double(player.org_str.size()) * 100;
    std::cout << "\n\nTiempo: " << duration << " segundos\n";
	std::cout << "Errores: " << player.errors << " errores\n";
	std::cout << "Precision: " << accuracy << " %\n";
	std::cout << "Palabras: " << player.words << "\n";
}

void Game::main_loop(){
	int index = 0;

	set_start_time();
	while (index < player.org_str.size()) {
		char c = getchar();

		if (c < 32) continue;
		if (c == 127){
			if (index > 0){
				index --;
				player.backspace(index);
			}

		} else if (c == player.rest_str[0]){
			player.type(c, true);
			index ++;

		} else{
			player.type(c, false);
			index ++;

		}
		render.update(player);
	}
	duration = get_time();
}

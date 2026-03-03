#include <termios.h>
#include "player.h"
#include "game.h"
#include "render.h"

int main(){
    termios oldt;
	Player player;
	Render render(oldt);
	
	Game game(player, render);

	game.start();
    game.end();

    return 0;
}

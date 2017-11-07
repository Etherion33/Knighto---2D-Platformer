#include <iostream>
#include "include/Game.h"
#include "include/Game_State_Menu.h"

int main()
{
	Game game;
	game.pushState(new Game_State_Menu(&game));
	game.run();
	return EXIT_SUCCESS;
}
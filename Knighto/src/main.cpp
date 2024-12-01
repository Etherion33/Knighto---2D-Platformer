#include <iostream>
#include "../include/Game.h"
#include "../include/Game_State_Menu.h"

int main()
{
	Game game; //create game object
	game.pushState(new Game_State_Menu(&game)); //push game state into Menu State
	game.run(); //main loop
	return EXIT_SUCCESS;
}
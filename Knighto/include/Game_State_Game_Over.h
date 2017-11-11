#pragma once
#include <SFML\Graphics.hpp>
#include "Game_State.h"
class Game_State_Game_Over: public Game_State
{
public:
	virtual void draw(const float dt);
	virtual void update(const float dt);
	virtual void handleInput();

	Game_State_Game_Over(Game* game);
private:
	sf::View view;
};


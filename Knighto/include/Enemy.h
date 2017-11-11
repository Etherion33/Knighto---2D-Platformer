#pragma once
#include "Character.h"

class Enemy: public Character
{
public:
	Enemy(Entity_Manager* entmgr, const sf::Texture& spritesheet);

	void update(float dt);
	void draw(sf::RenderWindow & window, float dt);
};


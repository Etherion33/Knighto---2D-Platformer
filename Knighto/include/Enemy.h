#pragma once
#include "Character.h"

class Enemy: public Character
{
public:
	Enemy(Entity_Manager* entmgr, const sf::Texture& spritesheet, sf::Vector2f enemyPos);

	void update(float dt);
	void draw(sf::RenderWindow & window, float dt);
};


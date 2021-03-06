#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\System\Time.hpp>
#include <map>
#include "AnimatedSprite.h"
#include "Texture_Manager.h"
#include "Character.h"

class Player : public Character
{
public:
	Player(Entity_Manager* entmgr, const sf::Texture& spritesheet);
	~Player();
	void update(float dt);
	void OnEntityCollision(EntityBase* l_collider, bool l_attack);
	void handleInput(std::string input);

};

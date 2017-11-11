#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "EntityBase.h"

class Character: public EntityBase
{
protected:
	unsigned int m_health;


public:
	Character(Entity_Manager* enmgr);
	virtual ~Character();

	virtual void draw(sf::RenderWindow & window, float dt);
	virtual void update(const float dt);

	virtual void OnEntityCollision(EntityBase* eb_collider, bool b_attack);
};


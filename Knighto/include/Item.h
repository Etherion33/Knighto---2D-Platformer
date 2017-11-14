#pragma once
#include "../include/EntityBase.h"
class Item :
	public EntityBase
{
public:
	Item();
	~Item();

	virtual void draw(sf::RenderWindow & window, float dt);
	virtual void update(const float dt);

	virtual void OnEntityCollision(EntityBase* eb_collider, bool b_attack);
};


#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "EntityBase.h"

enum class DIRECTION { LEFT, RIGHT, UP, DOWN };

class Character : public EntityBase
{
protected:
	unsigned int m_health;
	float m_jumpVelocity;

public:
	Character(Entity_Manager* entmgr);
	virtual ~Character();

	virtual void draw(sf::RenderWindow & window, float dt);
	virtual void update(const float dt);
	void move(const DIRECTION& dir);
	void jump();
	void animate();
	virtual void OnEntityCollision(EntityBase* eb_collider, bool b_attack);
};

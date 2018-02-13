#pragma once
#include <SFML/Graphics.hpp>
#include "AnimatedSprite.h"
#include "EntityBase.h"

enum class DIRECTION { LEFT, RIGHT, UP, DOWN };

class Character : public EntityBase
{
protected:
	float m_jumpVelocity;
	DIRECTION direct;
public:
	Character(Entity_Manager* entmgr, const sf::Texture& spritesheet);
	virtual ~Character();

	virtual void draw(sf::RenderWindow & window, float dt);
	virtual void update(const float dt);
	void getHurt(const int& l_damage);
	void move(const DIRECTION& dir);
	void jump();
	void animate();
	void attack();
	virtual void OnEntityCollision(EntityBase* eb_collider, bool b_attack) = 0;
	void UpdateAttackAABB();
	void resetHP() { m_health = 100; }
	unsigned int getHealth() { return m_health; }
	unsigned int getScore() { return score; }
	void setScore(unsigned int points) { score += points; }
	unsigned int score;

	sf::FloatRect m_attackAABB;
	sf::Vector2f m_attackAABBoffset;
	int m_health;
	bool m_isEquipped;
};

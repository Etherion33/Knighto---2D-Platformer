#pragma once
#include "Character.h"

enum class EnemyType{ Orc, Goblin, Skeleton};

class Enemy: public Character
{
private:
	EnemyType m_enemyType;
public:
	Enemy(EnemyType eType,const sf::Texture& spritesheet, sf::Vector2f enemyPos);

	void update(float dt);
	void draw(sf::RenderWindow & window, float dt);
};


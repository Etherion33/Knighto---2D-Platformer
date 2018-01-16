#pragma once
#include "Character.h"

enum class EnemyType { Orc, Orc_Shaman, Skeleton };

class Enemy : public Character
{
private:
	EnemyType m_enemyType;
public:
	Enemy(Entity_Manager * entmgr, EnemyType eType, const sf::Texture& spritesheet);
};

#pragma once
#include "Character.h"

enum class EnemyType { Orc, Orc_Shaman, Skeleton };

class Enemy : public Character
{
private:
	EnemyType m_enemyType;
	sf::Vector2f m_destination;
	bool m_hasDestination;
public:
	Enemy(Entity_Manager * entmgr, EnemyType eType, const sf::Texture& spritesheet);
	void OnEntityCollision(EntityBase* l_collider, bool l_attack);
	void update(float dt);
};

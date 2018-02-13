#pragma once
#include "../include/EntityBase.h"
#include "Character.h"
enum class ItemType {WEAPON, POTION, COIN , BUFF, TRAP};

class Item :
	public EntityBase
{
public:
	Item(Entity_Manager * entmgr,ItemType itemType, const sf::Texture& spritesheet);
	~Item();

	virtual void draw(sf::RenderWindow & window, float dt);
	virtual void update(const float dt);

	virtual void OnEntityCollision(EntityBase* eb_collider, bool b_attack);
	virtual unsigned int getHealth() { return 0; }
	virtual unsigned int getScore() { return 0; }
	virtual void setScore(unsigned int points) {}
	virtual void resetHP() {}
private:
	bool m_isCollected;
	ItemType m_itemType;
};

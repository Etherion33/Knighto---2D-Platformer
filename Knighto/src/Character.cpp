#include "../include/Character.h"

enum class EnitityState { Idle, Walking, Attacking, Jumping, Dying };


Character::Character(Entity_Manager* enmgr)
	: EntityBase(enmgr)
{
	m_health = 100;
}


Character::~Character()
{
}

void Character::draw(sf::RenderWindow & window, float dt)
{

}

void Character::update(const float dt)
{

}

void Character::OnEntityCollision(EntityBase * eb_collider, bool b_attack)
{

}

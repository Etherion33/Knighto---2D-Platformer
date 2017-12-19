#include "../include/Item.h"

Item::Item(Entity_Manager * entmgr) : EntityBase(entmgr)
{
}

Item::~Item()
{
}

void Item::draw(sf::RenderWindow & window, float dt)
{
}

void Item::update(const float dt)
{
}

void Item::OnEntityCollision(EntityBase * eb_collider, bool b_attack)
{
}
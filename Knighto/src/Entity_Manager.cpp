#include "../include/Entity_Manager.h"

Entity_Manager::Entity_Manager()
{

}


Entity_Manager::~Entity_Manager()
{

}

void Entity_Manager::add(EntityBase* e)
{
	m_entities.push_back(e);
}

EntityBase * Entity_Manager::getById(unsigned int id)
{
	return m_entities.back();
}

void Entity_Manager::draw(sf::RenderWindow & window, float dt)
{
	for (EntityBase* e : m_entities)
	{
		e->draw(window,dt);
	}
	//player.draw(window,dt);
}

void Entity_Manager::update(float dt)
{
	for (EntityBase* e : m_entities)
	{
		e->update(dt);
	}
	//player.update(dt);
}

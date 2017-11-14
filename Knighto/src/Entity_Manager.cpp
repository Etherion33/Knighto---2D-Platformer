#include "../include/Entity_Manager.h"

Entity_Manager::Entity_Manager()
{
	m_nOfEntities = 0;

}


Entity_Manager::~Entity_Manager()
{
}

void Entity_Manager::add(EntityBase* e)
{
	e->setId(m_nOfEntities);
	m_entities.push_back(e);
	m_nOfEntities++;
}

EntityBase * Entity_Manager::getById(unsigned int id)
{
	return m_entities.at(id);
}

EntityBase * Entity_Manager::getByName(const std::string & name)
{
	for (EntityBase* e : m_entities)
	{
		if (e->getName() == name)
		{
			return e;
		}
	}
	return nullptr;
}

int Entity_Manager::enCount()
{
	return m_nOfEntities;
}


void Entity_Manager::destroyAll()
{
	m_entities.clear();
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

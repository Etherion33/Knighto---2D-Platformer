#include "../include/Entity_Manager.h"
#include <iostream>

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
	for (EntityBase* e : m_entities)
	{
		if (e->getId() == id)
		{
			return e;
		}
	}
	return nullptr;
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

void Entity_Manager::Remove(unsigned int id)
{
	m_entitiesToRemove.emplace_back(id);
}

void Entity_Manager::destroyAll()
{
	m_entities.clear();
}

void Entity_Manager::draw(sf::RenderWindow & window, float dt)
{
	for (EntityBase* e : m_entities)
	{
		e->draw(window, dt);
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
	EntityCollisionCheck();
	ProcessRemovals();
	return;
}

void Entity_Manager::setLevel(Level* l_level)
{
	m_level = l_level;
}

Level* Entity_Manager::getData()
{
	return m_level;
}

void Entity_Manager::ProcessRemovals() {
	while (m_entitiesToRemove.begin() != m_entitiesToRemove.end()) {
		unsigned int id = m_entitiesToRemove.back();
		auto itr = find(m_entities.begin(), m_entities.end(), m_entities.at(id));
		if (itr != m_entities.end()) {
			std::cout << "Discarding entity: " << (*itr)->getId() << std::endl;
			m_entities.erase(itr);
		}
		m_entitiesToRemove.pop_back();
	}
}

void Entity_Manager::EntityCollisionCheck() {
	if (m_entities.empty()) { return; }
	for (auto itr = m_entities.begin(); std::next(itr) != m_entities.end(); ++itr)
	{
		for (auto itr2 = std::next(itr); itr2 != m_entities.end(); ++itr2)
		{
			if (itr == itr2) { continue; }
			// Regular AABB bounding box collision.
			if ((*itr)->m_AABB.intersects((*itr2)->m_AABB)) {
				(*itr)->OnEntityCollision((*itr2), false);
				(*itr2)->OnEntityCollision((*itr), false);
			}

			EntityType t1 = (*itr)->getType();
			EntityType t2 = (*itr2)->getType();
			if (t1 == EntityType::Player || t1 == EntityType::Enemy) {
				Character* c1 = (Character*)(*itr);
				if (c1->m_attackAABB.intersects((*itr2)->m_AABB)) {
					c1->OnEntityCollision((*itr2), true);
				}
			}

			if (t2 == EntityType::Player || t2 == EntityType::Enemy) {
				Character* c2 = (Character*)(*itr2);
				if (c2->m_attackAABB.intersects((*itr)->m_AABB)) {
					c2->OnEntityCollision((*itr), true);
				}
			}
		}
	}
}

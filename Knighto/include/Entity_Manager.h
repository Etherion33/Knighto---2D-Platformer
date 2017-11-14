#pragma once
#include <SFML/Graphics.hpp>
#include "EntityBase.h"

using EntityContainer = std::vector<EntityBase*>;

class Entity_Manager
{
public:
	Entity_Manager();
	~Entity_Manager();

	void add(EntityBase* e);
	EntityBase* getById(unsigned int id);
	EntityBase* getByName(const std::string& name);
	int enCount();
	void Remove(unsigned int id);
	void destroyAll();

	void draw(sf::RenderWindow & window, float dt);
	void update(float dt);

private:
	EntityContainer m_entities;
	unsigned int m_nOfEntities;
};


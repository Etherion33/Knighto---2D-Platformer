#pragma once
#include <SFML/Graphics.hpp>
#include "EntityBase.h"
#include "Level.h"

using EntityContainer = std::vector<EntityBase*>;

class Texture_Manager;
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
	Texture_Manager* m_texMgr;

	void setLevel(Level* l_gs);
	Level* getData();
private:
	EntityContainer m_entities;
	Level * m_level;
	unsigned int m_nOfEntities;
};
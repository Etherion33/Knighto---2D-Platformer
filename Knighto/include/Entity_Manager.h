#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "EntityBase.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"

using EntityContainer = std::vector<EntityBase*>;
//using EntityContainer = std::unordered_map<unsigned int, EntityBase*>;

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

	void ProcessRemovals();
	//void LoadEnemyTypes(const std::string& l_name);
	void EntityCollisionCheck();
	
	void draw(sf::RenderWindow & window, float dt);
	void update(float dt);
	Texture_Manager* m_texMgr;

	void setLevel(Level* l_gs);
	Level* getData();
private:
	EntityContainer m_entities;
	Level * m_level;
	unsigned int m_nOfEntities;

	std::vector<unsigned int> m_entitiesToRemove;

};
#pragma once
#include "Game.h"
#include "Game_State.h"
#include "Entity_Manager.h"

struct SharedData {
	SharedData() :
		m_wind(nullptr),
		m_textureManager(nullptr),
		m_entityManager(nullptr),
		m_level(nullptr) {}

	Game* m_wind;
	Texture_Manager* m_textureManager;
	Entity_Manager* m_entityManager;
	Level* m_level;
};
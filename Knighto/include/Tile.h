#pragma once
#include <SFML\Graphics.hpp>
#include "AnimatedSprite.h"

enum class TileType { AIR, GRASS, WATER, FOREST, DIRT, BRICK, PLAYER_SPAWN, MONSTER_SPAWN };

class Tile
{
public:
	unsigned int m_TileId;
	sf::Sprite m_TileSprite;
	sf::Vector2f m_TilePos;
	Animation m_TileAnimation;
	AnimatedSprite m_TileAnimatedSprite;
	int m_TileSize;
	sf::Vector2f m_friction;
	bool m_deadly;
	TileType m_TileType;
	void draw(sf::RenderWindow& window, float dt);
	void update();
	Tile() {}
	Tile(Animation& tileAnimation, const TileType tileType, sf::Vector2f tilePos, sf::Vector2f friction);
	bool isSolid;
};

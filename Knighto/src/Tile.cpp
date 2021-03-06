#include "../include/Tile.h"

void Tile::draw(sf::RenderWindow & window, float dt)
{
	this->m_TileAnimatedSprite.play(m_TileAnimation);
	this->m_TileAnimatedSprite.update(sf::seconds(dt));

	window.draw(this->m_TileAnimatedSprite);
	//window.draw(this->m_TileSprite);
}

void Tile::update()
{
	if (this->m_TileType == TileType::CHEST)
	{

	}
}

Tile::Tile(Animation& tileAnimation, const TileType tileType, sf::Vector2f tilePos, sf::Vector2f friction)
{
	this->m_TileSize = 8;
	this->m_TileType = tileType;
	this->m_TileAnimation = tileAnimation;
	this->m_TilePos = tilePos;
	this->m_friction = friction;
	this->m_TileAnimatedSprite = AnimatedSprite(sf::seconds(0.4), true, false);
	this->m_isVisible = true;
}
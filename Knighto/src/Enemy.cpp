#include "../include/Enemy.h"

Enemy::Enemy(Entity_Manager * entmgr, const sf::Texture& spritesheet, sf::Vector2f enemyPos)
	:Character(entmgr)
{
	m_Name = "Goblin";
	this->m_Animations["idle"].setSpriteSheet(spritesheet);
	this->m_Animations["idle"].addFrame(sf::IntRect(20, 0, 20, 20));

	this->m_Pos = enemyPos;

	this->currentAnimation = this->m_Animations["idle"];

	this->m_AnimatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	//m_PlayerSprite.setPosition(m_PlayerPos);
	this->m_AnimatedSprite.setPosition(m_Pos);
}

void Enemy::update(float dt)
{
	m_AnimatedSprite.play(currentAnimation);
	this->m_AnimatedSprite.update(sf::seconds(dt));
}

void Enemy::draw(sf::RenderWindow & window, float dt)
{
	window.draw(this->m_AnimatedSprite);
	return;
}


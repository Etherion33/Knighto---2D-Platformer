#include "../include/Enemy.h"

Enemy::Enemy(EnemyType eType,const sf::Texture& spritesheet, sf::Vector2f enemyPos)
	:Character()
{
	this->m_enType = EntityType::Enemy;
	this->m_enemyType = eType;
	
	switch (m_enemyType)
	{
		case EnemyType::Orc:
		{
			m_Name = "Orc";
			break;
		}
		case EnemyType::Skeleton:
			m_Name = "Skeleton";
			break;
		case EnemyType::Goblin:
			m_Name = "Goblin";
			break;
		
	}
	
	this->m_Animations["idle"].setSpriteSheet(spritesheet);
	this->m_Animations["idle"].addFrame(sf::IntRect(20, 0, 20, 20));

	this->m_Pos = enemyPos;

	this->currentAnimation = this->m_Animations["idle"];

	this->m_AnimatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
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


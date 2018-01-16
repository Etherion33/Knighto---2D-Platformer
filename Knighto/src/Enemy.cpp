#include "../include/Enemy.h"

Enemy::Enemy(Entity_Manager* entmgr,EnemyType eType, const sf::Texture& spritesheet)
	:Character(entmgr,spritesheet)
{
	this->m_enType = EntityType::Enemy;
	this->m_enemyType = eType;

	switch (m_enemyType)
	{
		case EnemyType::Orc:
		{
			m_Name = "Orc";
			this->m_health = 50;
			this->setSize(20, 20);
			break;
		}
		case EnemyType::Orc_Shaman: {
			m_Name = "Orc Shaman";
			this->m_health = 125;
			this->setSize(24, 24);
			break;
		}	
	}

	this->m_Velocity = { 10.f , 10.f };
	this->m_maxVelocity = { 30.f,30.f };
	this->m_Speed = { 15.f,15.f };

	this->currentAnimation = this->m_Animations["idle"];
	this->m_enState = EntityState::Idle;
	this->m_AnimatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	this->m_AnimatedSprite.setPosition(m_Pos);
}
#include "../include/Enemy.h"

Enemy::Enemy(Entity_Manager* entmgr,EnemyType eType, const sf::Texture& spritesheet)
	:Character(entmgr,spritesheet), m_hasDestination(false)
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
			this->m_health = 50;
			this->setSize(10, 14);
			this->m_attackAABBoffset = { 0 ,0 };
			this->m_attackAABB = { m_attackAABBoffset.x, m_attackAABBoffset.y, 14, 14 };
			break;
		}	
	}

	this->m_Velocity = { 10.f , 10.f };
	this->m_maxVelocity = { 30.f,30.f };
	this->m_Speed = { 15.f,15.f };

	this->currentAnimation = this->m_Animations["idle_left"];
	this->m_enState = EntityState::Idle;
	this->m_AnimatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	this->m_AnimatedSprite.setPosition(m_Pos);
}

void Enemy::OnEntityCollision(EntityBase * l_collider, bool l_attack)
{
	if (m_enState == EntityState::Dying) { return; }
	if (l_attack) { return; }
	if (l_collider->getType() != EntityType::Player) { return; }
	Character* player = (Character*)l_collider;
	setState(EntityState::Attacking);
	player->getHurt(5);
	if (m_Pos.x > player->getPosition().x) {
		player->addVelocity(-m_Speed.x, 0);
		direct = DIRECTION::LEFT;
	}
	else {
		player->addVelocity(m_Speed.y, 0);
		direct = DIRECTION::RIGHT;
	}
}

void Enemy::update(float dt)
{
	Character::update(dt);

	if (m_hasDestination) {
		if (abs(m_destination.x - m_Pos.x) < 16) { m_hasDestination = false; return; }
		if (m_destination.x - m_Pos.x > 0) { move(DIRECTION::RIGHT); }
		else { move(DIRECTION::LEFT); }
		if (m_collidingOnX) { m_hasDestination = false; }
		return;
	}
	int random = rand() % 1000 + 1;
	if (random != 1000) { return; }
	int newX = rand() % 65 + 0;
	if (rand() % 2) { newX = -newX; }
	m_destination.x = m_Pos.x + newX;
	if (m_destination.x < 0) { m_destination.x = 0; }
	m_hasDestination = true;
}

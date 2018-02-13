#include "../include/Player.h"
#include <iostream>

Player::Player(Entity_Manager* entmgr,const sf::Texture& spritesheet)
	: Character(entmgr,spritesheet)
{
	this->m_enType = EntityType::Player;
	this->m_Name = "Knighto";
	this->m_health = 100;
	this->m_maxVelocity = { 100.f,150.f };
	this->m_Speed = { 512.f,50.f };
	this->currentAnimation = m_Animations["idle_right"];
	//this->m_attackAABBoffset = { -5 ,0 };
	//this->m_attackAABB = { m_attackAABBoffset.x, m_attackAABBoffset.y, 10, 13 };
	this->m_enState = EntityState::Idle;
	this->setSize(10, 13);
	this->score = 0;
	this->m_AnimatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	//m_PlayerSprite.setPosition(m_PlayerPos);
	//this->m_AnimatedSprite.setPosition(m_Pos);
}

//void Player::draw(sf::RenderWindow& window, float dt)
//{
//	//window.draw(this->m_AnimatedSprite);
//	return;
//}
//
void Player::update(float dt)
{
	if (!m_isEquipped)
	{
		this->m_attackAABBoffset = { -5 ,0 };
		this->m_attackAABB = { m_attackAABBoffset.x, m_attackAABBoffset.y, 10, 13 };
	}
	else
	{
		this->m_attackAABBoffset = { -5 ,0 };
		this->m_attackAABB = { m_attackAABBoffset.x, m_attackAABBoffset.y, 15, 13 };
	}
	Character::update(dt);
}

void Player::OnEntityCollision(EntityBase * l_collider, bool l_attack)
{
	if (m_enState == EntityState::Dying) { return; }
	if (l_attack) {
		if (m_enState != EntityState::Attacking) { return; }
		//if (!m_spriteSheet.GetCurrentAnim()->IsInAction()) { return; }
		if (l_collider->getType() != EntityType::Enemy &&
			l_collider->getType() != EntityType::Player)
		{
			return;
		}
		Character* opponent = (Character*)l_collider;
		if (!this->m_isEquipped)
		{
			opponent->getHurt(5);
		}
		else {
			opponent->getHurt(20);
		}

		if (m_Pos.x > opponent->getPosition().x) {
			opponent->addVelocity(-32, 0);
		}
		else {
			opponent->addVelocity(32, 0);
		}
	}
	else {
		// Other behavior.
	}
}

Player::~Player()
{
}

void Player::handleInput(std::string input)
{
	if (input == "MoveLeft") {
		Character::move(DIRECTION::LEFT);
	}
	else if (input == "MoveRight") {
		Character::move(DIRECTION::RIGHT);
	}
	else if (input == "Jump") {
		Character::jump();
	}
	else if (input == "Attack") {
		Character::attack();
	}
}
#include "../include/Player.h"
#include <iostream>

Player::Player(Entity_Manager* entmgr,const sf::Texture& spritesheet)
	: Character(entmgr,spritesheet)
{
	this->m_enType = EntityType::Player;
	this->m_Name = "Knighto";
	this->m_health = 125;
	this->m_maxVelocity = { 200.f,1024.f };
	this->m_Speed = { 1024.f,128.f };
	
	this->currentAnimation = m_Animations["idle"];
	this->m_enState = EntityState::Idle;
	this->setSize(24, 24);

	this->m_AnimatedSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	//m_PlayerSprite.setPosition(m_PlayerPos);
	this->m_AnimatedSprite.setPosition(m_Pos);
}

//void Player::draw(sf::RenderWindow& window, float dt)
//{
//	//window.draw(this->m_AnimatedSprite);
//	return;
//}
//
//void Player::update(float dt)
//{
//	//m_AnimatedSprite.play(currentAnimation);
//	//this->m_AnimatedSprite.update(sf::seconds(dt));
//}

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
		//Character::attack();
	}
}
#include "../include/Player.h"
#include <iostream>

Player::Player(Entity_Manager* enmgr, const sf::Texture& spritesheet)
	: Character(enmgr)
{
	this->m_health = 125;
	this->m_Velocity = { 80.f , 80.f };
	this->m_Animations["idle"].setSpriteSheet(spritesheet);
	this->m_Animations["idle"].addFrame(sf::IntRect(24, 0, 24, 24));

	this->m_Animations["left"].setSpriteSheet(spritesheet);
	this->m_Animations["left"].addFrame(sf::IntRect(192, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(168, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(144, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(192, 72, 24, 24));

	this->m_Animations["right"].setSpriteSheet(spritesheet);
	this->m_Animations["right"].addFrame(sf::IntRect(0, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(24, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(48, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(0, 0, 24, 24));

	this->m_Animations["up"].setSpriteSheet(spritesheet);
	this->m_Animations["up"].addFrame(sf::IntRect(0, 0, 24, 24));
	this->m_Animations["up"].addFrame(sf::IntRect(24, 0, 24, 24));
	this->m_Animations["up"].addFrame(sf::IntRect(48, 0, 24, 24));
	this->m_Animations["up"].addFrame(sf::IntRect(0, 0, 24, 24));

	this->m_Animations["down"].setSpriteSheet(spritesheet);
	this->m_Animations["down"].addFrame(sf::IntRect(0, 0, 24, 24));
	this->m_Animations["down"].addFrame(sf::IntRect(24, 0, 24, 24));
	this->m_Animations["down"].addFrame(sf::IntRect(48, 0, 24, 24));
	this->m_Animations["down"].addFrame(sf::IntRect(0, 0, 24, 24));

	this->m_Animations["attack_left"].setSpriteSheet(spritesheet);
	this->m_Animations["attack_left"].addFrame(sf::IntRect(72,0,24,24));
	this->m_Animations["attack_left"].addFrame(sf::IntRect(96, 0, 24,24 ));
	this->m_Animations["attack_left"].addFrame(sf::IntRect(120, 0, 24, 24));

	this->m_Animations["attack_right"].setSpriteSheet(spritesheet);
	this->m_Animations["attack_right"].addFrame(sf::IntRect(144, 72, 24, 24));
	this->m_Animations["attack_right"].addFrame(sf::IntRect(96, 72, 24, 24));
	this->m_Animations["attack_right"].addFrame(sf::IntRect(72, 72, 24, 24));

	this->m_Animations["got_hurt_right"].setSpriteSheet(spritesheet);
	this->m_Animations["got_hurt_right"].addFrame(sf::IntRect(144,0,24,24));
	this->m_Animations["got_hurt_right"].addFrame(sf::IntRect(168, 0, 24, 24));

	this->m_Animations["got_hurt_left"].setSpriteSheet(spritesheet);
	this->m_Animations["got_hurt_left"].addFrame(sf::IntRect(48, 72, 24, 24));
	this->m_Animations["got_hurt_left"].addFrame(sf::IntRect(24, 72, 24, 24));

	this->m_Animations["died_right"].setSpriteSheet(spritesheet);
	this->m_Animations["died_right"].addFrame(sf::IntRect(192, 0, 24, 24));

	this->m_Animations["died_left"].setSpriteSheet(spritesheet);
	this->m_Animations["died_left"].addFrame(sf::IntRect(0, 72, 24, 24));

	this->currentAnimation = m_Animations["idle"];
	this->m_enState = EntityState::Idle;
	this->setSize(24, 24);
	m_Pos.x = 50.f;
	m_Pos.y = 50.f;

	this->m_AnimatedSprite =  AnimatedSprite(sf::seconds(0.2), true, false);
	//m_PlayerSprite.setPosition(m_PlayerPos);
	this->m_AnimatedSprite.setPosition(m_Pos);
}

void Player::draw(sf::RenderWindow& window, float dt)
{
	window.draw(this->m_AnimatedSprite);
	return;
}

void Player::move(float speedX, float speedY)
{
	if (speedX < 0 && speedY == 0)
	{
		this->currentAnimation = m_Animations["left"];
		this->velocity = { speedX, speedY };
		IsMoving = true;
	}
	if (speedX > 0 && speedY == 0)
	{
		this->currentAnimation = m_Animations["right"];
		this->velocity = { speedX, speedY };
		IsMoving = true;
	}
	if (speedX == 0 && speedY < 0)
	{
		this->currentAnimation = m_Animations["up"];
		this->velocity = { speedX, speedY };
		IsMoving = true;
	}
	if (speedX == 0 && speedY > 0)
	{
		this->currentAnimation = m_Animations["down"];
		this->velocity = { speedX, speedY };
		IsMoving = true;
	}
}

void Player::stop()
{
	this->m_AnimatedSprite.stop();
	return;
}

void Player::attack(EntityBase * other_entity)
{
	other_entity = NULL;
	if(true)
	{
		currentAnimation = m_Animations["attack_left"];
	}
	else {
		currentAnimation = m_Animations["attack_right"];
	}

}

void Player::update(float dt)
{
	sf::Time frameTime = sf::seconds(dt);
	m_AnimatedSprite.play(currentAnimation);
	m_AnimatedSprite.move(this->velocity* frameTime.asSeconds());
	
	m_Pos = m_AnimatedSprite.getPosition();

	velocity = { 0.0f, 0.0f };
	if (this->getState() == EntityState::Dying)
	{
		currentAnimation = m_Animations["died_left"];
	}



	m_AnimatedSprite.update(frameTime);

	//m_PlayerSprite.setPosition(m_PlayerPos);
}

Player::~Player()
{
}
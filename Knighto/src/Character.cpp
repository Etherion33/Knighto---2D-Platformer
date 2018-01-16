#include "../include/Character.h"
#include <iostream>

enum class EnitityState { Idle, Walking, Attacking, Jumping, Dying };

Character::Character(Entity_Manager * entmgr, const sf::Texture& spritesheet)
	: EntityBase(entmgr)
{
	m_health = 100;
	m_jumpVelocity = 500;
	direct = DIRECTION::LEFT;

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
	this->m_Animations["attack_left"].addFrame(sf::IntRect(72, 0, 24, 24));
	this->m_Animations["attack_left"].addFrame(sf::IntRect(96, 0, 24, 24));
	this->m_Animations["attack_left"].addFrame(sf::IntRect(120, 0, 24, 24));

	this->m_Animations["attack_right"].setSpriteSheet(spritesheet);
	this->m_Animations["attack_right"].addFrame(sf::IntRect(144, 72, 24, 24));
	this->m_Animations["attack_right"].addFrame(sf::IntRect(96, 72, 24, 24));
	this->m_Animations["attack_right"].addFrame(sf::IntRect(72, 72, 24, 24));

	this->m_Animations["got_hurt_right"].setSpriteSheet(spritesheet);
	this->m_Animations["got_hurt_right"].addFrame(sf::IntRect(144, 0, 24, 24));
	this->m_Animations["got_hurt_right"].addFrame(sf::IntRect(168, 0, 24, 24));

	this->m_Animations["got_hurt_left"].setSpriteSheet(spritesheet);
	this->m_Animations["got_hurt_left"].addFrame(sf::IntRect(48, 72, 24, 24));
	this->m_Animations["got_hurt_left"].addFrame(sf::IntRect(24, 72, 24, 24));

	this->m_Animations["died_right"].setSpriteSheet(spritesheet);
	this->m_Animations["died_right"].addFrame(sf::IntRect(192, 0, 24, 24));

	this->m_Animations["died_left"].setSpriteSheet(spritesheet);
	this->m_Animations["died_left"].addFrame(sf::IntRect(0, 72, 24, 24));
}

Character::~Character()
{


}

void Character::draw(sf::RenderWindow & window, float dt)
{
	window.draw(this->m_AnimatedSprite);
}

void Character::update(const float dt)
{
	EntityBase::update(dt);

	if (getState() != EntityState::Dying && getState() != EntityState::Attacking && getState() != EntityState::Hurt) {
		if (abs(m_Velocity.y) >= 0.001f) {
			setState(EntityState::Jumping);
		}
		else if (abs(m_Velocity.x) >= 0.1f) {
			setState(EntityState::Walking);
		}
		else {
			setState(EntityState::Idle);
		}
	}

	animate();
	m_AnimatedSprite.play(currentAnimation);
	m_AnimatedSprite.setPosition(m_Pos);
	m_AnimatedSprite.update(sf::seconds(dt));
}

void Character::move(const DIRECTION& dir)
{
	if (getState() == EntityState::Dying) return;
	if (dir == DIRECTION::LEFT)
	{
		currentAnimation = m_Animations["left"];
		accelerate(-m_Speed.x, 0);
	}
	else {
		currentAnimation = m_Animations["right"];
		accelerate(m_Speed.x, 0);
	}
	if (getState() == EntityState::Idle) { setState(EntityState::Walking); }
}

void Character::jump()
{
	if (getState() == EntityState::Dying || getState() == EntityState::Jumping || getState() == EntityState::Hurt) { return; }
	setState(EntityState::Jumping);

	addVelocity(0, -m_jumpVelocity);
}

void Character::animate()
{
	EntityState state = getState();

	if (state == EntityState::Walking)
	{
		if(direct == DIRECTION::LEFT)
			currentAnimation = m_Animations["left"];
		if(direct == DIRECTION::RIGHT)
			currentAnimation = m_Animations["right"];
	}
	else if (state == EntityState::Jumping)
	{
		currentAnimation = m_Animations["up"];
	}
	else if (state == EntityState::Attacking)
	{
		currentAnimation = m_Animations["attack_left"];
	}
	else if (state == EntityState::Hurt)
	{
		currentAnimation = m_Animations["got_hurt_right"];
	}
	else if (state == EntityState::Dying)
	{
		currentAnimation = m_Animations["died_left"];
	}
	else if (state == EntityState::Idle)
	{
		currentAnimation = m_Animations["idle"];
	}
}

void Character::OnEntityCollision(EntityBase * eb_collider, bool b_attack)
{

}
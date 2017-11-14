#include "../include/Character.h"
#include <iostream>
enum class EnitityState { Idle, Walking, Attacking, Jumping, Dying };


Character::Character()
	: EntityBase()
{
	m_health = 100;
	m_jumpVelocity = 250;
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
	system("cls");
	std::cout << "Delta Time:" << dt << std::endl;
	std::cout << "Entity acceleration x: " << m_Acceleration.x << "\ty: " << m_Acceleration.y << std::endl;
	std::cout << "Entity acceleration x: " << m_Speed.x << "\ty: " << m_Speed.y << std::endl;

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
		currentAnimation = m_Animations["left"];
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

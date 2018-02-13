#include "../include/Character.h"
#include "../include/Entity_Manager.h"
#include <iostream>

enum class EnitityState { Idle, Walking, Attacking, Jumping, Dying };

Character::Character(Entity_Manager * entmgr, const sf::Texture& spritesheet)
	: EntityBase(entmgr)
{
	m_health = 100;
	m_jumpVelocity = 100;
	direct = DIRECTION::LEFT;
	m_isEquipped = false;

	this->m_Animations["idle_right"].setSpriteSheet(spritesheet);
	this->m_Animations["idle_right"].addFrame(sf::IntRect(24, 0, 24, 24));

	this->m_Animations["idle_right_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["idle_right_armed"].addFrame(sf::IntRect(48, 0, 24, 24));

	this->m_Animations["idle_left"].setSpriteSheet(spritesheet);
	this->m_Animations["idle_left"].addFrame(sf::IntRect(168, 72, 24, 24));

	this->m_Animations["idle_left_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["idle_left_armed"].addFrame(sf::IntRect(168, 96, 24, 24));

	this->m_Animations["left"].setSpriteSheet(spritesheet);
	this->m_Animations["left"].addFrame(sf::IntRect(192, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(168, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(144, 72, 24, 24));
	this->m_Animations["left"].addFrame(sf::IntRect(192, 72, 24, 24));

	this->m_Animations["left_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["left_armed"].addFrame(sf::IntRect(192, 96, 24, 24));
	this->m_Animations["left_armed"].addFrame(sf::IntRect(168, 96, 24, 24));
	this->m_Animations["left_armed"].addFrame(sf::IntRect(144, 96, 24, 24));
	this->m_Animations["left_armed"].addFrame(sf::IntRect(192, 96, 24, 24));

	this->m_Animations["right"].setSpriteSheet(spritesheet);
	this->m_Animations["right"].addFrame(sf::IntRect(0, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(24, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(48, 0, 24, 24));
	this->m_Animations["right"].addFrame(sf::IntRect(0, 0, 24, 24));

	this->m_Animations["right_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["right_armed"].addFrame(sf::IntRect(0, 24, 24, 24));
	this->m_Animations["right_armed"].addFrame(sf::IntRect(24, 24, 24, 24));
	this->m_Animations["right_armed"].addFrame(sf::IntRect(48, 24, 24, 24));
	this->m_Animations["right_armed"].addFrame(sf::IntRect(0, 24, 24, 24));

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
	this->m_Animations["attack_left"].addFrame(sf::IntRect(120, 72, 24, 24));
	this->m_Animations["attack_left"].addFrame(sf::IntRect(96, 72, 24, 24));
	this->m_Animations["attack_left"].addFrame(sf::IntRect(72, 72, 24, 24));

	this->m_Animations["attack_left_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["attack_left_armed"].addFrame(sf::IntRect(120, 96, 24, 24));
	this->m_Animations["attack_left_armed"].addFrame(sf::IntRect(96, 96, 24, 24));
	this->m_Animations["attack_left_armed"].addFrame(sf::IntRect(72,96, 24, 24));

	this->m_Animations["attack_right"].setSpriteSheet(spritesheet);
	this->m_Animations["attack_right"].addFrame(sf::IntRect(72, 0, 24, 24));
	this->m_Animations["attack_right"].addFrame(sf::IntRect(96, 0, 24, 24));
	this->m_Animations["attack_right"].addFrame(sf::IntRect(120, 0, 24, 24));

	this->m_Animations["attack_right_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["attack_right_armed"].addFrame(sf::IntRect(72, 24, 24, 24));
	this->m_Animations["attack_right_armed"].addFrame(sf::IntRect(96, 24, 24, 24));
	this->m_Animations["attack_right_armed"].addFrame(sf::IntRect(120, 24, 24, 24));

	this->m_Animations["got_hurt_right"].setSpriteSheet(spritesheet);
	this->m_Animations["got_hurt_right"].addFrame(sf::IntRect(144, 0, 24, 24));
	this->m_Animations["got_hurt_right"].addFrame(sf::IntRect(168, 0, 24, 24));

	this->m_Animations["got_hurt_right_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["got_hurt_right_armed"].addFrame(sf::IntRect(144, 24, 24, 24));
	this->m_Animations["got_hurt_right_armed"].addFrame(sf::IntRect(168, 24, 24, 24));

	this->m_Animations["got_hurt_left"].setSpriteSheet(spritesheet);
	this->m_Animations["got_hurt_left"].addFrame(sf::IntRect(48, 72, 24, 24));
	this->m_Animations["got_hurt_left"].addFrame(sf::IntRect(24, 72, 24, 24));

	this->m_Animations["got_hurt_left_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["got_hurt_left_armed"].addFrame(sf::IntRect(48, 96, 24, 24));
	this->m_Animations["got_hurt_left_armed"].addFrame(sf::IntRect(24, 96, 24, 24));

	this->m_Animations["died_right"].setSpriteSheet(spritesheet);
	this->m_Animations["died_right"].addFrame(sf::IntRect(192, 0, 24, 24));

	this->m_Animations["died_right_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["died_right_armed"].addFrame(sf::IntRect(192, 24, 24, 24));

	this->m_Animations["died_left"].setSpriteSheet(spritesheet);
	this->m_Animations["died_left"].addFrame(sf::IntRect(0, 72, 24, 24));

	this->m_Animations["died_left_armed"].setSpriteSheet(spritesheet);
	this->m_Animations["died_left_armed"].addFrame(sf::IntRect(0, 96, 24, 24));
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
	if (m_attackAABB.width != 0 && m_attackAABB.height != 0) {
		UpdateAttackAABB();
	}
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
	else if (getState() == EntityState::Attacking || getState() == EntityState::Hurt) {
		 if (!m_AnimatedSprite.isPlaying()) {
			 setState(EntityState::Idle);
		 }
	 }
	else if (getState() == EntityState::Dying) {
		 if (!m_AnimatedSprite.isPlaying()) {
			 //m_entityManager->Remove(m_Id);
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
		direct = DIRECTION::LEFT;
		accelerate(-m_Speed.x, 0);
	}
	else {
		currentAnimation = m_Animations["right"];
		direct = DIRECTION::RIGHT;
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
		if (direct == DIRECTION::LEFT && m_isEquipped == true)
			currentAnimation = m_Animations["left_armed"];
		else
			currentAnimation = m_Animations["left"];

		if (direct == DIRECTION::RIGHT && m_isEquipped == true)
			currentAnimation = m_Animations["right_armed"];
		else
			currentAnimation = m_Animations["right"];

	}
	else if (state == EntityState::Jumping)
	{
		if (direct == DIRECTION::LEFT && m_isEquipped == true)
			currentAnimation = m_Animations["left_armed"];
		else
			currentAnimation = m_Animations["left"];

		if (direct == DIRECTION::RIGHT && m_isEquipped == true)
			currentAnimation = m_Animations["right_armed"];
		else
			currentAnimation = m_Animations["right"];
	}
	else if (state == EntityState::Attacking)
	{
		if (direct == DIRECTION::LEFT && m_isEquipped == true)
			currentAnimation = m_Animations["attack_left_armed"];
		else
			currentAnimation = m_Animations["attack_left"];

		if (direct == DIRECTION::RIGHT && m_isEquipped == true)
			currentAnimation = m_Animations["attack_right_armed"];
		else			
			currentAnimation = m_Animations["attack_right"];

	}
	else if (state == EntityState::Hurt)
	{
		if (direct == DIRECTION::LEFT && m_isEquipped == true)
			currentAnimation = m_Animations["got_hurt_left_armed"]; //armed
		else
			currentAnimation = m_Animations["got_hurt_left"];

		if (direct == DIRECTION::RIGHT && m_isEquipped == true)
			currentAnimation = m_Animations["got_hurt_right_armed"];
		else
			currentAnimation = m_Animations["got_hurt_right"];
	}
	else if (state == EntityState::Dying)
	{
		if (direct == DIRECTION::LEFT && m_isEquipped == true)
			currentAnimation = m_Animations["died_left_armed"]; //armed
		else
			currentAnimation = m_Animations["died_left"];

		if (direct == DIRECTION::RIGHT && m_isEquipped == true)
			currentAnimation = m_Animations["died_right_armed"];
		else
			currentAnimation = m_Animations["died_right"];
	}
	else if (state == EntityState::Idle)
	{
		if (direct == DIRECTION::LEFT && m_isEquipped == true)
			currentAnimation = m_Animations["idle_left_armed"]; //armed
		else
			currentAnimation = m_Animations["idle_left"];

		if (direct == DIRECTION::RIGHT && m_isEquipped == true)
			currentAnimation = m_Animations["idle_right_armed"];
		else
			currentAnimation = m_Animations["idle_right"];
	}
}

void Character::attack() {
	if (getState() == EntityState::Dying || getState() == EntityState::Jumping ||
		getState() == EntityState::Hurt || getState() == EntityState::Attacking)
	{
		return;
	}
	setState(EntityState::Attacking);
}

void Character::getHurt(const int& l_damage) {
	if (getState() == EntityState::Dying || getState() == EntityState::Hurt) { return; }
	m_health = (m_health - l_damage > 0 ? m_health - l_damage : 0);
	if (m_health) { setState(EntityState::Hurt); }
	else if (m_health <= 0) { setState(EntityState::Dying); }
	else { setState(EntityState::Dying); }
}

void Character::UpdateAttackAABB() {
	m_attackAABB.left =
		(direct == DIRECTION::LEFT ?
		(m_AABB.left - m_attackAABB.width) - m_attackAABBoffset.x
			: (m_AABB.left + m_AABB.width) + m_attackAABBoffset.x);
	m_attackAABB.top = m_AABB.top + m_attackAABBoffset.y;
}
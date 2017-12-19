#include "../include/EntityBase.h"
#include "../include/Entity_Manager.h"
#include "../include/Tile.h"
#include "../include/Game_State.h"
#include "../include/Game_State_Gameplay.h"
#include <iostream>

EntityBase::EntityBase(Entity_Manager* entmgr)
	:
	m_entityManager(entmgr),
	m_Name("BaseEntity"),
	m_enType(EntityType::Base), m_Id(0), m_referenceTile(nullptr),
	m_enState(EntityState::Idle),
	m_collidingOnX(false), m_collidingOnY(false) {}

EntityBase::~EntityBase() {}

bool SortCollisions(const CollisionElement& l_1, const CollisionElement& l_2)
{
	return l_1.m_area > l_2.m_area;
}

void EntityBase::setId(unsigned int id)
{
	m_Id = id;
}

void EntityBase::setPosition(float l_x, float l_y) {
	m_Pos = sf::Vector2f(l_x, l_y);
	this->m_AnimatedSprite.setPosition(m_Pos);
	UpdateAABB();
}

void EntityBase::setPosition(const sf::Vector2f& l_pos) {
	m_Pos = l_pos;
	this->m_AnimatedSprite.setPosition(m_Pos);
	UpdateAABB();
}

void EntityBase::setSize(float l_x, float l_y) {
	m_Size = sf::Vector2f(l_x, l_y);
	UpdateAABB();
}

void EntityBase::setAcceleration(float l_x, float l_y) {
	m_Acceleration = sf::Vector2f(l_x, l_y);
}

void EntityBase::setState(const EntityState& l_state) {
	if (m_enState == EntityState::Dying) { return; }
	m_enState = l_state;
}

const sf::Vector2f& EntityBase::getSize()const { return m_Size; }
std::string EntityBase::getName()const { return m_Name; }
EntityState EntityBase::getState()const { return m_enState; }
unsigned int EntityBase::getId()const { return m_Id; }
EntityType EntityBase::getType()const { return m_enType; }
const sf::Vector2f& EntityBase::getPosition()const { return m_Pos; }

void EntityBase::move(float l_x, float l_y) {
	m_oldPos = m_Pos;
	m_Pos += sf::Vector2f(l_x, l_y);
	sf::Vector2u mapSize = { 64,18 };
	if (m_Pos.x < 0) {
		m_Pos.x = 0;
	}
	else if (m_Pos.x > (mapSize.x + 1) * 8) {
		m_Pos.x = (mapSize.x + 1) * 8;
	}

	if (m_Pos.y < 0) {
		m_Pos.y = 0;
	}
	else if (m_Pos.y > (mapSize.y + 1) * 8) {
		m_Pos.y = (mapSize.y + 1) * 8;
		//setState(EntityState::Dying);
	}

	UpdateAABB();
}

void EntityBase::addVelocity(float l_x, float l_y) {
	m_Velocity += sf::Vector2f(l_x, l_y);
	if (abs(m_Velocity.x) > m_maxVelocity.x) {
		if (m_Velocity.x < 0) { m_Velocity.x = -m_maxVelocity.x; }
		else { m_Velocity.x = m_maxVelocity.x; }
	}

	if (abs(m_Velocity.y) > m_maxVelocity.y) {
		if (m_Velocity.y < 0) { m_Velocity.y = -m_maxVelocity.y; }
		else { m_Velocity.y = m_maxVelocity.y; }
	}
}

void EntityBase::accelerate(float l_x, float l_y) {
	m_Acceleration += sf::Vector2f(l_x, l_y);
}

void EntityBase::applyFriction(float l_x, float l_y) {
	if (m_Velocity.x != 0) {
		if (abs(m_Velocity.x) - abs(l_x) < 0) { m_Velocity.x = 0; }
		else {
			if (m_Velocity.x < 0) { m_Velocity.x += l_x; }
			else { m_Velocity.x -= l_x; }
		}
	}

	if (m_Velocity.y != 0) {
		if (abs(m_Velocity.y) - abs(l_y) < 0) { m_Velocity.y = 0; }
		else {
			if (m_Velocity.y < 0) { m_Velocity.y += l_y; }
			else { m_Velocity.y -= l_y; }
		}
	}
}

void EntityBase::UpdateAABB() {
	m_AABB = sf::FloatRect(m_Pos.x - (m_Size.x / 2), m_Pos.y - m_Size.y, m_Size.x, m_Size.y);
}

void EntityBase::CheckCollisions()
{
	Level* gameLevel = m_entityManager->getData();
	unsigned int tileSize = gameLevel->m_TileSize;
	int fromX = floor(m_AABB.left / tileSize);
	int toX = floor((m_AABB.left + m_AABB.width) / tileSize);
	int fromY = floor(m_AABB.top / tileSize);
	int toY = floor((m_AABB.top + m_AABB.height) / tileSize);

	for (int x = fromX; x <= toX; ++x) {
		for (int y = fromY; y <= toY; ++y) {
			Tile* tile = &gameLevel->GetTile(x, y);
			if (!tile) { continue; }
			std::cout << "Tile x: " << tile->m_TilePos.x  << " y: " << tile->m_TilePos.y << std::endl;
			sf::FloatRect tileBounds(x * tileSize, y * tileSize, tileSize, tileSize);
			sf::FloatRect intersection;
			m_AABB.intersects(tileBounds, intersection);
			float area = intersection.width * intersection.height;

			CollisionElement e(area, tile->isSolid, tileBounds);
			m_collisions.emplace_back(e);
		}
	}
}

void EntityBase::ResolveCollisions()
{
	if (!m_collisions.empty()) {
		std::sort(m_collisions.begin(), m_collisions.end(), SortCollisions);
		Level* gameMap = m_entityManager->getData();
		unsigned int tileSize = gameMap->m_TileSize;
		for (auto &itr : m_collisions) {
			if (!m_AABB.intersects(itr.m_tileBounds)) { continue; }
			//// Debug
			//if (m_entityManager->GetContext()->m_debugOverlay.Debug()) {
			//	sf::Vector2f tempPos(itr.m_tileBounds.left, itr.m_tileBounds.top);
			//	sf::RectangleShape* rect = new sf::RectangleShape(sf::Vector2f(tileSize, tileSize));
			//	rect->setPosition(tempPos);
			//	rect->setFillColor(sf::Color(255, 255, 0, 150));
			//	m_entityManager->GetContext()->m_debugOverlay.Add(rect);
			//}
			//// End debug.
			float xDiff = (m_AABB.left + (m_AABB.width / 2)) - (itr.m_tileBounds.left + (itr.m_tileBounds.width / 2));
			float yDiff = (m_AABB.top + (m_AABB.height / 2)) - (itr.m_tileBounds.top + (itr.m_tileBounds.height / 2));
			float resolve = 0;
			if (abs(xDiff) > abs(yDiff)) {
				if (xDiff > 0) {
					resolve = (itr.m_tileBounds.left + tileSize) - m_AABB.left;
				}
				else {
					resolve = -((m_AABB.left + m_AABB.width) - itr.m_tileBounds.left);
				}
				move(resolve, 0);
				m_Velocity.x = 0;
				m_collidingOnX = true;
			}
			else {
				if (yDiff > 0) {
					resolve = (itr.m_tileBounds.top + tileSize) - m_AABB.top;
				}
				else {
					resolve = -((m_AABB.top + m_AABB.height) - itr.m_tileBounds.top);
				}
				move(0, resolve);
				m_Velocity.y = 0;
				if (m_collidingOnY) { continue; }
				m_referenceTile = itr.m_tile;
				m_collidingOnY = true;
			}
		}
		m_collisions.clear();
	}
	if (!m_collidingOnY) { m_referenceTile = nullptr; }
}

std::string EntityBase::stateToString()
{
	switch (this->m_enState)
	{
	case EntityState::Jumping: return "Jumping";
	case EntityState::Attacking: return "Attacking";
	}
}

void EntityBase::draw(sf::RenderWindow & window, float dt)
{
	window.draw(this->m_AnimatedSprite);
	return;
}

void EntityBase::update(const float dt)
{
	Level* gameLevel = m_entityManager->getData();
	float gravity = 2.0f;
	accelerate(0, gravity);
	addVelocity(m_Acceleration.x * dt, m_Acceleration.y * dt);
	setAcceleration(0.0f, 0.0f);
	sf::Vector2f frictionValue;
	if (m_referenceTile) {
		frictionValue = m_referenceTile->m_friction;
		if (m_referenceTile->m_deadly) { setState(EntityState::Dying); }
	}
	else if (gameLevel->GetDefaultTile()) {

	}
	else {
		frictionValue = m_friction;
	}
	float friction_x = (m_Speed.x * 0.8f) * dt;
	float friction_y = (m_Speed.y * 0.0f) * dt;
	applyFriction(friction_x, friction_y);
	sf::Vector2f deltaPos = m_Velocity * dt;
	move(deltaPos.x, deltaPos.y);
	m_AnimatedSprite.move(deltaPos);
	m_AnimatedSprite.update(sf::seconds(dt));
	m_collidingOnX = false;
	m_collidingOnY = false;
	CheckCollisions();
	ResolveCollisions();
}
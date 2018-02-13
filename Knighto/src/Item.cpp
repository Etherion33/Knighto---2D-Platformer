#include "../include/Item.h"

Item::Item(Entity_Manager * entmgr, ItemType itemType, const sf::Texture& spritesheet) : EntityBase(entmgr)
{
	this->m_enType = EntityType::Item;

	m_isCollected = false;
	m_Animations["idle_item"].setSpriteSheet(spritesheet);
	m_Animations["idle_item"].addFrame(sf::IntRect(0, 0, 32, 32));
	m_Animations["idle_item"].addFrame(sf::IntRect(32, 0, 32, 32));
	m_Animations["idle_item"].addFrame(sf::IntRect(64, 0, 32, 32));
	m_Animations["idle_item"].addFrame(sf::IntRect(96, 0, 32, 32));

	this->m_itemType = itemType;

	switch (itemType)
	{
		case ItemType::COIN:{
			this->m_Name = "Coin";
			this->setSize(5, 5);
			break;
		}
		case ItemType::WEAPON: {
			this->m_Name = "Weapon";
			this->setSize(5, 5);
			break;
		}
		case ItemType::POTION: {
			this->m_Name = "Potion";
			this->setSize(5, 5);
			break;
		}
	default:
		break;
	}

	currentAnimation = m_Animations["idle_item"];
	this->m_enState = EntityState::Idle;
	this->m_AnimatedSprite = AnimatedSprite(sf::seconds(0.3), true, false);
	this->m_AnimatedSprite.setPosition(m_Pos);
}

Item::~Item()
{

}

void Item::draw(sf::RenderWindow & window, float dt)
{
	if (this->m_isCollected == false)
	{
		window.draw(this->m_AnimatedSprite);
	}
}

void Item::update(const float dt)
{
	EntityBase::update(dt);
	m_AnimatedSprite.play(currentAnimation);
	m_AnimatedSprite.setPosition(m_Pos);
	m_AnimatedSprite.update(sf::seconds(dt));
}

void Item::OnEntityCollision(EntityBase * eb_collider, bool b_attack)
{
	if (m_enState == EntityState::Dying) { return; }
	if (b_attack) { return; }
	if (eb_collider->getType() != EntityType::Player) { return; }
	Character* player = (Character*)eb_collider;
	if (this->m_itemType == ItemType::COIN)
	{
		player->setScore(5);
		this->m_isCollected = true;
	}
	else if (this->m_itemType == ItemType::POTION)
	{
		player->resetHP();
		this->m_isCollected = true;
	}
	else if (this->m_itemType == ItemType::WEAPON)
	{
		player->m_isEquipped = true;
		this->m_isCollected = true;
	}
	setState(EntityState::Dying);
}
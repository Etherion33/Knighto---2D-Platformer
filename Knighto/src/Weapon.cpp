#include "../include/Weapon.h"

Weapon::Weapon(Entity_Manager * entmgr, WeaponType wepType) : Item(entmgr)
{
	m_wepType = wepType;
	switch (m_wepType)
	{
	default:
	case WeaponType::FISTS:
		m_Name = "Fists of Fury";
		break;
	case WeaponType::SWORD:
		m_Name = "Sword of Light";
		break;
	case WeaponType::BAZOOKA:
		m_Name = "World Traumatizer";
		break;
	}
}

void Weapon::update(float dt)
{
}

void Weapon::draw(sf::RenderWindow & window, float dt)
{
}

Weapon::~Weapon()
{
}
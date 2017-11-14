#pragma once
#include "../include/Item.h"

enum class WeaponType{ FISTS, SWORD, BAZOOKA };


class Weapon :
	public Item
{
private:
	WeaponType m_wepType;
public:
	Weapon(WeaponType wepType);


	void update(float dt);
	void draw(sf::RenderWindow & window, float dt);
	~Weapon();
};


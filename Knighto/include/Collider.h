#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& rect);
	~Collider();

	void Move(float dx, float dy) { rect.move(dx, dy); }

	bool Collider::CheckCollision(Collider& other, float push);
	sf::Vector2f GetPosition() { return rect.getPosition(); }
	sf::Vector2f GetHalfSize() { return rect.getSize() / 2.0f; }

private:
	sf::RectangleShape& rect;
};

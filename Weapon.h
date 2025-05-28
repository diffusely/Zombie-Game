#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "Bullet.h"
#include "Defines.h"

class Weapon
{
public:

	Weapon(float speed);
	Weapon();

	void shoot(const sf::Vector2f& position, float rotationDegrees);
	void update(const float &dt, const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

private:

	std::vector<std::unique_ptr<Bullet>> bullets;
	float bullet_speed;
};


#pragma once

#include "Defines.h"
#include "Collider.h"

#include <SFML/Graphics.hpp>

#include <vector>

class Enemy
{
public:

	Enemy(sf::Vector2f pos);
	virtual ~Enemy();

	void move(const float& dt, sf::Vector2f);

	void update(const float& dt, sf::Vector2f pos);
	void draw(sf::RenderWindow* window);

	Collider& getCollider() { return collider; }

	float getHelath() const { return health; }

	bool isDead() { return health <= 0 ? true : false; }

	void takeDamage(float damage) { health -= damage; }

private:

	float speed = 50.f;
	sf::Texture texture;
	sf::Sprite enemy;

	Collider collider;
	float health;

private:

	void initSprite(sf::Vector2f pos);
};


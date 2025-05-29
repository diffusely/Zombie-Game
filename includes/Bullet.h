#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Bullet
{
public:

	Bullet(sf::Vector2f pos, sf::Vector2f vel);
	~Bullet();

	void update(const float& dt);
	bool isOffScreen(const sf::RenderWindow* window) const;
	void draw(sf::RenderWindow* window);
	
	Collider& getCollider() { return collider; };
	float getDamage() const { return damage; };

	void markForDeletion() { deleted = true; }
	bool shouldBeDeleted() const { return deleted; }

private:
	bool deleted = false;
	sf::Texture texture;
	//sf::Sprite bullet;

	sf::Vector2f velocty;
	sf::CircleShape bullet;

	Collider collider;
	float damage;

private:

	void initBullet();
};


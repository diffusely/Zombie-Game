#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:

	Bullet(sf::Vector2f pos, sf::Vector2f vel);
	~Bullet();

	void update(const float& dt);
	bool isOffScreen(const sf::RenderWindow& window) const;
	void draw(sf::RenderWindow& window);

private:
	sf::Texture texture;
	sf::Sprite bullet;

	sf::Vector2f velocty;
	sf::CircleShape bullet;


private:

	void initBullet();
};


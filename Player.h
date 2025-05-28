#pragma once

#include <SFML/Graphics.hpp>

#include "Weapon.h"
#include "Collider.h"

#include <exception>
#include <iostream>
#include <cmath>


class Player
{
public:

	Player(float speed);
	Player();
	~Player();


	void move(const float& dt);
	void update(const float& dt, const sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);
	void shoot();
	void aimDir(const sf::Vector2f& mouseWorldPos);

	

	// Get
	Collider& getCollider() { return collider; }
	Weapon& getWeapon() { return *weapon.get(); };
	sf::Vector2f getPos() const { return player.getPosition(); };
	
private:

	float player_speed;

	sf::Texture texture;
	sf::Sprite player;

	Collider collider;

	std::unique_ptr<Weapon> weapon;

private:
	void initSprite();

};


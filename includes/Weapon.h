#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <cmath>
#include <iostream>

#include "Bullet.h"
#include "Defines.h"

enum WeaponType {PISTOL, KNIF, SHOTGUN};

class Weapon
{
public:

	Weapon(float speed, float cooldown);
	Weapon();

	void shoot(const sf::Vector2f& position, float rotationDegrees, float angle);
	void update(const float &dt, const sf::RenderWindow* window);
	void draw(sf::RenderWindow* window);

	bool canFire();


	// Get
	std::vector<std::unique_ptr<Bullet>>& getBullets() { return bullets; };

private:

	void initSound();

private:

	std::vector<std::unique_ptr<Bullet>> bullets;
	WeaponType type{};
	float bullet_speed;

private:
	// Time
	sf::Clock fire_clock{};
	float fire_cooldown;

private:
	// Sound
	sf::SoundBuffer shoot_buffer;
	sf::Sound shoot_sound;

};


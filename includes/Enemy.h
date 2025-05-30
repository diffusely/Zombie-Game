#pragma once

#include "Defines.h"
#include "Collider.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Enemy
{
public:

	Enemy(sf::Vector2f pos);
	virtual ~Enemy();

	void move(const float& dt, sf::Vector2f);


	void updateAnimation(const float &dt);

	void update(const float& dt, sf::Vector2f pos);
	void draw(sf::RenderWindow* window);

	Collider& getCollider() { return collider; }

	float getHelath() const { return health; }

	bool isDead();

	void takeDamage(float damage) { health -= damage; }

private:

	float speed = 50.f;
	sf::Texture texture;
	sf::Sprite enemy;

	Collider collider;
	float health;

private:

	// Animation

	int currentFrame;
    float frameTime;
    float frameTimer;
    sf::Vector2i frameSize;
    int totalFrames;


private:

	// Sound
	sf::SoundBuffer dead_buffer;
	sf::Sound dead_sound;

	bool dead = false;
	sf::Clock deathClock;
	bool deathSoundPlayed = false;


private:

	void initSprite(sf::Vector2f pos);
	void initSound();


};


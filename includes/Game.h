#pragma once

#include "Player.h"
#include "Enemy.h"


#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <cmath>
#include <vector>


class Game
{
public:

	Game(int width, int height, std::string name);
	~Game();


	void run();
	

private:

	void update();
	void render();

	void updateEvent();
	void updateDeltaTime();
	void updateMousePos();


	void updateEnemies();
	void updatePlayer();
	void updateView();


	void checkCollison();



private:

	void initBackgorund();
	void initSound();

private:

	int width;
	int height;

	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Enemy>> enemies;

private:
	// Time
	sf::Clock clock{};
	float dt{};

private:
	// Mouse
	sf::Vector2i mouse_pixel_pos{};
	sf::Vector2f mouse_world_pos{};

private:
	// View
	sf::View view;

private:
	// Background
	sf::Texture background_texture;
	sf::Sprite background_sprite;

private:
	// Sound
	sf::SoundBuffer fight_buffer;
	sf::Sound fight_sound;

};


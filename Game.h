#pragma once

#include "Player.h"

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

private:

	int width;
	int height;

	std::unique_ptr<sf::RenderWindow> window;

	std::unique_ptr<Player> player;

private:
	// Time

};


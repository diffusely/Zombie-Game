#include "Game.h"

Game::Game(int width, int height, std::string name)
	: width(width)
	, height(height)
	, window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), name))
	, player(std::make_unique<Player>(200))
{

}

void Game::update()
{
	updateEvent();
	player->move(dt);
	player->update(dt,);
}

void Game::render()
{
	window->clear();


	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}

Game::~Game()
{

}

void Game::updateEvent()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

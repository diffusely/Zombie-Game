#include "Game.h"

Game::Game(int width, int height, std::string name)
	: width(width)
	, height(height)
	, window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), name))
	, player(std::make_unique<Player>(200.f))
{
	enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(100.f, 100.f)));
	enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(140.f, 140.f)));
	enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(300.f, 140.f)));
	enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(800.f, 140.f)));
	enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(200.f, 800.f)));
	enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(300.f, 900.f)));
}

void Game::update()
{
	updateEvent();
	updateDeltaTime();
	updateMousePos();

	checkCollison();

	if (!enemies.empty())
	{
		for (auto &it : enemies)
		{
			if (!player->getCollider().intersects(it->getCollider()))
				it->move(dt, player.get()->getPos());
		}
	}

	if (!enemies.empty())
	{
		for (auto& it : enemies)
		{
			it->update(dt, player.get()->getPos());
		}
	}

	player->aimDir(mouse_world_pos);
	player->move(dt);
	player->update(dt, window.get());
}

void Game::render()
{
	window->clear();

	player->draw(window.get());
	if (!enemies.empty())
	{
		for (auto &it : enemies)
			it->draw(window.get());
	}
		
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

void Game::updateDeltaTime()
{
	dt = clock.restart().asSeconds();
	//std::cout << dt << "\n";
}

void Game::updateMousePos()
{
	mouse_pixel_pos = sf::Mouse::getPosition(*window.get());
	mouse_world_pos = window.get()->mapPixelToCoords(mouse_pixel_pos);
}

void Game::checkCollison()
{
	if (enemies.empty())
		return;

	// Проверка столкновения игрока и врагов
	for (auto& enemy : enemies)
	{
		if (player->getCollider().intersects(enemy->getCollider()))
		{
			enemy->getCollider().setColor(sf::Color::Red);
			player->getCollider().setColor(sf::Color::Red);
		}
		else
		{
			enemy->getCollider().setColor(sf::Color::Blue);
			player->getCollider().setColor(sf::Color::Blue);
		}
	}

	// Урон по врагам от пуль
	auto& bullets = player->getWeapon().getBullets();
	for (auto& bullet : bullets)
	{
		for (auto& enemy : enemies)
		{
			if (bullet->getCollider().intersects(enemy->getCollider()))
			{
				enemy->takeDamage(bullet->getDamage());
				bullet->markForDeletion();
				break;
			}
		}
	}

	// Удаление пуль
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](const std::unique_ptr<Bullet>& bullet) {
			return bullet->shouldBeDeleted();
		}), bullets.end());

	// Удаление врагов
	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](const std::unique_ptr<Enemy>& enemy) {
			return enemy->isDead();
		}), enemies.end());
}

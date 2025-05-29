#include "Game.h"

Game::Game(int width, int height, std::string name)
	: width(width)
	, height(height)
	, window(std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), name))
	, player(std::make_unique<Player>(200.f))
	, view(sf::FloatRect(0.f, 0.f, 1200.f, 800.f))
{
	initBackgorund();
	initSound();


	view.setCenter(player.get()->getPos());
	//view.zoom(1.5f);
	//enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(100.f, 100.f)));
	//enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(140.f, 140.f)));
	//enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(300.f, 140.f)));
	//enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(800.f, 140.f)));
	//enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(200.f, 800.f)));
	//enemies.push_back(std::make_unique<Enemy>(sf::Vector2f(300.f, 900.f)));
}

void Game::update()
{
	updateEvent();
	updateDeltaTime();
	updateMousePos();

	checkCollison();

	updateEnemies();
	updatePlayer();

	updateView();

}

void Game::render()
{
	window->clear();

	window->draw(background_sprite);

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

void Game::updateEnemies()
{
	if (!enemies.empty())
	{
		for (auto& it : enemies)
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
}

void Game::updatePlayer()
{
	player->aimDir(mouse_world_pos);
	player->move(dt);
	player->update(dt, window.get());

}

void Game::updateView()
{
	sf::Vector2f playerPos = player->getPos();

	sf::Vector2f vs = view.getSize();
	float halfW = vs.x / 2.f;
	float halfH = vs.y / 2.f;

	sf::FloatRect bg = background_sprite.getGlobalBounds();
	float bgW = bg.width;
	float bgH = bg.height;


	float minX = halfW;
	float minY = halfH;
	float maxX = bgW - halfW;
	float maxY = bgH - halfH;

	float camX = std::clamp(playerPos.x, minX, maxX);
	float camY = std::clamp(playerPos.y, minY, maxY);

	view.setCenter(camX, camY);
	window->setView(view);
}

void Game::checkCollison()
{
	if (enemies.empty())
		return;

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

	bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
		[](const std::unique_ptr<Bullet>& bullet) {
			return bullet->shouldBeDeleted();
		}), bullets.end());

	enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
		[](const std::unique_ptr<Enemy>& enemy) {
			return enemy->isDead();
		}), enemies.end());
}

void Game::initBackgorund()
{
	if (!background_texture.loadFromFile("assets/Map1.jpg"))
	{
		throw std::runtime_error("background Map error!");
	}

	this->background_sprite.setTexture(background_texture);
	background_sprite.setScale(1.5f, 1.5f);
	//background_sprite.setOrigin(0.f, 0.f);
	background_sprite.setPosition(0.f, 0.f);

}

void Game::initSound()
{
	if (!fight_buffer.loadFromFile("audio/music/fight1.wav"))
	{
		throw std::runtime_error("Fight sound error!");
	}

	fight_sound.setBuffer(fight_buffer);
	fight_sound.setVolume(60.f);
	fight_sound.setLoop(true);
	fight_sound.play();
}

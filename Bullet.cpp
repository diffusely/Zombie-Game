#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel)
	: velocty(vel)
{
    bullet.setRadius(5);
    bullet.setFillColor(sf::Color::Yellow);
    bullet.setOrigin(5, 5);
    bullet.setPosition(pos);
}

Bullet::~Bullet()
{

}

void Bullet::update(const float& dt)
{
    bullet.move(velocty * dt);
}

bool Bullet::isOffScreen(const sf::RenderWindow& window) const
{
    sf::Vector2f pos = bullet.getPosition();
    return (pos.x < 0 || pos.y < 0 
        || pos.x > window.getSize().x 
        || pos.y > window.getSize().y);
}

void Bullet::draw(sf::RenderWindow& window)
{
    window.draw(bullet);
}

void Bullet::initBullet()
{

}

#include "Enemy.h"



Enemy::Enemy(sf::Vector2f pos)
    : collider(sf::Vector2f(100,100), sf::Vector2f(80, 40))
    , health(100.f)
{
    initSprite(pos);
}

Enemy::~Enemy()
{

}

void Enemy::move(const float& dt, sf::Vector2f pos)
{
    sf::Vector2f direction = pos - enemy.getPosition();

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0)
    {
        direction /= length;
        enemy.move(direction * speed * dt);
    }
}


void Enemy::update(const float& dt, sf::Vector2f pos)
{
    collider.setPos(enemy.getPosition());
    sf::Vector2f direction = pos - enemy.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180.f / PI - 90;

    collider.setAngle(angle);
    enemy.setRotation(angle);
}

void Enemy::draw(sf::RenderWindow *window)
{

    window->draw(enemy);
    collider.draw(window);
}

void Enemy::initSprite(sf::Vector2f pos)
{
    if (!this->texture.loadFromFile("assets/enemy.png"))
    {
        throw std::runtime_error("Enemy asset error!");
    }

    enemy.setTexture(texture);
    enemy.setTextureRect(sf::IntRect(55, 95, 185, 160));
    enemy.setOrigin(92, 80);
    enemy.setPosition(pos);
    enemy.setScale(0.5f, 0.5f);
}

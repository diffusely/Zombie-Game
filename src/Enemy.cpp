#include "Enemy.h"



Enemy::Enemy(sf::Vector2f pos)
    : collider(sf::Vector2f(100,100), sf::Vector2f(80, 40))
    , health(100.f)
{
    initSprite(pos);
    initSound();
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

    if (health <= 0) return;

    window->draw(enemy);
    collider.draw(window);
}

bool Enemy::isDead()
{
    if (health <= 0)
    {
        if (!deathSoundPlayed)
        {
            dead_sound.play();
            deathClock.restart();
            deathSoundPlayed = true;
        }

        return deathClock.getElapsedTime().asSeconds() > 0.5f;
    }

    return false;
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

void Enemy::initSound()
{
    if (!dead_buffer.loadFromFile("audio/zombie/dead.wav"))
    {
        throw std::runtime_error("Zombie sound error!");
    }

    dead_sound.setBuffer(dead_buffer);
    dead_sound.setVolume(100.f);
}

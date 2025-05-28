#include "Weapon.h"

Weapon::Weapon(float speed)
    : bullet_speed(speed)
{

}

Weapon::Weapon()
    : bullet_speed(500)
{

}

void Weapon::shoot(const sf::Vector2f& position, float rotationDegrees)
{
    float angleRad = rotationDegrees * PI / 180.0f;
    sf::Vector2f velocity(std::cos(angleRad) * bullet_speed, std::sin(angleRad) * bullet_speed);
    bullets.push_back(std::make_unique<Bullet>(position, velocity));
}

void Weapon::update(const float &dt, const sf::RenderWindow& window)
{
    for (auto& b : bullets)
        b->update(dt);

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [&](const std::unique_ptr<Bullet>& b) { return b->isOffScreen(window); }),
        bullets.end());
}

void Weapon::draw(sf::RenderWindow& window)
{
    for (auto& b : bullets)
        b->draw(window);
}

#include "Weapon.h"

Weapon::Weapon(float speed, float cooldown)
    : bullet_speed(speed)
    , fire_cooldown(cooldown)
{

}

Weapon::Weapon()
    : bullet_speed(500)
    , fire_cooldown(0.3f)
{

}

void Weapon::shoot(const sf::Vector2f& position, float rotationDegrees)
{
    fire_clock.restart();
    float angleRad = (rotationDegrees + 100) * PI / 180.0f;
    sf::Vector2f velocity(std::cos(angleRad) * bullet_speed, std::sin(angleRad) * bullet_speed);
    bullets.push_back(std::make_unique<Bullet>(position, velocity));
}

void Weapon::update(const float &dt, const sf::RenderWindow* window)
{
    for (auto& b : bullets)
        b->update(dt);

    for (auto& b : bullets)
        std::cout << "q";
    std::cout << "\n";
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [&](const std::unique_ptr<Bullet>& b) { return b->isOffScreen(window); }),
        bullets.end());
}

void Weapon::draw(sf::RenderWindow* window)
{
    for (auto& b : bullets)
        b->draw(window);
}

bool Weapon::canFire()
{
    return fire_clock.getElapsedTime().asSeconds() >= fire_cooldown;
}

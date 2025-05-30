#include "Bullet.h"

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, float angle)
    : velocty(vel)
    , collider(pos, 5.f)
    , damage(25.f)
{
    //bullet.setRadius(5);
    //bullet.setFillColor(sf::Color::Yellow);
    bullet.setOrigin(20, 5);
    sf::Vector2f temp = pos;
    bullet.setPosition(temp);
    if (!texture.loadFromFile("assets/weapon/fire.png"))
    {
        throw std::runtime_error("Fire.png load error!");
    }

    bullet.setTexture(texture);
    bullet.setTextureRect(sf::IntRect(400, 200, 20, 25));
    bullet.setRotation(angle);
    //bullet.setScale(0.5f, 0.5f);
}

Bullet::~Bullet()
{

}

void Bullet::update(const float& dt)
{
    collider.setPos(bullet.getPosition());
    bullet.move(velocty * dt);
}

bool Bullet::isOffScreen(const sf::RenderWindow* window) const
{
    const sf::View& view = window->getView();
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    float left = center.x - size.x / 2.f;
    float right = center.x + size.x / 2.f;
    float top = center.y - size.y / 2.f;
    float bottom = center.y + size.y / 2.f;

    sf::Vector2f pos = bullet.getPosition();

    return (pos.x < left || pos.x > right || pos.y < top || pos.y > bottom);
}

void Bullet::draw(sf::RenderWindow* window)
{
    window->draw(bullet);
    collider.draw(window);
}

void Bullet::initBullet()
{
        if (!texture.loadFromFile("assets/weapon/fire.png"))
    {
        throw std::runtime_error("Fire.png load error!");
    }

    bullet.setTexture(texture);

}

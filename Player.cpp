#include "Player.h"

Player::Player(float speed)
    : player_speed(speed)
    , weapon(std::make_unique<Weapon>(1000.f, 0.1f))
    , collider(sf::Vector2f(400.f, 300.f), 35)
{
    initSprite();
}

Player::Player()
    : Player(200)
{
}

Player::~Player()
{

}

void Player::move(const float &dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player.move(0, -player_speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        player.move(0, player_speed * dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player.move(-player_speed * dt, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player.move(player_speed * dt, 0);
}

void Player::update(const float& dt, const sf::RenderWindow* window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && weapon->canFire())
        shoot();
    weapon->update(dt, window);
    collider.setPos(player.getPosition());
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(player);
    collider.draw(window);
    weapon->draw(window);
}

void Player::shoot()
{
    float angleRad = (player.getRotation() + 120) * PI / 180.0f;

    sf::Vector2f muzzleOffset(std::cos(angleRad) * 45,
        std::sin(angleRad) * 45);
    sf::Vector2f bulletPos = player.getPosition() + muzzleOffset;
    weapon->shoot(bulletPos, player.getRotation());
}

void Player::aimDir(const sf::Vector2f& mouseWorldPos)
{
    sf::Vector2f pos = player.getPosition();
    float dx = mouseWorldPos.x - pos.x;
    float dy = mouseWorldPos.y - pos.y;

    float angle = std::atan2(dy, dx) * 180.0f / PI - 105;
    player.setRotation(angle);
}


void Player::initSprite()
{
    if (!this->texture.loadFromFile("assets/player.png"))
    {
        throw std::runtime_error("Player asset error!");
    }

    player.setTexture(texture);
    player.setTextureRect(sf::IntRect(50, 163, 115, 150));
    player.setOrigin(65, 75);
    player.setPosition(400, 300);
    player.setRotation(160);
    player.setScale(0.5f, 0.5f);
}

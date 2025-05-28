#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

struct Bullet {
    sf::CircleShape shape;
    sf::Vector2f velocity;

    void update(float dt) {
        shape.move(velocity * dt);
    }

    bool isOffscreen(const sf::RenderWindow& window) const {
        sf::Vector2f pos = shape.getPosition();
        return (pos.x < 0 || pos.y < 0 || pos.x > window.getSize().x || pos.y > window.getSize().y);
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Move and Rotate Sprite");
    window.setFramerateLimit(60);

    sf::Texture texture;
    if (!texture.loadFromFile("assets/q.png")) {
        std::cerr << "Failed to load texture\n";
        return -1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(50, 163, 115, 150));
    sprite.setOrigin(65, 75); // center
    sprite.setPosition(400, 300);
    sprite.setRotation(160);

    const float playerSpeed = 200.0f;
    const float bulletSpeed = 500.0f;
    sf::Clock clock;

    std::vector<Bullet> bullets;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();

        // --- Player Movement ---
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            sprite.move(0, -playerSpeed * dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            sprite.move(0, playerSpeed * dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            sprite.move(-playerSpeed * dt, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            sprite.move(playerSpeed * dt, 0);

        // --- Rotation toward Mouse ---
        sf::Vector2f spritePos = sprite.getPosition();
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

        float dx = mouseWorldPos.x - spritePos.x - 30;
        float dy = mouseWorldPos.y - spritePos.y + 10;
        float angle = std::atan2(dy, dx) * 180 / 3.14159265f - 100;
        sprite.setRotation(angle);

        // --- Fire Bullet ---
        static bool wasPressed = false;
        bool isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (isPressed && !wasPressed) {
            float angleRad = (sprite.getRotation() + 100) * 3.14159265f / 180.0f;

            float barrelLength = 80.0f; // distance from origin to barrel
            sf::Vector2f offset(std::cos(angleRad) * barrelLength,
                std::sin(angleRad) * barrelLength);
            sf::Vector2f bulletPos = spritePos + offset;
            bulletPos.x += 30;
            bulletPos.y -= 10;
            sf::Vector2f bulletVel(std::cos(angleRad) * bulletSpeed,
                std::sin(angleRad) * bulletSpeed);

            Bullet b;
            b.shape = sf::CircleShape(5);
            b.shape.setFillColor(sf::Color::Yellow);
            b.shape.setOrigin(5, 5);
            b.shape.setPosition(bulletPos);
            b.velocity = bulletVel;

            bullets.push_back(b);
        }
        wasPressed = isPressed;

        // --- Update Bullets ---
        for (auto& b : bullets) {
            b.update(dt);
        }

        // --- Remove Offscreen Bullets ---
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [&](const Bullet& b) { return b.isOffscreen(window); }),
            bullets.end());

        // --- Draw Everything ---
        sf::CircleShape crosshair(3);
        crosshair.setFillColor(sf::Color::Red);
        crosshair.setOrigin(3, 3);
        crosshair.setPosition(mouseWorldPos);

        window.clear();
        window.draw(sprite);
        for (auto& b : bullets)
            window.draw(b.shape);
        window.draw(crosshair);
        window.display();
    }

    return 0;
}

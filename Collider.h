#pragma once

#include <SFML/Graphics.hpp>
#include <variant>
#include <cmath>

class Collider
{
public:
	enum class Type {Circle, Rectangle};


    Collider(sf::Vector2f pos, sf::Vector2f size);
    Collider(sf::Vector2f pos, float radius);

    bool intersects(const Collider& other) const;
    void draw(sf::RenderWindow* window) const;

    Type getType() const;
    sf::Vector2f getPos() const;
    void setPos(const sf::Vector2f& newPos);

    sf::FloatRect getBounds() const;

    void setColor(sf::Color color);

private:
    Type type;
    sf::Vector2f pos;
    std::variant<sf::CircleShape, sf::RectangleShape> collision;
};


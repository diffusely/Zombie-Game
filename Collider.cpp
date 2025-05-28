#include "Collider.h"

Collider::Collider(sf::Vector2f pos, sf::Vector2f size)
	: type(Type::Rectangle)
	, pos(pos)
{
	sf::RectangleShape rec(size);
	rec.setPosition(pos);
	rec.setFillColor(sf::Color::Transparent);
	rec.setOutlineThickness(1.f);
	rec.setOutlineColor(sf::Color::Green);
	collision = sf::RectangleShape(size);
}



Collider::Collider(sf::Vector2f pos, float radius)
	: type(Type::Circle)
	, pos(pos)
{
	sf::CircleShape circle(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(pos);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Blue);
	circle.setOutlineThickness(1);
	collision = circle;
}

Collider::Type Collider::getType() const
{
	return type;
}

sf::Vector2f Collider::getPos() const
{
	return pos;
}

bool Collider::intersects(const Collider& other) const
{
	if (type == Type::Rectangle && other.type == Type::Rectangle)
	{
		auto a = std::get<sf::RectangleShape>(collision).getGlobalBounds();
		auto b = std::get<sf::RectangleShape>(other.collision).getGlobalBounds();
		return a.intersects(b);
	}
	if (type == Type::Circle && other.type == Type::Circle)
	{
		auto& a = std::get<sf::CircleShape>(collision);
		auto& b = std::get<sf::CircleShape>(other.collision);
		float dist = std::hypot(
			a.getPosition().x - b.getPosition().x,
			a.getPosition().y - b.getPosition().y);
		return dist < (a.getRadius() + b.getRadius());
	}
	return false;
}

void Collider::draw(sf::RenderWindow* window) const
{
	std::visit([&](auto& shape){
		window->draw(shape);
	}, collision);
}

void Collider::setPos(const sf::Vector2f &newPos)
{
	pos = newPos;
	std::visit([&](auto& shape) {
		shape.setPosition(newPos);
	}, collision);
}

sf::FloatRect Collider::getBounds() const
{
	return std::visit([](auto&& shape) -> sf::FloatRect {
		return shape.getGlobalBounds();
	}, collision);
}

void Collider::setColor(sf::Color color)
{
	std::visit([&](auto& shape) {
		shape.setOutlineColor(color);
	}, collision);
}

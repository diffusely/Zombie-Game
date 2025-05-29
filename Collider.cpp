#include "Collider.h"

Collider::Collider(sf::Vector2f pos, sf::Vector2f size)
	: type(Type::Rectangle)
	, pos(pos)
{
	sf::RectangleShape rec(size);
	rec.setOrigin(size.x / 2.f, size.y);
	rec.setPosition(pos);
	rec.setFillColor(sf::Color::Transparent);
	//rec.setOutlineThickness(1.f);
	//rec.setOutlineColor(sf::Color::Green);
	collision = rec;
}



Collider::Collider(sf::Vector2f pos, float radius)
	: type(Type::Circle)
	, pos(pos)
{
	sf::CircleShape circle(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(pos);
	circle.setFillColor(sf::Color::Transparent);
	//circle.setOutlineColor(sf::Color::Blue);
	//circle.setOutlineThickness(1);
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


	if (type == Type::Rectangle && other.type == Type::Circle)
	{
		const auto& rect = std::get<sf::RectangleShape>(collision);
		const auto& circle = std::get<sf::CircleShape>(other.collision);

		sf::Vector2f circleCenter = circle.getPosition();
		float radius = circle.getRadius();

		sf::FloatRect rectBounds = rect.getGlobalBounds();

		float closestX = std::clamp(circleCenter.x, rectBounds.left, rectBounds.left + rectBounds.width);
		float closestY = std::clamp(circleCenter.y, rectBounds.top, rectBounds.top + rectBounds.height);

		float dx = circleCenter.x - closestX;
		float dy = circleCenter.y - closestY;

		return (dx * dx + dy * dy) < (radius * radius);
	}
	else if (type == Type::Circle && other.type == Type::Rectangle)
	{
		return other.intersects(*this);
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

void Collider::setAngle(float angle)
{
	std::visit([&](auto& shape) {
		shape.setRotation(angle);
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

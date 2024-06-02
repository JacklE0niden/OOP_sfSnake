#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// // #include <SFML/include/SFML/Audio.hpp>
#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

// 定义了一个水果类，水果的位置是随机的
Fruit::Fruit(sf::Vector2f position)
{
	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(sf::Color::Red);
}

// 水果的位置是随机的
void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

// 返回水果的位置
sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}
#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 10.f;
const float SnakeNode::Height = 10.f;

//接受一个 sf::Vector2f 类型的参数 position，表示节点的初始位置
SnakeNode::SnakeNode(sf::Vector2f position)
: position_(position)
{
	//设置形状的位置
	shape_.setPosition(position_);
	//设置形状填充颜色
	shape_.setFillColor(sf::Color::Green);
	//设置形状的大小
	shape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));
	//设置轮廓颜色
	shape_.setOutlineColor(sf::Color::White);
	//设置轮廓厚度
	shape_.setOutlineThickness(-1.f);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	shape_.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	shape_.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	shape_.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

//当前节点的中心位置
sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}
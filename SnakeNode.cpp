#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include "SnakeNode.h"

#include<time.h>
#include<random>
#include<iostream>

using namespace sfSnake;
#define Pi 3.1415926
const float radius=5.f;
const float WIDTH=17.321;
static std::default_random_engine random(time(NULL));
static std::uniform_int_distribution colornum(0, 5);

const float SnakeNode::Width = 10.f;
// const float SnakeNode::Height = 10.f;

//接受一个 sf::Vector2f 类型的参数 position，表示节点的初始位置
SnakeNode::SnakeNode(sf::Vector2f position)
    : position_(position), angle_(0.f), timeOffset_(0.f)
{
	cir_shape_.setPosition(position_);
	cir_shape_.setRadius(radius);
	cir_shape_.setFillColor(fillcolor[colornum(random)]);

	//sf::Texture texture;
    // if (!texture.loadFromFile("C:/Users/24398/Desktop/oop/大作业/sfSnake/textures/snakenode.png")) {
    //     std::cerr << "Failed to load texture" << std::endl;
    // }

	rec_shape_.setPosition(sf::Vector2f(position.x+1.34,position.y+1.0*radius/2));
	rec_shape_.setSize(sf::Vector2f(WIDTH,HEIGHT));
	// rec_shape_.setTexture(&texture,true);
	//rec_shape_.setFillColor(fillcolor[colornum(random)]);
}

void SnakeNode::setPosition(sf::Vector2f position)
{
    position_ = position;
    cir_shape_.setPosition(position_);
    rec_shape_.setPosition(sf::Vector2f(position_.x + cos((angle_ + Pi / 2 - atan(radius * (1 - 0.866) / 5))) * 0.5176 * radius,
                                        position_.y + sin((angle_ + Pi / 2 - atan(radius * (1 - 0.866) / 5))) * 0.5176 * radius));
}

// void SnakeNode::setPosition(float x, float y)
// {
// 	position_.x = x;
// 	position_.y = y;
// 	shape_.setPosition(position_);
// }

// void SnakeNode::move(float xOffset, float yOffset)
// {
// 	position_.x += xOffset;
// 	position_.y += yOffset;
// 	shape_.setPosition(position_);
// }

void SnakeNode::update(sf::Time delta)
{
    timeOffset_ += delta.asSeconds();
    float offsetX = 1.f * std::sin(timeOffset_ * 3); // 控制扭动幅度和速度
    float offsetY = 1.f * std::cos(timeOffset_ * 3);
    position_ += sf::Vector2f(offsetX, offsetY);

    // 更新形状的位置
    setPosition(position_);

    // 更新旋转角度
    angle_ += delta.asSeconds() * 180.f / Pi; // 控制旋转速度
}


sf::FloatRect SnakeNode::getBounds() const
{
	return cir_shape_.getGlobalBounds();
}

//当前节点的中心位置
sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	// rec_shape_.setTexture(&texture,true);
	cir_shape_.setRotation(angle_/Pi*180);
	rec_shape_.setRotation(angle_/Pi*180);
	window.draw(cir_shape_);
	window.draw(rec_shape_);
} 
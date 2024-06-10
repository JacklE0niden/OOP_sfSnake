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
// const float WIDTH=17.321;
static std::default_random_engine random(time(NULL));
static std::uniform_int_distribution colornum(0, 5);

const float SnakeNode::Width = 10.f;
// const float SnakeNode::Height = 10.f;
const float SnakeNode::radius = 5.f;
//接受一个 sf::Vector2f 类型的参数 position，表示节点的初始位置
SnakeNode::SnakeNode(sf::Vector2f position)
    : position_(position), angle_(0.f), timeOffset_(0.f)
{
	cir_shape_.setPosition(position_);
	cir_shape_.setRadius(radius);
	// cir_shape_.setFillColor(sf::Color::Transparent); // Set to transparent
    // cir_shape_.setOrigin(radius, radius); // 设置圆心为中心

	// sf::Texture texture;
    if (!texture.loadFromFile("C:/Users/24398/Desktop/oop/大作业/sfSnake/textures/snakenode.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }

	// rec_shape_.setPosition(sf::Vector2f(posit/ion.x+1.34,position.y+1.0*radius/2));
    rec_shape_.setSize(sf::Vector2f(Width, Height));
    rec_shape_.setOrigin(Width / 2, Height / 2);
    // rec_shape_.setFillColor(sf::Color::Transparent);
    // rec_shape_.setTexture(&texture,true);
	// cir_shape_.setTexture(&texture,true);
	//rec_shape_.setFillColor(fillcolor[colornum(random)]);


    // Initialize triangle shape for tail
    tail_shape_.setPointCount(6);
    tail_shape_.setPoint(0, sf::Vector2f(0, 0));
    tail_shape_.setPoint(1, sf::Vector2f(radius * 2, 0));
    tail_shape_.setPoint(2, sf::Vector2f(radius, radius * 2));
    tail_shape_.setOrigin(Width / 2, Height / 2);
    tail_shape_.setTexture(&texture);


	setPosition(position_);

}
void SnakeNode::setPosition(sf::Vector2f position)   
{
	angle_ = 0;
	float dx = position.x - position_.x;
    float dy = position.y - position_.y;
    // Check if there is actual movement to avoid division by zero
    if (dx != 0 || dy != 0) {
        angle_ = std::atan2(dy, dx) * 180 / Pi + 90;
    }


	position_ = position;
	cir_shape_.setPosition(position_);
	rec_shape_.setPosition(position_);
	tail_shape_.setPosition(position_);
	// setAngle(angle_);

    // cir_shape_.setRotation(angle_ - 90); // 调整角度以适应默认方向
    // rec_shape_.setRotation(angle_ - 90);
    tail_shape_.setRotation(angle_);
}
// void SnakeNode::setPosition(sf::Vector2f position) {
//     position_ = position;
//     cir_shape_.setPosition(position_);
//     rec_shape_.setPosition(position_);
//     tail_shape_.setPosition(position_);
// }

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
    // 这里不进行位置和角度的更新，保持原始状态
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

// void SnakeNode::render(sf::RenderWindow& window, bool isHead, bool isTail)
// {
// 	cir_shape_.setTexture(&texture,true);
// 	rec_shape_.setTexture(&texture,true);
// 	if (isHead || isTail) {
//         cir_shape_.setRotation(angle_ / Pi * 180);
//         window.draw(cir_shape_);
// 		// window.draw(rec_shape_);
//     } else {
// 		rec_shape_.setRotation(angle_ / Pi * 180);
// 		window.draw(cir_shape_);
// 		window.draw(rec_shape_);
// 	}
// 	// cir_shape_.setRotation(angle_/Pi*180);
// 	// rec_shape_.setRotation(angle_/Pi*180);
// 	// window.draw(cir_shape_);
// 	// window.draw(rec_shape_);
// } 

// void SnakeNode::render(sf::RenderWindow& window, bool isHead, bool isTail) {

// 	if (isHead) {
//         cir_shape_.setRotation(angle_);
//         window.draw(cir_shape_);
//     } else if (isTail) {
//         tail_shape_.setRotation(angle_);
//         window.draw(tail_shape_);
//     } else {
//         rec_shape_.setRotation(angle_);
//         window.draw(rec_shape_);
//     }
// }
void SnakeNode::render(sf::RenderWindow& window, bool isHead, bool isTail)
{
	cir_shape_.setTexture(&texture,true);
	rec_shape_.setTexture(&texture,true);
    tail_shape_.setTexture(&texture,true);
    sf::Vector2f adjustedPosition = position_;
    adjustedPosition.x += radius;
    adjustedPosition.y += radius;

    if (isHead) {
        cir_shape_.setPosition(adjustedPosition);
        cir_shape_.setRotation(angle_);
        window.draw(cir_shape_);
    } else if (isTail) {
        tail_shape_.setPosition(adjustedPosition);
        tail_shape_.setRotation(angle_);
        window.draw(tail_shape_);
    } else {
        rec_shape_.setPosition(adjustedPosition);
        rec_shape_.setRotation(angle_);
        window.draw(rec_shape_);
    }
}


void SnakeNode::setAngle(float angle) {
    angle_ = angle;
}
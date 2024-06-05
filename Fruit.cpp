#include <SFML/Graphics.hpp>
#include "Fruit.h"

#include <iostream>
#include <ctime>
#include <random>

using namespace sfSnake;

Fruit::Fruit(sf::Vector2f position)
    : isBonus_(false),  // 初始化是否为奖励水果
	bonusLifetime_(sf::seconds(10)) // 设置 BonusFruit 的生命周期为 10 秒
{
    static std::mt19937 random(static_cast<unsigned>(time(NULL))); // 使用随机引擎
    static std::uniform_int_distribution<int> color_choose(0, 5);
    int colorIndex = color_choose(random);
    color_ = fruit_color[colorIndex];
    shape_.setPosition(position);
    shape_.setRadius(5.f);  // 默认半径
    shape_.setFillColor(color_);
}

void Fruit::render(sf::RenderWindow& window)
{
    //设置水果纹理
    shape_.setTexture(&texture_, true);
    window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
    return shape_.getGlobalBounds();
}

void Fruit::BonusFruit()
{
    shape_.setFillColor(sf::Color::Yellow); // 将奖励水果设置为黄色
    Fruit::Radius = 15.0f; // 奖励水果半径
    shape_.setRadius(Fruit::Radius);
    isBonus_ = true; // 设置为奖励水果
}

bool Fruit::operator==(const Fruit& other)
{
    return shape_.getPosition() == other.shape_.getPosition() && color_ == other.color_;
}


void Fruit::makeBonus()
{
    isBonus_ = true;
    shape_.setFillColor(sf::Color::Magenta);
    Radius = 10.f;
    shape_.setRadius(Radius);
    bonusClock_.restart();
}


void Fruit::update()
{
    if (isBonus_ && bonusClock_.getElapsedTime() > bonusLifetime_) {
        isBonus_ = false;
        // Radius = 5.f;
        // shape_.setRadius(Radius);
        // color_ = fruit_color[std::rand() % 6];
        // shape_.setFillColor(color_);
    }
}

bool Fruit::isExpired() const
{
    return isBonus_ && bonusClock_.getElapsedTime() > bonusLifetime_;
}

float Fruit::getRemainingTime() const
{
    if (isBonus_) {
        return bonusLifetime_.asSeconds() - bonusClock_.getElapsedTime().asSeconds();
    }
    return 0.f;
}
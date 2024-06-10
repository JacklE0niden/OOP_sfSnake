#include <SFML/Graphics.hpp>
#include "Fruit.h"
#include "Game.h"
#include <iostream>
#include <ctime>
#include <random>

using namespace sfSnake;

Fruit::Fruit(sf::Vector2f position)
    : isBonus_(false),  // 初始化是否为奖励水果
	bonusLifetimeFrames_(BonusLifetimeFrames) // 设置 BonusFruit 的生命周期为 10 秒
{
    static std::mt19937 random(static_cast<unsigned>(time(NULL))); // 使用随机引擎
    static std::uniform_int_distribution<int> color_choose(0, 4);
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

//更改对象为一个Bonus水果
void Fruit::BonusFruit()
{
    shape_.setFillColor(sf::Color::Red); // 将奖励水果设置为红色
    // 为奖励水果加载纹理
    if (!texture_.loadFromFile("../sfSnake/textures/apple.png")) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    shape_.setTexture(&texture_,true);
    Fruit::Radius = 15.0f; // 奖励水果半径
    shape_.setRadius(Fruit::Radius);
    isBonus_ = true; // 设置为奖励水果
    bonusLifetimeFrames_ = BonusLifetimeFrames;
    bonusClock_.restart(); // Ensure clock is reset when becoming bonus
}

bool Fruit::operator==(const Fruit& other)
{
    return shape_.getPosition() == other.shape_.getPosition() && color_ == other.color_;
}

void Fruit::update()
{
    // if (isBonus_ && bonusClock_.getElapsedTime() > bonusLifetime_) {
    //     isBonus_ = false;
        // Radius = 5.f;
        // shape_.setRadius(Radius);
        // color_ = fruit_color[std::rand() % 6];
        // shape_.setFillColor(color_);
    // }
    if (isBonus_ && bonusLifetimeFrames_ > 0) {
        --bonusLifetimeFrames_; // 每帧减少生命周期
    }
}

void Fruit::setcolor(sf::Color colors){
    color_ = colors;
    shape_.setFillColor(color_);
}

bool Fruit::isExpired() const
{
    if (isBonus_ && bonusLifetimeFrames_ <= 0) {
        return true;
    }
    // std::cout<<"expired"<<std::endl;
    return false;
}

int Fruit::getRemainingframe() const
{
    if (isBonus_) {
        // 获取 TimePerFrame 的值
        // sf::Time timePerFrame = Game::getTimePerFrame();
        // 将剩余的帧数转换为秒数
        return static_cast<int>(bonusLifetimeFrames_);
    }
    return 0.f;
}
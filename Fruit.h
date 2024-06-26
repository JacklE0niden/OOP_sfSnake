#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
class Fruit
{
public:
    Fruit(sf::Vector2f position = sf::Vector2f(0, 0));

    void render(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    // 获取形状、颜色、设置颜色
    sf::CircleShape getShape() { return shape_; }
    sf::Color color() { return color_; }

    // 改变颜色
    void color_change() { shape_.setFillColor(color_); }
    // 设置颜色
    void setcolor(sf::Color colors) ;

    // 获取颜色
    sf::Color getcolor() const { return color_; }

    // 是否为奖励的额外果实
    void BonusFruit();
    bool isBonus() const { return isBonus_; }
    // void makeBonus();

    // 重载==运算符
    bool operator==(const Fruit& other);

    // 更新 BonusFruit 状态
    void update();
    bool isExpired() const;
  	// 获取剩余时间
    int getRemainingframe() const;
    static const int BonusLifetimeFrames = 150;

private:
    sf::CircleShape shape_;
    // 半径
    float Radius;
    sf::Color color_;
    sf::Color fruit_color[5] = {
        sf::Color::Black, 
        sf::Color(139, 69, 19), // 棕色
        sf::Color::Red, 
        sf::Color::Blue, 
        sf::Color::Green
    };
    sf::Texture texture_;
    bool isBonus_;

	sf::Clock bonusClock_;
    // 只要保留一个
    int bonusLifetimeFrames_;
    
};
}

#endif
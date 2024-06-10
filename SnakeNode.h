#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	// 设置节点的角度
	void setAngle(float angle);

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window, bool isHead, bool isTail);

	void update(sf::Time delta);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	static const float Width;
	static const int Height = 10;
	// float timeOffset_;

private:
	sf::RectangleShape rec_shape_;
	sf::CircleShape cir_shape_;
	// sf::RectangleShape shape_;
	sf::Vector2f position_;
	sf::ConvexShape tail_shape_; // Added for the tail
	
	// newly added
	//为蛇节点着色、添加纹理和设置方向（角度）
    float angle_;
    float timeOffset_;

	static const float radius;

	sf::Color fillcolor[6]={sf::Color::Red,sf::Color::Green,sf::Color::Blue,sf::Color(255,0,255),sf::Color(0,255,255),sf::Color(255,255,0)};
	sf::Texture texture;
};
}

#endif
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

	void move(float xOffset, float yOffset);

	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;

	static const float Width;
	static const int HEIGHT = 10;

private:
	sf::RectangleShape rec_shape_;
	sf::CircleShape cir_shape_;
	// sf::RectangleShape shape_;
	sf::Vector2f position_;
	
	// newly added
	//为蛇节点着色、添加纹理和设置方向（角度）
	double angle_;

	sf::Color fillcolor[6]={sf::Color::Red,sf::Color::Green,sf::Color::Blue,sf::Color(255,0,255),sf::Color(0,255,255),sf::Color(255,255,0)};
	sf::Texture texture;
};
}

#endif
#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down
	};



// 这里只是声明，定义在cpp中
class Snake
{
public:
	Snake();

	void handleInput(const sf::RenderWindow&);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);
	sf::Sprite head(){return head_;};
	bool hitSelf() const;

	unsigned getSize() const;

private:
	void move();
	void grow();
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();

	bool hitSelf_;

	sf::Vector2f position_;
	Direction direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	//设置蛇头的纹理
	sf::Texture texture;
	sf::Sprite head_;

	std::vector<SnakeNode> nodes_;

	static const int InitialSize;
};
}

#endif
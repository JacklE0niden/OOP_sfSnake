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
	// 单独弄了一个蛇头
	sf::Sprite head(){return head_;};
	bool hitSelf() const;

	unsigned getSize() const;
	int getScore() const;

    void setcurrenteaten(int currenteaten){currenteaten_ = currenteaten;}
    void addcurrenteaten(){currenteaten_++;} // 新增加分数的函数
    int getcurrenteaten(){return currenteaten_;}

private:
    void move();
    void grow(int length = 1);
    void checkSelfCollisions();
    void checkEdgeCollisions();
    void initNodes();

    std::vector<SnakeNode> nodes_;
    sf::Sprite head_;
    sf::Texture texture;
    sf::SoundBuffer pickupBuffer_;
    sf::SoundBuffer dieBuffer_;
    sf::Sound pickupSound_;
    sf::Sound dieSound_;
    Direction direction_;
    bool hitSelf_;
    int score_;  // 新增分数成员变量
    int currenteaten_{0};
	static const int InitialSize;
};
}

#endif
#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void generateFruit();
	void updateScore();

	void renderBonusTimer(sf::RenderWindow& window, const Fruit& fruit);

private:
	Snake snake_;
	std::vector<Fruit> fruit_;
	//每隔一定的长度生成一个额外的奖励果实（基于蛇的长度来确定）

	int score{0};
	sf::Font font_;
	sf::Text text_;


	int flag{1};
};
}

#endif
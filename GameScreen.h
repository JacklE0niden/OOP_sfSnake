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

	int countCommonFruits() const;
	int countBonusFruits() const;

	//蛇节点移动
	// void generateSnake();



private:
	Snake snake_;
	std::vector<Fruit> fruit_;
	//每隔一定的长度生成一个额外的奖励果实（基于蛇的长度来确定）
	int bonusFruitInterval_{8};
	//当前吃的普通水果数量
	int currenteaten_{0};


	int score{0};
	sf::Font font_;
	sf::Text text_;

	// New clock for resetting fruits
    sf::Clock fruitResetClock; // New clock for resetting fruits
    const sf::Time fruitResetInterval = sf::seconds(20); // Interval for resetting fruits
	const sf::Time warningInterval = sf::seconds(5); // Time to show warning before reset
	void resetFruits(); // New function to reset fruits
	// 还有5秒就要重置水果
	sf::Text resetWarningText_; // New text for reset warning

	int flag{1};
};
}

#endif
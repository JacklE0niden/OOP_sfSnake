#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include "Screen.h"
#include "GameSettings.h"

namespace sfSnake
{
class GameOverScreen : public Screen
{
public:
	GameOverScreen(std::size_t score);

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	//设置当前游戏难度
    void setDifficulty(Difficulty difficulty) { currentDifficulty_ = difficulty; }

    //获取当前游戏难度
    Difficulty getDifficulty() const { return currentDifficulty_; }

private:
	sf::Font font_;
	sf::Text text_;

	unsigned score_;
	// Game& game_;
	Difficulty currentDifficulty_;
};
}

#endif
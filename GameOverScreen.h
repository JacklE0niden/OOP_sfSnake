#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include "Screen.h"
#include "Game.h"
#include "GameSettings.h"

namespace sfSnake
{
class GameOverScreen : public Screen
{
public:
	// GameOverScreen(int score, Game& game);
	GameOverScreen(int score);
	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	//设置当前游戏难度
    void setDifficulty(Difficulty difficulty) { currentDifficulty_ = difficulty; }

    //获取当前游戏难度
    Difficulty getDifficulty() const { return currentDifficulty_; }

	// ~GameOverScreen(){
	// 	std::cout << "GameOverScreen destroyed" << std::endl;
	// }

private:
	sf::Font font_;
	sf::Text text_;
	sf::Music music_;//游戏结束时的背景音乐

	int score_;
	// Game& game_;
	Difficulty currentDifficulty_;
};
}

#endif
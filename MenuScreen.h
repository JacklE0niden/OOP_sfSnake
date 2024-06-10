#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include "Screen.h"
#include "GameSettings.h"
namespace sfSnake
{
class MenuScreen : public Screen
{
public:
	MenuScreen();
	
	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	// 枚举类型表示游戏难度


	// 设置当前游戏难度
    void setDifficulty(Difficulty difficulty) { currentDifficulty_ = difficulty; }

    // 获取当前游戏难度
    Difficulty getDifficulty() const { return currentDifficulty_; }

private:
	sf::Font font_;
	sf::Text snakeText_;
	sf::Text text_;

	Difficulty currentDifficulty_;
};
}

#endif
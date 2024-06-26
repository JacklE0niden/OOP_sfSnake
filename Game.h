#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>
#include "GameSettings.h"
#include "Screen.h"
#include <iostream>

namespace sfSnake
{
class Game
{
public:
	Game();

	void run();
	void playmusic();
	void handleInput();
	void update(sf::Time delta);
	void render();

	// 根据难度设置帧率
	static void setframe(Difficulty difficulty);
	static sf::Time TimePerFrame;

	const sf::Time getTimePerFrame();

	void setDifficulty(Difficulty difficulty) { currentDifficulty_ = difficulty; }
	Difficulty getdifficulty() { return currentDifficulty_; }

	static const int Width = 640;
	static const int Height = 480;

	static std::shared_ptr<Screen> Screen;

	void setGameOver()
	{
		isRunning = false;
	}
	void setGameStart()
	{
		isRunning = true;
	}
	bool getGameStatus()
	{
		return isRunning;
	}
	~Game()
	{
		std::cout << "Game destroyed" << std::endl;
	}

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	//float framerate;
	Difficulty currentDifficulty_;
	bool isRunning;
	
};
}


#endif
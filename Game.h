#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

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
	void setlowframe();
	void sethighframe();

	static const int Width = 640;
	static const int Height = 480;

	static std::shared_ptr<Screen> Screen;

private:
	sf::RenderWindow window_;
	sf::Music bgMusic_;
	//float framerate;
	sf::Time TimePerFrame;
};
}


#endif
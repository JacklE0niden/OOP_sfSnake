#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 10.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake") //VideoMode构造函数的用法
{

	sf::Music bgMusic;
	bgMusic_.openFromFile("C:/Users/24398/Desktop/oop/大作业/sfSnake/Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::handleInput()
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window_.close();
	}

	Game::Screen->handleInput(window_);
}

void Game::update(sf::Time delta)
{
	Game::Screen->update(delta);
}

void Game::render()
{
	window_.clear();
	Game::Screen->render(window_);
	window_.display();
}

// 运行游戏主循环
void Game::run()
{
	sf::Clock clock;
	// 记录自上次更新以来经过的时间，初始值为零
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (window_.isOpen())
	{
		sf::Time delta = clock.restart();
		timeSinceLastUpdate += delta;

		while (timeSinceLastUpdate > Game::TimePerFrame)
		{
			//每一帧的时间间隔，处理用户输入，更新游戏状态
			timeSinceLastUpdate -= TimePerFrame;
			handleInput();
			update(TimePerFrame);
		}

		render();
	}
}
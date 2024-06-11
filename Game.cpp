#include <SFML/Graphics.hpp>
//#include"stopwatch.h"
#include <memory>
#include <iostream>
#include "MenuScreen.h"

#include "Game.h"
#include "GameScreen.h"

using namespace sfSnake;
std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
sf::Time Game::TimePerFrame;

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	isRunning = true;
	TimePerFrame = sf::seconds(1.f / 10.f);
}

void Game::playmusic(){
    bgMusic_.openFromFile("../sfSnake/Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::setframe(Difficulty difficulty)
{
    switch (difficulty)
    {
    case Difficulty::Easy:
        TimePerFrame = sf::seconds(1.f / 10.f);
        break;
    case Difficulty::Medium:
        TimePerFrame = sf::seconds(1.f / 15.f);
        break;
    case Difficulty::Hard:
        TimePerFrame = sf::seconds(1.f / 20.f);
        break;
    case Difficulty::Insane:
        TimePerFrame = sf::seconds(1.f / 30.f);
        break;
    default:
        break;
    }
}

const sf::Time Game::getTimePerFrame()
{
    return TimePerFrame;
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

void Game::run()
{
    // Game::Screen = std::make_shared<GameScreen>(*this);
    sf::Clock clock;
    
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time speedIncreaseInterval = sf::seconds(2.f);
    sf::Time timeSinceLastSpeedIncrease = sf::Time::Zero;
    std::cout << "Game::TimePerFrame: " << Game::TimePerFrame.asSeconds() << std::endl;
    
    // bool isRunning = true; // 添加一个标志来控制游戏循环

    while (window_.isOpen())
    {

        sf::Time delta = clock.restart();
        timeSinceLastUpdate += delta;
        timeSinceLastSpeedIncrease += delta;
        
        // std::cout << "timeSinceLastUpdate: " << timeSinceLastUpdate.asSeconds() << std::endl;
        
        while (timeSinceLastUpdate > Game::TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            handleInput();
            update(TimePerFrame);
        }

        render();

        if (timeSinceLastSpeedIncrease > speedIncreaseInterval)
        {
            std::cout << "timeSinceLastSpeedIncrease: " << timeSinceLastSpeedIncrease.asSeconds() << std::endl;
            std::cout << "TimePerFrame: " << Game::TimePerFrame.asSeconds() << std::endl;

            // 检查当前难度并相应地调整帧时间
            switch (currentDifficulty_)
            {
            case Difficulty::Medium:
                if (Game::TimePerFrame > sf::seconds(1.f / 30.f))
                {
                    Game::TimePerFrame -= sf::seconds(0.01f);
                }
                break;
            case Difficulty::Hard:
                if (Game::TimePerFrame > sf::seconds(1.f / 35.f))
                {
                    Game::TimePerFrame -= sf::seconds(0.01f);
                }
                break;
            case Difficulty::Insane:
                if (Game::TimePerFrame > sf::seconds(1.f / 45.f)) // 设置最快速度
                {
                    Game::TimePerFrame -= sf::seconds(0.01f);
                }
                break;
            default:
                break;
            }

            timeSinceLastSpeedIncrease = sf::Time::Zero; // 重置时间
        }
    } 
}
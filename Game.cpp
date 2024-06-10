#include <SFML/Graphics.hpp>
//#include"stopwatch.h"
#include <memory>
//#include<iostream>
#include "MenuScreen.h"
#include "Game.h"
#include "GameScreen.h"

using namespace sfSnake;

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();
sf::Time Game::TimePerFrame;

Game::Game()
: window_(sf::VideoMode(Game::Width, Game::Height), "sfSnake")
{
	
	TimePerFrame = sf::seconds(1.f / 10.f);
}

void Game::playmusic(){
    bgMusic_.openFromFile("../sfSnake/Music/bg_music.wav");
	bgMusic_.setLoop(true);
	bgMusic_.play();
}

void Game::setlowframe(){
	Game::TimePerFrame = sf::seconds(1.f / 5.f);
}

void Game::sethighframe(){
	Game::TimePerFrame = sf::seconds(1.f / 10.f);
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
	sf::Clock clock;
	
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time speedIncreaseInterval = sf::seconds(5.f);
    sf::Time timeSinceLastSpeedIncrease = sf::Time::Zero;

    while (window_.isOpen())
    {
        sf::Time delta = clock.restart();
        timeSinceLastUpdate += delta;
        timeSinceLastSpeedIncrease += delta;

        while (timeSinceLastUpdate > Game::TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            handleInput();
            update(TimePerFrame);
        }

        render();

        if (timeSinceLastSpeedIncrease > speedIncreaseInterval)
        {
            timeSinceLastSpeedIncrease -= speedIncreaseInterval;
            if (Game::TimePerFrame > sf::seconds(1.f / 30.f))
            {
                Game::TimePerFrame -= sf::seconds(0.01f);
            }
        }
    }
}
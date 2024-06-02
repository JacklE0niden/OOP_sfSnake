#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;

//创建蛇对象
GameScreen::GameScreen() : snake_()
{

}

//处理输入
void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput();
}


//更新游戏状态，蛇移动、水果生成、碰撞检测
void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}


//渲染游戏界面
void GameScreen::render(sf::RenderWindow& window)
{
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

//生成水果
void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}


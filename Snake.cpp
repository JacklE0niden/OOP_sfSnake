#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include <cmath>
#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false), score_(0)  // 初始化分数
{
    initNodes();

    pickupBuffer_.loadFromFile("C:/Users/24398/Desktop/oop/大作业/sfSnake/Sounds/pickup.wav");
    pickupSound_.setBuffer(pickupBuffer_);
    pickupSound_.setVolume(30);

    dieBuffer_.loadFromFile("C:/Users/24398/Desktop/oop/大作业/sfSnake/Sounds/die.wav");
    dieSound_.setBuffer(dieBuffer_);
    dieSound_.setVolume(50);
}

//初始化蛇的节点，这里的蛇的节点是一个vector，里面存放了很多个SnakeNode对象
// TODO: 更改蛇头形状和蛇的形状，让蛇头变得更明显
void Snake::initNodes()
{
    texture.loadFromFile("C:/Users/24398/Desktop/oop/大作业/sfSnake/textures/snake_head.png");

    // 假设蛇头图片较大，需要根据图片尺寸进行调整
    sf::Vector2u textureSize = texture.getSize();
    float scale = 0.5f; // 缩放比例

    // 设置蛇头的缩放比例
    head_.setTexture(texture);
    head_.setScale(scale, scale);

    // 设置蛇头的位置
    head_.setPosition(sf::Vector2f(
        Game::Width / 2 - SnakeNode::Width / 2 ,
        Game::Height / 2 - SnakeNode::Height / 2));

    // 初始化蛇身节点
    for (int i = 1; i < Snake::InitialSize; ++i)
    {
        SnakeNode node(sf::Vector2f(
            Game::Width / 2 - SnakeNode::Width / 2,
            Game::Height / 2 + (SnakeNode::Height * (i + 1)) - SnakeNode::Height / 2));
        nodes_.push_back(node);
    }
}

//处理用户输入，改变蛇方向
// TODO: 优化用户输入的处理，使得蛇不能直接180度转向
// TODO: 加入鼠标和wsad控制
void Snake::handleInput(const sf::RenderWindow &window)
{
    Direction newDirection = direction_;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        newDirection = Direction::Up;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        newDirection = Direction::Down;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        newDirection = Direction::Left;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        newDirection = Direction::Right;

    // 防止往反方向转向
    if (!((direction_ == Direction::Up && newDirection == Direction::Down) ||
          (direction_ == Direction::Down && newDirection == Direction::Up) ||
          (direction_ == Direction::Left && newDirection == Direction::Right) ||
          (direction_ == Direction::Right && newDirection == Direction::Left)))
    {
        direction_ = newDirection;
    }

	    // 处理鼠标点击
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f headPosition = head_.getPosition();

        float deltaX = mousePosition.x - headPosition.x;
        float deltaY = mousePosition.y - headPosition.y;

        if (std::abs(deltaX) > std::abs(deltaY))
        {
            if (deltaX > 0)
                newDirection = Direction::Right;
            else
                newDirection = Direction::Left;
        }
        else
        {
            if (deltaY > 0)
                newDirection = Direction::Down;
            else
                newDirection = Direction::Up;
        }

        if (!((direction_ == Direction::Up && newDirection == Direction::Down) ||
              (direction_ == Direction::Down && newDirection == Direction::Up) ||
              (direction_ == Direction::Left && newDirection == Direction::Right) ||
              (direction_ == Direction::Right && newDirection == Direction::Left)))
        {
            direction_ = newDirection;
        }
    }
}


void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
	// TODO: Add a method to check for collisions with obstacles.
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
    decltype(fruits.begin()) toRemove = fruits.end();

    for (auto it = fruits.begin(); it != fruits.end(); ++it)
    {
        if (it->getBounds().intersects(nodes_[0].getBounds()))
        {
            toRemove = it;

            sf::Color fruitColor = it->getcolor();

            if (it->isBonus())
            {
                score_ += 100;
                grow(1); // Bonus 水果增加1个单位长度
                float remainingframe = it->getRemainingframe();
                if (remainingframe < 0) remainingframe = 0; // Ensure positive time
                int decrementRate = it->BonusLifetimeFrames - remainingframe;
                float decrementScale = decrementRate / 1.5;
                std::cout << "Remaining Time: " << remainingframe << " Decrement Rate: " << decrementRate << std::endl;
                score_ -= static_cast<int>(decrementScale);
            }
            else
            {
                if (fruitColor == sf::Color::Black)
                {
                    std::cout << "Eaten Black" << std::endl;
                    score_ -= 3;
                    // 不增加长度
                }
                else if (fruitColor == sf::Color(139, 69, 19)) // 棕色
                {
                    std::cout << "Eaten Brown" << std::endl;
                    score_ += 1;
                    // 不增加长度
                }
                else if (fruitColor == sf::Color::Red)
                {
                    std::cout << "Eaten Red" << std::endl;
                    score_ -= 1;
                    grow(3); // 减少1个单位长度
                }
                else if (fruitColor == sf::Color::Blue)
                {
                    std::cout << "Eaten Blue" << std::endl;
                    score_ += 2;
                    grow(2); // 增加2个单位长度
                }
                else if (fruitColor == sf::Color::Green)
                {
                    std::cout << "Eaten Green" << std::endl;
                    score_ += 3;
                    grow(1); // 增加1个单位长度
                }

                addcurrenteaten();
                // std::cout << "currenteaten = " << currenteaten_ << std::endl;
            }
        }
    }

    if (toRemove != fruits.end())
    {
        pickupSound_.play();
        fruits.erase(toRemove);
    }
}
// 在移动方向的尾部添加一个节点
void Snake::grow(int length)
{
    for (int i = 0; i < length; ++i)
    {
        switch (direction_)
        {
        case Direction::Up:
            nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
                nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
            break;
        case Direction::Down:
            nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
                nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
            break;
        case Direction::Left:
            nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,
                nodes_[nodes_.size() - 1].getPosition().y)));
            break;
        case Direction::Right:
            nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,
                nodes_[nodes_.size() - 1].getPosition().y)));
            break;
        }
    }
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

unsigned Snake::getScore() const
{
	return score_;
}


// void Snake::checkSelfCollisions()
// {
// 	SnakeNode& headNode = nodes_[0];

// 	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
// 	{
// 		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
// 		{
// 			dieSound_.play();
// 			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
// 			hitSelf_ = true;
// 		}
// 	}
// }

// void Snake::checkEdgeCollisions()
// {
// 	SnakeNode& headNode = nodes_[0];

// 	if (headNode.getPosition().x <= 0)
// 		headNode.setPosition(Game::Width, headNode.getPosition().y);
// 	else if (headNode.getPosition().x >= Game::Width)
// 		headNode.setPosition(0, headNode.getPosition().y);
// 	else if (headNode.getPosition().y <= 0)
// 		headNode.setPosition(headNode.getPosition().x, Game::Height);
// 	else if (headNode.getPosition().y >= Game::Height)
// 		headNode.setPosition(headNode.getPosition().x, 0);
// }
void Snake::checkSelfCollisions()
{
    for (decltype(nodes_.size()) i = 3; i < nodes_.size(); ++i)
    {
        if (head_.getGlobalBounds().intersects(nodes_[i].getBounds()))
        {
            printf("hit on %d\n",i);
            dieSound_.play();
            sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
            hitSelf_ = true;
        }
    }
}
void Snake::checkEdgeCollisions()
{
	if (head_.getPosition().x <= 0)
		head_.setPosition(Game::Width, head_.getPosition().y);
	else if (head_.getPosition().x >= Game::Width)
		head_.setPosition(0, head_.getPosition().y);
	else if (head_.getPosition().y <= 0)
		head_.setPosition(head_.getPosition().x, Game::Height);
	else if (head_.getPosition().y >= Game::Height)
		head_.setPosition(head_.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}
	// 问题：蛇头不会动 设置蛇头的位置为nodes_[0]的位置
	if (!nodes_.empty()) {
		nodes_[0].setPosition(head_.getPosition());
	}
	switch (direction_)
	{
	case Direction::Up:
		head_.move(0, -SnakeNode::Height);
		break;
	case Direction::Down:
		head_.move(0, SnakeNode::Height);
		break;
	case Direction::Left:
		head_.move(-SnakeNode::Width, 0);
		break;
	case Direction::Right:
		head_.move(SnakeNode::Width, 0);
		break;
	}
}

void Snake::render(sf::RenderWindow& window) {
    // 临时保存当前蛇头的位置
    // sf::Vector2f originalHeadPosition = head_.getPosition();

    // // 将蛇头的位置向左和向上各移动半个节点的宽度和高度
    // head_.move(-SnakeNode::Width / 2, -SnakeNode::Height / 2);

    // 绘制蛇头
    window.draw(head_);

    // 恢复蛇头的位置
    // head_.setPosition(originalHeadPosition);

    // 绘制蛇身节点
    for (std::size_t i = 0; i < nodes_.size(); ++i) {
        bool isTail = (i == nodes_.size() - 1);
        nodes_[i].render(window, false, isTail);
    }
}
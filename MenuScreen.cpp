#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <iostream>
#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

// 菜单屏幕的各种信息
MenuScreen::MenuScreen() : currentDifficulty_(Difficulty::Easy)
{
    font_.loadFromFile("../sfSnake/Fonts/ARLRDBD.TTF");
    text_.setFont(font_);
    text_.setString(
        "\n\n\n\n\tPress [SPACE] to play\n\n\tPress [LSHIFT] for easier one\n\n\tPress [RSHIFT] for harder one\n\n\tPress [ESC] to quit");

    snakeText_.setFont(font_);
    snakeText_.setString("Snake!");
    snakeText_.setFillColor(sf::Color::Green);
    snakeText_.setCharacterSize(64);
    snakeText_.setStyle(sf::Text::Bold);

    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
        textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, Game::Height / 2);

    sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
    snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
        snakeTextBounds.top + snakeTextBounds.height / 2);
    snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        Game game;
		Game::Screen = std::make_shared<GameScreen>();
		window.close();
		
		game.setframe(currentDifficulty_);
		game.setDifficulty(currentDifficulty_);
		game.run();

	}
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        switch (currentDifficulty_)
        {
            case Difficulty::Hard:
                setDifficulty(Difficulty::Medium);
                // std::cout << "Current difficulty: Medium" << std::endl;
                break;
            case Difficulty::Medium:
                setDifficulty(Difficulty::Easy);
                // std::cout << "Current difficulty: Easy" << std::endl;
                break;
            case Difficulty::Insane: 
                setDifficulty(Difficulty::Hard);
                // std::cout << "Current difficulty: Hard" << std::endl;
                break;       
			case Difficulty::Easy:
                break;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
    {
        switch (currentDifficulty_)
        {
            case Difficulty::Easy:
                setDifficulty(Difficulty::Medium);
                // std::cout << "Current difficulty: Medium" << std::endl;
                break;
            case Difficulty::Medium:
                setDifficulty(Difficulty::Hard);
                // std::cout << "Current difficulty: Hard" << std::endl;
                break;
            case Difficulty::Hard:
              	setDifficulty(Difficulty::Insane);
                // std::cout << "Current difficulty: Insane" << std::endl;
                break;
            case Difficulty::Insane: // 如果当前是 Hard 或 Insane，按 RSHIFT 仍然设置为 Hard
                // 不执行任何操作，难度已经是最高的了
                break;
        }
    }
}


// 更新菜单界面的状态，例如标题的动画效果
void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	sf::Texture texture;
	texture.loadFromFile("../sfSnake/textures/background3.png");
	sf::Sprite sprite(texture);
	sprite.setPosition(sf::Vector2f(0,0));
	window.draw(sprite);
	window.draw(text_);
	window.draw(snakeText_);

	// 渲染游戏难度
    sf::Text difficultyText;
    difficultyText.setFont(font_);
    switch (currentDifficulty_)
    {
    case Difficulty::Easy:
        difficultyText.setString("Difficulty: Easy");
        break;
    case Difficulty::Medium:
        difficultyText.setString("Difficulty: Medium");
        break;
    case Difficulty::Hard:
        difficultyText.setString("Difficulty: Hard");
        break;
    case Difficulty::Insane:
        difficultyText.setString("Difficulty: Insane");
        break;
    default:
        break;
    }
    difficultyText.setCharacterSize(24);
    difficultyText.setFillColor(sf::Color::White);
    difficultyText.setPosition(10, 10);
    window.draw(difficultyText);
}
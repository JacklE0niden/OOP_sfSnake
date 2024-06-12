#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>

#include "Game.h"
#include "MenuScreen.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(int score)
    : score_(score)
{
	// font_.loadFromFile("Fonts/ARLRDBD.TTF");
	font_.loadFromFile("../sfSnake/Fonts/ARLRDBD.TTF");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!"
		"\n\nPress [SPACE] to retry"
		"\n\nPress [ESC] to quit");
	text_.setColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);
        
    // 加载并播放背景音乐
    if (!music_.openFromFile("../sfSnake/Music/split.wav")) {
        std::cerr << "Failed to load background music" << std::endl;
    } else {
        music_.setLoop(true);
        music_.play();
    }
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {   
        Game::Screen = std::make_shared<MenuScreen>();
		window.close();
		Game game;
		game.run();
        // Game::Screen = std::make_shared<MenuScreen>();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.close();
    }
}

void GameOverScreen::update(sf::Time delta)
{

}

// 增加了适应屏幕大小的背景
void GameOverScreen::render(sf::RenderWindow& window)
{
    sf::Texture texture;
    if (!texture.loadFromFile("../sfSnake/textures/gameover.png")) {
        std::cerr << "Failed to load texture" << std::endl;
        return;
    }

    sf::Sprite sprite(texture);

    // Get window size
    sf::Vector2u windowSize = window.getSize();

    // Get texture size
    sf::Vector2u textureSize = texture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    float scale = std::min(scaleX, scaleY); // Use the smaller scale factor to maintain aspect ratio

    // Apply the scale to the sprite
    sprite.setScale(scale, scale);

    // Center the sprite in the window
    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    sprite.setPosition(windowSize.x / 2, windowSize.y / 2);

    window.draw(sprite);
    window.draw(text_);
}
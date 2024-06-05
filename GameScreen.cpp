#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#define FRUITNUM 1
const float CIR_WIDTH=20.f;

using namespace sfSnake;

//随机数生成器
static std::uniform_int_distribution<int> xDistribution(0, Game::Width - CIR_WIDTH);
static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode ::HEIGHT);
static std::uniform_int_distribution<int> colorForm(0,1);

using namespace sfSnake;

//创建蛇对象
GameScreen::GameScreen() : snake_(), flag(1), score(0)
{
    font_.loadFromFile("C:/Users/24398/Desktop/oop/大作业/sfSnake/Fonts/ARLRDBD.TTF");
    text_.setFont(font_);
    text_.setCharacterSize(24); // Set the character size
    text_.setFillColor(sf::Color::White); // Set the text color
    updateScore(); // Ensure the score text is set initially
    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, Game::Height / 2);
}

//处理输入
void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}


//更新游戏状态，蛇移动、水果生成、碰撞检测
void GameScreen::update(sf::Time delta)
{
    if (fruit_.size() < 1)
        generateFruit();

    // Update all fruits' state
    for (auto& fruit : fruit_) {
        fruit.update();
    }

	// 更新蛇位置
    snake_.update(delta);
    snake_.checkFruitCollisions(fruit_);

    // 移除过期的 BonusFruit
    fruit_.erase(std::remove_if(fruit_.begin(), fruit_.end(),
                                [](const Fruit& fruit) { return fruit.isExpired(); }),
                 fruit_.end());


    if (snake_.hitSelf()) {
        flag = 1;
		printf("GAME OVER!");
        Game::Screen = std::make_shared<GameOverScreen>(snake_.getScore());
    }

    // // Remove expired BonusFruits
    // fruit_.erase(std::remove_if(fruit_.begin(), fruit_.end(), [](const Fruit& fruit) {
    //     return fruit.isExpired();
    // }), fruit_.end());

    updateScore();
}

//渲染游戏界面

//增加了一个进度条，表示bonus水果
void GameScreen::render(sf::RenderWindow& window)
{
    snake_.render(window);
    window.draw(text_);
    for (auto fruit : fruit_) {
        fruit.render(window);
        renderBonusTimer(window, fruit); // Render bonus fruit timer
    }
}
void GameScreen::renderBonusTimer(sf::RenderWindow& window, const Fruit& fruit)
{
    if (fruit.isBonus()) {
        // 计算 BonusFruit 剩余时间的比例
        float remainingTime = fruit.getRemainingTime();
        float progress = remainingTime / 10.;

        // 计算进度条的宽度
        float progressBarWidth = Game::Width * progress;

        // 创建和设置进度条
        sf::RectangleShape progressBar(sf::Vector2f(progressBarWidth, 10));
        progressBar.setFillColor(sf::Color::Red);
        progressBar.setPosition(0, Game::Height - 10);

        // 绘制进度条
        window.draw(progressBar);
    }
}
//生成水果

void GameScreen::generateFruit()
{
	static std::mt19937 cd_make(std::random_device{}());

	cd_make.seed(time(NULL));
	int brown_record=0;
	int black_record=0;
	while(fruit_.size()<FRUITNUM){
		if(fruit_.size()==0){
			fruit_.push_back(Fruit(sf::Vector2f(xDistribution(cd_make), yDistribution(cd_make))));
		}
		for(auto record : fruit_){
			if(record.color()==sf::Color(128,64,0)){
				brown_record++;
			}
			if(record.color()==sf::Color::Black){
				black_record++;
			}
		}
		// while(brown_record+black_record!=5){
		// 	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(cd_make), yDistribution(cd_make))));
		// 	if (colorForm(cd_make))
		// 	{
		// 		fruit_[fruit_.size() - 1].setcolor(sf::Color(128, 64, 0));
		// 		brown_record++;
		// 	}
		// 	else
		// 	{
		// 		fruit_[fruit_.size() - 1].setcolor(sf::Color::Black);
		// 		black_record++;
		// 	}
		// }
		// while(fruit_.size()<FRUITNUM){
		// 	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(cd_make), yDistribution(cd_make))));
		// }

		while(snake_.getSize() > flag*8){
			Fruit bonus = Fruit(sf::Vector2f(xDistribution(cd_make), yDistribution(cd_make)));
			bonus.BonusFruit();
			bonus.makeBonus();
			fruit_.push_back(bonus);

			flag++;
		}
	}
}
void GameScreen::updateScore()
{
    score = snake_.getScore();
    text_.setString("Score: " + std::to_string(score));
    // Update text position if necessary
    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
}
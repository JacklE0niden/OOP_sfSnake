#include <SFML/Graphics.hpp>
// #include <SFML/include/SFML/Graphics.hpp>
// #include <SFML/include/SFML/Audio.hpp>
#include <random>
#include <memory>
#include <iostream>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"
#define COMMON_FRUITNUM 20
const float CIR_WIDTH=20.f;

using namespace sfSnake;

//随机数生成器
static std::uniform_int_distribution<int> xDistribution(0, Game::Width - CIR_WIDTH);
static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode ::Height);
static std::uniform_int_distribution<int> colorForm(0,1);

std::string background_blank_choose[3]={
	"../sfSnake/textures/background1.png",
    "../sfSnake/textures/background2.png","../sfSnake/textures/background3.png"};

std::string background_net_choose[3]={
	"../sfSnake/textures/background_grid1.png",
    "../sfSnake/textures/background_grid2.png","../sfSnake/textures/background_grid3.png"};

using namespace sfSnake;

//创建蛇对象
// GameScreen::GameScreen(Game& game) : snake_(), flag(1), score(0), game_(game)
GameScreen::GameScreen() : snake_(), flag(1), score(0)
{
    if (!font_.loadFromFile("../sfSnake/Fonts/ARLRDBD.TTF"))
    {
        std::cerr << "Failed to load font" << std::endl;
        // return -1;
    }
    text_.setFont(font_);
    text_.setString("Score: 0");
    text_.setCharacterSize(16); // Set the character size
    text_.setFillColor(sf::Color(255, 165, 0));
    updateScore(); // Ensure the score text is set initially
    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    text_.setPosition(Game::Width / 2, Game::Height / 2);

    //重置水果倒计时
    resetWarningText_.setFont(font_);
    resetWarningText_.setCharacterSize(24); // Set the character size for warning
    resetWarningText_.setFillColor(sf::Color::Red);
    resetWarningText_.setString("Fruits will reset in 5 seconds!");
    sf::FloatRect warningBounds = resetWarningText_.getLocalBounds();
    resetWarningText_.setOrigin(warningBounds.left + warningBounds.width / 2,
                                warningBounds.top + warningBounds.height / 2);
    resetWarningText_.setPosition(Game::Width / 2, Game::Height / 2 + 50);
    // 加载并播放背景音乐
    if (!music_.openFromFile("../sfSnake/Music/bg_music.wav")) {
        std::cerr << "Failed to load background music" << std::endl;
    } else {
        music_.setLoop(true);
        music_.play();
    }
}

//处理输入
void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}


//更新游戏状态，蛇移动、水果生成、碰撞检测
void GameScreen::update(sf::Time delta)
{
    // if (countCommonFruits()<COMMON_FRUITNUM)
    generateFruit();


    // Check if it's time to reset fruits
    if (fruitResetClock.getElapsedTime() >= fruitResetInterval) {
        resetFruits();
    }

    // Show warning 5 seconds before reset


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
        std::cout<<"score = "<<snake_.getScore()<<std::endl;
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
    // newlyy added 渲染背景
    static int records=0;
	static std::string* background=background_blank_choose;
    sf::Texture tex; 
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		sf::sleep(sf::seconds(0.1));
		records++;
		records%=3;
		tex.loadFromFile(background[records]);
		tex.setRepeated(true);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
		sf::sleep(sf::seconds(0.1));
		if(background == background_blank_choose){
			background=background_net_choose;
		}
		else{
			background=background_blank_choose;
		}
		tex.loadFromFile(background[records]);
		tex.setRepeated(true);
	}
	else{
		tex.loadFromFile(background[records]);
		tex.setRepeated(true);
	}
	sf::RectangleShape rectangle(sf::Vector2f(640,480));
	rectangle.setTextureRect(sf::IntRect(0,0,640,480));
    rectangle.setTexture(&tex);
	rectangle.setOutlineColor(sf::Color::Yellow);
    rectangle.setOutlineThickness(5);
	rectangle.setPosition(sf::Vector2f(0,0));
	window.draw(rectangle); 

    snake_.render(window);
    window.draw(text_);
    for (auto& fruit : fruit_) { // Use auto& to avoid copying
        fruit.render(window);
        renderBonusTimer(window, fruit);
    }

    if (fruitResetClock.getElapsedTime() >= fruitResetInterval - warningInterval) {
        window.draw(resetWarningText_);
    }
}


void GameScreen::renderBonusTimer(sf::RenderWindow& window, const Fruit& fruit)
{
    if (fruit.isBonus()) {
        // 计算 BonusFruit 剩余时间的比例
        float remainingframe = fruit.getRemainingframe();
        float progress = remainingframe / fruit.BonusLifetimeFrames;

        // 计算进度条的宽度
        float progressBarWidth = Game::Width * progress;

        // 创建和设置进度条
        sf::RectangleShape progressBar(sf::Vector2f(progressBarWidth, 5));
        progressBar.setFillColor(sf::Color::Red);
        progressBar.setPosition(0, Game::Height-5);  // 设置进度条的位置在窗口底部之外

        // 绘制进度条
        window.draw(progressBar);
    }
}


//生成水果

void GameScreen::generateFruit()
{
    static std::mt19937 cd_make(std::random_device{}());
    cd_make.seed(time(NULL));

    int commonFruitCount = countCommonFruits();
    int blackbrown = 0;
    // int brownCount = 0;

    for (const auto& fruit : fruit_) {
        if (fruit.getcolor() == sf::Color::Black) {
            blackbrown++;
        }
        else if (fruit.getcolor() == sf::Color(139, 69, 19)) { // Brown color
            blackbrown++;
        }
    }

    while (commonFruitCount < COMMON_FRUITNUM) {
        Fruit newFruit(sf::Vector2f(xDistribution(cd_make), yDistribution(cd_make)));
        // bool isSpecialColor = ((blackCount + brownCount) < (COMMON_FRUITNUM / 4)) && (blackCount + brownCount) >= (COMMON_FRUITNUM / 5);
        bool isSpecialColor = (blackbrown) < (COMMON_FRUITNUM / 4);
        
        if (isSpecialColor) {
            static sf::Color spacialColors[2] = { sf::Color::Black, sf::Color(139, 69, 19)};
            static std::uniform_int_distribution<int> specialcolorDist(0, 1);
            newFruit.setcolor(spacialColors[specialcolorDist(cd_make)]);
            blackbrown++;
        }
        else {
            // Set the color to one of the other three colors
            static sf::Color otherColors[3] = { sf::Color::Red, sf::Color::Blue, sf::Color::Green };
            static std::uniform_int_distribution<int> othercolorDist(0, 2);
            newFruit.setcolor(otherColors[othercolorDist(cd_make)]);
            // std::cout<<"color = " << othercolorDist(cd_make) <<std::endl;
        }

        fruit_.push_back(newFruit);
        commonFruitCount++;
        // std::cout<<"commonFruitCount = "<<commonFruitCount<<std::endl;
    }

    while (snake_.getcurrenteaten() >= bonusFruitInterval_) {
        snake_.setcurrenteaten(0);
        if (countBonusFruits() > 0) {
            break;
        }
        else {
            Fruit bonus = Fruit(sf::Vector2f(xDistribution(cd_make), yDistribution(cd_make)));
            bonus.BonusFruit();
            fruit_.push_back(bonus);
        }
    }
}

void GameScreen::resetFruits()
{

    fruit_.erase(std::remove_if(fruit_.begin(), fruit_.end(), [](const Fruit& fruit) {
        return !fruit.isBonus(); 
    }), fruit_.end());

    static std::mt19937 cd_make(std::random_device{}());
    int blackbrown = 0;

    // Generate new common fruits
    for (int i = 0; i < COMMON_FRUITNUM; ++i) {
        Fruit newFruit(sf::Vector2f(xDistribution(cd_make), yDistribution(cd_make)));
        bool isSpecialColor = blackbrown < (COMMON_FRUITNUM / 4);

        if (isSpecialColor) {
            static sf::Color specialColors[2] = { sf::Color::Black, sf::Color(139, 69, 19) };
            static std::uniform_int_distribution<int> specialColorDist(0, 1);
            newFruit.setcolor(specialColors[specialColorDist(cd_make)]);
            blackbrown++;
        } else {
            static sf::Color otherColors[3] = { sf::Color::Red, sf::Color::Blue, sf::Color::Green };
            static std::uniform_int_distribution<int> otherColorDist(0, 2);
            newFruit.setcolor(otherColors[otherColorDist(cd_make)]);
        }

        fruit_.push_back(newFruit);
    }

    // Reset the clock
    fruitResetClock.restart();
}

int GameScreen::countCommonFruits() const
{
    int count = 0;
    for (const auto& fruit : fruit_) {
        if (!fruit.isBonus()) {
            ++count;
        }
    }
    return count;
}

int GameScreen::countBonusFruits() const
{
    int count = 0;
    for (const auto& fruit : fruit_) {
        if (fruit.isBonus()) {
            ++count;
        }
    }
    return count;
}

void GameScreen::updateScore()
{
    score = snake_.getScore();
    // std::cout << "Updating score: " << score << std::endl;

    std::string scoreString = "Score: " + std::to_string(score);
    // std::cout<<"scoreString = "<<scoreString<<std::endl;
    text_.setString(scoreString);
    // std::cout << "Score string set: " << text_.getString().toAnsiString() << std::endl;

    // Update text position if necessary
    sf::FloatRect textBounds = text_.getLocalBounds();
    text_.setOrigin(textBounds.left + textBounds.width / 2,
                    textBounds.top + textBounds.height / 2);
    // std::cout << "Text position updated" << std::endl;
}
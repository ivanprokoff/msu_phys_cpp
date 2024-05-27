#include <SFML/Graphics.hpp>
#include <vector>
#include <sstream>
#include <random>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

std::vector<std::vector<sf::RectangleShape>> generateLevels() {
    std::vector<std::vector<sf::RectangleShape>> levels;
    std::vector<sf::Vector2f> patterns = {
            {5, 3},
            {6, 4},
            {7, 5},
            {8, 3},
            {9, 2}
    };

    for (auto& pattern : patterns) {
        std::vector<sf::RectangleShape> blocks;
        int numBlocksX = pattern.x;
        int numBlocksY = pattern.y;
        for (int i = 0; i < numBlocksX; ++i) {
            for (int j = 0; j < numBlocksY; ++j) {
                sf::RectangleShape block(sf::Vector2f(760 / numBlocksX - 4, 25));
                block.setFillColor(sf::Color::Blue);
                block.setPosition(5 + i * (760 / numBlocksX), 5 + j * 30);
                blocks.push_back(block);
            }
        }
        levels.push_back(blocks);
    }
    return levels;
}

void resetGame(sf::RectangleShape& paddle, sf::CircleShape& ball, sf::Vector2f& ballVelocity, bool& gameOver, sf::Text& message, int& score, sf::Text& scoreText, std::vector<sf::RectangleShape>& currentBlocks, const std::vector<sf::RectangleShape>& levelBlocks) {
    paddle.setPosition(WINDOW_WIDTH / 2 - paddle.getSize().x / 2, WINDOW_HEIGHT - 20 - paddle.getSize().y);
    ball.setPosition(WINDOW_WIDTH / 2, 300);
    ballVelocity = sf::Vector2f(0.1f, -0.1f);

    gameOver = false;
    message.setString("");
    score = 0;
    scoreText.setString("Score: 0");

    currentBlocks = levelBlocks;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arcanoid Game");
    sf::RectangleShape paddle(sf::Vector2f(100, 20));
    paddle.setFillColor(sf::Color::Red);

    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::White);

    sf::Vector2f ballVelocity(0.1f, -0.1f);
    std::vector<std::vector<sf::RectangleShape>> levels = generateLevels();
    std::vector<sf::RectangleShape> currentBlocks;
    int score = 0, currentLevelIndex = 0;
    bool gameOver = true, gameStarted = false;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    sf::Text message("Press any key to start", font, 50);
    message.setPosition(120, 250);
    sf::Text scoreText("", font, 30);
    scoreText.setPosition(10, 10);

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, levels.size() - 1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && gameOver) {
                if (!gameStarted) {
                    currentLevelIndex = uni(rng);
                }
                resetGame(paddle, ball, ballVelocity, gameOver, message, score, scoreText, currentBlocks, levels[currentLevelIndex]);
                gameStarted = true;
                scoreText.setString("Score: 0");
            }
        }

        window.clear();
        if (gameStarted && !gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x > 0)
                paddle.move(-0.3f, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x < WINDOW_WIDTH - paddle.getSize().x)
                paddle.move(0.3f, 0);

            ball.move(ballVelocity);

            if (ball.getPosition().x <= 0 || ball.getPosition().x >= WINDOW_WIDTH - ball.getRadius() * 2)
                ballVelocity.x = -ballVelocity.x;
            if (ball.getPosition().y <= 0)
                ballVelocity.y = -ballVelocity.y;
            if (ball.getPosition().y >= WINDOW_HEIGHT - ball.getRadius() * 2) {
                message.setString("You lose. Press any key to restart.");
                message.setPosition(30, 250);
                gameOver = true;
            }

            if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds())) {
                float paddleCenter = paddle.getPosition().x + paddle.getSize().x / 2;
                float ballCenter = ball.getPosition().x + ball.getRadius();
                float offset = (ballCenter - paddleCenter) / (paddle.getSize().x / 2);
                ballVelocity.y = -ballVelocity.y;
                ballVelocity.x = 0.1f * offset;
            }

            auto it = currentBlocks.begin();
            while (it != currentBlocks.end()) {
                if (ball.getGlobalBounds().intersects(it->getGlobalBounds())) {
                    ballVelocity.y = -ballVelocity.y;
                    it = currentBlocks.erase(it);
                    score += 100;
                    std::ostringstream ss;
                    ss << "Score: " << score;
                    scoreText.setString(ss.str());
                } else {
                    ++it;
                }
            }

            if (currentBlocks.empty()) {
                message.setString("You win! Press any key to restart.");
                message.setPosition(30, 250);
                gameOver = true;
                gameStarted = false;
            }

            window.draw(paddle);
            window.draw(ball);
            for (auto& block : currentBlocks) {
                window.draw(block);
            }
        } else {
            window.draw(message);
        }
        window.draw(scoreText);
        window.display();
    }

    return 0;
}

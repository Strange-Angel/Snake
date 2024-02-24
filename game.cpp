#include "game.h"

Game::Game()
    : window(sf::VideoMode(width, height), "Snake Game")
    , flag(false)
    , m_flag(false)
{
    buffer.loadFromFile("resources/gameover.wav");
    gameover.setBuffer(buffer);
    snake = new Snake();
    window.setFramerateLimit(120);
    font.loadFromFile("resources/calibri.ttf");
    text.setFont(font);
    text.setString("Game Snake \nPress any key to start...");
    text.setFillColor(sf::Color::Green);
    text.setPosition(width / 2 - 130, height / 2 - 50);
    startGame();
}

void Game::startGame()
{
    while (window.isOpen()) {
        window.clear();
        if (snake->collide_with_itself()) {
            if (!m_flag) {
                gameover.play();
                m_flag = true;
            }
            gameOver();
        } else if (!flag) {
            menuInput();
        } else {
            m_flag = false;
            gameInput();
        }
        window.display();
    }
}

void Game::menuInput()
{
    window.clear();
    window.draw(text);
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            if (!flag) {
                gameInput();
                flag = true;
                break;
            }
        }
    }
}
void Game::gameInput()
{
    frame.setSize(sf::Vector2f(720, 520));
    frame.setPosition(40, 40);
    frame.setOutlineThickness(2.f);
    frame.setOutlineColor(sf::Color::Magenta);
    frame.setFillColor(sf::Color::Transparent);
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Up && snake->direction != Direction::Down
                       && snake->check_on_turn_vertical()) {
                snake->direction = Direction::Up;
            } else if (event.key.code == sf::Keyboard::Down && snake->direction != Direction::Up
                       && snake->check_on_turn_vertical()) {
                snake->direction = Direction::Down;
            } else if (event.key.code == sf::Keyboard::Left && snake->direction != Direction::Right
                       && snake->check_on_turn_horizontal()) {
                snake->direction = Direction::Left;
            } else if (event.key.code == sf::Keyboard::Right && snake->direction != Direction::Left
                       && snake->check_on_turn_horizontal()) {
                snake->direction = Direction::Right;
            }
        }
    }
    snake->update();

    window.clear();
    window.draw(frame);
    snake->grow();
    snake->draw(window);
}

void Game::gameOver()
{
    std::string score(snake->outText);
    std::string out = "   Game Over\n   " + score
                      + "\n   press Enter to continue...\n   or ESC to exit";
    text.setString(out);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    window.clear();
    window.draw(text);

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Enter) {
                delete snake;
                snake = new Snake();
                gameInput();
                break;
            }
        }
    }
}

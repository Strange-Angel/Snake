#ifndef GAME_H
#define GAME_H

#include "snake.h"

class Game
{
private:
    const unsigned int width = 800;
    const unsigned int height = 600;

    sf::RenderWindow window;
    sf::RectangleShape frame;
    sf::Text text;
    sf::Font font;
    bool flag;
    sf::SoundBuffer buffer;
    sf::Sound gameover;
    bool m_flag;

public:
    Game();
    Snake *snake;
    void startGame();
    void menuInput();
    void gameInput();
    void gameOver();
};

#endif // GAME_H

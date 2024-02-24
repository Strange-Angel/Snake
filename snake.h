#ifndef SNAKE_H
#define SNAKE_H

#include "food.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

enum class Direction { Up, Down, Left, Right };
extern unsigned int partSize;

class Snake
{
public:
    Snake();
    unsigned int initialLength;
    std::vector<sf::CircleShape> parts;
    sf::Texture texture;
    sf::Texture headTexture;
    unsigned int partSize = 40;
    Direction direction;
    sf::Vector2f head;
    sf::Vector2f tail;
    sf::Clock clock;
    Food *food;
    sf::Time time;
    float speed;
    sf::Text textscore;
    int score;
    sf::Font font;
    char outText[50];
    int deltascore;
    sf::SoundBuffer buffer1;
    sf::Sound eatApple;

    bool check_on_turn_horizontal();
    bool check_on_turn_vertical();
    void grow();
    bool eat_apple();
    bool circles_collide(sf::CircleShape circle1, sf::CircleShape circle2);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getHeadPosition();
    void move();
    void move(Direction direction);
    void setDirection(Direction direction);
    void update();
    bool collide_with_itself();
};

#endif // SNAKE_H

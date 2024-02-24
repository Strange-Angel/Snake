#include "snake.h"
#include <cmath>
#include <fmt/core.h>
#include <iostream>

Snake::Snake()
    : initialLength(4)
    , parts(initialLength)
    , direction(Direction::Right)
    , speed(0.3f)
    , score(0)
    , deltascore(10)
{
    buffer1.loadFromFile("resources/eat.wav");
    eatApple.setBuffer(buffer1);
    font.loadFromFile("resources/calibri.ttf");
    textscore.setFont(font);
    food = new Food;
    if (!texture.loadFromFile("resources/Snake.png")) {
        throw "Falled to load snake texture";
    }
    if (!headTexture.loadFromFile("resources/head.png")) {
        throw "Falled to load head texture";
    }

    sf::Vector2f position(80, 80);
    for (unsigned int i = 0; i < initialLength; i++) {
        parts[i].setRadius(partSize / 2);
        if (i != initialLength - 1) {
            parts[i].setTexture(&texture);
        }
        parts[i].setPosition(position);
        position.x += partSize;
    }
    sprintf(outText, "Score: %d", score);
    textscore.setString(outText);
    textscore.setPosition(350, 560);
    textscore.setFillColor(sf::Color::Green);
    parts[parts.size() - 1].setTexture(&headTexture);
    head = parts[parts.size() - 1].getPosition();
    tail = parts.begin()->getPosition();
}

void Snake::draw(sf::RenderWindow &window)
{
    for (unsigned int i = 0; i < parts.size() - 1; i++) {
        if (food->apple.getPosition().x == parts[i].getPosition().x
            && food->apple.getPosition().y == parts[i].getPosition().y) {
            delete food;
            food = new Food;
        }
    }
    food->draw(window);

    for (auto &part : parts) {
        window.draw(part);
    }
    window.draw(textscore);
}

void Snake::move()
{
    move(direction);
}

void Snake::move(Direction direction)
{
    if (direction == Direction::Up) {
        head.y -= partSize;
    } else if (direction == Direction::Down) {
        head.y += partSize;
    } else if (direction == Direction::Left) {
        head.x -= partSize;
    } else if (direction == Direction::Right) {
        head.x += partSize;
    }

    if (head.x == 760 && direction == Direction::Right) {
        head.x = 40;
    }
    if (head.y == 560 && direction != Direction::Right) {
        head.y = 40;
    }
    if (head.x == 0 && direction == Direction::Left) {
        head.x = 720;
    }
    if (head.y == 0 && direction == Direction::Up) {
        head.y = 520;
    }

    for (unsigned int i = 0; i < (parts.size() - 1); i++) {
        parts[i].setPosition(parts[i + 1].getPosition());
    }
    parts.back().setPosition(head);
}

sf::Vector2f Snake::getHeadPosition()
{
    return head;
}

void Snake::update()
{
    if (!collide_with_itself()) {
        time = sf::seconds(speed);

        while (clock.getElapsedTime() < time) {
        }

        clock.restart();
        move();
    }
}

void Snake::grow()
{
    if (eat_apple()) {
        sf::CircleShape newPart;
        newPart.setRadius(partSize / 2);
        newPart.setTexture(&texture);
        newPart.setPosition(parts[0].getPosition());
        parts.emplace(parts.begin(), newPart);
        delete food;
        food = new Food;
    }
}
bool Snake::eat_apple()
{
    if (head.x == food->apple.getPosition().x && head.y == food->apple.getPosition().y) {
        if (speed != 0.8f) {
            speed -= 0.01;

            deltascore += 3;
        }
        eatApple.play();
        score += deltascore;
        sprintf(outText, "Score: %d", score);
        textscore.setString(outText);

        return true;
    }

    return false;
}


bool Snake::check_on_turn_horizontal()
{
    if (head.x - partSize == parts[parts.size() - 2].getPosition().x) {
        return false;
    }
    if (head.x + partSize == parts[parts.size() - 2].getPosition().x) {
        return false;
    }
    return true;
}

bool Snake::check_on_turn_vertical()
{
    if (head.y - partSize == parts[parts.size() - 2].getPosition().y) {
        return false;
    }
    if (head.y + partSize == parts[parts.size() - 2].getPosition().y) {
        return false;
    }
    return true;
}

bool Snake::collide_with_itself()
{
    for (unsigned int i = 0; i < parts.size() - 1; i++) {
        if (head.x == parts[i].getPosition().x && head.y == parts[i].getPosition().y) {
            return true;
        }
    }
    return false;
}

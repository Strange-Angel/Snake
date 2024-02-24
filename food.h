#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>

class Food
{
public:
    Food();
    sf::CircleShape apple;
    sf::Texture texture;
    unsigned int partSize = 40;

    void draw(sf::RenderWindow &window);
};

#endif // FOOD_H

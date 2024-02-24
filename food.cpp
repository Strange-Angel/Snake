#include "food.h"
#include <random>

Food::Food()
{
    if (!texture.loadFromFile("/home/oleg/Изображения/apple.png")) {
        throw "Falled to load apple texture";
    }

    std::vector<int> itemsx;
    std::vector<int> itemsy;
    for (int i = 40; i < 760; i += partSize) {
        itemsx.push_back(i);
        if (i < 560) {
            itemsy.push_back(i);
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());

    std::shuffle(itemsx.begin(), itemsx.end(), gen);
    std::shuffle(itemsy.begin(), itemsy.end(), gen);

    int x = itemsx[0];
    int y = itemsy[0];

    apple.setPosition(x, y);
    apple.setRadius(partSize / 1.9);
    apple.setTexture(&texture);
}

void Food::draw(sf::RenderWindow &window)
{
    window.draw(apple);
}

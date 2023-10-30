// класс, отвечающий за расстановкиу карт на поле и обновление поля ???
// UPD: Class -- loader of Game Field. Only field!
#ifndef CARD_FIELD_H
#define CARD_FIELD_H

// #include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
// #include <chrono>
// #include <random>

#include "../card/Card.h"

using namespace sf;

class CardField
{
private:
    Texture fieldTexture;
    Sprite fieldSprite;

public:
    CardField()
    {
        if (!fieldTexture.loadFromFile("field\\field_1920_1080_ver2.png"))
        {
            //std::cerr << "load error";
        }
        // fieldTexture.loadFromFile("field\\field_1920_1080_ver2.png");
        fieldSprite.setTexture(fieldTexture);
        // sf::Vector2f v(0.0f, 0.0f);
        fieldSprite.setPosition({0.0f, 0.0f});
    };

    Sprite getSprite()
    {
        return this->fieldSprite;
    }
};

#endif
//класс, отвечающий за расстановкиу карт на поле и обновление поля ???
//UPD: Class -- loader of Game Field. Only field!
#ifndef CARD_FIELD_H
#define CARD_FIELD_H

// #include <iostream>
#include <SFML/Graphics.hpp>
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
        fieldTexture.loadFromFile("field\\field_1920_1080_ver2.png");
        fieldSprite.setTexture(fieldTexture);
        fieldSprite.setPosition(0, 0);
    };

    Sprite getSprite()
    {
        return this->fieldSprite;
    }
 
};

#endif
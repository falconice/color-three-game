// Class -- loader of Game Field. Only field!
#ifndef CARD_FIELD_H
#define CARD_FIELD_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


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
        if (!fieldTexture.loadFromFile("field\\field_1920_1080_ver3.png"))
        {
            //std::cerr << "load error";
        }
        
        fieldSprite.setTexture(fieldTexture);
        fieldSprite.setPosition({0.0f, 0.0f});
    };

    Sprite getSprite()
    {
        return this->fieldSprite;
    }
};

#endif
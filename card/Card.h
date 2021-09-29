#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Card
{

private:
    Sprite cardSprite;
    Texture cardTexture;
    std::string texturePath;

    int type;
    float x, y;
    void setCardTexture(String texturePath)
    {
        this->texturePath = texturePath;
        cardTexture.loadFromFile(texturePath);
        cardSprite.setTexture(cardTexture);
    };

public:
    Card(){};

    std::string getPath()
    {
        return this->texturePath;
    }

    void setCardType(int type)
    {
        this->type = type;

        if (type == 0)
        {
            this->setCardTexture("card\\card_textures\\Empty.png");
        }
        else if (type == 1)
        {
            this->setCardTexture("card\\card_textures\\RedCard.png");
        }
        else if (type == 2)
        {
            this->setCardTexture("card\\card_textures\\YellowCard.png");
        }
        else if (type == 3)
        {
            this->setCardTexture("card\\card_textures\\GreenCard.png");
        };
    };

    void setCardPosition(int x, int y)
    {
        cardSprite.setPosition(x, y);
        this->y = y;
        this->x = x;
    };

    Sprite getCardSprite()
    {
        return this->cardSprite;
    }

    // Sprite &getCardSprite()
    // {
    //     return this->card;
    // }

    int getCardX()
    {
        return this->x;
    }

     int getCardY()
    {
        return this->y;
    }
};

#endif
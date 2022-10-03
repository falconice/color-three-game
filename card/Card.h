#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Card
{

private:
    std::string texturePath;

    int type;
    float positionX;
    float positionY;

    int cardId;

    void setCardTexture(String texturePath)
    {
        this->texturePath = texturePath;
    };

public:
    Card(){};

    //--------SET-----///

    void setCardId(int id)
    {
        this->cardId = id;
    };

    void setCardPosition(float x, float y)
    {
        this->positionY = y;
        this->positionX = x;
    };

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

    //--------GET-----///

    float getCardX()
    {
        return this->positionX;
    }

    float getCardY()
    {
        return this->positionY;
    }

    int getCardId()
    {
        return this->cardId;
    }

    std::string getPath()
    {
        return this->texturePath;
    }

    int getCardType()
    {
        return this->type;
    }

    //--------OTHER-----///

    void changeCardPosition(float newX, float newY)
    {
        this->positionX = newX;
        this->positionY = newY;
    }
};

#endif
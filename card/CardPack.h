//класс, отвечающий за набор карт и их обновление
#ifndef CARD_PACK_H
#define CARD_PACK_H

// #include <iostream>
// #include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

#include "../card/Card.h"

using namespace sf;

class CardPack
{
private:
    //card array
    std::vector<Card> cardPack;
    int packSize;

    void cardShuffle()
    {
        //shuffle cards

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::vector<int> fullPack = {0, 0, 0, 0, 0, 0,
                                     1, 1, 1, 1, 1,
                                     2, 2, 2, 2, 2,
                                     3, 3, 3, 3, 3};

        std::shuffle(fullPack.begin(), fullPack.end(), std::default_random_engine(seed));

        for (int &x : fullPack)
        {
            Card card;
            card.setCardType(x);
            cardPack.push_back(card);
        }
    };

    void setPackPositions()
    {
        packSize = 0;

        //set positions for playable cards
        for (int y = 110; y < 1069; y = y + 192)
        {
            for (int x = 480; x < 1438; x = x + 192)
            {
                if (!((y == 302 && (x == 672 || x == 1056)) ||
                      (y == 686 && (x == 672 || x == 1056))))
                {
                    //set position and Id
                    this->cardPack.at(packSize).setCardPosition(x, y);
                    this->cardPack.at(packSize).setCardId(packSize);
                    packSize++;
                }
            }
        }
    };

public:
    CardPack()
    {
        cardShuffle();
        setPackPositions();
    };

    std::vector<Card> &getCardPack()
    {
        return this->cardPack;
    }

    int getPackSize()
    {
        return this->packSize;
    }
};

#endif
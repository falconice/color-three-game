#ifndef CARD_PACK_H
#define CARD_PACK_H

#include <random>
#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Card.h"

using namespace sf;

class CardPack
{
    std::vector<Card> cardPack;

private:
    void fullPackShuffle()
    {

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        std::vector<int> fullPack = {0, 0, 0, 0, 0, 0,
                                     1, 1, 1, 1, 1,
                                     2, 2, 2, 2, 2,
                                     3, 3, 3, 3, 3};

        std::shuffle(fullPack.begin(), fullPack.end(), std::default_random_engine(seed));

        //std::cout << "shuffled elements:";

        for (int &x : fullPack)
        {
            Card card;

            card.setCardType(x);
            std::cout << card.getCardX();
            break;

            cardPack.push_back(card);
            // std::cout << ' ' << x;
            // std::cout << '\n';
        }
    }

public:
    CardPack()
    {
        fullPackShuffle();
    };

    Card getCard(int number)
    {
        return cardPack.at(number);
    };

    const Sprite &getCardSprite(int number)
    {
        return cardPack.at(number).getCardSprite();
    }
    // Sprite card;
    // Texture cardTexture;
};
#endif
//класс, отвечающий за набор карт и их обновление
#ifndef CARD_PACK_H
#define CARD_PACK_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

#include "../card/Card.h"

using namespace sf;

class CardPack
{
private:
    std::vector<Card> cardPack; //массив карточек
    int counter;

    void cardShuffle()
    {
        //перемешиваем карточки

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
        counter = 0;

        //цикл для выставление позиций !игровым! карточками
        for (int y = 110; y < 1069; y = y + 192)
        {
            for (int x = 480; x < 1438; x = x + 192)
            {
                if (!((y == 302 && (x == 672 || x == 1056)) ||
                      (y == 686 && (x == 672 || x == 1056))))
                {
                    //задаем позицию и ID карточки
                    this->cardPack.at(counter).setCardPosition(x, y);
                    this->cardPack.at(counter).setCardId(counter);
                    counter = counter + 1;
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

    std::vector<Card> getCardPack(){
       return this->cardPack;
    }

};

#endif
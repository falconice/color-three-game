#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "card/CardPack.h"
#include "card/Card.h"

using namespace sf;

class Game
{

private:
    // CardPack cardPack;
    int counter;
    std::vector<Card> cardPack;

public:
    Game()
    {
    }

    void launchGame()
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
            cardPack.push_back(card);

            // std::cout << ' ' << x;
            // std::cout << '\n';
        }

        RenderWindow window(VideoMode().getDesktopMode(), "Three colours"); //Style::Fullscreen

        Sprite field;
        Texture fieldTexture;

        fieldTexture.loadFromFile("field\\field_1920_1080.png");
        field.setTexture(fieldTexture);
        field.setPosition(0, 0);

        // Sprite card;
        // Texture cardTexture;

        // cardTexture.loadFromFile("card\\card_textures\\GreenCard.png");
        // card.setTexture(cardTexture);

        Sprite testSprite;
        Texture testSpriteTexture;

        while (window.isOpen())
        {
            window.clear();
            window.draw(field); //рисуем основное поле

            counter = 0;

            //цикл для заполнения поля !игровыми! карточками
            for (int y = 110; y < 1069; y = y + 192)
            {
                for (int x = 480; x < 1438; x = x + 192)
                {
                    if (!((y == 302 && (x == 672 || x == 1056)) ||
                          (y == 686 && (x == 672 || x == 1056))))
                    {
                        //задаем позицию карточки
                        this->cardPack.at(counter).setCardPosition(x, y);

                        testSpriteTexture.loadFromFile(this->cardPack.at(counter).getPath());
                        testSprite.setTexture(testSpriteTexture);
                        testSprite.setPosition(cardPack.at(counter).getCardX(),
                                               cardPack.at(counter).getCardY());

                        // std::cout << cardPack.getCard(counter).getCardX();

                        //рисуем карточку
                        window.draw(testSprite);

                        counter = counter + 1;
                    }
                }
            }

            Event event;
            while (window.pollEvent(event))
            {

                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    // cardTexture.loadFromFile("card\\card_textures\\CardBlocked.png");
                    // card.setTexture(cardTexture);
                    // window.draw(card);
                };

                //Закрыть окно
                if (event.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape)))
                {
                    window.close();
                };
            }

            window.display();
        };
    };
};

#endif
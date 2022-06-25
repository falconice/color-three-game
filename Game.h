#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

#include "card/Card.h"
#include "card/CardPack.h"
#include "field/CardField.h"

using namespace sf;

class Game
{

private:
    int counter;

    CardPack cardPackClass;

    Sprite field;
    Texture fieldTexture;

    CardField cardField;

    Sprite testSprite;
    Texture testSpriteTexture;

    /*Card textures*/

    Texture redCardTexture;
    Texture yellowCardTexture;
    Texture greenCardTexture;
    Texture emptyCardTexture;

    int gameStarted = 0;

    const Texture &textureByType(int type) const
    {
        if (type == 0)
        {
            return emptyCardTexture;
        }
        else if (type == 1)
        {
            return redCardTexture;
        }
        else if (type == 2)
        {
            return yellowCardTexture;
        }
        else
        {
            return greenCardTexture;
        };
    };

    Card &getCardById(int id)
    {

        for (Card &card : cardPackClass.getCardPack())
        {
            if (card.getCardId() == id)
            {
                return card;
            }
        };
    };

    int getCardIdFromMouse(sf::Vector2i mousePosition)
    {
        int id = -1;

        int leftX, rightX;
        int leftY, rightY;

        for (Card &card : cardPackClass.getCardPack())
        {
            //обозначаем границы карточки
            leftX = card.getCardX();
            leftY = card.getCardY();

            rightX = leftX + 192;
            rightY = leftY + 192;

            if ((mousePosition.x <= rightX) && (mousePosition.x >= leftX) &&
                (mousePosition.y <= rightY) && (mousePosition.y >= leftY))
            {
                id = card.getCardId();
            }
        };

        return id;
    };

    void swapCardsById(RenderWindow *window, int firstId, int secondId)
    {

        Card &cardFirst = getCardById(firstId);
        Card &cardSecond = getCardById(secondId);

        int firstX, firstY;
        int secondX, secondY;
        int tempX, tempY;

        firstX = cardFirst.getCardX();
        firstY = cardFirst.getCardY();

        secondX = cardSecond.getCardX();
        secondY = cardSecond.getCardY();

        Texture textureF;
        textureF.loadFromFile(cardFirst.getPath());
        Texture textureS;
        textureS.loadFromFile(cardSecond.getPath());
        Sprite first;
        first.setTexture(textureF);
        Sprite second;
        second.setTexture(textureS);

        std::cout << "\nSWAP 1 FROM --> " << firstId << " " << firstX << " " << firstY << "\n";
        std::cout << "\nSWAP 2 FROM --> " << secondId << " " << secondX << " " << secondY << "\n";

        if (((firstX + 192) == secondX) ||
            ((firstX - 192) == secondX) ||
            ((firstY + 192) == secondY) ||
            ((firstY - 192) == secondY))
        {
            tempX = firstX;
            firstX = secondX;
            secondX = tempX;

            tempY = firstY;
            firstY = secondY;
            secondY = tempY;

            cardFirst.changeCardPosition(firstX, firstY);
            cardSecond.changeCardPosition(secondX, secondY);

            std::cout << "\nSWAP 1 TO--> " << firstX << " " << firstY << "\n";
            std::cout << "\nSWAP 2 TO --> " << secondX << " " << secondY << "\n";

            first.setPosition(firstX, firstY);
            second.setPosition(secondX, secondY);

            // window->clear();
            window->draw(first);
            window->draw(second);
        }
    };

public:
    Game()
    {
        // set cards textures
        redCardTexture.loadFromFile("card\\card_textures\\RedCard.png");
        yellowCardTexture.loadFromFile("card\\card_textures\\YellowCard.png");
        greenCardTexture.loadFromFile("card\\card_textures\\GreenCard.png");
        emptyCardTexture.loadFromFile("card\\card_textures\\Empty4.png");
    }

    void launchGame()
    {
        RenderWindow window(VideoMode().getDesktopMode(), "Three colours"); //, Style::Fullscreen

        int idFirst = -1;
        int idSecond = -1;
        int flag = 0;
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
            std::cout << card.getCardX();
            cardPackClass.getCardPack().push_back(card);
        }

        window.clear();

        while (window.isOpen())
        {

            window.draw(cardField.getSprite()); // draw background field

            counter = 0;

            //цикл для заполнения поля !игровыми! карточками
            for (int y = 110; y < 1069; y = y + 192)
            {
                for (int x = 480; x < 1438; x = x + 192)
                {
                    if (!((y == 302 && (x == 672 || x == 1056)) ||
                          (y == 686 && (x == 672 || x == 1056))))
                    {

                        // add texture by type
                        testSprite.setTexture(textureByType(cardPackClass.getCardPack().at(counter).getCardType()));

                        testSprite.setPosition(cardPackClass.getCardPack().at(counter).getCardX(),
                                               cardPackClass.getCardPack().at(counter).getCardY());

                        //рисуем карточки
                        window.draw(testSprite);

                        counter = counter + 1;
                    }
                }
            }

            Event event;

            //получение координат мышки относительно окна игры
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            while (window.pollEvent(event))
            {

                if (Mouse::isButtonPressed(Mouse::Left) && flag == 0)
                {
                    std::cout << "2) " << flag << " " << idFirst << " " << idSecond << "\n";
                    flag = 1;
                }
                else if (!Mouse::isButtonPressed(Mouse::Left) && flag == 1)
                {
                    idFirst = getCardIdFromMouse(localPosition);
                    if (idFirst != -1)
                    {
                        idSecond = idFirst;
                        flag = 2;
                    }
                }
                else if (Mouse::isButtonPressed(Mouse::Left) && flag == 2)
                {

                    idFirst = getCardIdFromMouse(localPosition);
                    if (idFirst != -1 && idSecond != idFirst)
                    {
                        std::cout << "3) " << flag << " " << idFirst << " " << idSecond << "\n";

                        swapCardsById(&window, idFirst, idSecond);
                        flag = 0;
                    }
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
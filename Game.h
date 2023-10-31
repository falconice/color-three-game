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

const int CONST_SIZE = 192;

class Game
{

private:
    int counter;

    CardPack cardPackClass;

    Sprite field;
    Texture fieldTexture;

    CardField cardField;

    Sprite tmpSprite;
    Texture tmpSpriteTexture;

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
            // обозначаем границы карточки
            leftX = card.getCardX();
            leftY = card.getCardY();

            rightX = leftX + CONST_SIZE;
            rightY = leftY + CONST_SIZE;

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

        std::cout << " TRY from: \n";
        std::cout << "   card_1 id: " << firstId << " x: " << firstX << " y: " << firstY << "\n";
        std::cout << "   card_2 id: " << secondId << " x: " << secondX << " y: " << secondY << "\n";

        bool upX = 0;
        bool upY = 0;
        bool downX = 0;
        bool downY = 0;

        // forbid to jump over 1+ cards
        if ((firstX + CONST_SIZE) <= secondX)
        {
            upX = 1;
        }

        if ((firstX - CONST_SIZE) >= secondX)
        {
            downX = 1;
        }

        if ((firstY + CONST_SIZE) <= secondY)
        {
            upY = 1;
        }

        if ((firstY - CONST_SIZE) >= secondY)
        {
            downY = 1;
        }

        if (!(upX && upY || downX && downY || upX && downY || downX && upY))
        {

            if (upY || upX || downY || downX)
            {
                tempX = firstX;
                firstX = secondX;
                secondX = tempX;

                tempY = firstY;
                firstY = secondY;
                secondY = tempY;

                cardFirst.changeCardPosition(firstX, firstY);
                cardSecond.changeCardPosition(secondX, secondY);
                std::cout << " SUCCESS : \n";
                std::cout << "   card_1 id: " << firstId << " x: " << firstX << " y: " << firstY << "\n";
                std::cout << "   card_2 id: " << secondId << " x: " << secondX << " y: " << secondY << "\n";

                first.setPosition({firstX, firstY});
                second.setPosition({secondX, secondY});

                // window->clear();
                window->draw(first);
                window->draw(second);
            }
        }
        else
        {
            std::cout << "<!> swap aborted <!>\n";
        }
    };

    void winCheck()
    {
        int winIndexRed = 480;    // type == 1
        int winIndexYellow = 864; // type == 2
        int winIndexGreen = 1248; // type == 3

        int red = 0, yellow = 0, green = 0;

        for (Card &card : cardPackClass.getCardPack())
        {
            if (card.getCardType() == 1 && card.getCardX() == winIndexRed)
            {
                red++;
            }
            else if (card.getCardType() == 2 && card.getCardX() == winIndexYellow)
            {
                yellow++;
            }
            else if (card.getCardType() == 3 && card.getCardX() == winIndexGreen)
            {
                green++;
            }
        };

        if (red == 5)
        {
            std::cout << " . * + red complete * . +  \n";
        }

        if (yellow == 5)
        {
            std::cout << " + * + yellow complete + . *   \n";
        }

        if (green == 5)
        {
            std::cout << " * + . green complete + * .   \n";
        }

        if (red == 5 && yellow == 5 && green == 5)
        {
            std::cout << "\n   WIN WIN WIN   \n";
        }
        else
        {
            std::cerr << "...next step...\n\n";
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
        RenderWindow window(VideoMode({1920, 1080}), "Three colours"); //, Style::Fullscreen

        int idFirst = -1;
        int idSecond = -1;


        window.clear();
        int flag = 0;

        while (window.isOpen())
        {
            // draw background field
            window.draw(cardField.getSprite());

            counter = 0;

            // show interactive cards
            for (int y = 110; y < 1069; y = y + CONST_SIZE)
            {
                for (int x = 480; x < 1438; x = x + CONST_SIZE)
                {
                    if (!((y == 302 && (x == 672 || x == 1056)) ||
                          (y == 686 && (x == 672 || x == 1056))))
                    {

                        // add texture by type
                        tmpSprite.setTexture(textureByType(cardPackClass.getCardPack().at(counter).getCardType()));

                        tmpSprite.setPosition({cardPackClass.getCardPack().at(counter).getCardX(),
                                               cardPackClass.getCardPack().at(counter).getCardY()});

                        // рисуем карточки
                        window.draw(tmpSprite);

                        counter = counter + 1;
                    }
                }
            }

            Event event;

            // get mouse coordinates releated to game window
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            while (window.pollEvent(event))
            {

                if (Mouse::isButtonPressed(Mouse::Left) && flag == 0)
                {

                    flag = 1;
                    std::cout << "START: flag: " << flag << " id1: " << idFirst << " id2: " << idSecond << "\n";
                }
                else if (!Mouse::isButtonPressed(Mouse::Left) && flag == 1)
                {
                    idFirst = getCardIdFromMouse(localPosition);
                    if (idFirst != -1)
                    {
                        idSecond = idFirst;
                        flag = 2;
                    }
                    std::cout << " 1) first step: flag: " << flag << " id1: " << idFirst << " id2: " << idSecond << "\n";
                }
                else if (Mouse::isButtonPressed(Mouse::Left) && flag == 2)
                {

                    idFirst = getCardIdFromMouse(localPosition);
                    if (idFirst != -1 && idSecond != idFirst)
                    {
                        std::cout << " 2) second step: flag: " << flag << " id1: " << idFirst << " id2: " << idSecond << "\n";

                        swapCardsById(&window, idFirst, idSecond);
                        flag = 0;
                        // std::cout << " after swap check: flag: " << flag << " id1: " << idFirst << " id2: " << idSecond << "\n";
                        winCheck();
                    }
                };

                // Close window
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
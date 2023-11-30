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

    Texture redTexture;
    Texture yellowTexture;
    Texture greenTexture;
    Texture emptyTexture;

    /*Beacons */
    Sprite redBe;
    Texture redBeTexture;

    Sprite yellowBe;
    Texture yellowBeTexture;

    Sprite greenBe;
    Texture greenBeTexture;

    Sprite win;
    Texture winTexture;
    /*-------------------------------*/
    int gameStarted = 0;

    int winIndexRed = 480;    // type == 1
    int winIndexYellow = 864; // type == 2
    int winIndexGreen = 1248; // type == 3

    int red = 0, yellow = 0, green = 0;

    const Texture &textureByType(int type) const
    {
        if (type == 0)
        {
            return emptyTexture;
        }
        else if (type == 1)
        {
            return redTexture;
        }
        else if (type == 2)
        {
            return yellowTexture;
        }
        else
        {
            return greenTexture;
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


        // coefficients which help to protect from jumping over 1+ cards
        double coef_x = 0;
        double coef_y = 0;

        coef_x = (firstX - secondX) / CONST_SIZE;
        coef_y = (firstY - secondY) / CONST_SIZE;

        if (((coef_x == 1 || coef_x == -1) && coef_y == 0) ||
            (coef_x == 0 && (coef_y == 1 || coef_y == -1)))
        {
            std::cout << " SWAAAAAAAAP : \n";
            std::cout << "   coef_x : " << coef_x << "\n";
            std::cout << "   coef_y : " << coef_y << "\n";

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

    bool winCheck()
    {
        red = 0, yellow = 0, green = 0;
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

        if (red == 5 && yellow == 5 && green == 5)
        {

            return true;
        }
        return false;
    };

    void winDisplay(RenderWindow *window)
    {
        if (red % 5 == 0 && red != 0)
        {
            redBe.setPosition({460.0, 0.0});
            window->draw(redBe);
            std::cout << " . * + red complete * . +  \n";
        }

        if (yellow % 5 == 0 && yellow != 0)
        {
            yellowBe.setPosition({810.0, 0.0});
            window->draw(yellowBe);
            std::cout << " + * + yellow complete + . *   \n";
        }

        if (green % 5 == 0 && green != 0)
        {
            greenBe.setPosition({1160.0, 0.0});
            window->draw(greenBe);
            std::cout << " * + . green complete + * .   \n";
        }

        if (red % 5 == 0 && yellow % 5 == 0 && green % 5 == 0 && green != 0 && yellow != 0 && red != 0)
        {
            redBe.setPosition({460.0, 0.0});
            window->draw(redBe);
            yellowBe.setPosition({810.0, 0.0});
            window->draw(yellowBe);
            greenBe.setPosition({1160.0, 0.0});
            window->draw(greenBe);

            win.setPosition({0.0, 0.0});
            window->draw(win);

            std::cout << "\n   WIN WIN WIN   \n";
        }
    };

public:
    Game()
    {
        // set  textures
        redTexture.loadFromFile("card\\card_textures\\RedCard.png");
        yellowTexture.loadFromFile("card\\card_textures\\YellowCard_3.png");
        greenTexture.loadFromFile("card\\card_textures\\GreenCard_2.png");
        emptyTexture.loadFromFile("card\\card_textures\\Empty_3.png");

        redBeTexture.loadFromFile("field\\beacon\\RedBeacon_.png");
        yellowBeTexture.loadFromFile("field\\beacon\\YellowBeacon_.png");
        greenBeTexture.loadFromFile("field\\beacon\\GreenBeacon_.png");
        winTexture.loadFromFile("card\\card_textures\\win_screeen_1.png");

        redBe.setTexture(redBeTexture);
        yellowBe.setTexture(yellowBeTexture);
        greenBe.setTexture(greenBeTexture);
        win.setTexture(winTexture);
    }

    void launchGame()
    {
        RenderWindow window(sf::VideoMode({1920, 1080}), "Three colours", Style::Close); // videomode, name, Style::Fullscreen
                                                                                         //  VideoMode({1920, 1080})
        int idFirst = -1;
        int idSecond = -1;

        window.clear();
        int flag = 0;

        int check = 0;

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
                if (check == false)
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
                            check = winCheck();
                            // winCheck(&window);
                        }
                    };
                }

                // Close window
                if (event.type == Event::Closed || (Keyboard::isKeyPressed(Keyboard::Escape)))
                {
                    window.close();
                };

                // check = winCheck();
            }

            winDisplay(&window);

            window.display();
        };
    };
};

#endif
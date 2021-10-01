#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

#include "card/Card.h"

using namespace sf;

class Game
{

private:
    int counter;
    //массив карточек
    std::vector<Card> cardPack;
    Sprite field;
    Texture fieldTexture;
    Sprite testSprite;
    Texture testSpriteTexture;

    int gameStarted = 0;

    Card &getCardById(int id)
    {

        for (Card &card : cardPack)
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

        for (Card &card : cardPack)
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

        Card cardFirst = getCardById(firstId);
        Card cardSecond = getCardById(secondId);

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

            window->clear();
            window->draw(first);
            window->draw(second);
        }
    };

    // void startGamePack(RenderWindow *window)
    // {
    //     int gameStarted = 1;
    // };

public:
    Game()
    {
    }

    void launchGame()
    {
        RenderWindow window(VideoMode().getDesktopMode(), "Three colours", Style::Fullscreen); //

        int idFirst = -1;
        int idSecond = -1;
        int flag = 0;
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

        // Sprite field;
        // Texture fieldTexture;

        fieldTexture.loadFromFile("field\\field_1920_1080.png");
        field.setTexture(fieldTexture);
        field.setPosition(0, 0);

        // Sprite card;
        // Texture cardTexture;

        // cardTexture.loadFromFile("card\\card_textures\\GreenCard.png");
        // card.setTexture(cardTexture);

        // Sprite testSprite;
        // Texture testSpriteTexture;
        while (window.isOpen())
        { //if (gameStarted == 0)
            //     {
            //         startGamePack(&window);
            //     }

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
                        this->cardPack.at(counter).setCardId(counter);

                        testSpriteTexture.loadFromFile(this->cardPack.at(counter).getPath());
                        testSprite.setTexture(testSpriteTexture);
                        testSprite.setPosition(cardPack.at(counter).getCardX(),
                                               cardPack.at(counter).getCardY());

                        // std::cout << cardPack.getCard(counter).getCardX();

                        //рисуем карточки
                        window.draw(testSprite);

                        counter = counter + 1;
                    }
                }
            }

            Event event;

            //получение координат мышки относительно окна игры
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);

            //std::cout << "0) " << flag << " " << idFirst << " " << idSecond << "\n";

            while (window.pollEvent(event))
            {
                // std::cout << "1) " << idFirst << " " << idSecond << "\n";

                if (Mouse::isButtonPressed(Mouse::Left) && flag == 0)
                {
                    std::cout << "2) " << flag << " " << idFirst << " " << idSecond << "\n";
                    flag = 1;
                }
                else if (!Mouse::isButtonPressed(Mouse::Left) && flag == 1)
                {
                    idFirst = getCardIdFromMouse(localPosition);
                    idSecond = idFirst;
                    flag = 2;
                }
                else if (Mouse::isButtonPressed(Mouse::Left) && flag == 2)
                {

                    idFirst = getCardIdFromMouse(localPosition);
                    std::cout << "3) " << flag << " " << idFirst << " " << idSecond << "\n";

                    swapCardsById(&window, idFirst, idSecond);
                    flag = 0;

                    //std::cout << getCardIdFromMouse(localPosition) << "\n";
                    // std::cout << idFirst << " " << idSecond << "\n";
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
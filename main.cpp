#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>

#include "card/Card.h"

#include "Game.h"

using namespace sf;

int main()
{
	Game game;
	game.launchGame();


	std::cout << "Hello World!" << std::endl;

	return 0;
}
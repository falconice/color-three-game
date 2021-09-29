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

	// unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	// std::vector<int> fullPack = {0, 0, 0, 0, 0, 0,
	// 							 1, 1, 1, 1, 1,
	// 							 2, 2, 2, 2, 2,
	// 							 3, 3, 3, 3, 3};

	// std::shuffle(fullPack.begin(), fullPack.end(), std::default_random_engine(seed));

	// std::cout << "shuffled elements:";
	// for (int &x : fullPack)
	// 	if (x == 3)
	// 		std::cout << ' ' << x;
	// std::cout << '\n';

	std::cout << "Hello World!" << std::endl;

	return 0;
}
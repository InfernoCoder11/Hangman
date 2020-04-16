/*
	A hangman implementation using modern C++ features.
*/

#include <iostream>   // std::cin, std::cout, std::endl, std::cin.get()
#include <cctype>     // std::toupper(int c)

#include "game.hpp"   // printGameRules(), game
#include "helper.hpp" // clearScreen()

int main() {
	char play = 'Y';
	int score = 0;
	printGameRules(); // print Hangman rules
	while (play == 'Y') { // main game loop
		clearScreen();
		std::cout << "Your current score is: " << score << '\n';
		score += game(); // game returns score of current round
		std::cout << "Your current score is: " << score << '\n';
		std::cout << "Enter 'y' if you want to play the next round: ";
		std::cin >> play;
		play = std::toupper(play);
	}
	std::cout << "Your final score: " << score << std::endl;
	std::cin.get();
}

/*
	A hangman implementation using modern C++ features such as iterators.
	NOT using .h versions of standard headers and not using non-standard headers such as conio.
	NOT making system calls.
	Program will be compiled and run from CLI as follows:

	g++ hangman_modern_cpp.cpp -o hangman_modern_cpp -O3 -Wall -Wextra -std=c++14
	./hangman_modern_cpp
	
	-std flag may be used for stale compilers with older default language standard.
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
		std::cout << "Your current score is: " << score << "\n";
		score += game(); // game returns score of current round
		std::cout << "Your current score is: " << score << "\n";
		std::cout << "Enter 'y' if you want to play the next round: ";
		std::cin >> play;
		play = std::toupper(play);
	}
	std::cout << "Your final score: " << score << std::endl;
	std::cin.get();
}

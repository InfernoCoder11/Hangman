#ifndef GAME_HPP
#define GAME_HPP

#include <array>      // std::array
#include <iostream>   // std::cin, std::cout, std::endl, std::cin.get()
#include <vector>     // std::vector

#include "helper.hpp" // random(const int exclusiveRange), convertToLower(std::string& s), clearScreen()

// global constant variables
const int NUMBER_OF_WORDS = 46;
const int NUMBER_OF_CHANCES = 7;

// a random word will be selected from this list
const std::array<std::string, NUMBER_OF_WORDS> WORDS = {
	"intelligent", "dumb",
	"unstoppable", "hangman",
	"hungry", "funny",
	"arrangement", "attempt",
	"border", "breeze",
	"constant", "contrast",
	"cookie", "damage",
	"discussion", "donkey",
	"essential", "exchange",
	"explanation", "fireplace",
	"garage", "heading",
	"independent", "manufacture",
	"mathematics", "memory",
	"mission", "monkey",
	"neighbourhood", "occasion",
	"official", "palace",
	"poetry", "policeman",
	"positive", "practical",
	"promise", "remark",
	"rhyme", "satellite",
	"selection", "shake",
	"shallow", "simple",
	"thumb", "university"
};

// function declarations
void printGameRules();
int game();
std::string createDrawWord(std::string& word);
void printAllGuesses(std::vector<std::string>& allGuesses);
void printHangman(int& n);
bool checkGuessEntered(std::string& inputGuess, std::vector<std::string>& allGuesses);
bool printDrawWord(std::string& word, std::string& drawWord, std::string& guess);
bool winCheck(std::string& drawWord);

/* Prints the Hangman game's rules. */
inline void printGameRules() {
	std::cout << "\tHangman - Word Guessing Game\n";
	std::cout << "1) The vowels of a word will be given as per their respective positions in the word.\n";
	std::cout << "2) The positions of consonants will be marked by an underscore (_).\n";
	std::cout << "3) Based on this information, you have to guess the complete word.\n";
	std::cout << "4) You can either enter a character to check if it is in the word,\n";
	std::cout << "   or you can enter the whole word to check if it is correct.\n";
	std::cout << "5) You can guess wrongly a maximum of " << NUMBER_OF_CHANCES << " times.\n";
	std::cout << "6) You get +4 points if you guess the word correctly and -1 if you don't.\n";
	std::cout << "\tAll The Best!\n";
	std::cout << "Press Enter to continue ... "<< std::endl;
	std::cout << "......................................................................................." ;
	std::cin.get();
	clearScreen();
}

/* Main game. Returns score for a turn. */
int game() {
	std::string
	// random word for a turn selected from WORDS
	word = WORDS[random(NUMBER_OF_WORDS)],
	// word to be drawn with missing consonants,
	// missing consonats are filled with correct guesses
	drawWord = createDrawWord(word),
	guess; // user's guess

	int numWrongAttempts = 0, turnScore = 0;

	bool result;

	std::vector<std::string> allGuesses = {}; // guesses already entered

	while(true) {
		std::cout << "Number of letters: " << word.size() << "\n";
		std::cout << "Number of guesses left: " << NUMBER_OF_CHANCES - numWrongAttempts << "\n";
		printAllGuesses(allGuesses);
		printHangman(numWrongAttempts);
		do {
			std::cout << "Enter your guess: ";
			std::cin >> guess;
		} while (checkGuessEntered(guess, allGuesses)); // checking if guess is already entered
		convertToLower(guess);
		allGuesses.push_back(guess); // adding guess to list of all guesses
		clearScreen();
		// checks guess against the word and updates drawWord
		result = printDrawWord(word, drawWord, guess);
		if (result == true) {
			std::cout << "Correct Guess!\n";
			// checking winning condition
			if (winCheck(drawWord)) {
				std::cout << "Congratulations, You have guessed the word!\n";
				turnScore = 4;
				break;
			}
		}
		else if (result == false) {
			std::cout << "Wrong Guess!\n";
			++numWrongAttempts;
			// check if attempts are over
			if (numWrongAttempts == NUMBER_OF_CHANCES) {
				std::cout << "You are out of chances!";
				printHangman(numWrongAttempts);
				std::cout << "The correct word is: " << word << "\n";
				turnScore = -1;
				break;
			}
		}
	}
	return turnScore;
}

/* Returns the word to be drawn with missing consonats. */
std::string createDrawWord(std::string& word) {
	std::string drawWord;

	for (const auto& w : word) {
		switch (w) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				drawWord.push_back(w);
				break;
			default:
				drawWord.push_back('_');
		}
		drawWord.push_back(' ');
	}
	std::cout << drawWord << '\n';
	return drawWord;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	for (const T& x : v) {
		os << x << ' ';
	}
	return os;
}

/* Prints all guesses entered till now. */
void printAllGuesses(std::vector<std::string>& allGuesses) {
	std::cout << "Guesses till now: ";
	if (allGuesses.size() == 0) {
		std::cout << "nil";
	}
	else {
		std::cout << allGuesses;
	}
	std::cout << std::endl;
}

/* Prints Hangman based on the number of guesses left.
   _______
	|    |
	|    o
	|   /|\
	|    |
	|   / \
   _|_
  |   |______
  |          |
  |__________|

*/
inline void printHangman(int& n) {
	switch (n) {
		case 0:
			std::cout << "\n _______\n  |    |\n  |    \n  |   \n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
			break;
		case 1:
			std::cout << "\n _______\n  |    |\n  |    o\n  |   \n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
			break;
		case 2:
			std::cout << "\n _______\n  |    |\n  |    o\n  |   /\n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
			break;
		case 3:
			std::cout << "\n _______\n  |    |\n  |    o\n  |   /|\n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
			break;
		case 4:
			std::cout << "\n _______\n  |    |\n  |    o\n  |   /|\\\n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
			break;
		case 5:
			std::cout << "\n _______\n  |    |\n  |    o\n  |   /|\\\n  |    |\n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
			break;
		case 6:
			std::cout << "\n _______\n  |    |\n  |    o\n  |   /|\\\n  |    |\n  |   /\n _|_\n|   |______\n|          |\n|__________|\n";
			break;
		case 7:
			std::cout << "\n _______\n  |    |\n  |    o\n  |   /|\\\n  |    |\n  |   / \\\n _|_\n|   |______\n|          |\n|__________|\n";
			break;
	}
	std::cout << '\n';
}

/* Checks whether guess was already entered, or is a vowel. */
bool checkGuessEntered(
	std::string& inputGuess,
	std::vector<std::string>& allGuesses
	) {
	bool check = false;

	// check if guess was a single character
	if (inputGuess.size() == 1) {
		switch (inputGuess[0]) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
				std::cout << "Vowels are already given!\n";
				check = true;
				break;
			default:
				// check if guess was already entered
				// goto justification: reduce code duplication
				goto check;
		}
	}
	else {
		check:
		for (std::string guess: allGuesses) {
			if (guess == inputGuess) {
				std::cout << inputGuess << " already entered!\n";
				check = true;
			}
		}
	}
	return check;
}

/* Checks if guess is getting closer to the actual word, and updates word to be drawn. */
bool printDrawWord(
	std::string& word,
	std::string& drawWord,
	std::string& guess
	) {
	bool result = false;

	// guess is correct
	if (guess == word) {
		result = true;
		for (unsigned int i = 0; i < drawWord.size(); ++i) {
			if (drawWord[i] == '_') {
				drawWord[i] = word[i / 2]; // replace missing consonats with the correct character
			}
		}
	}
	// guess is a character
	else if (guess.size() == 1) {
		for (unsigned int i = 0; i < word.size(); ++i) {
			if (guess[0] == word[i]) { // guessed character is in the word
				result = true;
				drawWord[i * 2] = guess[0]; // replace missing consonant with the correctly guessed character
			}
		}
	}
	std::cout << drawWord << "\n";
	return result;
}

/* Checks if no characters are left to guess. */
bool winCheck(std::string& drawWord) {
	bool win = true;

	for (auto itr = drawWord.begin(); itr < drawWord.end(); itr += 2) {
		if (*itr == '_') {
			win = false;
			break;
		}
	}
	return win;
}

#endif

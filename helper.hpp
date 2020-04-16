#ifndef HELPER_HPP
#define HELPER_HPP

#include <chrono>  // system_clock::now(), time_since_epoch(), count()
#include <random>  // std::default_random_engine, std::uniform_int_distribution
#include <cctype>  // std::tolower(int c)
#include <cstdlib> // system()

/* Returns a pseudo-random number seeded by the system clock. */
int random(const int exclusiveRange) {
	// using namespace in function scope, helps readability
	using namespace std::chrono;

	// initializing seed
	static unsigned int seed = system_clock::now().time_since_epoch().count();

	// seed the generator
	static std::default_random_engine generator (seed);

	// generate distribution between 0 and NUMBER_OF_WORDS (exclusive)
	static std::uniform_int_distribution<int> distribution(0, exclusiveRange - 1);

	return distribution(generator); // return pseudo-random number
}

/* Converts a string to lowercase. */
void convertToLower(std::string& s) {
	for (auto& c : s) {
		c = tolower(c);
	}
}

/* Clears screen, not the recommended way. */
void clearScreen() {
	system("cls");
}

#endif

#ifndef HELPER_HPP // could have used #pragma once as well
#define HELPER_HPP

#include <chrono>  // system_clock::now(), time_since_epoch(), count()
#include <random>  // std::default_random_engine, std::uniform_int_distribution
#include <cctype>  // std::tolower(int c)
#include <cstdlib> // system()

/* Returns a pseudo-random number seeded by the system clock. */
int random(const int exclusiveRange) {
	using namespace std::chrono; // using namespace in function scope, helps readability
	static unsigned int seed = system_clock::now() // initializing seed
		.time_since_epoch() // get duration between epoch and time point
		.count(); // count milliseconds

	static std::default_random_engine generator (seed); // seed the generator

	static std::uniform_int_distribution<int> distribution(0, exclusiveRange - 1); // generate distribution between 0 and NUMBER_OF_WORDS (exclusive)

	return distribution(generator); // return pseudo-random number
}

/* Converts a string to lowercase. */
void convertToLower(std::string& s) {
	for (auto it = s.begin(); it < s.end(); ++it) {
		*it = tolower(*it); // iterating over the whole string and lowering each character
	}
}

/* Clears screen, not the recommended way. */
void clearScreen() {
	system("cls");
}

#endif

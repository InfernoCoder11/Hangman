# include <iostream>
# include <time.h>

using namespace std;

// Function Prototypes
int Game();

// Global Variable Declarations
int NumberOfWords = 0;

int main(){
    srand(time(0)); // Seed rand() with system time
    char Words[][20] = {"intelligent", // A random word will be selected from this list
                        "unstoppable",
                        "hangman",
                        "silly",
                        "funny",
                        };
    NumberOfWords = sizeof(Words)/sizeof(Words[0]);
    bool Play = 1;
    while (Play){
        Game();
    }
    return 0;
}

int Game(){
    return 0;
}
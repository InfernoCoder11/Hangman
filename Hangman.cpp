# include <iostream>
# include <time.h>
# include <string.h>

using namespace std;

// Function Prototypes
int Game(char [][20]);
int random();

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
        Game(Words);
        Play = 0; //Just for now
    }
    return 0;
}

int Game(char Words[][20]){
    char Word[20];
    int LengthOfWord;

    strcpy(Word, Words[random()]);
    LengthOfWord = strlen(Word);
    for (int i = 0; i < LengthOfWord; ++i)
        cout<<"_ ";
    cout<<endl<<"Number of letters: "<<LengthOfWord<<endl;
    return 0;
}

int random(){
    int rnd = rand();
    rnd = rnd % NumberOfWords;
    return rnd;
}
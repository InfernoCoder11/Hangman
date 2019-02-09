# include <iostream>
# include <time.h>
# include <string.h>

using namespace std;

// Function Prototypes
int Game(char [][20]);
void CreateDrawWord(char [], int);
bool PrintDrawWord(char [], char[], char[], int);
int random();

// Global Variable Declarations
int NumberOfWords = 0;

int main(){
    srand(time(0)); // Seed rand() with system time
    char Words[][20] = {"intelligent", // A random word will be selected from this list
                        "unstoppable",
                        "hangman",
                        "hungry",
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
    char Word[20], DrawWord[40], Guesses[7];
    int LengthOfWord, c = 0;
    bool Guessed = 0, result;

    strcpy(Word, Words[random()]);
    LengthOfWord = strlen(Word);
    CreateDrawWord(DrawWord, LengthOfWord);
    cout<<"Length of Word: "<<LengthOfWord<<endl;
    while (!Guessed){
        cout<<"Enter your guess: ";
        cin>>Guesses[c++];
        result = PrintDrawWord(Word, DrawWord, Guesses, c);
        if (!result)
            cout<<"Wrong Guess!"<<endl;
        else
            cout<<"Correct Guess!"<<endl;
    }
    cout<<endl<<"Number of letters: "<<LengthOfWord<<endl;
    return 0;
}

void CreateDrawWord(char DrawWord[], int LengthOfWord){
    int i, c = 0;
    for (i = 0; i < LengthOfWord; ++i){
        DrawWord[c++] = '_';
        DrawWord[c++] = ' ';
    }
    DrawWord[c++] = '\0';
    cout<<DrawWord<<endl;
}

bool PrintDrawWord(char Word[], char DrawWord[], char Guesses[], int n){
    bool result = 0;
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; Word[j] != '\0'; ++j)
            if (Guesses[i] == Word[j])
                DrawWord[j*2] = Guesses[i];
    for (j = 0; Word[j] != '\0'; ++j)
        if (Guesses[n - 1] == Word[j])
            result = 1;
    cout<<DrawWord<<endl;
    return result;
}

int random(){
    int rnd = rand();
    rnd = rnd % NumberOfWords;
    return rnd;
}
# include <iostream>
# include <time.h>
# include <conio.h>
# include <string.h>

using namespace std;

// Function Prototypes
int Game(char [][20]);
void CreateDrawWord(char[], char [], int);
bool PrintDrawWord(char [], char[], char[], int);
bool WinCheck(char []);
int random();

// Global Variable Declarations
int NumberOfWords = 0;
const int chances = 7;

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
        getch();
        Play = 0; //Just for now
    }
    return 0;
}

int Game(char Words[][20]){
    char Word[20], DrawWord[40], Guesses[chances];
    int LengthOfWord, c = 0;
    bool Guessed = 0, result;

    strcpy(Word, Words[random()]);
    LengthOfWord = strlen(Word);
    CreateDrawWord(Word, DrawWord, LengthOfWord);
    cout<<"Number of letters: "<<LengthOfWord<<endl;
    while (!Guessed){
        cout<<"Number of guesses left: "<<chances - c<<endl;
        cout<<"Enter your guess: ";
        cin>>Guesses[c++];
        result = PrintDrawWord(Word, DrawWord, Guesses, c);
        if (!result)
            cout<<"Wrong Guess!"<<endl;
        else
            cout<<"Correct Guess!"<<endl;
        if (WinCheck(DrawWord)){
            cout<<"Congratulations, you have guessed the word!"<<endl;
            return 0;
        }
        else if (c == chances){
            cout<<"You are out of chances!"<<endl;
            cout<<"The correct word is: "<<Word<<endl;
            return -1;
        }
    }
    return -2;
}

void CreateDrawWord(char Word[], char DrawWord[], int LengthOfWord){
    int i, c = 0;
    for (i = 0; i < LengthOfWord; ++i){
        switch(Word[i]){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u': DrawWord[c++] = Word[i];
                      break;
            default: DrawWord[c++] = '_';
        }
        DrawWord[c++] = ' ';
    }
    DrawWord[c++] = '\0';
    cout<<DrawWord<<endl;
}

bool PrintDrawWord(char Word[], char DrawWord[], char Guesses[], int n){
    bool result = 0;
    int i, j;
    for (j = 0; Word[j] != '\0'; ++j)
        for (i = 0; i < n; ++i)
            if (Guesses[i] == Word[j])
                DrawWord[j*2] = Guesses[i];
    for (j = 0; Word[j] != '\0'; ++j)
        if (Guesses[n - 1] == Word[j])
            result = 1;
    cout<<DrawWord<<endl;
    return result;
}

bool WinCheck(char DrawWord[]){
    bool Win = 1;
    for (int i = 0; DrawWord[i] != '\0'; i += 2)
        if (DrawWord[i] == '_')
            Win = 0;
    return Win;
}

int random(){
    int rnd = rand();
    rnd = rnd % NumberOfWords;
    return rnd;
}
# include <iostream>
# include <time.h> // For srand()
# include <conio.h>
# include <string.h>
# include <stdlib.h> // For system()
# include <ctype.h> // For toupper(), tolower()

using namespace std;

// Function Prototypes
int Game();
void CreateDrawWord(char[], char [], int);
bool PrintDrawWord(char [], char[], char[], char[], int);
bool WinCheck(char []); // Check if player has met winning conditions or not
int random();
void ConvertToLower(char []);
void clrscr();
void PrintGameRules();

// Global Variable Declarations
int NumberOfWords = 0;
const int chances = 7;
char Words[][20] = {"intelligent", // A random word will be selected from this list
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
                        }; // 45 words

int main(){
    PrintGameRules();
    srand(time(0)); // Seed rand() with system time
    NumberOfWords = sizeof(Words)/sizeof(Words[0]);
    char Play = 'Y';
    while (Play == 'Y'){
        clrscr();
        Game();
        cout<<"Enter 'y' if you want to play again"<<endl;
        cin>>Play;
        Play = toupper(Play);
    }
    return 0;
}

int Game(){
    char Word[20], DrawWord[40], Guess[20], Guesses[chances];
    int LengthOfWord, c = 0;
    bool Guessed = 0, result;

    strcpy(Word, Words[random()]);
    LengthOfWord = strlen(Word);
    CreateDrawWord(Word, DrawWord, LengthOfWord);
    cout<<"Number of letters: "<<LengthOfWord<<endl;
    while (!Guessed){
        cout<<"Number of guesses left: "<<chances - c<<endl;
        cout<<"Enter your guess: ";
        cin>>Guess;
        ConvertToLower(Guess);
        Guesses[c++] = Guess[0];
        clrscr();
        result = PrintDrawWord(Word, DrawWord, Guess, Guesses, c);
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

bool PrintDrawWord(char Word[], char DrawWord[], char Guess[], char Guesses[], int n){
    bool result = 0;
    int i, j;
    if (strcmp(Guess, Word) == 0){
        result = 1;
        for (i = 0; DrawWord[i] != '\0'; i += 2)
            if (DrawWord[i] == '_')
                DrawWord[i] = Word[i/2];
        cout<<DrawWord<<endl;
        return result;
    }
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

void ConvertToLower(char Guess[]){
    for (int i = 0; Guess[i] != '\0'; ++i)
        Guess[i] = tolower(Guess[i]);
}

void clrscr(){
    system("cls");
}

void PrintGameRules(){
    cout<<"\tWord Guessing Game"<<endl;
    cout<<" 1) The vowels of a word will be given as per their respective positions in the word"<<endl;
    cout<<" 2) The positions of consonants will be marked by an underscore (_)"<<endl;
    cout<<" 3) Based on this information, you have to guess the complete word"<<endl;
    cout<<" 4) You can either enter a character to check if it is in the word,"<<endl;
    cout<<"    or you can enter the whole word to check if it is correct"<<endl;
    cout<<" 5) You only have "<<chances<<" attempts to guess the word"<<endl;
    cout<<"\tAll The Best!"<<endl;
    cout<<"Enter any character to continue....."<<endl;
    cout<<".......................................................................................";
    getch();
    clrscr();
}
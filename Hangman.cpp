# include <iostream>
# include <time.h> // To seed srand()
# include <conio.h>
# include <string.h>
# include <stdlib.h> // For system()
# include <ctype.h> // For toupper(), tolower()

using namespace std; // To use features of C++ standard library

// Global Variable Declarations
int NumberOfWords = 0;
const int chances = 7;
const int MaxLength = 50;
int Score = 0;
char Words[][MaxLength] = {"intelligent", // A random word will be selected from this list
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

// Function Prototypes
int Game(); // Each round starts and ends in this function
void CreateDrawWord(char[], char [], int); // Initialises DrawWord with default values
bool PrintDrawWord(char [], char[], char[], char[], int); // Updates DrawWord based on user input
bool WinCheck(char []); // Check if player has met winning conditions or not
int random(); // To generate a random number within the required range
void ConvertToLower(char []); // Converts string to lower case
void PrintAllGuesses(char [][MaxLength], int);
bool CheckInput(char[][MaxLength], int, char[]); // Checks if user has given vaild input
void clrscr();
void PrintGameRules();
void PrintHangman(int);

int main(){
    char Play = 'Y';
    PrintGameRules();
    srand(time(0)); // Seed rand() with system time
    NumberOfWords = sizeof(Words)/sizeof(Words[0]);
    while (Play == 'Y'){
        clrscr();
        cout<<"  Your current score is: "<<Score<<endl;
        Score += Game(); // Game returns score of current round
        cout<<"  Your current score is: "<<Score<<endl;
        cout<<"  Enter 'y' if you want to play the next round"<<endl<<"  ";
        cin>>Play;
        Play = toupper(Play);
    }
    cout<<"  Your final score: "<<Score;
    getch();
    return 0;
}

int Game(){
    char Word[MaxLength], DrawWord[2*MaxLength], Guess[MaxLength], Guesses[MaxLength];
    char AllGuesses[MaxLength][MaxLength];
    int LengthOfWord, c = 0, NumberOfWrongAttempts = 0;
    bool Guessed = 0, result;

    strcpy(Word, Words[random()]); // Random word selected and copied into local string
    LengthOfWord = strlen(Word);
    CreateDrawWord(Word, DrawWord, LengthOfWord); // Initialze DrawWord with defualt values
    while (!Guessed){
        cout<<"  Number of letters: "<<LengthOfWord<<endl;
        cout<<"  Number of guesses left: "<<chances - NumberOfWrongAttempts<<endl;
        PrintAllGuesses(AllGuesses, c);
        PrintHangman(NumberOfWrongAttempts);
        do{
            cout<<endl<<"  Enter your guess: ";
            cin>>Guess;
        }
        while (!CheckInput(AllGuesses, c, Guess)); // Checks if Guess is a vowel or previously entered input
        ConvertToLower(Guess); // Converts Guess into lower case
        strcpy(AllGuesses[c], Guess); // Adding current guess to list of all guesses
        Guesses[c++] = Guess[0]; // To differentiate between character or string input
        clrscr();
        result = PrintDrawWord(Word, DrawWord, Guess, Guesses, c);
        if (!result){
            cout<<"  Wrong Guess!"<<endl;
            ++NumberOfWrongAttempts;
        }
        else
            cout<<"  Correct Guess!"<<endl;
        if (WinCheck(DrawWord)){
            cout<<"  Congratulations, you have guessed the word!"<<endl;
            return 4;
        }
        else if (NumberOfWrongAttempts == chances){
            cout<<"  You are out of chances!";
            PrintHangman(NumberOfWrongAttempts);
            cout<<"  The correct word is: "<<Word<<endl;
            return -1;
        }
    }
    return -2; // Program will usually never reach this point
}

void CreateDrawWord(char Word[], char DrawWord[], int LengthOfWord){
    int i, c = 0;
    for (i = 0; i < LengthOfWord; ++i){
        switch(Word[i]){ // Puts vowels in their places
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u': DrawWord[c++] = Word[i];
                      break;
            default: DrawWord[c++] = '_';
        }
        DrawWord[c++] = ' '; // Leaving space between each letter
    }
    DrawWord[c++] = '\0';
    cout<<"  "<<DrawWord<<endl;
}

bool PrintDrawWord(char Word[], char DrawWord[], char Guess[], char Guesses[], int n){
    bool result = 0;
    int i, j;
    if (strcmp(Guess, Word) == 0){ // Guess is correct
        result = 1;
        for (i = 0; DrawWord[i] != '\0'; i += 2)
            if (DrawWord[i] == '_')
                DrawWord[i] = Word[i/2];
        cout<<"  "<<DrawWord<<endl;
        return result;
    }
    if (strlen(Guess) > 1){ //User enters an incorrect string
        cout<<"  "<<DrawWord<<endl;
        return result;
    }
    for (j = 0; Word[j] != '\0'; ++j)
        for (i = 0; i < n; ++i)
            if (Guesses[i] == Word[j])
                DrawWord[j*2] = Guesses[i]; // Placing guess in correct place
    for (j = 0; Word[j] != '\0'; ++j)
        if (Guesses[n - 1] == Word[j]) // Check if Guess matches any of the letters of Word
            result = 1;
    cout<<"  "<<DrawWord<<endl;
    return result;
}

bool WinCheck(char DrawWord[]){
    bool Win = 1;
    for (int i = 0; DrawWord[i] != '\0'; i += 2) // Checks if no letters are left to guess
        if (DrawWord[i] == '_')
            Win = 0;
    return Win;
}

int random(){
    int rnd = rand();
    rnd = rnd % NumberOfWords; // rnd is between 0 and NumberOfWords - 1
    return rnd;
}

void ConvertToLower(char Guess[]){
    for (int i = 0; Guess[i] != '\0'; ++i)
        Guess[i] = tolower(Guess[i]);
}

void PrintAllGuesses(char AllGuesses[][MaxLength], int n){
    cout<<"  Guesses till now: ";
    if (n == 0)
        cout<<"nil";
    else
        for (int i = 0; i < n; ++i)
            cout<<AllGuesses[i]<<" ";
}

bool CheckInput(char AllGuesses[][MaxLength], int n, char Guess[]){
    bool val = 1;
    if (strlen(Guess) == 1) // Check if Guess is a character
        switch(Guess[0]){ // Check if input is a vowel
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u': cout<<"  Vowels are already given!"<<endl;
                      return 0;
        }
    for (int i = 0; i < n; ++i)
        if (strcmp(AllGuesses[i], Guess) == 0){ // Check if Guess has been entered before
            val = 0;
            cout<<"  You have already entered "<<Guess<<endl;
            return val;
        }
    return val;
}

void clrscr(){
    system("cls"); // Windows cmd command to clear screen
}

void PrintGameRules(){
    cout<<"\tHangman - Word Guessing Game"<<endl;
    cout<<" 1) The vowels of a word will be given as per their respective positions in the word"<<endl;
    cout<<" 2) The positions of consonants will be marked by an underscore (_)"<<endl;
    cout<<" 3) Based on this information, you have to guess the complete word"<<endl;
    cout<<" 4) You can either enter a character to check if it is in the word,"<<endl;
    cout<<"    or you can enter the whole word to check if it is correct"<<endl;
    cout<<" 5) You can guess wrongly a maximum of "<<chances<<" times"<<endl;
    cout<<" 6) Your current score is 0. +4 if you guess the word correctly and -1 if you don't"<<endl;
    cout<<"\tAll The Best!"<<endl;
    cout<<"  Enter any character to continue....."<<endl;
    cout<<".......................................................................................";
    getch();
    clrscr();
}

void PrintHangman(int n){
    switch (n){
        case 0: cout<<"\n _______\n  |    |\n  |    \n  |   \n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
                break;
        case 1: cout<<"\n _______\n  |    |\n  |    o\n  |   \n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
                break;
        case 2: cout<<"\n _______\n  |    |\n  |    o\n  |   /\n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
                break;
        case 3: cout<<"\n _______\n  |    |\n  |    o\n  |   /|\n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
                break;
        case 4: cout<<"\n _______\n  |    |\n  |    o\n  |   /|\\\n  |    \n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
                break;
        case 5: cout<<"\n _______\n  |    |\n  |    o\n  |   /|\\\n  |    |\n  |   \n _|_\n|   |______\n|          |\n|__________|\n";
                break;
        case 6: cout<<"\n _______\n  |    |\n  |    o\n  |   /|\\\n  |    |\n  |   /\n _|_\n|   |______\n|          |\n|__________|\n";
                break;
        case 7: cout<<"\n _______\n  |    |\n  |    o\n  |   /|\\\n  |    |\n  |   / \\\n _|_\n|   |______\n|          |\n|__________|\n";
                break;
    }
    cout<<endl;
}

/*     _______
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
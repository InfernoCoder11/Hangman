# include <iostream>
# include <time.h>

using namespace std;

int main(){
    srand(time(0)); // Seed rand() with system time
    char Words[][20] = {"intelligent",
                        "unstoppable",
                        "hangman",
                        "silly",
                        "funny"};
    return 0;
}
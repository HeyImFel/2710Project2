
/*
* ************
* *********
* project2_******_gls0043_v2.cpp
* Compile code by using VSCode or on AU server

* personal info censored because of public repository


* Strategy 2 is better than Strategy 1 because, since neither Bob nor Charlie will target Aaron on their first turns
* because of his bad accuracy, it is guaranteed that one will kill the other (50/50 on who it is, depending on the
* outcome of Bob's accuracy) Aaron, instead of being punished with instantly dying to Charlie if his aim is on point
* for his first turn, will be able to potentially win with the turn where he doesn't intentionally miss. The odds sway
* in his favor because he can both shoot first in the final duel and potentially get a second shot if he's dueling Bob
* and Bob misses.
*/

# include <iostream>
# include <stdlib.h>
# include <assert.h>
# include <ctime>
#include <cassert>
using namespace std;
const int A = 3; // 1/3 chance for aaron to miss
const int B = 2; // 1/2 chance for bob to miss
const int C = 1; // 1/1 chance for charlie to miss (guaranteed)
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);

bool guaranteeSuccess = false;
int main()
{
    srand(static_cast<unsigned int>(std::time(nullptr)));
    cout << fixed;
    cout.precision(2);
    int ATruelsWon = 0;
    int BTruelsWon = 0;
    int CTruelsWon = 0;
    float case1AWins = 0;
    float case2AWins = 0;
    int totalSimulations = 10000;


    for (int i = 0; i < totalSimulations; i++) {
        bool A_alive = true;
        bool B_alive = true;
        bool C_alive = true;

        while (at_least_two_alive(A_alive, B_alive, C_alive)) { // aaron taking first shot
            if (A_alive) Aaron_shoots1(B_alive, C_alive);
            if (B_alive) Bob_shoots(A_alive, C_alive);
            if (C_alive) Charlie_shoots(A_alive, B_alive); // don't really need do-while.
        }                                                   
        /* 
         * explanation of do - while to make sure y'all know I understand it:
         * do-while is basically just a while loop but it runs the inside code segment
         * before checking the conditional
         */
        if (A_alive) ATruelsWon++;
        else if (B_alive) BTruelsWon++;
        else CTruelsWon++;
    }

    case1AWins = (float)ATruelsWon / 100; //only 100 to get the percentage as a number greater than 0, easier to work with
    cout << "Aaron won " << ATruelsWon << "/10000, totalling " << case1AWins << "% win rate\n";
    cout << "Bob won " << BTruelsWon << "/10000, totalling " << (float)BTruelsWon / (float)100 << "% win rate\n";
    cout << "Charlie won " << CTruelsWon << "/10000, totalling " << (float)CTruelsWon / (float)100 << "% win rate\n\n";
    cout << "Ready to test strategy 2 (run 10000 times)\nPress enter to continue.\n";
    cin.get();

    ATruelsWon = 0;
    BTruelsWon = 0;
    CTruelsWon = 0;

    for (int i = 0; i < totalSimulations; i++) {//aaron missing first shot
        bool A_alive = true;
        bool B_alive = true;
        bool C_alive = true;

        while (at_least_two_alive(A_alive, B_alive, C_alive)) {
            if (A_alive) Aaron_shoots2(B_alive, C_alive);
            if (B_alive) Bob_shoots(A_alive, C_alive);
            if (C_alive) Charlie_shoots(A_alive, B_alive); 
        }

        if (A_alive) ATruelsWon++;
        else if (B_alive) BTruelsWon++;
        else CTruelsWon++;
    }
    case2AWins = (float)ATruelsWon / 100; //only 100 to get the percentage as a number greater than 0, easier to work with
    cout << "Aaron won " << ATruelsWon << "/10000, totalling " << case2AWins << "% win rate\n";
    cout << "Bob won " << BTruelsWon << "/10000, totalling " << (float)BTruelsWon / (float)100 << "% win rate\n";
    cout << "Charlie won " << CTruelsWon << "/10000, totalling " << (float)CTruelsWon / (float)100 << "% win rate\n\n";


    cout << "using Strategy 1, Aaron won " << case1AWins << "% of the truels.\n";
    cout << "using Strategy 2, Aaron won " << case2AWins << "% of the truels.\n";

    if (case2AWins > case1AWins) {
        cout << "Strategy 2 is better than strategy 1.\n";
    }
    else {
        cout << "Strategy 1 is better than strategy 2.\n"; // should never occur, but i put it here just in case
    }

}
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {

    return (A_alive && B_alive) || (A_alive && C_alive) || (B_alive && C_alive);
}

void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    if (C_alive) {

        if (rand() % A == 0 || guaranteeSuccess) {  // 1/3 chance to hit
            C_alive = false;
        }
    }
    else if (B_alive) {

        if (rand() % A == 0 || guaranteeSuccess) {
            B_alive = false;
        }
    }
}

void Bob_shoots(bool& A_alive, bool& C_alive) {

    if (C_alive) {

        if (rand() % B == 0 || guaranteeSuccess) {  // 1/2 chance to hit
            C_alive = false;
        }
    }
    else if (A_alive) {

        if (rand() % B == 0 || guaranteeSuccess) {
            A_alive = false;
        }
    }
}

void Charlie_shoots(bool& A_alive, bool& B_alive) {

    if (B_alive) {

        if (rand() % C == 0 || guaranteeSuccess) {  // 1/1 chance to hit (guaranteed
            B_alive = false;
        }
    }
    else if (A_alive) {

        if (rand() % C == 0 || guaranteeSuccess) {
            A_alive = false;
        }
    }
}

void Aaron_shoots2(bool& B_alive, bool& C_alive) {
    if (B_alive && C_alive) {     // if both are alive it is Aaron's first turn so he misses on purpose.
        return;
    }
    if (C_alive) {
        if (rand() % A == 0 || guaranteeSuccess) {
            C_alive = false;
        }
    }
    else if (B_alive) {
        if (rand() % A == 0 || guaranteeSuccess) {
            B_alive = false;
        }
    }
}




////////////////////////////////////////////////////////////////
// Project Flip: Part A
// Written by James Napier, Julia Rasmussen, and Samuel Sheehan
////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "d_node.h"
#include "card.h"
#include "deck.h"

using namespace std;

/*
* Initializes the code object.
* n: integer n, representing the length of the new code object.
* m: integer m, representing the range of the new code object.
*/
deck::deck(const int& n, const int& m)
{
    LENGTH = n;
    RANGE = m;
    CODE.resize(LENGTH);
    COUNT = 0;
}

/*
* Gets the value of length from a given code object.
* No inputs.
*/
int code::getLength()
{
    return LENGTH;
}

/*
* Gets the code stored in a given code object.
* No inputs.
*/
std::vector<int> code::getCode()
{
    return CODE;
}

/*
* Initializes the random code to guess.
* No inputs.
*/
void code::initializeCode()
{
    for (int i = 0; i < LENGTH; i++)
    {
        CODE[i] = rand() % RANGE;
    }
}

/*
* Sets a specific digit in the code.
* digit: new integer value of the digit.
* index: integer index of the digit to change.
*/
void code::setCodeDigit(int digit, int index)
{
    CODE[index] = digit;
}

/*
* Returns the number of digits in the correct position.
* guess: code object to compare against the original code object.
*/
int code::checkCorrect(code& guess)
{
    int numCorrect = 0;
    for (int i = 0; i < LENGTH; i++)
    {
        if (guess.CODE[i] == CODE[i])
        {
            numCorrect++;
        }
    }
    return numCorrect;
}

/*
* Returns the number of digits in the incorrect position.
* guess: code object to compare against the original code object.
*/
int code::checkIncorrect(code& guess)
{
    int numIncorrect = 0;
    int count = LENGTH;
    vector<int> temp = CODE;
    for (int i = 0; i < count; i++)
    {
        if (guess.CODE[i] == temp[i]) {
            guess.CODE.erase(guess.CODE.begin() + i);
            temp.erase(temp.begin() + i);
            i--;
            count--;
        }
    }
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (guess.CODE[i] == temp[j])
            {
                temp[j] = RANGE + 2;
                numIncorrect++;
                break;
            }
        }
    }
    return numIncorrect;
}

/*
* Prints the stored code.
* No inputs.
*/
void code::print()
{
    for (int i = 0; i < LENGTH; i++)
    {
        cout << CODE[i];
    }
}
=
/*
* Overrides the == function for comparing two responses.
* lhs: the response on the left hand side of the == operator, the first response to compare.
* rhs: the response on the right hand side of the == operator, the second response to compare.
*/
bool operator == (const response& lhs, const response& rhs)
{
    return ((lhs.getCorrect() == rhs.getCorrect()) && (lhs.getIncorrect() == rhs.getIncorrect()));
}

/*
* Overrides the << function for a response.
* ostr: the ostream to print to.
* rhs: the response to print out.
*/
ostream& operator << (ostream& ostr, const response& rhs)
{
    ostr << rhs.getCorrect() << ", " << rhs.getIncorrect();
    return ostr;
}

/*
* Intialize mastermind object with a secret code of length 5 and range 10.
* No inputs.
*/
mastermind::mastermind() : secretCode(5, 10)
{
    secretCode.initializeCode();
    n = 5;
    m = 10;
}

/*
* Intialize mastermind object with a secret code of length nGiven and range mGiven.
* nGiven: integer length of the initialized secret code.
* nGiven: integer range of the initialized secret code.
*/
mastermind::mastermind(const int& nGiven, const int& mGiven) : secretCode(nGiven, mGiven)
{
    secretCode.initializeCode();
    n = nGiven;
    m = mGiven;
}

/*
* Print the secret code from the mastermind object.
* No inputs.
*/
void mastermind::printSecretCode()
{
    secretCode.print();
}


/*
* The main function, runs the whole code.
* No inputs.
*/
int main()
{
    int len, ran;
    cout << "================================================================================";
    cout << "\nPlease enter the length of the guess you want to play with: ";
    cin >> len;
    cout << "Please enter the upper limit of the range of numbers you want to play with: ";
    cin >> ran;
    cout << "================================================================================";
    mastermind master(len, ran);
    master.playGame();
}

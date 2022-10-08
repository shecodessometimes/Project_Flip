////////////////////////////////////////////////////////////////
// Project Flip: Part A
// Written by James Napier, Julia Rasmussen, and Samuel Sheehan
////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <tuple>
#include "d_node.h"
#include "card.h"
#include "deck.h"

using namespace std;

//=============================================================================
// Deck Methods
//=============================================================================

/*
* Initializes the deck object, in 1-13 and suit order.
*/
deck::deck()                                                    // Donish
{
    //linked list of a deck
    string suit_list[] = {"club", "diamond", "heart", "spade"};
    for (int s = 0; s < 4; s++)
    {
        for (int n = 1; n < 14; n++)
        {
            node<card> *newCard;
            //if first card
            if (s == 0 && n == 1)
            {
                card new_card(suit_list[s], n);
                newCard = new node<card> (new_card, NULL);
                front = newCard;
                back = newCard;
            }
            else
            {
                node<card> *curr;
                curr = front;
                while (curr->next != NULL)
                {
                    curr = curr->next;
                }
                card new_card(suit_list[s], n);
                newCard = new node<card> (new_card, NULL);
                curr->next = newCard;
                back = newCard;
            }
        }
    }
}


/*
* Shuffle the deck represented by the deck object.
*/
void deck::shuffle()
{
    node<card> *curr1;
    node<card> *prev1;
    node<card> *curr2;
    node<card> *prev2;
    curr1 = front;
    for (int ind = 0; ind < 50; ind++)
    {
        srand (time(NULL));
        int off = 51 - ind;
        int swap_ind = rand() % off + ind;
        //cout << "Swap Index: " << swap_ind << endl;
        if (ind != swap_ind)
        {
            if (ind != 0)
            {
                prev1 = curr1;
                curr1 = curr1->next;
                curr2 = curr1;
                card temp3 = prev1->nodeValue;
                card temp4 = curr1->nodeValue;
                /*
                cout << "Previous Baseline: " << temp3.getSuit() << "," << temp3.getValue() << endl;
                cout << "Current Baseline: " << temp4.getSuit() << "," << temp4.getValue() << endl;
                cout << "Now: " << ind << ",Then: " << swap_ind << endl;
                */
            }
            else
            {
                curr2 = curr1;
            }
            if (swap_ind != ind)
            {
                for (int ind2 = ind; ind2 < swap_ind; ind2++)
                {
                    prev2 = curr2;
                    curr2 = curr2->next;
                    card temp3 = prev2->nodeValue;
                    card temp4 = curr2->nodeValue;
                    /*
                    cout << "Previous: " << temp3.getSuit() << "," << temp3.getValue() << endl;
                    cout << "Current: " << temp4.getSuit() << "," << temp4.getValue() << endl;
                    */
                }

                node<card> *temp;
                if (ind == 0)
                {
                    front = curr2;
                    prev2->next = curr1;
                    temp = curr1->next;
                    curr1->next = curr2->next;
                    curr2->next = temp;
                    curr1 = curr2;
                    //cout << "==========================\n";
                    //this->printDeck();
                }
                else
                {
                    prev1->next = curr2;
                    prev2->next = curr1;
                    temp = curr1->next;
                    curr1->next = curr2->next;
                    curr2->next = temp;
                    curr1 = curr2;
                    //this->printDeck();
                    //cout << "==========================\n";
                }
            }          
        }
    }
}

void deck::printDeck()
{
    node<card> *curr;
    curr = front;
    while (curr != NULL)
    {
        cout << curr->nodeValue << endl;
        curr = curr->next;
    }
    
}

//=============================================================================
// Card Methods
//=============================================================================

/*
* Initializes the card object.
* v: integer v, the numerical value of the card (1 is ace, 11 is jack, 12 is queen, 13 is king).
* s: integer s, the suit of the card (0 = hearts, 1 = suits, etc.)
*/
card::card(const string& s, const int& v)                       // Done
{
    value = v;
    suit = s;
}

/*
* Overrides the << function for a card.
* ostr: the ostream to print to.
* rhs: the response to print out.
*/
ostream& operator << (ostream& ostr, const card& rhs)           // Doneish
{
    ostr << rhs.getValue() << ", " << rhs.getSuit();
    return ostr;
}


void card::setValue(const int& v)                               // Doneish
{
    bool valid = false;
    while(!valid)
    {
        if (v > 0 && v < 13)
        {
            valid == true;
        }
        else
        {
            cout << "\nInvalid value, please try again";
        }
    }
    value = v;
}


int card::getValue() const                                           // Doneish
{
    return value;
}


void card::setSuit(const string& s)                             // Doneish
{
    bool valid = false;
    cout <<"\nPlease enter a suit (lowercase):";
    while(!valid)
    {
        valid = true;
        if (s == "club" || s == "diamond" || s == "heart" || s == "spade")
        {
            suit = s;
        }
        else
        {
            valid = false;
            cout << "\nInvalid suit, please try again.";
        }
    }
}


string card::getSuit() const
{
    return suit;
}

//=============================================================================
// 
//=============================================================================

/*
* Gets the code stored in a given code object.
* No inputs.
*/
/*
std::vector<int> code::getCode()
{
    return CODE;
}
*/
/*
* Initializes the random code to guess.
* No inputs.
*/
/*
void code::initializeCode()
{
    for (int i = 0; i < LENGTH; i++)
    {
        CODE[i] = rand() % RANGE;
    }
}
*/
/*
* Sets a specific digit in the code.
* digit: new integer value of the digit.
* index: integer index of the digit to change.
*/
/*
void code::setCodeDigit(int digit, int index)
{
    CODE[index] = digit;
}

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
*/
/*
* Prints the stored code.
* No inputs.
*/
/*
void code::print()
{
    for (int i = 0; i < LENGTH; i++)
    {
        cout << CODE[i];
    }
}
*/
/*
* Overrides the == function for comparing two responses.
* lhs: the response on the left hand side of the == operator, the first response to compare.
* rhs: the response on the right hand side of the == operator, the second response to compare.
*/
/*
bool operator == (const response& lhs, const response& rhs)
{
    return ((lhs.getCorrect() == rhs.getCorrect()) && (lhs.getIncorrect() == rhs.getIncorrect()));
}
*/
/*
* Intialize mastermind object with a secret code of length 5 and range 10.
* No inputs.
*/
/*
mastermind::mastermind() : secretCode(5, 10)
{
    secretCode.initializeCode();
    n = 5;
    m = 10;
}
*/
/*
* Intialize mastermind object with a secret code of length nGiven and range mGiven.
* nGiven: integer length of the initialized secret code.
* nGiven: integer range of the initialized secret code.
*/
/*
mastermind::mastermind(const int& nGiven, const int& mGiven) : secretCode(nGiven, mGiven)
{
    secretCode.initializeCode();
    n = nGiven;
    m = mGiven;
}
*/
/*
* Print the secret code from the mastermind object.
* No inputs.
*/
/*
void mastermind::printSecretCode()
{
    secretCode.print();
}
*/

/*
* The main function, runs the whole code.
* No inputs.
*/

int main()
{
    deck testDeck;
    testDeck.printDeck();
    testDeck.shuffle();
    cout << "==========================\n";
    testDeck.printDeck();
}
